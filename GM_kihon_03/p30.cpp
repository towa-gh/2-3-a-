//#include"DxLib.h"
////プログラムはWinMainから始まります
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//
//int g_RankingImage;
//int g_WaitTime = 0;
//
//int g_Score = 3500;
//
//int g_GameState = 1;
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
//struct RankingData  g_Ranking[10] = {
//	{1,"**********",100000},
//	{2,"**********",50000},
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
//void InputRanking(void);
//void SortRanking(void);
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
//		
//		switch (g_GameState) {
//		     case 0:
//				DrawRanking();
//				break;
//
//		     case 1:
//				 InputRanking();
//				 break;
//		}
//
//
//		ScreenFlip();
//
//	}
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}
//
//void SortRanking(void) {
//	RankingData work;
//
//	for (int i = 0; i < 9; i++) {
//		for (int j = i + 1; j < 10; j++) {
//			if (g_Ranking[i].score <= g_Ranking[j].score) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//
//	for (int i = 0; i < 10; i++) {
//		g_Ranking[i].no = 1;
//	}
//
//	for (int i = 0; i < 9; i++) {
//		for (int j = i + 1; j < 10; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
//
//void DrawRanking(void) {
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	SetFontSize(30);
//	for (int i = 0; i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d   %10s   %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "--Press[SPACE]Key--", 0xFF0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}
//void InputRanking(void) {
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	SetFontSize(20);
//
//	DrawString(150, 240,"ランキングに登録します", 0x000000);
//	DrawString(150, 270, "名前を英字で入力してください", 0x000000);
//
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score;
//		SortRanking();
//		g_GameState = 0;
//	}
//}