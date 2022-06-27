//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//int g_MenuNumber = 0;
//int g_MouseX;
//int g_MouseY;
//int g_TitleImage;
//
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_TitleImage = LoadGraph("images/Title2.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	SetMouseDispFlag(TRUE);
//
//	while (ProcessMessage() == 0) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//			GetMousePoint(&g_MouseX, &g_MouseY);
//			g_MenuNumber = 9;
//
//			if (g_MouseX > 120 && g_MouseX < 210 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 0;
//			}
//			if (g_MouseX > 300 && g_MouseX < 410 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 1;
//			}
//			if (g_MouseX > 510 && g_MouseX < 555 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 2;
//			}
//		}
//		ClearDrawScreen();
//
//		DrawGraph(0, 0, g_TitleImage, FALSE);
//
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "MenuNumber=%d", g_MenuNumber);
//
//		ScreenFlip();
//	}
//	
//
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}