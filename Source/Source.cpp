#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream> 
#include <tchar.h>
#include <intrin.h>


using namespace std;

bool IsOnlyInstance() {
	/*HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS) {
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd) {
			// An instance of your game is already running.
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			return false;
		}
	}
	return true;*/
	CreateMutex(0, FALSE, "COOL GAME");
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		cout << "It has been running" << "\n";
		return false;
	}
	cout << "This is the only window opening." << "\n";
	return true;
}

bool CheckStorage(const DWORDLONG diskSpaceNeeded) {
	// Check for enough free disk space on the current disk.
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = diskSpaceNeeded /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters) {
		// if you get here you don have enough disk space!
		//GCC_ERROR(heckStorage Failure : Not enough physical storage.?;
		cout << "CheckStorge Failure : Not enough physical storage." << "\n";
		return false;
	}
	cout << "You have enough physical storage." << "\n";
	return true;
}

DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)
			&dwMHz, &BufSize);
	}
	
	return dwMHz;
}

void CheckMemory() {
	MEMORYSTATUSEX statex;
	statex.dwLength = sizeof(statex);
	GlobalMemoryStatusEx(&statex);
	
	cout << "There are " << statex.ullTotalPhys/(1024*1024) << " total MB of physical memory" << "\n" ;
	cout << "There are " << statex.ullAvailPhys / (1024 * 1024) << " free MB of physical memory" << "\n";

	cout << "There are " << statex.ullTotalVirtual/(1024*1024) << " total MB of virtual memory" << "\n";
	cout << "There are " << statex.ullAvailVirtual / (1024*1024) << " free MB of virtual memory" << "\n";
}


void GetProcessorName()
{
	int CPUInfo[4] = { -1 };
	char CPUBrandString[0x40];
	__cpuid(CPUInfo, 0x80000000);
	unsigned int nExIds = CPUInfo[0];
	
	memset(CPUBrandString, 0, sizeof(CPUBrandString));

	// Get the information associated with each extended ID.
	for (int i = 0x80000000; i <= nExIds; ++i)
	{
		__cpuid(CPUInfo, i);
		// Interpret CPU brand string.
		if (i == 0x80000002)
			memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000003)
			memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
		else if (i == 0x80000004)
			memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
	}
	cout << "The CPU in this computer is: " << CPUBrandString << "\n";
}

int main()
{
	IsOnlyInstance();
	CheckStorage(3e+8);
	CheckMemory();
	cout << "Your CPU Speed is "<<ReadCPUSpeed()<< "MHz" <<  "\n";
	GetProcessorName();
	system("pause");
	return 0;
}