#pragma once
#include <d3d11.h>
#include "spdlog/spdlog.h"
#include "dxgitype.h"
#include "dxgi.h"
#include "gamestructs.h"
const D3D_DRIVER_TYPE DRIVER_TYPE_LIST[4] = { D3D_DRIVER_TYPE_REFERENCE, D3D_DRIVER_TYPE_SOFTWARE, D3D_DRIVER_TYPE_HARDWARE, D3D_DRIVER_TYPE_WARP };
typedef HRESULT(__stdcall* D3D_PRESENT_FUNCTION)(IDXGISwapChain* pThis, UINT SyncInterval, UINT Flags);
#define SAFE_RELEASE(p) if (p) { p->Release(); p = nullptr; } 
bool GetD3D11SwapchainDeviceContext(IDXGISwapChain** pSwapchain, ID3D11Device** pDevice,
    ID3D11DeviceContext** pContextTable);

D3D_PRESENT_FUNCTION GetD3D11PresentFunction();
extern D3D_PRESENT_FUNCTION fn_originalPresent;
extern HWND window;
extern bool initialized;
extern ID3D11Device* g_pDevice;
extern ID3D11DeviceContext* g_pContext;
extern ID3D11RenderTargetView* g_pRenderTargetView;
bool WorldToScreenCustom(const Vector3 & worldPos, Vector2 & screenPos,
    const Matrix1 & viewMatrix,
    float screenWidth, float screenHeight);