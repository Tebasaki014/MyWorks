#include "Light.h"

//static����
ID3D12Device* Light::device = nullptr;
Light* Light::instance = nullptr;

Light::Light(ID3D12Device* device)
{
	//null�`�F�b�N
	assert(device);
	//static�Z�b�g(���ɂ���Ă��疳��)
	if (!Light::device) {
		Light::device = device;
	}
}

Light* Light::Create(ID3D12Device* device)
{
	//�܂�����ĂȂ�������
	if (!Light::instance) {
		//���a
		Light::instance = new Light(device);
	}

	return Light::instance;
}

void Light::Initialize()
{
	HRESULT result;

	//�萔�o�b�t�@
	//����
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff)
	);
	if (FAILED(result)) { assert(0); }
	//�����
	TransferBuffer();
}

void Light::Update()
{
	//�ύX���������ꍇ
	if (dirty) {
		//�萔�o�b�t�@�ɂԂ񓊂���
		TransferBuffer();
		dirty = false;
	}
}

void Light::Draw(ID3D12GraphicsCommandList* cmdList, UINT rootPrmIdx)
{
	//�萔�o�b�t�@������
	cmdList->SetGraphicsRootConstantBufferView(rootPrmIdx, constBuff->GetGPUVirtualAddress());
}

void Light::TransferBuffer()
{
	HRESULT result;
	//�萔�o�b�t�@�֓]��
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->lightv = direc;
		constMap->lightcolor = color;
		constBuff->Unmap(0, nullptr);
	}
}