#pragma once
#include"SceneViewer.h"

class SceneViewer;

//�V�[�����N���X
class Scene
{
public:
	Scene(CommonData* commonData, SceneViewer* viewer);
	virtual ~Scene() = default;
	void ChangeScene(Scene* pNewScene);

	//����4���I�[�o�[���C�h
	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void End() = 0;
protected:
	CommonData* commonData = nullptr;
	SceneViewer* viewer = nullptr;
	WatashiEngine* wangine = nullptr;
	Input* input = nullptr;
	Camera* camera = nullptr;
};