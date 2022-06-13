#pragma once
#include<memory>

//�V���O���g��
template<class T>
class Singleton
{
protected:
	//�R���X�g���N�^
	Singleton() = default;
	//�R�s�[�֎~
	Singleton& operator=(const Singleton&) = delete;
	Singleton(const Singleton&) = delete;
	//�f�X�g���N�^
	virtual ~Singleton() = default;
	//�C���X�^���X
	static T* instance;

public:

	//�C���X�^���X�擾(�Ȃ���ΐ������Ď擾)
	static inline T* GetInstance() {
		if (!instance) {
			instance = new T();
		}

		return instance;
	}

	//�C���X�^���X�j��
	static inline void Destroy() {
		if (instance) {
			delete instance;
		}
	}
};



//�V���O���g��(�C���X�^���X��unique_ptr)
template<class T>
class Singleton_Unique
{
protected:
	//�R���X�g���N�^
	Singleton_Unique() = default;
	//�R�s�[�֎~
	Singleton_Unique& operator=(const Singleton_Unique&) = delete;
	Singleton_Unique(const Singleton_Unique&) = delete;
	//�C���X�^���X
	static std::unique_ptr<T> instance;

public:

	//�C���X�^���X�擾(�Ȃ���ΐ������Ď擾)
	static inline T* GetInstance() {
		if (!instance) {
			instance.reset(new T());
		}

		return instance.get();
	}
};



//�V���O���g��(�C���X�^���X��shared_ptr)
template<class T>
class Singleton_Shared
{
protected:
	//�R���X�g���N�^
	Singleton_Shared() = default;
	//�R�s�[�֎~
	Singleton_Shared& operator=(const Singleton_Shared&) = delete;
	Singleton_Shared(const Singleton_Shared&) = delete;
	//�C���X�^���X
	static std::shared_ptr<T> instance;

public:

	//�C���X�^���X�擾(�Ȃ���ΐ������Ď擾)
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