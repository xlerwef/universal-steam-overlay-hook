#include "stdio.h"
#include "iostream"
#include "drawing.h"
#include "hooks.h"
#include "dllmain.h"
#include "polyhook2/Detour/ADetour.hpp"
#include "directx.h"
#include "gamestructs.h"

bool bMenu = true;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
std::map<int64_t*, Actor*> map = std::map<int64_t*, Actor*>();
EntityMoveFn fn_entityHook;

HRESULT __stdcall hookEntity(int64_t* p1, int32_t* p2) {
	map.emplace(p1, (Actor*)p1);
	return fn_entityHook(p1, p2);
}
bool doW2S;
HRESULT __stdcall hookPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags)
{
	if (!initialized) {
		initialized = initialize_imgui(pThis);
		spdlog::info("Initialized ImGui and D3D11.");
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		bMenu = !bMenu;
	};
	if (GetAsyncKeyState(VK_END) & 1) {
		DllMain(NULL, DLL_PROCESS_DETACH, NULL);
	}
	if (GetAsyncKeyState(VK_F7) & 1) {
		doW2S = !doW2S;
	}
	begin_draw();

	if(bMenu)
		ImGui::ShowDemoWindow();
	for (auto& ent : map) {
		Vector2 screenPos;
		WorldToScreenCustom(ent.second->vPosition, screenPos, *pViewMatrix, 3440,1440);
		//ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(screenPos.x, screenPos.y), ImVec2(screenPos.x + 20, screenPos.y + 30), IM_COL32(.5f,.5f,1.f,1.f));
	}
	
	end_draw();

	return fn_originalPresent(pThis, SyncInterval, Flags);
}

LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (!bMenu) {
		CallWindowProcW(fn_originalWndProc, hWnd,uMsg,wParam,lParam);
	}

	POINT MousePos;
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam) == 0) {
		GetCursorPos(&MousePos);
		ScreenToClient(hWnd, &MousePos);
		ImGui::GetIO().MousePos.x = (MousePos.x);
		ImGui::GetIO().MousePos.y = (MousePos.y);
	};

	return CallWindowProcW(fn_originalWndProc, hWnd, uMsg, wParam, lParam);
}