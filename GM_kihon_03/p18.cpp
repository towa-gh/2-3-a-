//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//
//int g_RankingImage;
//int g_WaitTime = 0;
//
//struct RankingData{
//	int no;
//    char name[11];
//	long score;
//};
//struct RankingData  g_Ranking[10] = {
//	{1,"**********",100000},
//	{2,"**********",500000},
//	{3,"**********",10000},
//	{4,"**********",5000},
//	{5,"**********",1000},
//	{6,"**********",500},
//	{7,"**********",100},
//	{8,"**********",50},
//	{9,"**********",10},
//	{10,"**********",5},
//};
//
//void DrawRanking(void);
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		if (g_KeyFlg & PAD_INPUT_M) break;
//
//		ClearDrawScreen();
//		DrawRanking();
//		ScreenFlip();
//
//	}
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}
//
//void DrawRanking(void) {
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	SetFontSize(30);
//	for (int i = 0; i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d   %10s   %10d",g_Ranking[i].no,g_Ranking[i].name,g_Ranking[i].score);
//	}
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "--Press[SPACE]Key--", 0x0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}