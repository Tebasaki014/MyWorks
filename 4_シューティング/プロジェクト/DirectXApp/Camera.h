#pragma once
#include "Vector2.h"
#include "Vector3.h"
#include "Quaternion.h"

class Camera
{
protected:
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

	//ビュー行列
	XMMATRIX matView = DirectX::XMMatrixIdentity();
	//ビルボード行列
	XMMATRIX matBillboard = DirectX::XMMatrixIdentity();
	//Y軸回りビルボード行列
	XMMATRIX matBillboardY = DirectX::XMMatrixIdentity();
	//射影行列
	XMMATRIX matProjection = DirectX::XMMatrixIdentity();
	//ビュー射影行列
	XMMATRIX matViewProjection = DirectX::XMMatrixIdentity();
	//ビュー行列ダーティフラグ
	bool viewDirty = false;
	//射影行列ダーティフラグ
	bool projectionDirty = false;
	//視点座標
	Vector3 eye = { 0, 0, -20 };
	//注視点座標
	Vector3 target = { 0, 0, 0 };
	//上方向
	Vector3 up = { 0, 1, 0 };
	//右方向
	Vector3 right = { 1, 0, 0 };
	//視線方向
	Vector3 lookAt = { 0, 0, 1 };
	//ワールド座標Y
	const Vector3 worldY = { 0, 1, 0 };
	//アスペクト比
	float aspectRatio = 1.0f;

public:

	Camera(int window_width, int window_height);
	virtual ~Camera() = default;

	//更新
	virtual void Update();
	//ビュー行列更新
	void UpdateViewMatrix();
	//射影行列更新
	void UpdateProjectionMatrix();
	//ビュー行列取得
	inline const XMMATRIX& GetViewMatrix() {
		return matView;
	}
	//射影行列取得
	inline const XMMATRIX& GetProjectionMatrix() {
		return matProjection;
	}
	//ビュー射影行列取得
	inline const XMMATRIX& GetViewProjectionMatrix() {
		return matViewProjection;
	}
	//ビルボード行列取得
	inline const XMMATRIX& GetBillboardMatrix() {
		return matBillboard;
	}
	//注視点座標取得
	inline const Vector3& GetEye() {
		return eye;
	}
	//視点座標設定
	inline void SetEye(Vector3 eye) {
		this->eye = eye; viewDirty = true;
	}
	//注視点座標取得
	inline const Vector3& GetTarget() {
		return target;
	}
	//注視点座標設定
	inline void SetTarget(Vector3 target) {
		this->target = target; viewDirty = true;
	}
	//上方向取得
	inline const Vector3& GetUp() {
		return up;
	}
	//右方向取得
	inline const Vector3& GetRight() {
		return right;
	}
	//視線方向取得
	inline const Vector3& GetLook() {
		return lookAt;
	}
	//上方向
	inline void SetUp(Vector3 up) {
		this->up = up; viewDirty = true;
	}
	//右方向
	inline void SetRight(Vector3 right) {
		this->right = right; viewDirty = true;
	}
	//注視点ごと移動
	void MoveEyeVector(const Vector3 & move);
	//本体だけ移動
	void MoveVector(const Vector3 & move);
	//注視点を中心に回転
	void RotateAroundTarget(const Vector2& angle);
	//ある点を中心に回転
	void RotateAround(const Vector3& ankerPoint, const Vector2& angle);

	void Rota(Quaternion angle);
};