#pragma once
#include<Windows.h>
#include<wrl.h>
#include<d3d12.h>
#include<vector>
#include"Vector2.h"
#include"Vector3.h"

//typedef float Color[4];
typedef UINT Texture;     
class Sprite
{
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//�e�N�X�`��
	// �e�N�X�`���̍ő喇��
	static const int srvCount = 256;
	// ���_��
	static const int vertNum = 4;
	// �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootSignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelineState;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texBuff[srvCount];

	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// �e�N�X�`���ԍ�
	Texture tex = 0;
	// Z�����̉�]�p
	float rotation = 0.0f;
	// ���W
	Vector2 position{};
	// �X�v���C�g���A����
	Vector2 size = { 100.0f, 100.0f };
	// �A���J�[�|�C���g
	Vector2 anchorpoint = { 0, 0 };
	// ���[���h�s��
	XMMATRIX matWorld{};
	// �F
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// ���E���]
	bool isFlipX = false;
	// �㉺���]
	bool isFlipY = false;
	// �e�N�X�`���n�_
	Vector2 texBase = { 0, 0 };
	// �e�N�X�`�����A����
	Vector2 texSize = { 100.0f, 100.0f };

	//���_�f�[�^�]��
	void TransferVertices();

public:
	//���_�f�[�^�\����
	struct VertexPosUv
	{
		Vector3 pos; // xyz���W
		Vector2 uv;  // uv���W
	};

	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
	};

	//�ÓI������
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);
	//�e�N�X�`���ǂݍ���
	static bool LoadTexture(Texture tex, const wchar_t* filename);
	//�`��O����
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//�`��㏈��
	static void PostDraw();
	/// �X�v���C�g����
	static Sprite* Create(Texture tex, Vector2 position, XMFLOAT4 color = { 1, 1, 1 ,1 }, Vector2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	Sprite(Texture tex, Vector2 position, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY);
	//������
	bool Initialize();
	//�p�x�ݒ�
	void SetRotation(float rotation);
	//���W�擾
	const Vector2& GetPosition() { return position; }
	//���W�ݒ�
	void SetPosition(Vector2 position);
	//�T�C�Y�ݒ�
	void SetSize(Vector2 size);
	//�A���J�[�|�C���g�ݒ�
	void SetAnchorPoint(Vector2 anchorpoint);
	//���E���]�ݒ�
	void SetIsFlipX(bool isFlipX);
	//�㉺���]�̐ݒ�
	void SetIsFlipY(bool isFlipY);
	//�e�N�X�`���͈͐ݒ�
	void SetTextureRect(Vector2 texBase, Vector2 texSize);
	//�`��
	void Draw(XMFLOAT4 dcolor);
};