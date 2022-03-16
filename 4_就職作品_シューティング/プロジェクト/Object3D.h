#pragma once
#include"Model.h"
#include "Camera.h"
#include"Light.h"
#include"Shader.h"
#include"Quaternion.h"

//前方宣言(c4430防止)
class Shader;

class Object3D
{
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:
	// パイプラインセット
	struct PipelineSet
	{
		// ルートシグネチャ
		ComPtr<ID3D12RootSignature> rootsignature;
		// パイプラインステートオブジェクト
		ComPtr<ID3D12PipelineState> pipelinestate;
	};

	// 定数バッファ用データ構造体B0
	struct ConstBufferDataB0
	{
		XMMATRIX viewproj;	//ビュープロジェクション行列
		XMMATRIX world;		//ワールド行列
		Vector3 cameraPos;	//カメラ座標
	};

private:
	// デバイス
	static ID3D12Device* dev;
	// コマンドリスト
	static ID3D12GraphicsCommandList* cmdList;
	// パイプライン
	static PipelineSet pipelineSet;
	// カメラ
	static Camera* camera;

	// 定数バッファ
	ComPtr<ID3D12Resource> constBuffB0; 
	// 色
	XMFLOAT4 color = { 1,1,1,1 };
	// ローカルスケール
	Vector3 scale = { 1,1,1 };
	//回転クォータニオン
	Quaternion rotation = Quaternion::Identity();

	// ローカル座標
	Vector3 position = { 0,0,0 };
	// ローカルワールド変換行列
	XMMATRIX matWorld;
	// 親オブジェクト
	Object3D* parent = nullptr;
	// モデル
	Model* model = nullptr;
	// ビルボード
	bool isBillboard = false;

	//ワールド軸(回転用)　←そのうちなんとかする
	const Vector3 worldX = { 1,0,0 };
	const Vector3 worldY = { 0,1,0 };
	const Vector3 worldZ = { 0,0,1 };
	//ローカル軸(回転用)
	Vector3 sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, rotation));
	Vector3 upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, rotation));
	Vector3 forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, rotation));

public:
	//静的初期化
	static void StaticInitialize(ID3D12Device* dev, Camera* camera = nullptr);
	//描画前処理
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);
	//描画後処理
	static void PostDraw();
	//3Dオブジェクト生成
	static Object3D* Create(Model* model = nullptr);
	//カメラセット
	static void SetCamera(Camera* camera) {
		Object3D::camera = camera;
	}

	//初期化
	bool Initialize();
	//更新処理
	void Update();
	//描画
	void Draw(const Shader& shader);

	//座標取得
	const Vector3& GetPosition() { return position; }
	//座標設定
	void SetPosition(Vector3 position) { this->position = position; }
	//回転設定
	void SetRotation(Quaternion rotation) { this->rotation = rotation; }
	//回転クォータニオン取得
	const Quaternion& GetRotation() { return rotation; }
	//ローカルX軸取得
	const Vector3& GetSide() { return sideAxis; }
	//ローカルY軸取得
	const Vector3& GetUp() { return upAxis; }
	//ローカルZ軸取得
	const Vector3& GetForword() { return forwordAxis; }
	//ベクトルで回転
	void RotationVector(const Vector3& RollPitchYow);
	//クォータニオンで回転
	void RotationQuaternion(const Quaternion& q);
	
	//スケール設定
	void SetScale(Vector3 scale) { this->scale = scale; }
	//モデルセット
	void SetModel(Model* model) { this->model = model; }
	//ビルボードする？
	void SetBillboard(bool isBillboard) { this->isBillboard = isBillboard; }
	//Quaternion bill = Quaternion::Identity();
};