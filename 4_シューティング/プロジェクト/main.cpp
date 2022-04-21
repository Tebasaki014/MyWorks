#include"SceneViewer.h"

int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {
	//¢Š«–‚–@
	SceneViewer* viewer = new SceneViewer();

	while (true)
	{
		//XVˆ—
		viewer->Update();
		//•`‰æˆ—
		if (!viewer->Draw()) { break; }
	}
	viewer->End();
	SDelete(viewer);
	return 0;
}