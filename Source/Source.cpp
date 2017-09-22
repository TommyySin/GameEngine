#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream> 


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
	cout << "This is the only one." << "\n";
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
	cout << "Enough" << "\n";
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

bool CheckMemory() {
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	
	cout << status.ullTotalPhys << "\n" ;
	cout << status.ullAvailVirtual << "\n";

	/*if (status.ullTotalPhys) 
	{
		 you don’t have enough physical memory. Tell the
		player to go get a real computer and give this one to
		his mother. 
		GCC_ERROR(“CheckMemory Failure : Not enough physical
			memory.”); 
		return false;
	}*/
	// Check for enough free memory.
	/*if (status.ullAvailVirtual) {
		// you don’t have enough virtual memory available.
		// Tell the player to shut down the copy of Visual
		//Studio running in the background.
			GCC_ERROR(“CheckMemory Failure : Not enough virtual
				memory.”);
		return false;
	}*/
	return true;
}

int main()
{
	IsOnlyInstance();
	CheckStorage(3e+8);
	CheckMemory();
	cout << ReadCPUSpeed()<< "\n";
	system("pause");
	return 0;
}