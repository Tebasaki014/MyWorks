#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"
#include "d3dx12.h"
#include <forward_list>

#include "Camera.h"
#include "SDelete.h"

/// <summary>
/// パーティクルマネージャ
/// </summary>
class ParticleManager
{
private:
	//Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	//頂点データ構造体
	struct VertexPos
	{
		Vector3 pos; // xyz座標
		float scale; // スケール
		Vector3 color; //色
	};

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMMATRIX mat;	// ビュープロジェクション行列
		XMMATRIX matBillboard;	// ビルボード行列
	};

	//1粒
	class Tsubu
	{
		//Microsoft::WRL::を省略
		template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
		//DirectX::を省略
		using XMFLOAT4 = DirectX::XMFLOAT4;
		using XMMATRIX = DirectX::XMMATRIX;
	public:
		//座標
		Vector3 position = {};
		//速度
		Vector3 velocity = {};
		//方向
		Vector3 direction = {};
		//加速度
		float accel = {};
		//重力(引力)
		Vector3 gravity = {};
		//色
		Vector3 color = {};
		//スケール
		float scale = 1.0f;
		//回転
		float rotation = 0.0f;
		//初期値
		Vector3 s_color = {};
		float s_scale = 1.0f;
		float s_rotation = 0.0f;
		//最終値
		Vector3 e_color = {};
		float e_scale = 0.0f;
		float e_rotation = 0.0f;
		//現在フレーム
		int frame = 0;
		//終了フレーム
		int num_frame = 0;
	};

private:
	static const int vertexCount = 65536;// 頂点数

public:
	//インスタンス生成
	static void Create(ID3D12Device* device, Camera* camera);
	//インスタンス取得
	static ParticleManager* GetInstance();
	//インスタンス破棄
	inline static void Destroy() {
		SDelete(instace);
	}

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画
	void Draw(ID3D12GraphicsCommandList * cmdList);

	//パーティクルの追加
	void Add(
		int life,
		Vector3 position,
		Vector3 direction,
		float speed,
		float start_scale = 1.0f,
		float end_scale = 0.1f,
		Vector3 start_color = Vector3(1.0f,1.0f,1.0f),
		Vector3 end_color = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 gravity = Vector3::Zero()
		);

	//デスクリプタヒープ初期化
	void InitializeDescriptorHeap();
	//グラフィックパイプライン生成
	void InitializeGraphicsPipeline();
	//テクスチャ読み込み
	void LoadTexture();
	//モデル作成
	void CreateModel();

private:
	//デバイス
	ID3D12Device* device = nullptr;
	//デスクリプタサイズ
	UINT descriptorHandleIncrementSize = 0u;
	//ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootsignature;
	//パイプラインステートオブジェクト
	ComPtr<ID3D12PipelineState> pipelinestate;
	//デスクリプタヒープ
	ComPtr<ID3D12DescriptorHeap> descHeap;
	//頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	//テクスチャバッファ
	ComPtr<ID3D12Resource> texbuff;
	//シェーダリソースビューのハンドル(CPU)
	CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	//シェーダリソースビューのハンドル(CPU)
	CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//パーティクル配列
	std::forward_list<Tsubu> tsubutsubu;
	//カメラ
	Camera* camera = nullptr;

	ParticleManager(ID3D12Device* device, Camera* camera);
	static ParticleManager* instace;
};

class ParticleEmitter 
{
public:
	enum class Shape
	{
		Dot,
		Box,
	};

	ParticleEmitter(
		int life,
		Vector3 position,
		float speed,
		int density = 10,
		float start_scale = 1.0f,
		float end_scale = 0.1f,
		Vector3 start_color = Vector3(1.0f, 1.0f, 1.0f),
		Vector3 end_color = Vector3(1.0f, 1.0f, 1.0f)
	);
	~ParticleEmitter() = default;

	void Live(Vector3 pos);

#pragma region Setter
	void SetGravity(const Vector3& gravity = { 0.0f, -1.0f, 0.0f });

#pragma endregion

private:
	ParticleManager* manager = nullptr;
	int life = 0;
	Vector3 position = {};
	float speed = 0.0f;
	float startScale = 0.0f;
	float endScale = 0.0f;
	Vector3 startColor = {};
	Vector3 endColor = {};

	Vector3 gravity = {};

	//密度
	int density = 10;
};