#include "Sprite.h"
#include <cassert>
#include "d3dx12.h"
#include <d3dcompiler.h>
#include "DirectXTex.h"

#pragma comment(lib, "d3dcompiler.lib")

using namespace DirectX;
using namespace Microsoft::WRL;

ID3D12Device* Sprite::device = nullptr;
UINT Sprite::descriptorHandleIncrementSize;
ID3D12GraphicsCommandList* Sprite::cmdList = nullptr;
ComPtr<ID3D12RootSignature> Sprite::rootSignature;
ComPtr<ID3D12PipelineState> Sprite::pipelineState;
XMMATRIX Sprite::matProjection;
ComPtr<ID3D12DescriptorHeap> Sprite::descHeap;
ComPtr<ID3D12Resource> Sprite::texBuff[srvCount];

void Sprite::TransferVertices()
{
	HRESULT result = S_FALSE;

	//左下、左上、右下、右上
	enum { LB, LT, RB, RT };

	float left = (0.0f - anchorpoint.x) * size.x;
	float right = (1.0f - anchorpoint.x) * size.x;
	float top = (0.0f - anchorpoint.x) * size.y;
	float bottom = (1.0f - anchorpoint.x) * size.y;
	if (isFlipX)
	{//左右反転
		left = -left;
		right = -right;
	}

	if (isFlipY)
	{//上下反転
		top = -top;
		bottom = -bottom;
	}

	//頂点データ
	VertexPosUv vertices[vertNum];

	vertices[LB].pos = { left,	bottom,	0.0f }; // 左下
	vertices[LT].pos = { left,	top,	0.0f }; // 左上
	vertices[RB].pos = { right,	bottom,	0.0f }; // 右下
	vertices[RT].pos = { right,	top,	0.0f }; // 右上

	//テクスチャ情報取得
	if (texBuff[tex])
	{
		D3D12_RESOURCE_DESC resDesc = texBuff[tex]->GetDesc();

		float tex_left = texBase.x / resDesc.Width;
		float tex_right = (texBase.x + texSize.x) / resDesc.Width;
		float tex_top = texBase.y / resDesc.Height;
		float tex_bottom = (texBase.y + texSize.y) / resDesc.Height;

		vertices[LB].uv = { tex_left,	tex_bottom }; // 左下
		vertices[LT].uv = { tex_left,	tex_top }; // 左上
		vertices[RB].uv = { tex_right,	tex_bottom }; // 右下
		vertices[RT].uv = { tex_right,	tex_top }; // 右上
	}

	//頂点バッファへのデータ転送
	VertexPosUv* vertMap = nullptr;
	result = vertBuff->Map(0, nullptr, (void**)&vertMap);
	if (SUCCEEDED(result)) {
		memcpy(vertMap, vertices, sizeof(vertices));
		vertBuff->Unmap(0, nullptr);
	}
}

