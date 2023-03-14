#include "stdafx.h"

bool bHACKMEfixes;
bool bDevMode=1;

void Init()
{
	std::string TakeoverMD = "Quickstart template HDBeefup | Compiled at " __DATE__ ", " __TIME__ " |";
	
    CIniReader iniReader("quickhdb.ini");
    int ResX = iniReader.ReadInteger("MAIN", "ResX", 0);
    int ResY = iniReader.ReadInteger("MAIN", "ResY", 0);
    bHACKMEfixes = iniReader.ReadInteger("Patchworks", "HACKMEfixes", 1);
	
	     if (!ResX || !ResY)
         std::tie(ResX, ResY) = GetDesktopRes();
	 
	 // before writing your code, do test compile to make sure it's all good and working =)
	 
}


BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		Init();
	}
	return TRUE;
}