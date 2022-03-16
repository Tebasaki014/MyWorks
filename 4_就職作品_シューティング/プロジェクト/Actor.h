#pragma once
#include"WatashiEngine.h"

//前方宣言(c4430防止)
class Object3D;
class Shader;

class Actor3D
{
public:
	//モデルパスを渡して生成
	Actor3D(std::string modelPath);
	//モデルのポインタを渡して生成
	Actor3D(Model* model);
	//モデルなしで生成(今のところは内部でモデルを生成する必要あり)
	Actor3D();
	//削除
	~Actor3D();

	//座標
	Vector3 position = {};
	//スケール
	Vector3 Scale = { 1.0f,1.0f,1.0f };
	//ビルボードフラグ
	bool billboordFlag = false;

	//初期化処理
	virtual void Start();
	//更新処理
	virtual void Update();
	//削除時処理
	virtual void End();

	//モデル描画
	virtual void Draw(const Shader& shader);
	//XYZ回転角で回転
	void RotationVector(const Vector3& RollPitchYow);
	//クォータニオンで直接回転
	void RotationQuaternion(const Quaternion& q);

	//ローカル軸X取得
	Vector3& GetSideAxis() { return sideAxis; }
	//ローカル軸Y取得
	Vector3& GetUpAxis() { return upAxis; }
	//ローカル軸Z取得
	Vector3& GetForWordAxis() { return forwordAxis; }
	//回転クォータニオン取得
	Quaternion& GetRotation() { return qLocal; }
	//回転クォータニオン設定
	void SetRotation(const Quaternion& q){
		this->qLocal = q;
	}

protected:
	//モデル更新
	void ModelUpdate();
	//ワールドXYZ
	const Vector3 worldX = { 1.0f, 0.0f, 0.0f };
	const Vector3 worldY = { 0.0f, 1.0f, 0.0f };
	const Vector3 worldZ = { 0.0f, 0.0f, 1.0f };
	Object3D* object = nullptr;
	Model* model = nullptr;

	//回転クォータニオン（バグりやすいのでprivate）
	Quaternion qLocal = Quaternion::Identity();
	//ローカル軸X
	Vector3 sideAxis = {};
	//ローカル軸Y
	Vector3 upAxis = {};
	//ローカル軸Z
	Vector3 forwordAxis = {};

	bool IsFixRotation = true;
};

//ほったらかし中
class Actor2D
{
	Sprite* sprite = nullptr;
	//static int textureCount;
	//Texture* spriteTex = nullptr;
public:
	Actor2D(Texture texIdx, const wchar_t* texturePath);
	~Actor2D();

	Vector2 position = {};
	float rotation = 0.0f;
	Vector2 Size = {};

	void Update();
	void Draw(DirectX::XMFLOAT4 color);

private:

};