#include "Camera.h"
using namespace DirectX;

Camera::Camera(int window_width, int window_height)
{
	aspectRatio = (float)window_width / window_height;
	//ビュー行列の計算
	UpdateViewMatrix();
	// 射影行列の計算
	UpdateProjectionMatrix();
	// ビュープロジェクションの合成
	matViewProjection = matView * matProjection;
}

void Camera::Update()
{
	if (viewDirty || projectionDirty) {
		// 再計算必要なら
		if (viewDirty) {
			// ビュー行列更新
			UpdateViewMatrix();
			viewDirty = false;
		}
		// 再計算必要なら
		if (projectionDirty) {
			// ビュー行列更新
			UpdateProjectionMatrix();
			projectionDirty = false;
		}
		// ビュープロジェクション合成
		matViewProjection = matView * matProjection;
	}
}

void Camera::UpdateViewMatrix()
{
	//視点座標
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	//注視点座標
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	//（仮の）上方向
	XMVECTOR upVector = XMLoadFloat3(&up);
	//Z軸（視線方向）
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	//0ベクトルだと向きが定まらないので除外
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	//正規化
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);
	XMStoreFloat3(&lookAt, cameraAxisZ);

	//X軸（右方向）
	XMVECTOR cameraAxisX;
	//上方向→Z軸の外積で求まる
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	//正規化
	cameraAxisX = XMVector3Normalize(cameraAxisX);
	XMStoreFloat3(&right, cameraAxisX);

	//Y軸（上方向）
	XMVECTOR cameraAxisY;
	//Z軸→X軸の外積で求まる
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
	XMStoreFloat3(&up, cameraAxisY);

	// カメラ回転行列
	XMMATRIX matCameraRot;
	// カメラ座標系→ワールド座標系の変換行列
	matCameraRot.r[0] = cameraAxisX;
	matCameraRot.r[1] = cameraAxisY;
	matCameraRot.r[2] = cameraAxisZ;
	matCameraRot.r[3] = XMVectorSet(0, 0, 0, 1);
	// 転置により逆行列（逆回転）を計算
	matView = XMMatrixTranspose(matCameraRot);
	// 視点座標に-1を掛けた座標
	XMVECTOR reverseEyePosition = XMVectorNegate(eyePosition);
	// カメラの位置からワールド原点へのベクトル（カメラ座標系）
	XMVECTOR tX = XMVector3Dot(cameraAxisX, reverseEyePosition);	// X成分
	XMVECTOR tY = XMVector3Dot(cameraAxisY, reverseEyePosition);	// Y成分
	XMVECTOR tZ = XMVector3Dot(cameraAxisZ, reverseEyePosition);	// Z成分
	// 一つのベクトルにまとめる
	XMVECTOR translation = XMVectorSet(tX.m128_f32[0], tY.m128_f32[1], tZ.m128_f32[2], 1.0f);
	// ビュー行列に平行移動成分を設定
	matView.r[3] = translation;

#pragma region 全方向ビルボード行列
	// ビルボード行列
	matBillboard.r[0] = cameraAxisX;
	matBillboard.r[1] = cameraAxisY;
	matBillboard.r[2] = cameraAxisZ;
	matBillboard.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma region

#pragma region Y軸回りビルボード行列
	// カメラX軸、Y軸、Z軸
	XMVECTOR ybillCameraAxisX, ybillCameraAxisY, ybillCameraAxisZ;
	// X軸は共通
	ybillCameraAxisX = cameraAxisX;
	// Y軸はワールド座標系のY軸
	ybillCameraAxisY = XMVector3Normalize(upVector);
	// Z軸はX軸→Y軸の外積で求まる
	ybillCameraAxisZ = XMVector3Cross(ybillCameraAxisX, ybillCameraAxisY);
	// Y軸回りビルボード行列
	matBillboardY.r[0] = ybillCameraAxisX;
	matBillboardY.r[1] = ybillCameraAxisY;
	matBillboardY.r[2] = ybillCameraAxisZ;
	matBillboardY.r[3] = XMVectorSet(0, 0, 0, 1);
#pragma endregion
}

void Camera::UpdateProjectionMatrix()
{
	// 透視投影による射影行列の生成
	matProjection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(60.0f),
		aspectRatio,
		0.1f, 1000.0f
	);
}

void Camera::MoveEyeVector(const Vector3& move)
{
	// 視点座標を移動し、反映
	Vector3 eye_moved = GetEye();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	SetEye(eye_moved);
}

void Camera::MoveVector(const Vector3& move)
{
	// 視点と注視点座標の移動、反映
	Vector3 eye_moved = GetEye();
	Vector3 target_moved = GetTarget();

	eye_moved.x += move.x;
	eye_moved.y += move.y;
	eye_moved.z += move.z;

	target_moved.x += move.x;
	target_moved.y += move.y;
	target_moved.z += move.z;

	SetEye(eye_moved);
	SetTarget(target_moved);
}

void Camera::RotateAroundTarget(const Vector2& angle)
{
	Vector3 position = GetEye();
	Vector3 targetp = GetTarget();
	Vector3 upv = GetUp();
	position = position - targetp;
	
	Quaternion qCameraRightAngle = Quaternion::RotationAxis(upv, angle.x);
	Vector3 cameraSide = upv.Cross(-position).Nomalize();
	Quaternion qCameraUpAngle = Quaternion::RotationAxis(cameraSide, angle.y);

	Quaternion q = qCameraRightAngle * qCameraUpAngle;

	Quaternion qCameraPos = { position.x, position.y, position.z, 0.0f };
	Quaternion qq = Quaternion::Conjugate(q);
	qCameraPos = q * qCameraPos * qq;

	Quaternion qCameraUp = { upv.x, upv.y, upv.z, 0.0f };
	qCameraUp = q * qCameraUp * qq;

	position = { qCameraPos.x, qCameraPos.y, qCameraPos.z };
	upv = { qCameraUp.x, qCameraUp.y, qCameraUp.z };

	SetEye(position + targetp);
	SetUp(upv);
}

void Camera::RotateAround(const Vector3& ankerPoint, const Vector2& angle)
{
	Vector3 position = GetEye();
	Vector3 targetp = GetTarget();
	Vector3 upv = GetUp();
	Vector3 rightv = GetRight();
	position = Quaternion::RotationAround(position, target, upv, angle.x);
	//upv = Quaternion::RotationAround(upv, position, rightv );

	Vector3 lookv = Vector3::Nomalize(targetp - position);
	rightv = Vector3::Nomalize(Vector3::Cross(upv, lookv));

	position = Quaternion::RotationAround(position, target, rightv, angle.y);

	lookv = targetp - position;
	upv = Vector3::Cross(lookv, rightv);
	upv.Nomalize();
	rightv = Vector3::Cross(upv, lookv);
	rightv.Nomalize();
}

void Camera::Rota(Quaternion angle)
{
	Quaternion qq = Quaternion::Conjugate(angle);
	Vector3 pos = GetEye();
	Quaternion qPos = { pos.x, pos.y, pos.z, 0.0f };

	qPos = angle * qPos * qq;

	pos = { qPos.x, qPos.y, qPos.z };

	SetEye(pos);
}