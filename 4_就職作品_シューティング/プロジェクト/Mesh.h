#pragma once
#include <Windows.h>
#include "Material.h"
#include <vector>
#include <unordered_map>

class Mesh
{
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// 頂点データ構造体（テクスチャあり）
	struct VertexPosNormalUv
	{
		Vector3 pos; // xyz座標
		Vector3 normal; // 法線ベクトル
		Vector2 uv;  // uv座標
	};

private:
	// デバイス
	static ID3D12Device* dev;
	// 名前
	std::string name;
	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// インデックスバッファ
	ComPtr<ID3D12Resource> indexBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView = {};
	// インデックスバッファビュー
	D3D12_INDEX_BUFFER_VIEW ibView = {};
	// 頂点データ配列
	std::vector<VertexPosNormalUv> vertices;
	// 頂点インデックス配列
	std::vector<unsigned short> indices;
	// マテリアル
	Material* material = nullptr;
	//頂点法線スムージング用データ
	std::unordered_map<unsigned short, std::vector<unsigned short>> smoothData;

public:
	//静的初期化
	static void StaticInitialize(ID3D12Device* dev);

	//名前取得
	inline const std::string& GetName() { return name; }
	//名前セット
	void SetName(const std::string& name);
	//頂点データ追加
	void AddVertex(const VertexPosNormalUv& vertex);
	//頂点インデックス追加
	void AddIndex(unsigned short index);
	//エッジ平滑化用データ追加
	void AddSmoothData(unsigned short idxPosition, unsigned short idxVert);
	//平滑化頂点法線の計算
	void CalculateSmoothedVertNormals();
	//マテリアル取得
	inline Material* GetMaterial() { return material; }
	//マテリアルセット
	void SetMaterial(Material* material);
	//バッファ生成
	void CreateBuffers();
	//頂点バッファ取得
	inline const D3D12_VERTEX_BUFFER_VIEW& GetVBView() { return vbView; }
	//インデックスバッファ取得
	inline const D3D12_INDEX_BUFFER_VIEW& GetIBView() { return ibView; }
	//頂点数取得
	inline size_t GetVertexCount() { return vertices.size(); }
	
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
};