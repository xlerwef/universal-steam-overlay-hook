#include "pch.h"
#include <iostream>
#include "directx.h"
#include <d3d11.h>
#include "dxgitype.h"
#include "dxgi.h"
#include <DirectXMath.h>
#include "gamestructs.h"
bool initialized;
ID3D11Device* g_pDevice = nullptr;
ID3D11DeviceContext* g_pContext = nullptr;
ID3D11RenderTargetView* g_pRenderTargetView = nullptr;
D3D_PRESENT_FUNCTION fn_originalPresent = nullptr;

bool WorldToScreenCustom(const Vector3& worldPos, Vector2& screenPos, 
                   const Matrix1& viewMatrix,
                   float screenWidth, float screenHeight) 
{
    // Transform world position to view space
    Vector3 viewPos;
    viewPos.x = worldPos.x * viewMatrix[0][0] + worldPos.y * viewMatrix[1][0] + worldPos.z * viewMatrix[2][0] + viewMatrix[3][0];
    viewPos.y = worldPos.x * viewMatrix[0][1] + worldPos.y * viewMatrix[1][1] + worldPos.z * viewMatrix[2][1] + viewMatrix[3][1];
    viewPos.z = worldPos.x * viewMatrix[0][2] + worldPos.y * viewMatrix[1][2] + worldPos.z * viewMatrix[2][2] + viewMatrix[3][2];

    // Assuming Z = 0 represents the plane you want to project onto
    if (viewPos.z > 0) // Object behind the camera
        return false;

    // Orthographic projection - map view coordinates directly to screen coordinates
    // Adjust these mappings based on your camera's position and orientation
    screenPos.x = (viewPos.x + 1.0f) * (screenWidth / 2.0f);
    screenPos.y = (-viewPos.y + 1.0f) * (screenHeight / 2.0f);

    return true;
}