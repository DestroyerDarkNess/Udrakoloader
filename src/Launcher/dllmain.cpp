#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <TlHelp32.h>
#include <stdlib.h>
#include <string>
#include <vector>

#include "Injection.h"

using namespace std;



//---------------------------------------------------------------------------------------------

string wchar_t2string(const wchar_t *wchar)
{
	string str = "";
	int index = 0;
	while (wchar[index] != 0)
	{
		str += (char)wchar[index];
		++index;
	}
	return str;
}

wchar_t *string2wchar_t(const string &str)
{
	wchar_t wchar[260];
	int index = 0;
	while (index < str.size())
	{
		wchar[index] = (wchar_t)str[index];
		++index;
	}
	wchar[index] = 0;
	return wchar;
}

void listFilesInDirectory(char *szFilter, vector<string>& thevector)
{
	WIN32_FIND_DATAA FindFileData;
	thevector.clear();
	HANDLE hFind = FindFirstFileA(szFilter, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do
	{
		if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			thevector.push_back(std::string(FindFileData.cFileName));
		}
	} while (FindNextFileA(hFind, &FindFileData) != 0);

	FindClose(hFind);
}

wchar_t *convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

// near the top of your CPP file
EXTERN_C IMAGE_DOS_HEADER __ImageBase;


char szProcessName[MAX_PATH];

void Run()
{

	//for (int i = 1; i <= 1000000000; i++){
	
	//}

	//MessageBox(NULL, L"Run", L"Loading...", MB_ICONEXCLAMATION | MB_OK);

	DWORD Pid = GetCurrentProcessId();   //GetCurrentProcessId(); //GetProcessIdByName("gta_sa.exe"); ' Bug
	
	//std::wstring wstr = std::to_wstring(Pid);
	
	//MessageBox(NULL, wstr.c_str(), L"Process Pid", MB_ICONEXCLAMATION | MB_OK);
	
	TCHAR path[MAX_PATH + 1] = L"";
	DWORD len = GetCurrentDirectory(MAX_PATH, path);

	wstring test(&path[0]); //convert to wstring
	string test2(test.begin(), test.end()); //and convert to string.

	std::string startPath = test2 + std::string("\\Udrakoloader\\*.dll");

	std::wstring wistr = std::wstring(startPath.begin(), startPath.end());

	
//	MessageBox(NULL, wistr.c_str(), L"Archivo : ", MB_ICONEXCLAMATION | MB_OK);

	// Bootstrapper
	char DllName[MAX_PATH];
	GetCurrentDirectoryA(MAX_PATH, DllName);
	strcat_s(DllName, "\\Udrakoloader\\lib\\Bootstrapper.dll"); //\\Udrakoloader\\lib
	
	char* chr = const_cast<char*>(startPath.c_str());

	//MessageBox(NULL, startPath.c_str(), L"Archivo : ", MB_ICONEXCLAMATION | MB_OK);

	vector<string> listFiles;

	listFilesInDirectory(chr, listFiles); //"\\Udrakoloader\\*.dll"

	for each (string str in listFiles)
	{

	std:string dllrute = "\\Udrakoloader\\" + str;


		std::wstring widestr = std::wstring(dllrute.begin(), dllrute.end());


		//LPWSTR strConverted = convertCharArrayToLPCWSTR(cstr);

		// Test para ver si se recorren los archivos.
		//MessageBox(NULL, widestr.c_str(), L"Archivo : ", MB_ICONEXCLAMATION | MB_OK);


		wchar_t DllNameW[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, DllNameW);
		wcscat_s(DllNameW, widestr.c_str());


		InjectAndRunThenUnload(Pid, DllName, "LoadManagedProject", DllNameW);


	}

}


//---------------------------------------------------------------------------------------------

int main()
{
	//Run();
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Run, 0, 0, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
	switch (fdwReason) {
	case DLL_PROCESS_ATTACH: // some code to initialize your plugin (will be executed at game start)
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&Run, 0, 0, 0);
		//Run();
		break;
	case DLL_PROCESS_DETACH: // some code to deinitialize your plugin (will be executed at game closing)
		break;
	}
	return TRUE;
}


