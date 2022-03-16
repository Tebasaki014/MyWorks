#include "Mesh.h"
#include <d3dcompiler.h>
#include <cassert>

#pragma comment(lib, "d3dcompiler.lib")

ID3D12Device* Mesh::dev = nullptr;

void Mesh::StaticInitialize(ID3D12Device* dev)
{
	// 再初期化チェック
	assert(!Mesh::dev);
	Mesh::dev = dev;

	// マテリアル静的初期化
	Material::StaticInitialize(dev);
}

void Mesh::SetName(const std::string& name)
{
	this->name = name;
}

void Mesh::AddVertex(const VertexPosNormalUv& vertex)
{
	vertices.emplace_back(vertex);
}

void Mesh::AddIndex(unsigned short index)
{
	indices.emplace_back(index);
}

void Mesh::AddSmoothData(unsigned short idxPosition, unsigned short idxVert)
{
	smoothData[idxPosition].emplace_back(idxVert);
}

void Mesh::CalculateSmoothedVertNormals()
{
	auto itr = smoothData.begin();
	for (; itr != smoothData.end(); itr++) {
		//各面用の共通頂点コレクション
		std::vector<unsigned short>& v = itr->second;
		//全頂点の法線を平均
		Vector3 normal = {};
		for (unsigned short i : v) {
			normal += vertices[i].normal;
		}
		normal = Vector3::Nomalize(normal / (float)v.size());

		//法線を共有する頂点に書き込み
		for (unsigned short i : v) {
			vertices[i].normal = normal;
		}
	}
}

void Mesh::SetMaterial(Material* material)
{
	this->material = material;
}

void Mesh::CreateBuffers()
{
	HRESULT result;

	// 頂点バッファ生成
	UINT sizeVB = static_cast<UINT>(sizeof(VertexPosNormalUv) * vertices.size());
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeVB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	// 頂点バッファへのデータ転送
	VertexPosNormalUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		std::copy(vertices.begin(), vertices.end(), vertMap);
		vertBuff->Unmap(0, nullptr);
	}
	// 頂点バッファビューの作成
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeVB;
	vbView.StrideInBytes = sizeof(vertices[0]);

	if (FAILED(result)) {
		assert(0);
		return;
	}
	
	// インデックスバッファ生成
	UINT sizeIB = static_cast<UINT>(sizeof(unsigned short) * indices.size());
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeIB),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&indexBuff));
	if (FAILED(result)) {
		assert(0);
		return;
	}
	// インデックスバッファへのデータ転送
	unsigned short* indexMap = nullptr;
	result = indexBuff->Map(0, nullptr, (void**)&indexMap);
	if (SUCCEEDED(result)) {
		std::copy(indices.begin(), indices.end(), indexMap);
		indexBuff->Unmap(0, nullptr);
	}
	// インデックスバッファビューの作成
	ibView.BufferLocation = indexBuff->GetGPUVirtualAddress();
	ibView.Format = DXGI_FORMAT_R16_UINT;
	ibView.SizeInBytes = sizeIB;
}

void Mesh::Draw(ID3D12GraphicsCommandList* cmdList)
{
	// 頂点バッファセット
	cmdList->IASetVertexBuffers(0, 1, &vbView);
	// インデックスバッファセット
	cmdList->IASetIndexBuffer(&ibView);
	// シェーダリソースビューセット
	cmdList->SetGraphicsRootDescriptorTable(2, material->GetGpuHandle());
	// マテリアルの定数バッファセット
	ID3D12Resource* constBuff = material->GetConstantBuffer();
	cmdList->SetGraphicsRootConstantBufferView(1, constBuff->GetGPUVirtualAddress());

	// 描画コマンド
	cmdList->DrawIndexedInstanced((UINT)indices.size(), 1, 0, 0, 0);
}