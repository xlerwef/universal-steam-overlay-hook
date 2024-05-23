#include "stdio.h"
#include "iostream"
#include "drawing.h"
#include "hooks.h"

bool bMenu = true;
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HRESULT __stdcall hookPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags)
{
	if (!initialized) {
		initialized = initialize_imgui(pThis);
		spdlog::info("Initialized ImGui and D3D11.");
	}
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		bMenu = !bMenu;
	};
	begin_draw();

	if(bMenu)
		ImGui::ShowDemoWindow();
	
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