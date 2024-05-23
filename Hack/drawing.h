#pragma once
#include "directx.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx11.h"
#include <d3d11.h>

bool initialize_imgui(IDXGISwapChain* pThis);
void begin_draw();
void end_draw();