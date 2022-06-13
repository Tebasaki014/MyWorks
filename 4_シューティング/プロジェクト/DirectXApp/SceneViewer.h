#pragma once
#include"CommonData.h"
#include"Singleton.h"
#include"Actor.h"

#include"Scene.h"

class Scene;
struct CommonData;

//�V�[���؂�ւ��N���X
class SceneViewer : public Singleton_Unique<SceneViewer>
{
private:
	//�V���O���g������
	friend Singleton_Unique<SceneViewer>;
	SceneViewer() = default;
public:

	void ChangeScene(Scene* pNewScene);

	void Initialize();
	void End();

	void Update();
	bool Draw();
	
private:

	CommonData* commonData = nullptr;
	Scene* nowScene = nullptr;
};