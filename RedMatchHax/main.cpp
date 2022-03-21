#include "includes.h"
#include <d3d11.h>
#include "SDK.h"
#include <windows.h>
#pragma comment(lib, "d3d11.lib")
#include <stdio.h>
#include "Menu.h"
#include "CheatManager.h"
#include "SDK.h"
#include "Logger.h"

// Globals
HINSTANCE dll_handle;
HWND window = NULL;

typedef long(__stdcall* present)(IDXGISwapChain*, UINT, UINT);
present p_present;
present p_present_target;
bool showOpenKey = true;
bool get_present_pointer()
{
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	HANDLE handle = GetCurrentProcess();
	DWORD pid = GetProcessId(handle);
	window = findWindowFromProcessId(pid);
	sd.OutputWindow = window;
	sd.SampleDesc.Count = 1;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	IDXGISwapChain* swap_chain;
	ID3D11Device* device;

	const D3D_FEATURE_LEVEL feature_levels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
	if (D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		feature_levels,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&device,
		nullptr,
		nullptr) == S_OK)
	{
		void** p_vtable = *reinterpret_cast<void***>(swap_chain);
		swap_chain->Release();
		device->Release();
		//context->Release();
		p_present_target = (present)p_vtable[8];
		return true;
	}
	return false;
}

WNDPROC oWndProc;
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (true && ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	if (uMsg == WM_KEYUP && wParam == VK_INSERT) { menu.isOpen = !menu.isOpen; showOpenKey = false; } // Toggle menu

	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}

bool init = false;
ID3D11Device* p_device = NULL;
ID3D11DeviceContext* p_context = NULL;
ID3D11RenderTargetView* mainRenderTargetView = NULL;


ImFont* titleFont;
static long __stdcall detour_present(IDXGISwapChain* p_swap_chain, UINT sync_interval, UINT flags) {
	if (!init) {
		if (SUCCEEDED(p_swap_chain->GetDevice(__uuidof(ID3D11Device), (void**)&p_device)))
		{
			p_device->GetImmediateContext(&p_context);
			ID3D11Texture2D* pBackBuffer;
			p_swap_chain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

			D3D11_RENDER_TARGET_VIEW_DESC desc = {};
			memset(&desc, 0, sizeof(desc));
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // most important change!
			desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

			p_device->CreateRenderTargetView(pBackBuffer, &desc, &mainRenderTargetView);
			pBackBuffer->Release();
			oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
			ImGui_ImplWin32_Init(window);
			ImGui_ImplDX11_Init(p_device, p_context);
			uint64_t domain = (uint64_t)fnIl2cpp_domain_get();
			fnIl2cpp_thread_attach(domain);
			menu.onStart();
			init = true;

			titleFont = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahoma.ttf", 25);


		}
		else
			return p_present(p_swap_chain, sync_interval, flags);
	}



	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	menu.onRender();

	int witdh = fnGetWindowWitdh();
	int height = fnGetWindowHeight();

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(witdh, height));
	ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoBackground);
	auto pDrawList = ImGui::GetWindowDrawList();

	if (showOpenKey)
	{
		ImGui::PushFont(titleFont);
		pDrawList->AddText(ImVec2(10, 10), ImColor(255, 255, 255), "Press [Insert] to open the menu");
		ImGui::PopFont();
	}

	cheatManager.onRender();

	ImGui::End();
	ImGui::EndFrame();
	ImGui::Render();
	p_context->OMSetRenderTargets(1, &mainRenderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	return p_present(p_swap_chain, sync_interval, flags);
}

DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(dll_handle, 0);
	Sleep(100);
	return 0;
}


//"main" loop
int WINAPI main()
{


	if (!get_present_pointer())
	{
		printf("Failed to get present_pointer");
		return 1;
	}

	MH_STATUS status = MH_Initialize();
	if (status != MH_OK)
	{
		printf("Failed to init MinHook");
		return 1;
	}

	if (MH_CreateHook(reinterpret_cast<void**>(p_present_target), &detour_present, reinterpret_cast<void**>(&p_present)) != MH_OK) {
		printf("Failed to hook dx11");
		return 1;
	}


	INIT_CONSOLE();
	initSDK();
	cheatManager.init();
	
	if (MH_EnableHook(p_present_target) != MH_OK) {
		return 1;
	}

	
	Beep(523, 500);
	while (isCheatRunning) {
		Sleep(15);

		if (GetAsyncKeyState(VK_NUMPAD0) & 1) {
			dumpObjects();
		}

		if (GetAsyncKeyState(VK_END) & 1) {
			isCheatRunning = false;
		}


		cheatManager.onUpdate();
	}

	//Cleanup
	if (MH_DisableHook(MH_ALL_HOOKS) != MH_OK) {
		return 1;
	}
	if (MH_Uninitialize() != MH_OK) {
		return 1;
	}

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();

	if (mainRenderTargetView) { mainRenderTargetView->Release(); mainRenderTargetView = NULL; }
	if (p_context) { p_context->Release(); p_context = NULL; }
	if (p_device) { p_device->Release(); p_device = NULL; }
	SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)(oWndProc));

	cheatManager.destroy();


	CLOSE_CONSOLE();
	Beep(253, 500);
	CreateThread(0, 0, EjectThread, 0, 0, 0);
	return 0;
}



BOOL __stdcall DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		dll_handle = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{

	}
	return TRUE;
}