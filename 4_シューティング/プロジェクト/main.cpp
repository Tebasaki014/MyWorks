#include"SceneViewer.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//�������@
	SceneViewer* viewer = new SceneViewer();

	while (true)
	{
		//�X�V����
		viewer->Update();
		//�`�揈��
		if (!viewer->Draw()) { break; }
	}
	viewer->End();
	SDelete(viewer);
	return 0;
}