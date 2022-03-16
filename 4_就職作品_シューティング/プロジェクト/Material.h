#pragma once
#include <d3d12.h>
#include "DirectXTex/d3dx12.h"
#include "Vector2.h"
#include "Vector3.h"
#include <wrl.h>
#include <string>

class Material
{
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	// デバイス
	static ID3D12Device* dev;
	// テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;

	// コンストラクタ
	Material() {
		ambient = { 0.3f, 0.3f, 0.3f };
		diffuse = { 0.0f, 0.0f, 0.0f };
		specular = { 0.0f, 0.0f, 0.0f };
		alpha = 1.0f;
	}

public:
	// 定数バッファ用データ構造体B1
	struct ConstBufferDataB1
	{
		Vector3 ambient; // アンビエント係数
		float pad1; // パディング
		Vector3 diffuse; // ディフューズ係数
		float pad2; // パディング
		Vector3 specular; // スペキュラー係数
		float alpha;	// アルファ
	};

	std::string name;	// マテリアル名
	Vector3 ambient;	// アンビエント
	Vector3 diffuse;	// ディフューズ
	Vector3 specular;	// スペキュラー
	float alpha;		// アルファ
	std::string textureFilename;// テクスチャファイル

private:
	//初期化
	void Initialize();
	//定数バッファの生成
	void CreateConstantBuffer();

public:
	//静的初期化
	static void StaticInitialize(ID3D12Device* dev);
	//生成
	static Material* Create();
	// 定数バッファ取得
	ID3D12Resource* GetConstantBuffer() { return constBuff.Get(); }
	//テクスチャ読み込み
	void LoadTexture(const std::string& directoryPath, CD3DX12_CPU_DESCRIPTOR_HANDLE cpuHandle, CD3DX12_GPU_DESCRIPTOR_HANDLE gpuHandle);
	//更新
	void Update();
	const CD3DX12_CPU_DESCRIPTOR_HANDLE& GetCpuHandle() { return cpuDescHandleSRV; }
	const CD3DX12_GPU_DESCRIPTOR_HANDLE& GetGpuHandle() { return gpuDescHandleSRV; }
};