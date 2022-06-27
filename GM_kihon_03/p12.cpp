//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//int g_EndImage;
//int g_WaitTime;
//int g_PosY;
//
//void DrawEnd(void);
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0 && g_WaitTime < 900) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();
//
//		DrawEnd();
//
//		ScreenFlip();
//	}
//
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}
//
//void DrawEnd(void) {
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	SetFontSize(20);
//
//    if(++g_WaitTime<600) g_PosY = 300 - g_WaitTime / 2;
//
//	DrawString(110, 170 + g_PosY, "タイトル　　　〇〇〇 Game", 0x000000);
//	DrawString(110,200+g_PosY,"バージョン　　　2,0",0x000000);
//	DrawString(110,230+g_PosY,"最終更新日　　　2018年07月01日",0x000000);
//	DrawString(110,260+g_PosY,"制作者　　　国際電子ビジネス専門学校",0x000000);
//	DrawString(110, 290 + g_PosY, "　　　　   国際太郎", 0x000000);
//	DrawString(110, 310 + g_PosY, "素材利用", 0x000000);
//	DrawString(110, 340 + g_PosY, "　BGM　　　　魔王魂", 0x000000);
//	DrawString(110, 365 + g_PosY, "　SE　　　　煉獄庭園", 0x000000);
//
//}