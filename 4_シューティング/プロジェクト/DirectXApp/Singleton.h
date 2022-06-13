#pragma once
#include<memory>

//シングルトン
template<class T>
class Singleton
{
protected:
	//コンストラクタ
	Singleton() = default;
	//コピー禁止
	Singleton& operator=(const Singleton&) = delete;
	Singleton(const Singleton&) = delete;
	//デストラクタ
	virtual ~Singleton() = default;
	//インスタンス
	static T* instance;

public:

	//インスタンス取得(なければ生成して取得)
	static inline T* GetInstance() {
		if (!instance) {
			instance = new T();
		}

		return instance;
	}

	//インスタンス破棄
	static inline void Destroy() {
		if (instance) {
			delete instance;
		}
	}
};



//シングルトン(インスタンスがunique_ptr)
template<class T>
class Singleton_Unique
{
protected:
	//コンストラクタ
	Singleton_Unique() = default;
	//コピー禁止
	Singleton_Unique& operator=(const Singleton_Unique&) = delete;
	Singleton_Unique(const Singleton_Unique&) = delete;
	//インスタンス
	static std::unique_ptr<T> instance;

public:

	//インスタンス取得(なければ生成して取得)
	static inline T* GetInstance() {
		if (!instance) {
			instance.reset(new T());
		}

		return instance.get();
	}
};



//シングルトン(インスタンスがshared_ptr)
template<class T>
class Singleton_Shared
{
protected:
	//コンストラクタ
	Singleton_Shared() = default;
	//コピー禁止
	Singleton_Shared& operator=(const Singleton_Shared&) = delete;
	Singleton_Shared(const Singleton_Shared&) = delete;
	//インスタンス
	static std::shared_ptr<T> instance;

public:

	//インスタンス取得(なければ生成して取得)
	static inline T* GetInstance() {
		if (!instance) {
			instance.reset(new T());
		}

		return instance.get();
	}
};

template< typename T > T* Singleton<T>::instance = nullptr;
template< typename T > std::unique_ptr<T> Singleton_Unique<T>::instance = nullptr;
template< typename T > std::shared_ptr<T> Singleton_Shared<T>::instance = nullptr;