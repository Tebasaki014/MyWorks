#pragma once
#include <Windows.h>
#include "Material.h"
#include <vector>
#include <unordered_map>

class Mesh
{
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// ���_�f�[�^�\���́i�e�N�X�`������j
	struct VertexPosNormalUv
	{
		Vector3 pos; // xyz���W
		Vector3 normal; // �@���x�N�g��
		Vector2 uv;  // uv���W
	};

private:
	// �f�o�C�X
	static ID3D12Device* dev;
	// ���O
	std::string name;
	// ���_�o�b�t�@
	ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	ComPtr<ID3D12Resource> indexBuff;
	// ���_�o�b�t�@�r���[
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// �C���f�b�N�X�o�b�t�@�r���[
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// ���_�f�[�^�z��
	std::vector<VertexPosNormalUv> vertices;
	// ���_�C���f�b�N�X�z��
	std::vector<unsigned short> indices;
	// �}�e���A��
	Material* material = nullptr;
	//���_�@���X���[�W���O�p�f�[�^
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;

public:
	//�ÓI������
	static void StaticInitialize(ID3D12Device* dev);

	//���O�擾
	inline const std::string& GetName() { return name; }
	//���O�Z�b�g
	void SetName(const std::string& name);
	//���_�f�[�^�ǉ�
	void AddVertex(const VertexPosNormalUv& vertex);
	//���_�C���f�b�N�X�ǉ�
	void AddIndex(unsigned short index);
	//�G�b�W�������p�f�[�^�ǉ�
	void AddSmoothData(unsigned short idxPosition, unsigned short idxVert);
	//���������_�@���̌v�Z
	void CalculateSmoothedVertNormals();
	//�}�e���A���擾
	inline Material* GetMaterial() { return material; }
	//�}�e���A���Z�b�g
	void SetMaterial(Material* material);
	//�o�b�t�@����
	void CreateBuffers();
	//���_�o�b�t�@�擾
	inline const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }
	//�C���f�b�N�X�o�b�t�@�擾
	inline const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }
	//���_���擾
	inline size_t GetVertexCount() { return vertices.size(); }
	
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList);
};