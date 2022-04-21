#pragma once
#include"WatashiEngine.h"
class Shader
{
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//デバイス
	static ID3D12Device* dev;

public:
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	// パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;

	Shader(const LPCWSTR filenameVS, const LPCWSTR filenamePS);

	//デバイスセット
	static inline void SetDivice(ID3D12Device* device) {
		if (Shader::dev == nullptr) {
			Shader::dev = device;
		}
	}
};