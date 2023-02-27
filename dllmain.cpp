#include <Windows.h>
#include <iostream>
#include "csgosdk.h"
#include "netvar.h"

DWORD WINAPI HackThread(HMODULE hModule)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);

	auto ClientEntityList = GetInterface<IClientEntityList>("client.dll", "VClientEntityList003");
	auto BaseClientDll = GetInterface<IBaseClientDLL>("client.dll", "VClient018");
	
	while (!GetAsyncKeyState(VK_END))
	{
		ClientClass* clientclass = BaseClientDll->GetAllClasses();

		uintptr_t healthoOffset = GetNetVarOffset("DT_BasePlayer", "m_iHealth", clientclass);
		std::cout << std::hex << healthoOffset << std::endl;

		//for (int i = 1; i < 16; i++)
		//{
		//	auto ent = ClientEntityList->GetClientEntity(i);
		//		
		//	if (!ent)
		//		continue;

		//	std::cout << "Player" << i << ": " << ent->GetHealth() << std::endl;
		//}


		Sleep(200);
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD reason, LPVOID reserve)
{
	DisableThreadLibraryCalls(hModule);
	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(HackThread), hModule, 0, 0);

	return true;
}