#ifdef OS_WINDOWS
#include <windows.h>
#include <stdio.h>
#include "../MainLaunch.h"

void ParseCommandLine(char** * args, int CmdLines)
{

}

int WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
#ifdef ENABLE_CONSOLE
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
#endif

	HANDLE launchMutex = CreateMutexA(NULL, FALSE, "SizzleEngine");

	
	if (!launchMutex)
	{
		MessageBoxA(NULL, "Could not start the Engine", "Error!", MB_OK);
		return -1;
	}

	if (ERROR_ALREADY_EXISTS == GetLastError())
	{
		MessageBoxA(NULL, "An instance is already running!", "Error!", MB_OK);
		return -1;
	}


	//Launch
	int ret = MainLaunch(0, NULL);
	FreeConsole();
	CloseHandle(launchMutex);
	return ret;
}
#endif