////<ランキングデータの並べ替え関数>)
//
////*ランキングデータの並べ替え
//#include "DxLib.h"
//
//
////変数の宣言
//int g_OldKey; //前回の入力キー
//
//int g_NowKey; //今回の入力キー
//
//int g_KeyFlg; //入力キー情報
//
//int g_RankingImage; //画像用変数
//
//int g_WaitTime = 0; //待ち時間
//
//int g_Score = 3500; //スコア
//
//int g_GameState = 1; //ゲームステータス(状態)
//
////　ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキングデータ初期化
//struct RankingData g_Ranking[10]={
//		{1,"**********",100000},
//		{2,"**********",50000},
//		{3,"**********",10000},
//		{4,"**********",5000},
//		{5,"**********",1000},
//		{6,"**********",500},
//		{7,"**********",100},
//		{8,"**********",50},
//		{9,"**********",10},
//		{10,"**********",5}
//	};
////関数のプロトコルタイプ宣言
//void DrawRanking(void); //ランキング描画
//
//void InputRanking(void);//ランキングの入力
//
//void SortRanking(void);//ランキングの並べ替え
//
//
////プログラムの開始
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	//ウィンドウモードで起動
//	ChangeWindowMode(TRUE);
//
//	//DXライブラリの初期化処理
//	if (DxLib_Init() == -1)return -1;
//
//	//ランキング画像データの読み込み
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	//描画先を裏にする
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//ゲームループ
//	while (ProcessMessage() == 0) {
//
//		//入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//スペースキーで強制終了
//		if (g_KeyFlg & PAD_INPUT_M)break;
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		switch (g_GameState) {
//		case 0:
//			DrawRanking();//ランキング描画処理
//			break;
//		case 1:
//			InputRanking();//ランキング入力処理
//			break;
//		}
//
//		//裏画面の内容を表画面に反映
//		ScreenFlip();
//	}
//
//	//DXライブラリ使用の終了処理
//	DxLib_End();
//
//	return 0; //ソフトの終了
//}
//
//
//    void SortRanking(void)
//{
//	RankingData work;
//
//	//選択法ソート
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
//	//順位付け
//	for (int i = 0; i < 10; i++) {
//		g_Ranking[i].no = 1;
//	}
//	//得点が同じ場合は同じ順位とする
//	//同順位があった場合の次の順位はデータ個数が加算された順位とする
//	for (int i = 0; i < 9; i++) {
//		for (int j = i + 1;j < 10; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
//	//ランキング描画処理
//	void DrawRanking(void)
//	{
//		//ランキング画像表示
//		DrawGraph(0, 0, g_RankingImage, FALSE);
//
//		//ランキング一覧表示
//		SetFontSize(30);
//		for (int i = 0;i < 10; i++) {
//			DrawFormatString(80, 170 + i * 25, 0x000000, "%2d %10s  %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//		}
//
//		//文字の表示(点滅)
//		if (++g_WaitTime < 30) {
//			SetFontSize(24);
//			DrawString(150, 450, "-- Press[SPACE]Key --", 0xFF0000);
//		}
//		else if (g_WaitTime > 60) {
//			g_WaitTime = 0;
//		}
//	}
//	//ランキング入力処理
//
//	void InputRanking(void)
//	{
//		//ランキング画像表示
//		DrawGraph(0, 0, g_RankingImage, FALSE);
//
//		//フォントサイズの設定
//		SetFontSize(20);
//
//		//名前入力指示文字列の描画
//		DrawString(150, 240, "ランキングに登録", 0x000000);
//		DrawString(150, 270, "名前を英字で入力してください", 0x000000);
//
//		//名前入力
//		DrawString(150, 310, ">",0x000000);
//		DrawBox(160, 305, 300, 335, 0x000000,TRUE);
//		if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//			g_Ranking[9].score = g_Score;//ランキングデータの10番目にスコアを登録
//			SortRanking();//ランキング並べ替え
//			g_GameState = 0;//ゲームステータスの変更
//		}
//	}
//
