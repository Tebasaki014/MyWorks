#include"Scene.h"

Scene::Scene(CommonData* commonData, SceneViewer* viewer)
{
	this->commonData = commonData;
	this->wangine = commonData->wangine;
	this->input = wangine->input;
	this->camera = wangine->camera;
	this->viewer = viewer;
}

void Scene::ChangeScene(Scene* pNewScene)
{
	viewer->ChangeScene(pNewScene);
}