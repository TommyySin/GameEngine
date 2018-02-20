#include "Lupa.h"

Lupa::GameState Lupa::_gameState;
sf::RenderWindow* Lupa::_mainWindow;
GameObject* Lupa::_gameObject;

bool IsOnlyInstance() 
{
	HANDLE handle = CreateMutex(NULL, TRUE, "The Game");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
		return false;
	return true;
}

bool CheckStorage(const DWORDLONG diskSpaceNeeded)
{  // Check for enough free disk space on the current disk. 
	int const drive = _getdrive();
	struct _diskfree_t diskfree;
	_getdiskfree(drive, &diskfree);
	unsigned __int64 const neededClusters = diskSpaceNeeded /
		(diskfree.sectors_per_cluster*diskfree.bytes_per_sector);
	if (diskfree.avail_clusters < neededClusters)
	{  // if you get here you don’t have enough disk space! 
		cout << "CheckStorage Failure : Not enough physical storage." << endl;
		return false;
	}

	cout << "You have enough storage amount!" << endl;
	return true;
}

void CheckMemory()
{
	MEMORYSTATUSEX status;
	status.dwLength = sizeof(status);
	GlobalMemoryStatusEx(&status);
	DWORDLONG physInGB = status.ullAvailPhys / 1073741824;
	DWORDLONG virtInGB = status.ullAvailVirtual / 1073741824;
	//cout << "Your Available Physical Memory: " << physInGB << "GB." << endl;
	//cout << "Your Available Virtual Memory: " << virtInGB << "GB." << endl;
	if (physInGB > 1)
	{
		cout << "You have enough memory" << endl;
	}
}

void ReadCPU(string whatToRead)
{
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden:
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0, KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS)
	{
		if (whatToRead == "speed")
		{
			RegQueryValueEx(hKey, " ̃ MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
			dwMHz /= 1048576;
		}
		else
		{
			RegQueryValueEx(hKey, "Platform Specific Field 1", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
		}
	}
	if (dwMHz > 512)
	{
		cout << "This pc can run this game." << endl;
	}
	else
	{
		exit(1);
	}
}


void Lupa::Start(void)
{
	if (_gameState != Uninitialized) return;
	_mainWindow->create(sf::VideoMode(1024, 768, 32), "Don't hit me");
	_gameState = Lupa::ShowingSplash;
	SplashScreen::Show(*_mainWindow);

	while (!IsExiting())
	{
		GameLoop();
	}
	_mainWindow->close();
}

bool Lupa::IsExiting(void)
{
	return false;
}

void Lupa::Initialize(void)
{
	CheckStorage(2.4e+7);
	CheckMemory();
	ReadCPU("speed");
	_mainWindow = new sf::RenderWindow();
	SceneGraph();
	//SceneGraph* scene = new SceneGraph();
}

void Lupa::GameLoop(void)
{

}
