#pragma once
#include"WatashiEngine.h"
class Light
{
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//�萔�o�b�t�@�p
	struct ConstBufferData
	{
		Vector3 lightv;
		Vector3 lightcolor;
	};

	//�C���X�^���X�쐬
	static Light* Create(ID3D12Device* device);

	//������
	void Initialize();
	//�X�V
	void Update();
	//�`��(�O���t�B�b�N�X�R�}���h)
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootPrmIdx);
	//�萔�o�b�t�@��
	void TransferBuffer();

	//�C���X�^���X�擾
	static inline Light* GetInstance() {
		if (instance == nullptr) {
			return nullptr;
		}
		else{
			return instance;
		}
	}
	//�C���X�^���X�j��
	inline static void Destroy() {
		delete instance;
		instance = nullptr;
	}

	/* �Z�b�^�[�̊F�l */
	//���C�g�����w��
	inline void SetDirection(const Vector3& direction) {
		//���K�����ă|�C
		this->direc = Vector3::Nomalize(direction);
		dirty = true;
	}

	//���C�g�F�w��
	inline void SetColor(const Vector3& color) {
		this->color = color;
		dirty = true;
	}

private:
	//�f�o�C�X
	static ID3D12Device* device;

	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���C�g�����x�N�g��(���K������)
	Vector3 direc = { 0,1,0 };
	//���C�g�F
	Vector3 color = { 1,1,1 };
	//�_�[�e�B
	bool dirty = false;

	//static������
	Light(ID3D12Device* device);
	//�ۂ��ۂ�
	~Light() = default;

	//�C���X�^���X
	static Light* instance;
};