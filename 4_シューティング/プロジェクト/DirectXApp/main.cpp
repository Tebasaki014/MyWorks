#include"SceneViewer.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//�������@
	SceneViewer::GetInstance()->Initialize();

	while (true)
	{
		//�X�V����
		SceneViewer::GetInstance()->Update();
		//�`�揈��
		if (!SceneViewer::GetInstance()->Draw()) { break; }
	}
	SceneViewer::GetInstance()->End();

	return 0;
}