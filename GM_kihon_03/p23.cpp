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
//void InputRanking(void);
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
//		InputRanking();
//		ScreenFlip();
//
//	}
//	DxLib_End();    //DXライブラリ使用の終了処理
//
//	return 0;     //ソフトの終了
//}
//
//void InputRanking(void) {
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	SetFontSize(20);
//	
//	DrawString(150, 240, "ランキングに登録します。", 0x000000);
//	DrawString(150, 270, "名前を英字で入力してください。", 0x000000);
//
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//
//	DrawFormatString(0, 0, 0x000000, "Ranking[9].no   =%2d", g_Ranking[9].no);
//	DrawFormatString(0, 20, 0x000000, "Ranking[9].name   =%10s", g_Ranking[9].name);
//	DrawFormatString(0, 40, 0x000000, "Ranking[9].score   =%10d", g_Ranking[9].score);
//
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score;
//	}
//
//}