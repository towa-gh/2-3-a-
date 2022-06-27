//#include "DxLib.h"
//
//int g_LoopCount = 0;
//
//int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return -1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0) {
//
//		ClearDrawScreen();
//
//		DrawFormatString(0, 0, GetColor(255, 255, 255),
//			"LoopCount = %d", g_LoopCount++);
//
//		ScreenFlip();
//	}
//
//	DxLib_End();
//
//	return 0;
//}