#include <windows.h>
#include <stdio.h>
#include <direct.h>
#include <stdlib.h>
#include <ctype.h>
#include <iostream>

using namespace std;

bool IsOnlyInstance(LPCTSTR gameTitle) {
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
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
	return true;
}

int main() 
{
	IsOnlyInstance ? cout << "true" << "\n ": cout << "false" ;
	system("pause");
	return 0;
}