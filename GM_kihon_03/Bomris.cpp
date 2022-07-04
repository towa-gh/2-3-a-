///***********************************************
// ** 　第6章　ミニゲームをつくる(3)
// **　　　　　　　ボムリス(テトリス)
// ***********************************************/
//#include "DxLib.h"
//#include<math.h>
// /***********************************************
//  *列挙体の宣言
//  ***********************************************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_RANKING,
//	GAME_END,
//	GAME_MAIN,
//	GAME_OVER,
//	INPUT_RANKING,
//	END=99
//};
// /***********************************************
//  *変数宣言
//  ***********************************************/
//int g_OldKey;//前回の入力キー
//int g_NowKey;//今回の入力キー
//int g_KeyFlg;//入力キー情報
//
//int g_GameState = GAME_TITLE;//ゲームモード
//
//int g_TitleImage;//タイトル画像
//
//int g_Score = 0;//スコア
//int g_RankingImage;//画像用変数
//
//int g_WaitTime = 0;//待ち時間
//int g_EndImage;
//
//int g_StageImage;//ステージ画像
//
//int g_GameOverImage;//ゲームオーバー画像
//
//const int HEIGHT = 21;
//const int WIDTH = 12;
//const int BLOCKSIZE = 24;
//
//int g_BlockImage[10];//ブロック画像
////ブロック配列
//int g_Field[HEIGHT][WIDTH];//ステージ用
//
//int g_Block[4][4] = { 0 };//新しいブロック用
//int g_Next[4][4] = { 0 };//次のブロック用
//int g_Stock[4][4] = { 0 };//ストックのブロック用
//int g_StockFlg = 0;//ストックのフラグ
//
//int g_Blocklist[7][4][4] = {
//	{
//		{0,0,0,0},
//        {0,1,1,0},
//	    {0,1,1,0},
//	    {0,0,0,0},
//},
//    {
//		{0,0,0,0},
//	    {0,0,0,0},
//	    {2,2,2,2},
//	    {0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{1,0,0,0},
//		{1,1,1,0},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,0,0,2},
//		{0,2,2,2},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,1,1,0},
//		{0,0,1,1},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,2,2,0},
//		{2,2,0,0},
//		{0,0,0,0},
//},
//	{
//		{0,0,0,0},
//	    {0,7,0,0},
//	    {7,7,7,0},
//	    {0,0,0,0},
//}
//
//
//};
//int g_x = 6;//移動可能ブロック(x)
//int g_y = 0;//移動可能ブロック(y)
//
//int g_NumberImage[10];//数字画像
//
//int g_Level;//レベルアップ
//int g_Speed[5] = { 50,40,30,20,10 };//落下スピード配列
////int g_Speed = 60;//落下スピード
//
//int g_BomCnt;//ボム残数
//int g_BomFlg;
//int g_BomX, g_BomY;
//int g_BomImg;
//int g_BomAddScore;
//const int BOM_ADD_SCORE = 5000;
//
//int g_TitleBGM;
//int g_stageBGM;
//int g_GameOverSE;
//int g_SE1;
//int g_SE2;
//int g_SE3;
//int g_SE4;
//int g_SE5;
//
// /***********************************************
//  *定数の宣言
//  ***********************************************/
//const int RANK_MAX = 5;
//
//
///***********************************************
// *構造体の宣言
// ***********************************************/
////ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキングデータ変数宣言
//struct RankingData g_Ranking[RANK_MAX];
//
///***********************************************
// *関数のプロトタイプ宣言
// ***********************************************/
//void GameInit(void);//ゲーム初期化処理
//void GameMain(void);//ゲームメイン処理
//
//void DrawGameTitle(void);//ゲームタイトル描画処理
//void DrawGameOver(void);//ゲームオーバー画像描画処理
//void DrawEnd(void);//ゲームエンド描画処理
//
//void DrawRanking(void);//ランキング描画処理
//void InputRanking(void);//ランキング入力
//
//int LoadImages();  //画像読み込み
//
//void SortRanking(void);//ランキング並べ替え
//int SaveRanking(void);//ランキングデータの保存
//int ReadRanking(void);//ランキングデータの読み込み
//
//void BlockInit(void);
//void DrawStage(void);
//
//void CreateBlock(void);//ブロック生成とNextブロックの移動
//
//void ControlBlock(void);//ブロックの移動処理
//
//int CheckOverlap(int x2, int y2);//ブロックの移動可能チェック処理
//
//void TurnBlock(void);//ブロックの回転処理
//
//void LockBlock(int x2, int y2);//着地したブロックを固定済みブロックに加える
//
//void CheckLines(void);//ブロックが横一列になれば消去、上のブロックをおろす
//
//void ChangeBlock(void);//ブロックの交換処理
//
//void BomStage(void);//ボムの移動処理
//
//int LoadSounds();
//
///***********************************************
// *プログラムの開始
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
//
//	SetMainWindowText("ボ ム リ ス");//タイトルを設定
//	ChangeWindowMode(TRUE);//ウィンドウモードで起動
//	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
//	SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
//	if (LoadImages() == -1)return -1;//画像読み込み関数を呼び出し
//	if (LoadSounds() == -1)return -1;//サウンド読み込み関数を呼び出し
//	if (ReadRanking() == -1) return -1;//ランキングデータの読み込み
//
//	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
//		// 入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//		ClearDrawScreen();//画像の初期化
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();	//ゲームタイトル描画処理
//			break;
//		case GAME_INIT:
//			GameInit();		//ゲーム初期処理
//			break;
//		case GAME_RANKING:
//			DrawRanking();	//ランキング描画処理
//			break;
//		case GAME_END:
//			DrawEnd();		//エンド描画処理
//			break;
//		case GAME_MAIN:
//			GameMain();     //ゲームメイン処理
//			break;
//		case GAME_OVER:
//			DrawGameOver(); //ゲームオーバー描画処理
//			break;
//		case INPUT_RANKING:
//			InputRanking(); //ランキング入力処理
//			break;
//		}
//		ScreenFlip();     //裏画面の内容を表画面に反映
//	}
//	DxLib_End();
//
//	return 0;
//}
///***********************************************
// *ゲームタイトル描画処理(メニュー画面)
// ***********************************************/
//void DrawGameTitle(void) {
//	static int MenuNo = 0;
//	int PosY;
//	PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_BACK, FALSE);
//
//	//メニューカーソル移動処理
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		PlaySoundMem(g_SE1, DX_PLAYTYPE_BACK, TRUE);
//		if (++MenuNo > 2)MenuNo = 0;
//	}
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		PlaySoundMem(g_SE1, DX_PLAYTYPE_BACK, TRUE);
//		if (--MenuNo < 0)MenuNo = 2;
//	}
//	//Zキーでメニュー選択
//	if (g_KeyFlg & PAD_INPUT_A) {
//		StopSoundMem(g_TitleBGM);
//		PlaySoundMem(g_SE2, DX_PLAYTYPE_BACK, TRUE);
//		g_GameState = MenuNo + 1;
//	}
//	//タイトル画像表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//	
//	//メニューカーソル(三角形)の表示
//	PosY = MenuNo * 45;
//	DrawTriangle(140, 210 + PosY, 170, 230 + PosY, 140, 250 + PosY, GetColor(255, 0, 0), TRUE);
//}
///***********************************************
// *ゲーム初期処理
// ***********************************************/
//void GameInit(void){
//	//ゲームメイン処理へ
//	g_GameState = GAME_MAIN;
//	//スコアの初期化
//	g_Score = 0;
//	//ステージ用配列の初期化
//	BlockInit();
//
//	//ブロック生成とNextブロックの移動
//	CreateBlock();
//	CreateBlock();
//
//	//レベルの初期化
//	g_Level = 1;
//
//	//ボム残数の初期化
//	g_BomCnt = 3;
//	//ボム使用フラグ
//	g_BomFlg = 0;
//	//ボム追加スコア
//	g_BomAddScore = BOM_ADD_SCORE;
//}
///***********************************************
// * ランキング入力処理
// ***********************************************/
//void InputRanking(void)
//{
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	// フォントサイズの設定
//	SetFontSize(16);
//
//	// 名前入力指示文字列の描画
//	DrawString(80,150,"ランキングに登録します", 0xFFFF00);
//	DrawString(80,170, "名前を英字で入力してください", 0xFFFF00);
//
//	// 名前の入力
//	DrawString(80, 200, "> ", 0xFFFF00);
//	DrawBox(90, 195, 200, 220, 0xFFFF00, FALSE);
//	if (KeyInputSingleCharString(90, 200, 10, g_Ranking[RANK_MAX - 1].name, FALSE) == 1) {
//		g_Ranking[RANK_MAX - 1].score = g_Score;	// ランキングデータの5番目にスコアを登録
//		SortRanking();		// ランキング並べ替え
//		SaveRanking();		// ランキングデータの保存
//		g_GameState = GAME_RANKING;		// ゲームモードの変更
//	}
//}
///***********************************************
// * ランキング並べ替え
// ***********************************************/
//void SortRanking(void)
//{
//	int i, j;
//	RankingData work;
//	// 選択法ソート
//	for (int i = 0; i < RANK_MAX-1; i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score <= g_Ranking[i].score) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//	// 順位付け
//	for (int i = 0; i < RANK_MAX; i++) {
//		g_Ranking[i].no = 1;
//	}
//	// 得点が同じ場合は、同じ順位とする
//	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
//	for (int i = 0; i < RANK_MAX-1; i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
///***********************************************
// * ランキングデータの保存
// ***********************************************/
//int  SaveRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	// ファイルオープン
//	if ((fp = fopen("dat/chapter5/rankingdata.txt", "w")) == NULL) {
//		/* エラー処理 */
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//	// ランキングデータ分配列データを書き込む
//	for (int i = 0; i < RANK_MAX; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
///*************************************
// * ランキングデータ読み込み
// *************************************/
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
//	//ランキングデータ配分列データを読み込む
//	for (int i = 0; i < RANK_MAX; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
///***********************************************
//*ゲームランキング描画処理
//***********************************************/
//void DrawRanking(void) {
//	//スペースでメニューに戻る
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//ランキング一覧を表示
//	SetFontSize(18);
//	for (int i = 0; i < RANK_MAX; i++) {
//		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//	DrawString(100, 450, "---スペースキーを押してタイトルに戻る---", 0xffffff, 0);
//
//}
///***********************************************
// * ゲームエンド処理
// ***********************************************/
//void DrawEnd(void) {
//	//エンド画像表示
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	SetFontSize(24);
//	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);
//
//	//タイムの加算処理＆終了
//	if (++g_WaitTime > 180)g_GameState = END;
//}
///***********************************************
// * ゲームメイン
// ***********************************************/
//void GameMain(void) {
//	//ステージ画像表示
//	DrawGraph(0, 0, g_StageImage, FALSE);
//
//	//ブロック描画
//	DrawStage();
//
//	//ブロックの移動処理
//	ControlBlock();
//
//	PlaySoundMem(g_stageBGM, DX_PLAYTYPE_BACK, FALSE);
//
//	if (g_BomFlg == 0) {
//		//落下処理
//		g_WaitTime++;
//		if (g_WaitTime > g_Speed[g_Level - 1]) {
//			if (CheckOverlap(g_x, g_y + 1) == 0) {
//				g_y++;
//			}
//			else {
//				//ブロックの固定
//				LockBlock(g_x, g_y);
//				//ブロックの消去＆ブロックをおろす処理
//				CheckLines();
//				//新しいブロック作成
//				CreateBlock();
//				//レベルアップ判断処理
//				if (g_Score / 1000 > g_Level && g_Level < 5) {
//					g_Level++;
//				}
//			}
//			//時間管理変数の初期化
//			g_WaitTime = 0;
//		}
//	}
//	else {
//		BomStage();
//	}
//}
///***********************************************
//*ゲームオーバー描画処理
//***********************************************/
//void DrawGameOver(void) {
//	//ゲームオーバー画像表示
//	DrawGraph(0, 0, g_GameOverImage, FALSE);
//
//	PlaySoundMem(g_GameOverSE, DX_PLAYTYPE_BACK, FALSE);
//
//	//スペースキーでメニューに戻る
//	if (g_KeyFlg & PAD_INPUT_M) {
//		if (g_Ranking[RANK_MAX].score >= g_Score) {
//			g_GameState = GAME_TITLE;
//		}
//		else {
//			g_GameState = INPUT_RANKING;
//		}
//	}
//	DrawString(150, 450, "---スペースキーを押してタイトルへ戻る---", 0xffffff, 0);
//}
///***********************************************
// * ブロック配列の初期化
// ***********************************************/
//void BlockInit(void) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1) {
//				g_Field[i][j] = 9;
//			}
//			else {
//				g_Field[i][j] = 0;
//			}
//		}
//	}
//}
///***********************************************
// * ステージにブロックを描画
// ***********************************************/
//void DrawStage(void) {
//	int PosX, TmpScore;
//	//レベル表示
//	DrawGraph(400, 140, g_NumberImage[g_Level], TRUE);
//
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Field[i][j] != 9) {
//				DrawGraph(BLOCKSIZE * j, BLOCKSIZE * i, g_BlockImage[g_Field[i][j]], TRUE);
//			}
//		}
//	}
//	//移動可能ブロックを描画
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				DrawGraph(BLOCKSIZE * (j+g_x), BLOCKSIZE * (i+g_y), g_BlockImage[g_Block[i][j]], TRUE);
//			}
//		}
//	}
//	//Nextブロックを描画
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			DrawGraph(BLOCKSIZE * j + 480, BLOCKSIZE * i + 350, g_BlockImage[g_Next[i][j]], TRUE);
//			DrawGraph(BLOCKSIZE * j + 360, BLOCKSIZE * i + 240, g_BlockImage[g_Stock[i][j]], TRUE);
//		}
//	}
//
//	PosX = 600;
//	TmpScore = g_Score;
//	do {
//		DrawGraph(PosX, 30, g_NumberImage[TmpScore % 10], TRUE);
//		TmpScore /= 10;
//		PosX -= 30;
//	} while (TmpScore > 0);
//	for (int i = 0; i < g_BomCnt; i++) {
//		DrawGraph(40 * i + 440, 440, g_BomImg, TRUE);
//	}
//}
///***********************************************
// * ブロック生成とNextブロックの移動
// ***********************************************/
//void CreateBlock(void) {
//	//ランダム選択
//	int r = GetRand(6);
//
//	//新しいブロックをセット＆次のブロックの移動
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			g_Block[i][j] = g_Next[i][j];
//			g_Next[i][j] = g_Blocklist[r][i][j];
//		}
//	}
//	//新しいブロックの出現位置をセット
//	g_x = 4;
//	g_y = -1;
//
//	if (CheckOverlap(g_x, g_y) != 0) {
//		g_GameState = GAME_OVER;
//		StopSoundMem(g_stageBGM);
//	}
//}
///***********************************************
// * ブロックのキー移動処理
// ***********************************************/
//void ControlBlock(void) {
//	//キーを入力したら左移動
//	if (g_KeyFlg & PAD_INPUT_LEFT) {
//		if (CheckOverlap(g_x - 1, g_y) == 0) {
//			g_x--;
//		}
//	}
//	//キーを入力したら右移動
//	if (g_KeyFlg & PAD_INPUT_RIGHT) {
//		if (CheckOverlap(g_x + 1, g_y) == 0) {
//			g_x++;
//		}
//	}
//	//キーを入力したらした移動
//	if (g_NowKey & PAD_INPUT_DOWN) {
//		if (CheckOverlap(g_x, g_y + 1) == 0) {
//			PlaySoundMem(g_SE4, DX_PLAYTYPE_BACK, TRUE);
//			g_y++;
//			WaitTimer(60);
//		}
//	}
//	//↑キーを入力したら右に回転
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		PlaySoundMem(g_SE5, DX_PLAYTYPE_BACK, TRUE);
//		TurnBlock();
//	}
//	//Zキーを入力したらブロックの交換
//	if (g_KeyFlg & PAD_INPUT_A) {
//		ChangeBlock();
//	}
//	//Xキーを入力したらボムを使用する
//	if (g_KeyFlg & PAD_INPUT_B && g_BomCnt > 0 && g_BomFlg == 0) {
//		g_BomCnt--;
//		g_BomFlg = 1;
//		g_BomX = WIDTH / 2 - 1;
//		g_BomY = HEIGHT / 2 - 1;
//	}
//}
///***********************************************
// * ブロックの移動可能チェック処理
// ***********************************************/
//int CheckOverlap(int x2, int y2) {
//	int i, j;
//	//接触の確認
//	for (i = 0; i < 4; i++) {
//		for (j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				if (g_Field[y2 + i][x2 + j] != 0) {
//					return 1;
//				}
//			}
//		}
//	}
//	return 0;
//}
///***********************************************
// * ブロックの回転処理
// ***********************************************/
//void TurnBlock(void) {
//	int Temp[4][4] = { 0 };
//
//	do {
//
//		//ブロック一時保持
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				Temp[j][3 - i] = g_Block[i][j];
//			}
//		}
//		//ブロック回転
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				g_Block[i][j] = Temp[i][j];
//			}
//		}
//		//壁側の補正処理
//		if (CheckOverlap(g_x, g_y) == 1 && g_x >= 9)g_x--;
//		if (CheckOverlap(g_x, g_y) == 1 && g_x <= 0)g_x++;
//	} while (CheckOverlap(g_x, g_y) == 1);
//}
///***********************************************
// * 着地したブロックを固定済みブロックを加える
// ***********************************************/
//void LockBlock(int x2, int y2) {
//	PlaySoundMem(g_SE4, DX_PLAYTYPE_BACK, TRUE);
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				g_Field[y2 + i][x2 + j] = g_Block[i][j];
//			}
//		}
//	}
//}
///***********************************************
// * ブロックが横一列になれば消去、上のブロックをおろす
// ***********************************************/
//void CheckLines(void) {
//	int Linecnt = 0, Flg;
//
//	//ブロックが横一列だったらフラグ0
//	for (int i = 0; i < HEIGHT - 1; i++) {
//		Flg = 0;
//		//ブロックが横一列じゃなければフラグ1
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Field[i][j] == 0) {
//				Flg = 1;
//				break;
//			}
//		}
//		//フラグが0なら加算
//		if (Flg == 0) {
//			Linecnt++;
//			//固定済みブロックをおろす
//			for (int k = i; k > 0; k--) {
//				for (int j = 1; j < WIDTH - 1; j++) {
//					g_Field[k][j] = g_Field[k - 1][j];
//				}
//				PlaySoundMem(g_SE3, DX_PLAYTYPE_BACK, TRUE);
//			}
//			g_Score += 1000;
//		}
//	}
//	//スコア加算処理
//	if (Linecnt != 0) {
//		g_Score += (long)(100 * pow(2.0, (Linecnt - 1.0)));
//		if (g_Score > g_BomAddScore) {
//			if (g_BomCnt < 5)g_BomCnt++;
//			g_BomAddScore += BOM_ADD_SCORE;
//		}
//	}
//}
///***********************************************
// * ブロックの交換処理
// ***********************************************/
//void ChangeBlock(void) {
//	int Temp[4][4] = { 0 };
//	if (g_StockFlg == 0) {
//		g_StockFlg = 1;
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				g_Stock[i][j] = g_Block[i][j];
//			}
//		}
//		//新しいブロックのセットアップ＆次のブロックを生成
//		CreateBlock();
//	}
//	else {
//		//ブロックの交換
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				Temp[i][j] = g_Block[i][j];
//				g_Block[i][j] = g_Stock[i][j];
//				g_Stock[i][j] = Temp[i][j];
//			}
//		}
//	}
//}
///***********************************************
// * ボムの移動処理
// ***********************************************/
//void BomStage(void) {
//	DrawGraph(BLOCKSIZE * g_BomX + 4, BLOCKSIZE * g_BomY + 4, g_BomImg, TRUE);
//	//キーを入力したら左移動
//	if (g_KeyFlg & PAD_INPUT_LEFT) {
//		if (g_BomX > 1)g_BomX--;
//	}
//	//キーを入力したら右移動
//	if (g_KeyFlg & PAD_INPUT_RIGHT) {
//		if (g_BomX < WIDTH - 3)g_BomX++;
//	}
//	//キーを入力したら下移動
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		if (g_BomY < HEIGHT - 3)g_BomY++;
//	}
//	//キーを入力したら上移動
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		if (g_BomY > 0)g_BomY--;
//	}
//	//Zキーを入力したらブロックの交換
//	if (g_KeyFlg & PAD_INPUT_C) {
//		g_BomFlg = 0;
//		g_Field[g_BomY][g_BomX] = 0;
//		g_Field[g_BomY][g_BomX + 1] = 0;
//		g_Field[g_BomY + 1][g_BomX] = 0;
//		g_Field[g_BomY + 1][g_BomX + 1] = 0;
//	}
//}
///***********************************************
// * サウンド読み込み
// ***********************************************/
//int LoadSounds() {
//	//タイトルBGMデータの読み込み
//	if ((g_TitleBGM = LoadSoundMem("sounds/BGM041.ogg")) == -1) return -1;
//
//	//ステージBGMデータの読み込み
//	if ((g_stageBGM = LoadSoundMem("sounds/BGM017.ogg")) == -1) return -1;
//
//	//ゲームオーバー音データの読み込み
//	if ((g_GameOverSE = LoadSoundMem("sounds/GameOver.mp3")) == -1) return -1;
//
//	//SE1 データの読み込み
//	if ((g_SE1 = LoadSoundMem("sounds/SE1.mp3")) == -1) return -1;
//
//	//SE2 データの読み込み
//	if ((g_SE2 = LoadSoundMem("sounds/SE2.mp3")) == -1) return -1;
//
//	//SE3 データの読み込み
//	if ((g_SE3 = LoadSoundMem("sounds/SE3.mp3")) == -1) return -1;
//
//	//SE4 データの読み込み
//	if ((g_SE4 = LoadSoundMem("sounds/SE6.mp3")) == -1) return -1;
//
//	//SE5 データの読み込み
//	if ((g_SE5 = LoadSoundMem("sounds/SE5.wav")) == -1) return -1;
//
//	//SEの音量調整
//	ChangeVolumeSoundMem(80, g_SE2);
//	ChangeVolumeSoundMem(150, g_SE3);
//	ChangeVolumeSoundMem(120, g_SE1);
//	ChangeVolumeSoundMem(150, g_SE4);
//	ChangeVolumeSoundMem(130, g_SE5);
//}
//
//
///***********************************************
//*画像読み込み
//***********************************************/
//int LoadImages() {
//	//タイトル
//	if ((g_TitleImage = LoadGraph("images/chapter6/Title.bmp")) == -1)return -1;
//
//	//ランキング
//	if ((g_RankingImage = LoadGraph("images/chapter6/ranking.bmp")) == -1)return -1;
//
//	//エンド画像の読み込み
//	if ((g_EndImage = LoadGraph("images/chapter6/end.bmp")) == -1)return -1;
//
//	//ステージ画像の読み込み
//	if ((g_StageImage = LoadGraph("images/chapter6/stage.bmp")) == -1)return -1;
//
//	//ゲームオーバー画像の読み込み
//	if ((g_GameOverImage = LoadGraph("images/chapter6/GameOver.bmp")) == -1)return -1;
//
//	//ブロック画像の読み込み
//	if (LoadDivGraph("images/chapter6/block.bmp", 10, 10, 1, 24, 24, g_BlockImage) == -1) return -1;
//
//	//数字画像読み込み
//	if (LoadDivGraph("images/chapter6/number.bmp", 10, 10, 1, 24, 37, g_NumberImage) == -1) return -1;
//
//	if (LoadDivGraph("images/chapter6/number.bmp", 10, 10, 1, 24, 37, g_NumberImage) == -1) {
//		return -1;
//	}
//	//ボム画像の読み込み
//	if ((g_BomImg = LoadGraph("images/chapter6/bom.bmp")) == -1)return -1;
//
//	return 0;
//}