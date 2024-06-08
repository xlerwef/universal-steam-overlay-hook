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
#include "map"
#include "dllmain.h"
PLH::Detour* present_hook;
PLH::Detour* entity_hook;

float Matrix[16] = { 0 };

Matrix1* pViewMatrix;
Matrix1 v;

Matrix4* mat;
void init_hooks() {
	auto baseAddress = (DWORD64)GetModuleHandleA("Fallout4.exe");
	DWORD64 vm = (DWORD64)baseAddress+0x2D260A0;
	auto ptr = (DWORD64*)vm;
	//pViewMatrix = reinterpret_cast<Matrix1*>(ptr);
	pViewMatrix = (Matrix1*)ptr;
	//mat = reinterpret_cast<Matrix4*>(ptr);
	auto pCreate_hk = ModuleSignature("gameoverlayrenderer64.dll", steam_create_hook_pattern).find();
	auto pPresent_hk = ModuleSignature("gameoverlayrenderer64.dll", steam_present_hook_pattern).find();
	auto pEntity_move_hk = ModuleSignature("Fallout4.exe", entity_move_hook_pattern).find();
	PLH::Detour* present_hook = new PLH::x64Detour((uint64_t)pPresent_hk, (uint64_t)&hookPresent, (uint64_t*)&fn_originalPresent);
	present_hook->hook();
	if (!present_hook->isHooked()) {
		spdlog::error("Unable to hook DXGIPresent.");
		exit(1);
	}
	spdlog::info("Hooked DXGIPresent");

	PLH::Detour* entity_hook = new PLH::x64Detour((uint64_t)pEntity_move_hk, (uint64_t)&hookEntity, (uint64_t*)&fn_entityHook);
	entity_hook->hook();
	if (!entity_hook->isHooked()) {
		spdlog::error("Unable to hook entities.");
		exit(1);
	}
	spdlog::info("Hooked EntityMove Function.");
}
void safe_unhook() {
	if (entity_hook && entity_hook->isHooked()) {
		entity_hook->unHook();
		spdlog::info("Unhooked entity_hook");
	}
	if (present_hook && present_hook->isHooked()) {
		entity_hook->unHook();
		spdlog::info("Unhooked present_hook");
	}
}
HMODULE hMod = 0;
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	hMod = hModule;
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, LPTHREAD_START_ROUTINE(init_hooks), NULL, NULL, NULL);
		break;
	case DLL_PROCESS_DETACH:
		safe_unhook();
		FreeLibraryAndExitThread(hMod, 0);
	}
	return TRUE;
}