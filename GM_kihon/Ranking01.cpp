//#include "DxLib.h"
//
////*変数の宣言
//int g_OldKey; //前回の入力キー
//int g_NowKey; //今回の入力キー
//int g_KeyFlg; //入力キー情報
//
//int g_RankingImage;//画像用変数
//
//int g_WaitTime = 0; //画像用変数
//
////ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキングデータ初期化
//struct RankingData g_Ranking[10] = {
//
//	{1,"**********",100000},
//	{2,"**********",50000},
//	{3,"**********",10000},
//	{4,"**********",5000},
//	{5,"**********",1000},
//	{6,"**********",500},
//	{7,"**********",100},
//	{8,"**********",50},
//	{9,"**********",10},
//	{10,"**********",5}
//};
////*関数のプロトコル宣言
//void DrawRanking(void);//ランキング描画処理
////*プログラム開始
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE);//ウィンドウモードで起動
//	
//	if (DxLib_Init() == -1)return -1; //DXライブラリの初期化処理
//
//	//ランキング画像データ読み込み
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1) return -1;
//
//		SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
//
//		//ゲームループ
//		while (ProcessMessage() == 0) {
//			//入力キー取得
//			g_OldKey = g_NowKey;
//			g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//			g_KeyFlg = g_NowKey & ~g_OldKey;
//
//			if (g_KeyFlg & PAD_INPUT_M)break;//スペースキーで強制終了
//			
//			ClearDrawScreen();//画面の初期化
//
//			DrawRanking();//ランキング描画処理
//			
//			ScreenFlip(); //裏画面の内容を表画面に反映
//		}
//
//	DxLib_End(); //DXライブラリ使用の終了処理
//	return 0; //ソフトの終了
//}
////*ランキング描画処理
//void DrawRanking(void) {
//	
//	//ランキング画面表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//	
//	//ランキング一覧表示
//	SetFontSize(30);
//	for (int i = 0; i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d  %10s  %10d",
//			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//	//文字の表示(点滅)
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "-- Press[SPACE]key --", 0xFF0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}
//
//
