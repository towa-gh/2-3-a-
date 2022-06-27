//#include "DxLib.h"
//
////*変数の宣言
//int g_OldKey; //前回の入力キー
//int g_NowKey; //今回の入力キー
//int g_KeyFlg; //入力キー情報
//
//int g_RankingImage;//画像用変数
//
//int g_WaitTime = 0;//待ち時間
//
//int g_Score = 3500;//スコア
//
////ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキングデータ初期化
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
////*関数プロトコルタイプ宣言
//void InputRanking(void);//ランキング入力処理
//
////*プログラムの開始
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE);//ウィンドウモードで起動
//	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
//
//	//ランキング画像データの読み込み
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);//描画画面を裏にする
//
//	SetFontSize(20);//文字サイズを設定
//	//ゲームループ
//
//	while (ProcessMessage() == 0) {
//		//入力キー取得
//		g_OldKey = g_NowKey;
//
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		if (g_KeyFlg & PAD_INPUT_M)break; //スペースキーで強制終了
//
//		ClearDrawScreen();//画面の初期化
//
//		InputRanking();//ランキング入力処理
//
//		ScreenFlip();//裏画面の内容を表画面に反映
//	}
//	DxLib_End();//DXライブラリ使用の終了処理
//
//	return 0; //ソフトの終了
//}
//
////*ランキング入力処理
//void InputRanking(void)
//{
//	//ランキング画面表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//フォントサイズの設定
//	SetFontSize(20);
//
//	//名前入力文字列の描画
//	DrawString(150, 240, "ランキングに登録します", 0x000000);
//	DrawString(150, 270, "名前を英字で入力", 0x000000);
//
//
//	//名前入力
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//
//	//テスト用変数表示
//	DrawFormatString(0, 0, 0x000000, "Ranking[9].no =%2d", g_Ranking[9].no);
//	DrawFormatString(0, 20, 0x000000, "Ranking[9].name =%10s", g_Ranking[9].name);
//	DrawFormatString(0, 40, 0x000000, "Ranking[9].score =%10d", g_Ranking[9].score);
//
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score; //ランキングデータの10番目にスコアを登録
//	}
//}
//
//
