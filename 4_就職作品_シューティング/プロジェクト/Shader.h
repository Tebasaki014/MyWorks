#pragma once
#include"WatashiEngine.h"
class Shader
{
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//�f�o�C�X
	static ID3D12Device* dev;

public:
	// ���[�g�V�O�l�`��
	ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	ComPtr<ID3D12PipelineState> pipelinestate;

	Shader(const LPCWSTR filenameVS, const LPCWSTR filenamePS);

	//�f�o�C�X�Z�b�g
	static inline void SetDivice(ID3D12Device* device) {
		if (Shader::dev == nullptr) {
			Shader::dev = device;
		}
	}
};