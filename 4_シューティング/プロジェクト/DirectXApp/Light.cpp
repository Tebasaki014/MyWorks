#include "Light.h"

//static実体
ID3D12Device* Light::device = nullptr;
Light* Light::instance = nullptr;

Light::Light(ID3D12Device* device)
{
	//nullチェック
	assert(device);
	//staticセット(既にやってたら無視)
	if (!Light::device) {
		Light::device = device;
	}
}

Light* Light::Create(ID3D12Device* device)
{
	//まだ作ってなかったら
	if (!Light::instance) {
		//爆誕
		Light::instance = new Light(device);
	}

	return Light::instance;
}

void Light::Initialize()
{
	HRESULT result;

	//定数バッファ
	//つくる
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);
	if (FAILED(result)) { assert(0); }
	//いれる
	TransferBuffer();
}

void Light::Update()
{
	//変更があった場合
	if (dirty) {
		//定数バッファにぶん投げる
		TransferBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootPrmIdx)
{
	//定数バッファせっと
	cmdList->SetGraphicsRootConstantBufferView(rootPrmIdx, constBuff->GetGPUVirtualAddress());
}

void Light::TransferBuffer()
{
	HRESULT result;
	//定数バッファへ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = direc;
		constMap->lightcolor = color;
		constBuff->Unmap(0, nullptr);
	}
}