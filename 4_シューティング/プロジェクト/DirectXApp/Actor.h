#pragma once
#include"WatashiEngine.h"

//�O���錾(c4430�h�~)
class Object3D;
class Shader;

class Actor3D
{
public:
	//���f���p�X��n���Đ���
	Actor3D(std::string modelPath);
	//���f���̃|�C���^��n���Đ���
	Actor3D(Model* model);
	//���f���Ȃ��Ő���(���̂Ƃ���͓����Ń��f���𐶐�����K�v����)
	Actor3D();
	//�폜
	~Actor3D();

	//���W
	Vector3 position = {};
	//�X�P�[��
	Vector3 Scale = { 1.0f,1.0f,1.0f };
	//�r���{�[�h�t���O
	bool billboordFlag = false;

	//����������
	virtual void Start();
	//�X�V����
	virtual void Update();
	//�폜������
	virtual void End();

	//���f���`��
	virtual void Draw(const Shader& shader);
	//XYZ��]�p�ŉ�]
	void RotationVector(const Vector3& RollPitchYow);
	//�N�H�[�^�j�I���Œ��ډ�]
	void RotationQuaternion(const Quaternion& q);

	//���[�J����X�擾
	Vector3& GetSideAxis() { return sideAxis; }
	//���[�J����Y�擾
	Vector3& GetUpAxis() { return upAxis; }
	//���[�J����Z�擾
	Vector3& GetForWordAxis() { return forwordAxis; }
	//��]�N�H�[�^�j�I���擾
	Quaternion& GetRotation() { return qLocal; }
	//��]�N�H�[�^�j�I���ݒ�
	void SetRotation(const Quaternion& q){
		this->qLocal = q;
	}

protected:
	//���f���X�V
	void ModelUpdate();
	//���[���hXYZ
	const Vector3 worldX = { 1.0f, 0.0f, 0.0f };
	const Vector3 worldY = { 0.0f, 1.0f, 0.0f };
	const Vector3 worldZ = { 0.0f, 0.0f, 1.0f };
	Object3D* object = nullptr;
	Model* model = nullptr;

	//��]�N�H�[�^�j�I���i�o�O��₷���̂�private�j
	Quaternion qLocal = Quaternion::Identity();
	//���[�J����X
	Vector3 sideAxis = {};
	//���[�J����Y
	Vector3 upAxis = {};
	//���[�J����Z
	Vector3 forwordAxis = {};

	bool IsFixRotation = true;
};

//�ق����炩����
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