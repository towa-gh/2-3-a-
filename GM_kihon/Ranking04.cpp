//#include "DxLib.h"
//
////列挙体
//
//typedef enum MENU_MODE {
//	GAME_TITLE,
//	GAME_MAIN,
//	GAME_RANKING,
//	GAME_END,
//	INPUT_RANKING,
//	END = 99
//};
////変数の宣言
//
//int g_OldKey; //前回の入力キー
//int g_NowKey; //今回の入力キー
//int g_KeyFlg; //入力キー情報
//
//int g_MenuNumber = 0; //メニューカーソル位置
//int g_MenuY; //メニューカーソルY座標
//
//int g_TitleImage; //画像用変数
//int g_RankingImage; //画像用変数
//int g_EndImage; //画像用変数
//
//int g_WaitTime = 0; //待ち時間
//int g_PosY; //スクロール時のY座標
//
//int g_Score = 3500; //スコア
//
//int g_GameState = GAME_TITLE; //ゲームモード
//
////ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキングデータの変数宣言
//struct RankingData g_Ranking[10];
//
////関数のプロトコルタイプ宣言
//void DrawGameTitle(void); //ゲームタイトル処理
//void DrawGameMain(void); //ゲームメイン処理
//void DrawEnd(void); //ゲームエンド処理
//
//void DrawRanking(void); //ゲームランキング処理
//void InputRanking(void); //ランキング入力
//void SortRanking(void); //ランキング並べ替え
//int SaveRanking(void); //ランキングデータの保存
//int ReadRanking(void); //ランキングデータ読み込み
//
//
////プログラムの開始
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE); //ウィンドウモードで起動
//	if (DxLib_Init() == -1) return -1; //DXライブラリの初期化処理
//
//	//タイトル画像データ読み込み
//	if ((g_TitleImage = LoadGraph("images/Title.bmp")) == -1) return -1;
//
//	//ランキング画像データの読み込み
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return -1;
//
//	//エンド画面データ読み込み
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1) return -1;
//
//	if (ReadRanking() == -1) return -1; //ランキングデータの読み込み
//
//	SetDrawScreen(DX_SCREEN_BACK);//描画先を裏にする
//
//	//ゲームループ
//	while (ProcessMessage() == 0 && g_GameState != END) {
//
//		//入力キー取得
//		g_OldKey = g_NowKey;
//
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen(); //画面の初期化
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();//ゲームタイトル処理
//			break;
//		case GAME_MAIN:
//			DrawGameMain(); //ゲームメイン処理
//			break;
//		case GAME_RANKING:
//			DrawRanking(); //ゲームランキング処理
//			break;
//		case GAME_END:
//			DrawEnd(); //ゲームエンド処理
//			break;
//		}
//
//		ScreenFlip(); //裏画面の内容を表画面に反映
//	}
//
//	DxLib_End(); //DXライブラリ使用の終了処理
//
//	return 0;//ソフトの終了
//}
//
////ランキング並べ替え
//void SortRanking(void)
//{
//	int i, j;
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
////ランキング描画処理
//void DrawRanking(void)
//{
//	//スペースキーでメニューに戻る
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//ランキング一覧表示
//	SetFontSize(30);
//	for (int i = 0;i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d  %10s   %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	//文字の表示(点滅)
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "-- Press[SPACE]Key --", 0xFF0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}
//
////ランキング入力処理
//void InputRanking(void)
//{
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//フォントサイズの設定
//	SetFontSize(20);
//
//	//名前入力指示文字列の描画
//	DrawString(150, 240, "ランキングに登録します", 0x000000);
//	DrawString(150, 270, "名前を英字で入力してください", 0x000000);
//
//	//名前入力
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score; //ランキングデータの10番目にスコアを登録
//		SortRanking(); //ランキング並べ替え
//		SaveRanking(); //ランキングデータの保存
//		g_GameState = GAME_RANKING; //ゲームモードの変更
//	}
//
//}
////ランキングデータの保存
//
//int SaveRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL) {
//		//エラー処理
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ分配列データを書き込む
//	for (int i = 0; i < 10; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
//
////ランキングデータ読み込み
//int ReadRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL) {
//		//エラー処理
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ分配列データを読み込む
//	for (int i = 0; i < 10; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
////ゲームタイトル表示(メニュー画面)
//
//void DrawGameTitle(void)
//{
//	//メニューカーソル移動処理
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		if (++g_MenuNumber > 2)g_MenuNumber = 0;
//	}
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		if (--g_MenuNumber < 0)g_MenuNumber = 2;
//	}
//
//	//Zキーでメニュー選択
//	if (g_KeyFlg & PAD_INPUT_A)g_GameState = g_MenuNumber + 1;
//
//	//タイトル画面表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	//メニューカーソル(三角形)の表示
//	g_MenuY = g_MenuNumber * 52;
//	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);
//}
////ゲームメイン
//void DrawGameMain(void)
//{
//	//ランキング入力
//	InputRanking();
//}
////ゲームエンド処理(エンドロール)
//
//void DrawEnd(void)
//{
//	//エンド画像表示
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	//エンディング表示
//	if (++g_WaitTime < 600)g_PosY = 300 - g_WaitTime / 2;
//
//	SetFontSize(24);
//	DrawString(110, 170 + g_PosY, "タイトル　　〇〇〇　Game", 0x000000);
//	DrawString(110, 200 + g_PosY, "バージョン　　2.0", 0x000000);
//	DrawString(110, 230 + g_PosY, "最新更新日　2018年07月01日", 0x000000);
//	DrawString(110, 260 + g_PosY, "制作者　　国際電子ビジネス専門学校", 0x000000);
//	DrawString(110, 290 + g_PosY, "国際　太郎", 0x000000);
//	DrawString(110, 310 + g_PosY, "素材利用", 0x000000);
//	DrawString(110, 340 + g_PosY, "BGM      魔王魂", 0x000000);
//	DrawString(110, 365 + g_PosY, "SE   煉獄庭園", 0x000000);
//
//	//タイムの加算処理&終了
//	if (++g_WaitTime > 900)g_GameState = END;
//}
