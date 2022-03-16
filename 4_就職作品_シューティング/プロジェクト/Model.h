#pragma once
#include <unordered_map>
#include "Mesh.h"
class Model
{
	//Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//�f�B���N�g��
	static const std::string baseDirectory;
	//�f�o�C�X
	static ID3D12Device* device;
	//�f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;

	//���O
	std::string name;
	//���b�V���R���e�i
	std::vector<Mesh*> meshes;
	//�}�e���A���R���e�i
	std::unordered_map<std::string, Material*> materials;
	//�f�t�H���g�}�e���A��
	Material* defaultMaterial = nullptr;
	//�f�X�N���v�^�q�[�v
	ComPtr<ID3D12DescriptorHeap> descHeap;

	//�X���[�W���O����?
	bool isSmoothing = true;

	//�}�e���A���ǂݍ���
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	//�}�e���A���Z�b�g
	void AddMaterial(Material* material);
	//�f�X�N���v�^�q�[�v����
	void CreateDescriptorHeap();
	//�e�N�X�`���ǂݍ���
	void LoadTextures();

public:
	//�ÓI������
	static void StaticInitialize(ID3D12Device* device);
	//OBJ�t�@�C�����烁�b�V������
	static Model* CreateFromOBJ(const std::string& modelname);
	~Model();
	//������
	void Initialize(const std::string& modelname);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�X���[�W���O����H
	inline void SetSmooth(bool smooth){
		this->isSmoothing = smooth;
	}
};