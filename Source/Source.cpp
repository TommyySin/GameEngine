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
		// if you get here you don’t have enough disk space!
		//GCC_ERROR(“CheckStorage Failure : Not enough physical storage.”);
		cout << "CheckStorge Failure : Not enough physical storage." << "\n";
		return false;
	}
	cout << "Enough" << "\n";
	return true;
}

int main()
{
	IsOnlyInstance();
	CheckStorage(3e+8);
	system("pause");
	return 0;
}