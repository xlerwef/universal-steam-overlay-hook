#include "pch.h"
#include <windows.h>
#include <d3d11.h>
#include "directx.h"
#include "signatures.h"
#include "polyhook2/IHook.hpp"
#include "polyhook2/Detour/x64Detour.hpp"
#include "polyhook2/Detour/ADetour.hpp"
#include "polyhook2/Virtuals/VTableSwapHook.hpp"
#include "hooks.h"


void init_hooks() {
	auto pCreate_hk = ModuleSignature("gameoverlayrenderer64.dll", steam_create_hook_pattern).find();
	auto pPresent_hk = ModuleSignature("gameoverlayrenderer64.dll", steam_present_hook_pattern).find();

	PLH::Detour* presentHook = new PLH::x64Detour((uint64_t)pPresent_hk, (uint64_t)&hookPresent, (uint64_t*)&fn_originalPresent);
	presentHook->hook();
	if (!presentHook->isHooked()) {
		spdlog::error("Unable to hook DXGIPresent.");
		exit(1);
	}
	spdlog::info("Hooked DXGIPresent");
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(init_hooks), NULL, NULL, NULL);
		break;
	}
	return TRUE;
}