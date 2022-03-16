#pragma once
#include <unordered_map>
#include "Mesh.h"
class Model
{
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//ディレクトリ
	static const std::string baseDirectory;
	//デバイス
	static ID3D12Device* device;
	//デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;

	//名前
	std::string name;
	//メッシュコンテナ
	std::vector<Mesh*> meshes;
	//マテリアルコンテナ
	std::unordered_map<std::string, Material*> materials;
	//デフォルトマテリアル
	Material* defaultMaterial = nullptr;
	//デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;

	//スムージングする?
	bool isSmoothing = true;

	//マテリアル読み込み
	void LoadMaterial(const std::string& directoryPath, const std::string& filename);
	//マテリアルセット
	void AddMaterial(Material* material);
	//デスクリプタヒープ生成
	void CreateDescriptorHeap();
	//テクスチャ読み込み
	void LoadTextures();

public:
	//静的初期化
	static void StaticInitialize(ID3D12Device* device);
	//OBJファイルからメッシュ生成
	static Model* CreateFromOBJ(const std::string& modelname);
	~Model();
	//初期化
	void Initialize(const std::string& modelname);
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//スムージングする？
	inline void SetSmooth(bool smooth){
		this->isSmoothing = smooth;
	}
};