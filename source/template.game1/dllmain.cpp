#include "stdafx.h"

char textStuff;
float CamMaxZoomIn;
int SWINEEdi;
bool bEnableExperimentResPW, bEnableCheats, bDevMode, bHACKMEfixes;

void Init()
{
    CIniReader iniReader("quickhdb.ini");  /// HDB Settings
    int ResX = iniReader.ReadInteger("MAIN", "ResX", 0);
    int ResY = iniReader.ReadInteger("MAIN", "ResY", 0);
    bHACKMEfixes = iniReader.ReadInteger("Patchworks", "HACKMEfixes", 1);

    if (!ResX || !ResY)
        std::tie(ResX, ResY) = GetDesktopRes();

	auto BaseAddressptr = (uintptr_t)GetModuleHandle(NULL); // if you get relocation table in x64dbg.. tldr addresses change on every launch
	OutputDebugStringA("Hello HDBEEFUP!"); // optional but can be useful

	bEnableExperimentResPW = iniReader.ReadInteger("Patchworks", "EnableExperimentResPW", 0);
	bEnableCheats = iniReader.ReadInteger("Patchworks", "EnableCheats", 0);

	// Mods -- how to read int from config
	int ColorMM = iniReader.ReadInteger("Mods", "ColorMainMenu", 0xF0F0F0); // if you want to change color and its a hex color
	injector::WriteMemory<int>(BaseAddressptr+0xEA74F, ColorMM, true); // COLOR

	std::string textSwap = iniReader.ReadString("Mods", "MultiplayerMaster", "nat.example.com"); // Multiplayer hub
    injector::WriteMemory<DWORD>(BaseAddressptr+0x73F52, (DWORD)((char*)strdup(textSwap.c_str())), true); // master.gamespy.com

	// Camera -- common float example
	CamMaxZoomIn = iniReader.ReadFloat("Camera", "MaxZoomIn", 10.0f);
	
	std::string TakeoverMD = "Brand Thief Attenion Definitive %s Edition | Compiled at " __DATE__ ", " __TIME__ " |";
	injector::WriteMemory<DWORD>(BaseAddressptr + 0x6DB46, (DWORD)((char*)strdup(TakeoverMD.c_str())), true); // @ 6CF46 Relative Virtual Address... fancyyy
	injector::WriteMemory<DWORD>(0x43A85E, (DWORD)((char*)strdup(TakeoverMD.c_str())), true); // static address you can use in cheat engine too
	
	//injector::WriteMemory<unsigned char>(0x43a82d, 11, true); // SWINE Edition (byte) / no CD

    injector::WriteMemory<float>(0x05B1349, (float)ResX / (float)ResY, true); // aspect fix (when fullscreen borderless or something, and there is like streched out 3d view, inaccuracies with where unit/tank/whatever goes, clicking on things...)
	injector::WriteMemory<DWORD>(0x416921, (DWORD)((char*)"Auto"), true); //simple and short and cute to replace origin resoliution in settings
   
   // After ending mission, doesn't go to 800x600 (e.g. tutorial and the rest) MUST HAVE
	injector::WriteMemory(0x4330f6, ResX, true); // 800
	injector::WriteMemory(0x4330f1, ResY, true); // 600
	
	// sometimes resoliution is a float too... idk about doubles yet

  /* INI Writer if game uses .INI for layout */
CIniReader iniWriter("..\Pannels\\menuprincipal.ini");
iniWriter.WriteInteger("MENUPRINCIPAL", "WIDTH", ResX );
iniWriter.WriteInteger("MENUPRINCIPAL", "HEIGHT", ResY);
iniWriter.WriteInteger("MAINMENU_LOGOMICROROOT", "X", ResX - 610);
iniWriter.SetIniPath("Pannels\\menucredits.ini");
iniWriter.WriteInteger("MENUCREDITS", "WIDTH", ResX);  

 /* ====== Mods ====== */
  injector::WriteMemory<unsigned char>(BaseAddressptr+0xDF7AB, 0x85, true); // Enable Cheats 0x9bf7ab (hex compare swined and swinehd.exe) || DF7AB direct, less direct 0xDF7DB

  injector::WriteMemory<DWORD>(0x496add, (DWORD)((char*)"gamedata/units.ini"), true);
  injector::WriteMemory<float>(0x4CB3D5, CamMaxZoomIn, true); // Map Cameralimit DEF: 48 || hd remaster does not have it
	 
  injector::WriteMemory<float>(BaseAddressptr+0xCDD71, CamMaxZoomIn, true); // Max zoom in DEF: 11

	  if (bEnableExperimentResPW) {
		  /* if true, aka is 1, i will run commands between these two --> { <-things- >} <-- */
  } else { //in case of fallback or alternative idk.. i'm not the coder here, you are
  }
}


/* INIT THE HOOK, SHOULD THIS ASI RUN?*/

BOOL APIENTRY DllMain(HMODULE /*hModule*/, DWORD reason, LPVOID /*lpReserved*/)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        Init(); //aka JUST RUN, NO QUESTIONS ASKED
    }
    return TRUE;
}

/* ============ OR ============ */

/*
BOOL APIENTRY DllMai................. and all that.. comments don't want to comment all this.. so remove this line. KEEP THAT ^ NO QUESTIONS ASKED BOOL APIENTRY DllMain(HMODULE.....
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        if (bDevMode >=1) { // when developing but still want map editor or other programs in same directory without need to bundle asi into exe... bc then entry point is different and thus crashes and issues
            uintptr_t base = (uintptr_t)GetModuleHandleA(NULL);
            IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
            IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

            if ((base + nt->OptionalHeader.AddressOfEntryPoint + (0x400000 - base)) == 0x067399D) // the first breakpoint x64dbg sees when it reached to yourgame.exe. | Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
                Init();

            else
            {
                MessageBoxA(NULL, "Happy map editing, developer!", "template HDBEEFUP", MB_OK); // or something about "hey you use incompatible version"
                return FALSE;
            }
        } else { Init(); return TRUE;
         }
    }
    return TRUE;
}

*/