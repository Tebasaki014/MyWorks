#include "Object3D.h"
#include <d3dcompiler.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace std;

ID3D12Device* Object3D::dev = nullptr;
ID3D12GraphicsCommandList* Object3D::cmdList = nullptr;
Object3D::PipelineSet Object3D::pipelineSet;
Camera* Object3D::camera = nullptr;

void Object3D::StaticInitialize(ID3D12Device* dev, Camera* camera)
{
	//再初期化チェック
	assert(!Object3D::dev);

	//nullptrチェック
	assert(dev);

	Object3D::dev = dev;
	Object3D::camera = camera;

	//モデルの静的初期化
	Model::StaticInitialize(dev);
}

void Object3D::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	//PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Object3D::cmdList == nullptr);
	//コマンドリストをセット
	Object3D::cmdList = cmdList;
	//プリミティブ形状を設定
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void Object3D::PostDraw()
{
	//コマンドリスト解除
	Object3D::cmdList = nullptr;
}

Object3D* Object3D::Create(Model* model)
{
	//3Dオブジェクトのインスタンスを生成
	Object3D* object3D = new Object3D();
	if (object3D == nullptr) {
		return nullptr;
	}

	//初期化
	if (!object3D->Initialize()) {
		delete object3D;
		assert(0);
	}

	if (model) {
		object3D->SetModel(model);
	}

	return object3D;
}

bool Object3D::Initialize()
{
	//nullptrチェック
	assert(dev);
	HRESULT result;
	//定数バッファ
	result = dev->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD), 	//アップロード可
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferDataB0) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuffB0));

	return true;
}

void Object3D::Update()
{
	assert(camera);

	HRESULT result;
	XMMATRIX matScale, matRot,matTrans;

	if (isBillboard) {
		const Quaternion bill = Quaternion::QuaternionRotationMatrix(camera->GetBillboardMatrix());
		rotation = rotation * bill;
	}

	// スケール、回転、平行移動行列の計算
	matScale = XMMatrixScaling(scale.x, scale.y, scale.z);
	matRot = XMMatrixIdentity();
	matRot = Quaternion::MatrixRotationQuaternion(rotation);
	matTrans = XMMatrixTranslation(position.x, position.y, position.z);
	// ワールド行列の合成
	matWorld = XMMatrixIdentity(); //リセット
	matWorld *= matScale; //スケール
	matWorld *= matRot; //回転
	matWorld *= matTrans; //平行移動


	//親オブジェクトがあれば
	if (parent != nullptr) {
		//親オブジェクトのワールド行列を掛ける
		matWorld *= parent->matWorld;
	}

	const XMMATRIX& matViewProjection = camera->GetViewProjectionMatrix();

	// 定数バッファへデータ転送
	ConstBufferDataB0* constMap = nullptr;
	result = constBuffB0->Map(0, nullptr, (void**)&constMap);
	constMap->viewproj = matViewProjection;	//ビュー行列
	constMap->world = matWorld;				//ワールド行列
	constMap->cameraPos = camera->GetEye();	//カメラ座標
	constBuffB0->Unmap(0, nullptr);

	camera->Update();

	//ローカル軸を回転
	sideAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldX, rotation));
	upAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldY, rotation));
	forwordAxis = Quaternion::GetAxis(Quaternion::RotationVector(worldZ, rotation));
}

void Object3D::Draw(const Shader& shader)
{
	//nullptrチェック
	assert(dev);
	assert(Object3D::cmdList);

	//モデルの割り当てがなければ描画しない
	if (model == nullptr) {
		return;
	}

	//パイプラインステート
	//cmdList->SetPipelineState(pipelineSet.pipelinestate.Get());
	cmdList->SetPipelineState(shader.pipelinestate.Get());
	//ルートシグネチャ
	cmdList->SetGraphicsRootSignature(shader.rootsignature.Get());
	//定数バッファビュー
	cmdList->SetGraphicsRootConstantBufferView(0, constBuffB0->GetGPUVirtualAddress());

	//ライトの描画コマンド
	Light::GetInstance()->Draw(cmdList, 3);
	//描画
	model->Draw(cmdList);
}

void Object3D::RotationVector(const Vector3& RollPitchYow)
{
	Quaternion qRoll = Quaternion::RotationAxis(upAxis, RollPitchYow.x);
	Quaternion qPitch = Quaternion::RotationAxis(sideAxis, RollPitchYow.y);
	Quaternion qYow = Quaternion::RotationAxis(forwordAxis, RollPitchYow.z);

	rotation = qRoll * rotation;
	rotation = qPitch * rotation;
	rotation = qYow * rotation;
}

void Object3D::RotationQuaternion(const Quaternion& q)
{
	rotation = q * rotation;
}