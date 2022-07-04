//#include"DxLib.h"
////プログラムはWinMainから始まります
//
//typedef enum MENU_MODE {
//	GAME_TITLE,
//	GAME_MAIN,
//	GAME_RANKING,
//	GAME_END,
//	INPUT_RANKING,
//	END=99
//};
//
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//
//int g_MenuNumber = 0;
//int g_MenuY;
//
//int g_TitleImage;
//int g_RankingImage;
//int g_EndImage;
//
//int g_WaitTime = 0;
//
//int g_PosY;
//
//int g_Score = 3500;
//int g_GameState = GAME_TITLE;
//
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
//
//struct RankingData     g_Ranking[10];
//
//void DrawGameTitle(void);
//void DrawGameMain(void);
//void DrawEnd(void);
//
//void DrawRanking(void);
//void InputRanking(void);
//void SortRanking(void);
//int SaveRanking(void);
//int ReadRanking(void);
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_TitleImage = LoadGraph("images/Title.bmp")) == -1)return -1;
//
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1)return-1;
//
//	if (ReadRanking() == -1)return-1;
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0&& g_GameState!=END) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();
//			break;
//
//		case GAME_MAIN:
//			DrawGameMain();
//			break;
//         
//		case GAME_END:
//			DrawEnd();
//			break;
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
//	int i, j;
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
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//
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
//
//void InputRanking(void) {
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	SetFontSize(20);
//
//	DrawString(150, 240, "ランキングに登録します", 0x000000);
//	DrawString(150, 270, "名前を英字で入力してください", 0x000000);
//
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score;
//		SortRanking();
//		SaveRanking();
//		g_GameState = GAME_RANKING;
//	}
//}
//int SaveRanking(void) {
//	FILE* fp;
//#pragma warning(disable:4996)
//	if ((fp=fopen("dat/rankingdata.txt", "w")) == NULL) {
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//	for (int i = 0; i < 10; i++) {
//		fprintf(fp, "%2d   %10s   %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	fclose(fp);
//
//	return 0;
//}
//
//int ReadRanking(void) {
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	if ((fp = fopen("dat/capter3rankingdata.txt", "r")) == NULL) {
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	for (int i = 0; i < 10; i++) {
//		fscanf(fp,"%2d   %10s   %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//	fclose(fp);
//	return 0;
//}
//void DrawGameTitle(void) {
//
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		if (++g_MenuNumber > 2)g_MenuNumber = 0;
//	}
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		if (g_MenuNumber < 0)g_MenuNumber = 2;
//	}
//	if (g_KeyFlg & PAD_INPUT_A)g_GameState = g_MenuNumber + 1;
//
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	g_MenuY = g_MenuNumber * 52;
//	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);
//}
//void DrawGameMain(void) {
//
//	InputRanking();
//
//
//}
//void DrawEnd(void) {
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//
//	if (++g_WaitTime < 600) g_PosY = 300 - g_WaitTime / 2;
//
//	DrawString(110, 170 + g_PosY, "タイトル　　　〇〇〇 Game", 0x000000);
//	DrawString(110, 200 + g_PosY, "バージョン　　　2,0", 0x000000);
//	DrawString(110, 230 + g_PosY, "最終更新日　　　2018年07月01日", 0x000000);
//	DrawString(110, 260 + g_PosY, "制作者　　　国際電子ビジネス専門学校", 0x000000);
//	DrawString(110, 290 + g_PosY, "　　　　   国際太郎", 0x000000);
//	DrawString(110, 310 + g_PosY, "素材利用", 0x000000);
//	DrawString(110, 340 + g_PosY, "　BGM　　　　魔王魂", 0x000000);
//	DrawString(110, 365 + g_PosY, "　SE　　　　煉獄庭園", 0x000000);
//
//	if (++g_WaitTime > 900)g_GameState = END;
//}