bool Sprite::StaticInitialize(ID3D12Device* device, int window_width, int window_height)
{
	//nullptr?
	assert(device);

	Sprite::device = device;
	//for (unsigned short i = 0; i < srvCount; i++) {
	//	texLimit[i] = false;
	//}

	//デスクリプタサイズ
	descriptorHandleIncrementSize = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);

	HRESULT result = S_FALSE;
	ComPtr<ID3DBlob> vsBlob; // 頂点シェーダオブジェクト
	ComPtr<ID3DBlob> psBlob;	// ピクセルシェーダオブジェクト
	ComPtr<ID3DBlob> errorBlob; // エラーオブジェクト

	//頂点シェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/SpriteVS.hlsl",	//シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //インクルード可能にする
		"main", "vs_5_0",	//エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //デバッグ用設定
		0,
		&vsBlob, &errorBlob);
	if (FAILED(result)) {
		//errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());

		return false;
	}

	//ピクセルシェーダの読み込みとコンパイル
	result = D3DCompileFromFile(
		L"Resources/Shaders/SpritePS.hlsl",	//シェーダファイル名
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE, //インクルード可能にする
		"main", "ps_5_0",	//エントリーポイント名、シェーダーモデル指定
		D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION, //デバッグ用設定
		0,
		&psBlob, &errorBlob);
	if (FAILED(result)) {
		//errorBlobからエラー内容をstring型にコピー
		std::string errstr;
		errstr.resize(errorBlob->GetBufferSize());

		std::copy_n((char*)errorBlob->GetBufferPointer(),
			errorBlob->GetBufferSize(),
			errstr.begin());
		errstr += "\n";
		//エラー内容を出力ウィンドウに表示
		OutputDebugStringA(errstr.c_str());

		return false;
	}

	//頂点レイアウト
	D3D12_INPUT_ELEMENT_DESC inputLayout[] = {
		{ //xy座標
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
		{ //uv座標
			"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0,
			D3D12_APPEND_ALIGNED_ELEMENT,
			D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0
		},
	};

	//グラフィックスパイプライン設定
	D3D12_GRAPHICS_PIPELINE_STATE_DESC gpipeline{};
	gpipeline.VS = CD3DX12_SHADER_BYTECODE(vsBlob.Get());
	gpipeline.PS = CD3DX12_SHADER_BYTECODE(psBlob.Get());

	//サンプルマスク
	gpipeline.SampleMask = D3D12_DEFAULT_SAMPLE_MASK; // 標準設定
	//ラスタライザステート
	gpipeline.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	gpipeline.RasterizerState.CullMode = D3D12_CULL_MODE_NONE;
	//デプスステンシルステート
	gpipeline.DepthStencilState = CD3DX12_DEPTH_STENCIL_DESC(D3D12_DEFAULT);
	gpipeline.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_ALWAYS; // 常に上書きルール

	//ブレンド
	D3D12_RENDER_TARGET_BLEND_DESC blenddesc{};
	blenddesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;	// RBGA全てのチャンネルを描画
	blenddesc.BlendEnable = true;
	blenddesc.BlendOp = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
	blenddesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;

	blenddesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
	blenddesc.SrcBlendAlpha = D3D12_BLEND_ONE;
	blenddesc.DestBlendAlpha = D3D12_BLEND_ZERO;

	//ブレンドステート設定
	gpipeline.BlendState.RenderTarget[0] = blenddesc;

	//深度バッファのフォーマット
	gpipeline.DSVFormat = DXGI_FORMAT_D32_FLOAT;

	//頂点レイアウト設定
	gpipeline.InputLayout.pInputElementDescs = inputLayout;
	gpipeline.InputLayout.NumElements = _countof(inputLayout);

	//図形の形状設定（三角形）
	gpipeline.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;

	gpipeline.NumRenderTargets = 1;	//描画対象1つ
	gpipeline.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM; //0〜255指定のRGBA
	gpipeline.SampleDesc.Count = 1; //1ピクセルにつき1回サンプリング

	//デスクリプタレンジ
	CD3DX12_DESCRIPTOR_RANGE descRangeSRV;
	descRangeSRV.Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 1, 0); //t0 レジスタ

	//ルートパラメータ
	CD3DX12_ROOT_PARAMETER rootparams[2] = { CD3DX12_ROOT_PARAMETER() };
	rootparams[0].InitAsConstantBufferView(0, 0, D3D12_SHADER_VISIBILITY_ALL);
	rootparams[1].InitAsDescriptorTable(1, &descRangeSRV, D3D12_SHADER_VISIBILITY_ALL);

	//スタティックサンプラー
	CD3DX12_STATIC_SAMPLER_DESC samplerDesc = CD3DX12_STATIC_SAMPLER_DESC(0, D3D12_FILTER_MIN_MAG_MIP_POINT); // s0 レジスタ

	//ルートシグネチャの設定
	CD3DX12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc;
	rootSignatureDesc.Init_1_0(_countof(rootparams), rootparams, 1, &samplerDesc, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);

	ComPtr<ID3DBlob> rootSigBlob;
	//バージョン自動判定のシリアライズ
	result = D3DX12SerializeVersionedRootSignature(&rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1_0, &rootSigBlob, &errorBlob);
	if (FAILED(result)) {
		assert(0);
		return false;
	}
	//ルートシグネチャの生成
	result = device->CreateRootSignature(0, rootSigBlob->GetBufferPointer(), rootSigBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	gpipeline.pRootSignature = rootSignature.Get();

	//グラフィックスパイプラインの生成
	result = device->CreateGraphicsPipelineState(&gpipeline, IID_PPV_ARGS(&pipelineState));

	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//射影行列計算
	matProjection = XMMatrixOrthographicOffCenterLH(
		0.0f, (float)window_width,
		(float)window_height, 0.0f,
		0.0f, 1.0f);

	//デスクリプタヒープ生成	
	D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc = {};
	descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
	descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;//シェーダから見えるように
	descHeapDesc.NumDescriptors = srvCount;
	result = device->CreateDescriptorHeap(&descHeapDesc, IID_PPV_ARGS(&descHeap));//生成
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	return true;
}

