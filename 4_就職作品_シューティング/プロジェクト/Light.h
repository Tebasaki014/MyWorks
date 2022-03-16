#pragma once
#include"WatashiEngine.h"
class Light
{
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	//定数バッファ用
	struct ConstBufferData
	{
		Vector3 lightv;
		Vector3 lightcolor;
	};

	//インスタンス作成
	static Light* Create(ID3D12Device* device);

	//初期化
	void Initialize();
	//更新
	void Update();
	//描画(グラフィックスコマンド)
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootPrmIdx);
	//定数バッファへ
	void TransferBuffer();

	//インスタンス取得
	static inline Light* GetInstance() {
		if (instance == nullptr) {
			return nullptr;
		}
		else{
			return instance;
		}
	}
	//インスタンス破棄
	inline static void Destroy() {
		delete instance;
		instance = nullptr;
	}

	/* セッターの皆様 */
	//ライト向き指定
	inline void SetDirection(const Vector3& direction) {
		//正規化してポイ
		this->direc = Vector3::Nomalize(direction);
		dirty = true;
	}

	//ライト色指定
	inline void SetColor(const Vector3& color) {
		this->color = color;
		dirty = true;
	}

private:
	//デバイス
	static ID3D12Device* device;

	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト向きベクトル(正規化しろ)
	Vector3 direc = { 0,1,0 };
	//ライト色
	Vector3 color = { 1,1,1 };
	//ダーティ
	bool dirty = false;

	//static初期化
	Light(ID3D12Device* device);
	//ぽいぽい
	~Light() = default;

	//インスタンス
	static Light* instance;
};