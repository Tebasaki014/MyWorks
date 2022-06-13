#include"SceneViewer.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//¢Š«–‚–@
	SceneViewer::GetInstance()->Initialize();

	while (true)
	{
		//XVˆ—
		SceneViewer::GetInstance()->Update();
		//•`‰æˆ—
		if (!SceneViewer::GetInstance()->Draw()) { break; }
	}
	SceneViewer::GetInstance()->End();

	return 0;
}