bool Sprite::LoadTexture(Texture tex, const wchar_t* filename)
{
	// nullptr?
	assert(device);

	HRESULT result;

	////テクスチャ番号割り当て
	//for (unsigned short i = 0; i < srvCount; i++) {
	//	if (!texLimit[i]) { 
	//		tex = i; 
	//		texLimit[i] = true;
	//		break;
	//	}
	//}

	//WICテクスチャのロード
	TexMetadata metadata{};
	ScratchImage scratchImg{};

	result = LoadFromWICFile(
		filename, WIC_FLAGS_NONE,
		&metadata, scratchImg);
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	const Image* img = scratchImg.GetImage(0, 0, 0); //生データ抽出

	//リソース設定
	CD3DX12_RESOURCE_DESC texresDesc = CD3DX12_RESOURCE_DESC::Tex2D(
		metadata.format,
		metadata.width,
		(UINT)metadata.height,
		(UINT16)metadata.arraySize,
		(UINT16)metadata.mipLevels
	);

	//テクスチャ用バッファの生成
	auto a = CD3DX12_HEAP_PROPERTIES(D3D12_CPU_PAGE_PROPERTY_WRITE_BACK, D3D12_MEMORY_POOL_L0);
	result = device->CreateCommittedResource(
		&a,
		D3D12_HEAP_FLAG_NONE,
		&texresDesc,
		D3D12_RESOURCE_STATE_GENERIC_READ, //テクスチャ用指定
		nullptr,
		IID_PPV_ARGS(&texBuff[tex]));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//テクスチャバッファにデータ転送
	result = texBuff[tex]->WriteToSubresource(
		0,
		nullptr, //全領域へコピー
		img->pixels,    //元データアドレス
		(UINT)img->rowPitch,  //1ラインサイズ
		(UINT)img->slicePitch //1枚サイズ
	);
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//シェーダリソースビュー作成
	D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc{}; //設定構造体
	D3D12_RESOURCE_DESC resDesc = texBuff[tex]->GetDesc();

	srvDesc.Format = resDesc.Format;
	srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;//2Dテクスチャ
	srvDesc.Texture2D.MipLevels = 1;

	device->CreateShaderResourceView(texBuff[tex].Get(), //ビューと関連付けるバッファ
		&srvDesc, //テクスチャ設定情報
		CD3DX12_CPU_DESCRIPTOR_HANDLE(descHeap->GetCPUDescriptorHandleForHeapStart(), tex, descriptorHandleIncrementSize)
	);

	return true;
}

void Sprite::PreDraw(ID3D12GraphicsCommandList* cmdList)
{
	//PreDrawとPostDrawがペアで呼ばれていなければエラー
	assert(Sprite::cmdList == nullptr);

	//コマンドリストをセット
	Sprite::cmdList = cmdList;

	//パイプラインステート
	cmdList->SetPipelineState(pipelineState.Get());
	//ルートシグネチャ
	cmdList->SetGraphicsRootSignature(rootSignature.Get());
	//プリミティブ形状
	cmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}

void Sprite::PostDraw()
{
	// コマンドリスト解除
	Sprite::cmdList = nullptr;
}

