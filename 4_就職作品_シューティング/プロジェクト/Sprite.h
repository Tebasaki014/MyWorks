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
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

	//テクスチャ
	// テクスチャの最大枚数
	static const int srvCount = 256;
	// 頂点数
	static const int vertNum = 4;
	// デバイス
	static ID3D12Device* device;
	// デスクリプタサイズ
	static UINT descriptorHandleIncrementSize;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// ルートシグネチャ
	static ComPtr<ID3D12RootSignature> rootSignature;
	// パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState> pipelineState;
	// 射影行列
	static XMMATRIX matProjection;
	// デスクリプタヒープ
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// テクスチャバッファ
	static ComPtr<ID3D12Resource> texBuff[srvCount];

	// 頂点バッファ
	ComPtr<ID3D12Resource> vertBuff;
	// 定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	// 頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView{};
	// テクスチャ番号
	Texture tex = 0;
	// Z軸回りの回転角
	float rotation = 0.0f;
	// 座標
	Vector2 position{};
	// スプライト幅、高さ
	Vector2 size = { 100.0f, 100.0f };
	// アンカーポイント
	Vector2 anchorpoint = { 0, 0 };
	// ワールド行列
	XMMATRIX matWorld{};
	// 色
	XMFLOAT4 color = { 1, 1, 1, 1 };
	// 左右反転
	bool isFlipX = false;
	// 上下反転
	bool isFlipY = false;
	// テクスチャ始点
	Vector2 texBase = { 0, 0 };
	// テクスチャ幅、高さ
	Vector2 texSize = { 100.0f, 100.0f };

	//頂点データ転送
	void TransferVertices();

public:
	//頂点データ構造体
	struct VertexPosUv
	{
		Vector3 pos; // xyz座標
		Vector2 uv;  // uv座標
	};

	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMFLOAT4 color;	// 色 (RGBA)
		XMMATRIX mat;	// ３Ｄ変換行列
	};

	//静的初期化
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);
	//テクスチャ読み込み
	static bool LoadTexture(Texture tex, const wchar_t* filename);
	//描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//描画後処理
	static void PostDraw();
	/// スプライト生成
	static Sprite* Create(Texture tex, Vector2 position, XMFLOAT4 color = { 1, 1, 1 ,1 }, Vector2 anchorpoint = { 0.0f, 0.0f }, bool isFlipX = false, bool isFlipY = false);

	Sprite(Texture tex, Vector2 position, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY);
	//初期化
	bool Initialize();
	//角度設定
	void SetRotation(float rotation);
	//座標取得
	const Vector2& GetPosition() { return position; }
	//座標設定
	void SetPosition(Vector2 position);
	//サイズ設定
	void SetSize(Vector2 size);
	//アンカーポイント設定
	void SetAnchorPoint(Vector2 anchorpoint);
	//左右反転設定
	void SetIsFlipX(bool isFlipX);
	//上下反転の設定
	void SetIsFlipY(bool isFlipY);
	//テクスチャ範囲設定
	void SetTextureRect(Vector2 texBase, Vector2 texSize);
	//描画
	void Draw(XMFLOAT4 dcolor);
};