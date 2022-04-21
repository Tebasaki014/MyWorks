#pragma once
#include<d3d12.h>
#include<dxgi1_6.h>
#include<vector>
#include<d3dcompiler.h>
#include "DirectXTex/DirectXTex.h"
#include "DirectXTex/d3dx12.h"
#include<wrl.h>

#include"WinApp.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

using namespace Microsoft::WRL;
using namespace DirectX;

typedef float Color[4];

class Dx12App
{
private:
	// いろいろ
	WinApp* win = nullptr;
	ComPtr<ID3D12Device> dev;
	ComPtr<IDXGIFactory6> dxgiFactory;
	ComPtr<IDXGISwapChain4> swapchain;
	ComPtr<ID3D12CommandAllocator> cmdAllocator;
	ComPtr<ID3D12GraphicsCommandList> cmdList;
	ComPtr<ID3D12CommandQueue> cmdQueue;
	std::vector<ComPtr<ID3D12Resource>> backBuffers;
	ComPtr<ID3D12Resource> depthBuffer;
	ComPtr<ID3D12DescriptorHeap> rtvHeaps;
	ComPtr<ID3D12DescriptorHeap> dsvHeap;
	ComPtr<ID3D12Fence> fence;
	UINT64 fenceVal = 0;

	//デバイス初期化
	HRESULT InitializeDXGIDevice();
	//コマンド関連初期化
	HRESULT InitializeCommand();
	//スワップチェーン生成
	HRESULT CreateSwapChain();
	//レンダーターゲット生成
	HRESULT CreateFinalRenderTargets();
	//深度バッファ生成
	HRESULT CreateDepthBuffer();
	//フェンス生成
	HRESULT CreateFence();

public:
	//初期化
	void Initialize(WinApp* win);
	//描画開始
	void BeginDraw(Color clearColor);
	//描画おわり
	void EndDraw();
	//レンダーターゲットクリア
	void ClearRenderTarget(Color clearColor);
	//深度バッファクリア
	void ClearDepthBuffer();

	//デバイス取得
	ID3D12Device* GetDevice() { return dev.Get(); }
	//コマンドリスト取得
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }
};