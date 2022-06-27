//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_LoooCount = 0;
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//	
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while(ProcessMessage() == 0) {
//		ClearDrawScreen();
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "LoopCount=%d", g_LoooCount++);
//		ScreenFlip();
//	}
//
//
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}