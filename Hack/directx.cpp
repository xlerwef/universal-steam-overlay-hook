#include "pch.h"
#include <iostream>
#include "directx.h"
#include <d3d11.h>
#include "dxgitype.h"
#include "dxgi.h"
bool initialized;
ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
D3D_PRESENT_FUNCTION fn_originalPresent = nullptr;