Sprite* Sprite::Create(Texture tex, Vector2 position, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
{
	//仮サイズ
	Vector2 size = { 100.0f, 100.0f };

	if (texBuff[tex])
	{
		//テクスチャ情報
		D3D12_RESOURCE_DESC resDesc = texBuff[tex]->GetDesc();
		//スプライトのサイズをテクスチャのサイズに設定
		size = { (float)resDesc.Width, (float)resDesc.Height };
	}

	//Spriteインスタンス
	Sprite* sprite = new Sprite(tex, position, size, color, anchorpoint, isFlipX, isFlipY);
	if (sprite == nullptr) {
		return nullptr;
	}

	//初期化
	if (!sprite->Initialize()) {
		delete sprite;
		assert(0);
		return nullptr;
	}

	return sprite;
}

Sprite::Sprite(Texture tex, Vector2 position, Vector2 size, XMFLOAT4 color, Vector2 anchorpoint, bool isFlipX, bool isFlipY)
{
	this->position = position;
	this->size = size;
	this->anchorpoint = anchorpoint;
	this->matWorld = XMMatrixIdentity();
	this->color = color;
	this->tex = tex;
	this->isFlipX = isFlipX;
	this->isFlipY = isFlipY;
	this->texSize = size;
}

bool Sprite::Initialize()
{
	//nullptr?
	assert(device);

	HRESULT result = S_FALSE;

	//頂点バッファ
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer(sizeof(VertexPosUv) * vertNum),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&vertBuff));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//頂点バッファにデータ転送
	TransferVertices();

	//頂点バッファビュー
	vbView.BufferLocation = vertBuff->GetGPUVirtualAddress();
	vbView.SizeInBytes = sizeof(VertexPosUv) * 4;
	vbView.StrideInBytes = sizeof(VertexPosUv);

	//定数バッファ
	result = device->CreateCommittedResource(
		&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),//アップロード可能
		D3D12_HEAP_FLAG_NONE,
		&CD3DX12_RESOURCE_DESC::Buffer((sizeof(ConstBufferData) + 0xff) & ~0xff),
		D3D12_RESOURCE_STATE_GENERIC_READ,
		nullptr,
		IID_PPV_ARGS(&constBuff));
	if (FAILED(result)) {
		assert(0);
		return false;
	}

	//定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	result = constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->color = color;
		constMap->mat = matProjection;
		constBuff->Unmap(0, nullptr);
	}

	return true;
}

void Sprite::SetRotation(float rotation)
{
	this->rotation = rotation;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetPosition(Vector2 position)
{
	this->position = position;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetSize(Vector2 size)
{
	this->size = size;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetAnchorPoint(Vector2 anchorpoint)
{
	this->anchorpoint = anchorpoint;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetIsFlipX(bool isFlipX)
{
	this->isFlipX = isFlipX;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetIsFlipY(bool isFlipY)
{
	this->isFlipY = isFlipY;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::SetTextureRect(Vector2 texBase, Vector2 texSize)
{
	this->texBase = texBase;
	this->texSize = texSize;
	//頂点バッファへ
	TransferVertices();
}

void Sprite::Draw(XMFLOAT4 dcolor)
{
	//ワールド行列更新
	this->matWorld = XMMatrixIdentity();
	this->matWorld *= XMMatrixRotationZ(XMConvertToRadians(rotation));
	this->matWorld *= XMMatrixTranslation(position.x, position.y, 0.0f);

	//定数バッファにデータ転送
	ConstBufferData* constMap = nullptr;
	HRESULT result = this->constBuff->Map(0, nullptr, (void**)&constMap);
	if (SUCCEEDED(result)) {
		constMap->color = dcolor;
		constMap->mat = this->matWorld * matProjection;	// 行列の合成	
		this->constBuff->Unmap(0, nullptr);
	}

	//頂点バッファ設定
	cmdList->IASetVertexBuffers(0, 1, &this->vbView);

	//デスクリプタヒープ
	ID3D12DescriptorHeap* ppHeaps[] = { descHeap.Get() };
	cmdList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
	//定数バッファビュー
	cmdList->SetGraphicsRootConstantBufferView(0, this->constBuff->GetGPUVirtualAddress());
	//シェーダリソースビュー
	cmdList->SetGraphicsRootDescriptorTable(1, CD3DX12_GPU_DESCRIPTOR_HANDLE(descHeap->GetGPUDescriptorHandleForHeapStart(), this->tex, descriptorHandleIncrementSize));
	//描画コマンド
	cmdList->DrawInstanced(4, 1, 0, 0);
}