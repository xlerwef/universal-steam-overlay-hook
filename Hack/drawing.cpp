#include "drawing.h"
#include "hooks.h"
WNDPROC fn_originalWndProc = NULL;
HWND window = NULL;
void begin_draw() {
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void end_draw() {
	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	g_pContext->OMSetRenderTargets(1, &g_pRenderTargetView, NULL);
}

bool initialize_imgui(IDXGISwapChain* pThis) {
	pThis->GetDevice(__uuidof(ID3D11Device), (void**)&g_pDevice);
	if (&g_pDevice == nullptr) {
		spdlog::error("Unable to retrieve global pointer to ID3D11Device.");
		return false;
	}

	g_pDevice->GetImmediateContext(&g_pContext);
	if (&g_pContext == nullptr) {
		spdlog::error("Unable to retrieve D3D11DeviceContext.");
		return false;
	}

	DXGI_SWAP_CHAIN_DESC desc;
	pThis->GetDesc(&desc);
	if (&desc == nullptr) {
		spdlog::error("Unable to retrieve DXGI_SWAP_CHAIN_DESC while initializing GUI.");
		return false;
	}

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	window = desc.OutputWindow;
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX11_Init(g_pDevice, g_pContext);

	ID3D11Texture2D* pBackBuffer;
	pThis->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	if (!pBackBuffer) {
		spdlog::error("Unable to retrieve ID3D11Texture2D buffer.");
		return false;
	}

	g_pDevice->CreateRenderTargetView(pBackBuffer, NULL, &g_pRenderTargetView);
	fn_originalWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)hookWndProc);
	pBackBuffer->Release();
	return true;
}