//Server
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <fstream>
SOCKET Connections[10000000];
int ConnectionCounter = 0;

int sendmessage(int client, std::string str) {
	//std::cout << str;//DEBUG
	int CCheck = send(Connections[client], str.c_str(), str.size(), NULL);
	if (CCheck == SOCKET_ERROR) {
		closesocket(Connections[client]);
		std::cout << "Failed: Client disconnected: " << client << std::endl;
		return 1;
	}
	return 0;
}

void ReciveMessages(){
	int Disconnected;
	Disconnected = 0;
	std::cout << "RMS";
	//while (true) {
	//	char buff[256];
	//	int Connected;
	//	Connected = ConnectionCounter - Disconnected;
	//	for (int i = 0; i < Connected; i++) {
	//		int CCHECK = recv(Connections[i], buff, sizeof(buff), NULL);
	//		if (CCHECK == SOCKET_ERROR) {
	//			Disconnected++;
	//			closesocket(Connections[i]);
	//			std::cout << "Disconnected";
	//		}else {
	//			if (buff == "Alive") {
	//			}
	//			else {
	//				std::cout << buff << std::endl;
	//				//std::cout << "RM"; //DEBUG
	//			}
	//		}
	//	}
	//	Sleep(10000);
	//}
}

int DataComunications(int index) {
	char buffer1[256];
	std::string buffer;
	recv(Connections[index], buffer1, sizeof(buffer), NULL);
	buffer = buffer1;
	//std::cout << "receved" << buffer.c_str(); DEBUG
	if (buffer == "NULL") {
		std::cout << "New Client Connected!" << std::endl;
		std::string str;
		std::string t;
		str =("ID:");
		for (int i = 0; i < 10; i++) {
			int num = rand() % 26;
			char upper = static_cast<char>('A' + num);
			t = upper;
			str.append(t);
		}
		//std::cout << str.c_str() << std::endl;
		sendmessage(index, str.c_str());
	}
	else {
		std::cout << "Client " << buffer.c_str() << " has connected" << std::endl;
	}
	return 0;
}

std::string getFileContents(std::ifstream& File)
{
	std::string Lines = ""; 
	if (File) 
	{
		while (File.good())
		{
			std::string TempLine;     
			std::getline(File, TempLine);    
			TempLine += "\n";                   
			Lines += TempLine;                 
		}
		return Lines;
	}
	else               
	{
		return "ERROR File does not exist.";
	}
}

void Commands() {
	while (true) {
		std::string buffer1;
		char buffer2[512];
		std::cin.getline(buffer2, sizeof(buffer2));
		buffer1 = buffer2;
		system("CLS");

		std::ifstream Reader("art.txt");             
		std::string Art = getFileContents(Reader);       
		std::cout << Art << std::endl;              
		Reader.close(); 
		
		if (buffer1 == "help") {
			std::cout << "To get a list of commands do helpc" << std::endl << "Commands work like this: ClientName:Command" << std::endl;
		}
		
		if (buffer1 == "helpc") {
			std::cout << "To get a list of commands do helpc" << std::endl << "Commands work like this: ClientName:Command Or Global:Command" << std::endl;
		}
		
		if (buffer1 == "list") {
			std::cout << "Total Pings: " << ConnectionCounter << std::endl; 
			for (int i = 0; i < ConnectionCounter; i++) {
				char buffer[256];
				if (sendmessage(i, "Global R") == 1){//FIX ALL THE CLOSESOCKET ISSUES
				}
				else {
					recv(Connections[i], buffer, sizeof(buffer), NULL);
					std::cout << std::endl<< buffer << std::endl;
					if (i = ConnectionCounter) {
						i = 0;
						break;
					}
				}
			}
			
		}
		
		if (buffer1 != "help" && buffer1 != "list" && buffer1 != "helpc") {
			for (int i = 0; i < ConnectionCounter; i++) {
				sendmessage(i, buffer1.c_str());
				buffer1.empty();
			}
		}
		Sleep(10);
	}
}

int main() {



	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0) {
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(1);
	}

	SOCKADDR_IN addr;
	int addrlen = sizeof(addr);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);

	std::ifstream Reader("art.txt");
	std::string Art = getFileContents(Reader);
	std::cout << Art << std::endl;
	Reader.close();

	SOCKET newConnection;
	//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ReciveMessages, NULL, NULL, NULL);
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Commands, NULL, NULL, NULL);
	for (int c = 0; c < 10000000; c++){
		newConnection = accept(sListen, (SOCKADDR*)&addr, &addrlen);
		if (newConnection == 0) {
			std::cout << "Pinnged" << std::endl;
		}else {
			//std::cout << "cp1" << std::endl; DEGUB
			CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)DataComunications, (LPVOID)(c), NULL,NULL);
			Connections[c] = newConnection;
			ConnectionCounter++;
		}
	}
	system("pause");
}