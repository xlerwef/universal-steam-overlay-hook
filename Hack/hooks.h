#pragma once
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui.h"
#include "stdio.h"
#include "iostream"
#include "drawing.h"
#include "spdlog/spdlog.h"

extern D3D_PRESENT_FUNCTION fn_originalPresent;
extern WNDPROC fn_originalWndProc;
HRESULT __stdcall hookPresent(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
LRESULT CALLBACK hookWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);