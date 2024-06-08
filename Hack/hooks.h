#pragma once
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"
#include "stdio.h"
#include "iostream"
#include "drawing.h"
#include "spdlog/spdlog.h"
#include "polyhook2/Detour/ADetour.hpp"
#include "gamestructs.h"

extern PLH::Detour* present_hook;
extern PLH::Detour* entity_hook;
extern D3D_PRESENT_FUNCTION fn_originalPresent;
extern WNDPROC fn_originalWndProc;
extern Matrix1* pViewMatrix;
extern Matrix1 v;
typedef HRESULT(__stdcall* EntityMoveFn)(int64_t* p1, int32_t* p2);
HRESULT __stdcall hookPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRESULT __stdcall hookEntity(int64_t* p1, int32_t* p2);
extern EntityMoveFn fn_entityHook;