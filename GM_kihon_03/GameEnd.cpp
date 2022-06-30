//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//int g_EndImage;
//int g_WaitTime = 0;
//int g_FadeIn = 0;
//
//void DrawEnd(void);
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_EndImage = LoadGraph("images/KadaiEnd.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0 && ++g_WaitTime < 900) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();
//		DrawEnd();
//		ScreenFlip();
//	}
//	
//	
//
//
//
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}
//void DrawEnd(void) {
//	if (++g_FadeIn >= 255) g_FadeIn = 255;
//
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	SetFontSize(20);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_FadeIn);
//
//	DrawString(110, 170 , "タイトル　　　〇〇〇 Game", 0x000000);
//	DrawString(110, 200 , "バージョン　　　2,0", 0x000000);
//	DrawString(110, 230 , "最終更新日　　　2018年07月01日", 0x000000);
//	DrawString(110, 260 , "制作者　　　国際電子ビジネス専門学校", 0x000000);
//	DrawString(110, 290 , "　　　　   国際太郎", 0x000000);
//	DrawString(110, 310 , "素材利用", 0x000000);
//	DrawString(110, 340 , "　BGM　　　　魔王魂", 0x000000);
//	DrawString(110, 365 , "　SE　　　　煉獄庭園", 0x000000);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}