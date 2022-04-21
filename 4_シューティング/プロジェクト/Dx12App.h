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
	// ���낢��
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

	//�f�o�C�X������
	HRESULT InitializeDXGIDevice();
	//�R�}���h�֘A������
	HRESULT InitializeCommand();
	//�X���b�v�`�F�[������
	HRESULT CreateSwapChain();
	//�����_�[�^�[�Q�b�g����
	HRESULT CreateFinalRenderTargets();
	//�[�x�o�b�t�@����
	HRESULT CreateDepthBuffer();
	//�t�F���X����
	HRESULT CreateFence();

public:
	//������
	void Initialize(WinApp* win);
	//�`��J�n
	void BeginDraw(Color clearColor);
	//�`�您���
	void EndDraw();
	//�����_�[�^�[�Q�b�g�N���A
	void ClearRenderTarget(Color clearColor);
	//�[�x�o�b�t�@�N���A
	void ClearDepthBuffer();

	//�f�o�C�X�擾
	ID3D12Device* GetDevice() { return dev.Get(); }
	//�R�}���h���X�g�擾
	ID3D12GraphicsCommandList* GetCommandList() { return cmdList.Get(); }
};