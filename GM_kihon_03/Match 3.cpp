///***********************************************
// ** 　第8章　ミニゲームをつくる(5)
// **　　　　　　　Match 3 Puzzle(マッチ3パズル)
// ***********************************************/
//#include "DxLib.h"
//#include <stdlib.h>
// /***********************************************
//  *列挙体の宣言
//  ***********************************************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_END,
//	GAME_MAIN,
//	GAME_CLEAR,
//	GAME_OVER,
//	END = 99
//};
///***********************************************
// *変数宣言
// ***********************************************/
//int g_OldKey;//前回の入力キー
//int g_NowKey;//今回の入力キー
//int g_KeyFlg;//入力キー情報
//int g_MouseX;//マウスX座標
//int g_MouseY;//マウスY座標
//
//int g_GameState = GAME_TITLE;//ゲームモード
//
//int g_TitleImage;//タイトル画像
//
//int g_StageImage;//ステージ画像
//
//int g_GameClearImage;//ゲームクリア画像
//
//int g_GameOverImage;//ゲームオーバー画像
//
//int g_BlockImage[10];//ブロック画像
//
//const int ITEM_MAX = 8;
//const int TIMELIMIT = 3600 * 3;
//
//int g_NumberImage[10];//ナンバー画像
//int g_Score;//スコア
//int g_Level;//レベル
//int g_Mission;//ミッション
//int g_Item[ITEM_MAX];//ステージクリア用の変数
//int g_Time;//制限時間
//
//int g_Status = 0;
//int g_SelectX1;
//int g_SelectY1;
//int g_SelectX2;
//int g_SelectY2;
//
////サウンド用変数
//int g_TitleBGM;
//int g_GameClearSE;
//int g_GameOverSE;
//int g_ClickSE;
//int g_FadeOutSE;
//int g_MoveBlockSE;
///***********************************************
// *定数の宣言
// ***********************************************/
//const int HEIGHT = 12;
//const int WIDTH = 12;
//const int BLOCKSIZE = 48;
//const int MARGIN = 0;
///***********************************************
// *構造体の宣言
// ***********************************************/
//struct Object {
//	int flg;
//	int x, y;
//	int w, h;
//	int image;
//	int backup;
//};
//struct Object g_Block[HEIGHT][WIDTH];
///***********************************************
// *関数のプロトタイプ宣言
// ***********************************************/
//void GameInit(void);//ゲーム初期化処理
//void GameMain(void);//ゲームメイン処理
//
//void DrawGameTitle(void);//ゲームタイトル描画処理
//void DrawGameClear(void);//ゲームクリア画像描画処理
//void DrawGameOver(void);//ゲームオーバー画像描画処理
//void DrawEnd(void);//ゲームエンド描画処理
//
//int LoadImages(void);  //画像読み込み
//
//void DrawStage(void);//Block[][]の中身で、画像を描画
//
//void StageInit(void);//ステージ初期処理
//
//int RensaCheck(int y, int x);//ブロック連鎖チェック
//int RensaCheckH(int y, int x, int* cnt, int* col);//ブロック連鎖チェック(縦)
//int RensaCheckW(int y, int x, int* cnt, int* col);//ブロック連鎖チェック(横)
//void SaveBlock(void);//ブロックをバックアップする
//void RestoreBlock(void);//バックアップブロックを戻す
//
//void SelectBlock(void);//Blockを選択
//
//void MoveBlock(void);//ブロック移動
//
//void CheckBlock(void);
//
//void CheckClear(void);
//
//void FadeOutBlock(void);//消去するブロックをフェードアウトする
//
//int LoadSounds(void);
///***********************************************
// *プログラムの開始
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
//
//	SetMainWindowText("Match 3 Puzzle(マッチ3パズル)");//タイトルを設定
//	ChangeWindowMode(TRUE);//ウィンドウモードで起動
//	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
//	SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
//	if (LoadImages() == -1)return -1;//画像読み込み関数を呼び出し
//	if (LoadSounds() == -1)return-1;//サウンド読み込み関数を呼び出し
//	
//	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {
//		// 入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//		//マウスの位置を取得
//		GetMousePoint(&g_MouseX, &g_MouseY);
//
//		ClearDrawScreen();//画像の初期化
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();	//ゲームタイトル描画処理
//			break;
//		case GAME_INIT:
//			GameInit();		//ゲーム初期処理
//			break;
//		case GAME_END:
//			DrawEnd();		//エンド描画処理
//			break;
//		case GAME_MAIN:
//			GameMain();     //ゲームメイン処理
//			break;
//		case GAME_CLEAR:
//			DrawGameClear();//ゲームクリア処理
//			break;
//		case GAME_OVER:
//			DrawGameOver(); //ゲームオーバー描画処理
//			break;
//		}
//		ScreenFlip();     //裏画面の内容を表画面に反映
//	}
//	DxLib_End();
//
//	return 0;
//}
///***********************************************
// *ゲームタイトル表示(メニュー画面)
// ***********************************************/
//void DrawGameTitle(void) {
//	//タイトルBGMを再生
//	if (CheckSoundMem(g_TitleBGM) == 0) {
//		PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_BACK);
//	}
//
//	//タイトル画像表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	//ゲームモードを切り替える
//	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//		if (g_MouseX > 120 && g_MouseX < 290 && g_MouseY>260 && g_MouseY < 315) {
//			g_GameState = GAME_INIT;//ゲームスタートの選択
//			StopSoundMem(g_TitleBGM);//ゲームBGMを止める
//		}
//		else if (g_MouseX > 120 && g_MouseX < 220 && g_MouseY>345 && g_MouseY < 400) {
//			g_GameState = GAME_END;//ゲームエンドの選択
//			StopSoundMem(g_TitleBGM);//ゲームBGMを止める
//		}
//	}
//
//}
///***********************************************
// *ゲーム初期処理
// ***********************************************/
//void GameInit(void) {
//	//ゲームメイン処理へ
//	g_GameState = GAME_MAIN;
//	//スコアの初期化
//	g_Score = 0;
//	//レベルの初期化
//	g_Level = 0;
//	//ミッションの初期化
//	g_Mission = 2;
//
//	//ブロックの初期化
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1 || i == 0) {
//				g_Block[i][j].flg = 0;
//				g_Block[i][j].image = 0;
//			}
//			else {
//				g_Block[i][j].flg = 1;
//				g_Block[i][j].x = (j - 1) * BLOCKSIZE + MARGIN;
//				g_Block[i][j].y = (i - 1) * BLOCKSIZE;
//				g_Block[i][j].w = BLOCKSIZE;
//				g_Block[i][j].h = BLOCKSIZE;
//				g_Block[i][j].image = GetRand(7)+1;//1～8までの乱数を発生
//			}
//		}
//	}
//	//ステージ初期処理
//	StageInit();
//}
///***********************************************
// *エンド描画処理
// ***********************************************/
//void DrawEnd(void) {
//	static int WaitTime = 0;
//	//タイトル画像表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	SetFontSize(24);
//	DrawString(360, 480 - 24, "Thank you for Playing", 0x003333, 0);
//
//	//タイムの加算処理&終了
//	if (++WaitTime > 180)g_GameState = END;
//
//}
///***********************************************
// *ゲームメイン
// ***********************************************/
//void GameMain(void) {
//	//ステージ画像表示
//	DrawGraph(0, 0, g_StageImage, FALSE);
//	//ブロック描画
//	DrawStage();
//
//	//タイム変数をデクリメントして、0未満ならゲームオーバーへ移行する
//	if (--g_Time < 0) {
//		g_GameState = GAME_OVER;
//	}
//
//	//ステージにより処理を分ける
//	switch (g_Status) {
//	   case 0:
//		   SelectBlock();//ブロックを選択
//		   break;
//	   case 1:
//		   FadeOutBlock();//ブロックをフェードアウトして消す
//		   break;
//	   case 2:
//		   MoveBlock();//Blockの移動
//		   break;
//	   case 3:
//		   CheckBlock();//Blockの連鎖チェック
//		   break;
//	   case 4:
//		   CheckClear();//クリア条件のチェック
//		   break;
//	}
//}
///***********************************************
// *ゲームクリア表示
// ***********************************************/
//void DrawGameClear(void) {
//
//	static int GameClearFlg = 0;
//	//ゲームクリア効果音を再生
//	if (CheckSoundMem(g_GameClearSE) == 0) {
//		if (GameClearFlg++ == 0) {
//			PlaySoundMem(g_GameClearSE, DX_PLAYTYPE_BACK);
//		}
//		else {
//			//g_GameState=GAME_TITLE;
//			//ステージ初期処理
//			StageInit();
//			g_GameState = GAME_MAIN;
//			GameClearFlg = 0;
//		}
//	}
//	//ゲームクリア画像表示
//	DrawGraph(0, 0, g_GameClearImage, FALSE);
///*
//	//右クリックでメニューへ戻る
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT) {
//		//g_GameState = GAME_TITLE;
//		//ステージ初期処理
//		StageInit();
//		g_GameState = GAME_MAIN;
//	}
//
//	//SetFontSize(16);
//	//DrawString(150, 450, "---右クリックを押してタイトルへ戻る---", 0xffffff, 0);
//
//	SetFontSize(20);
//	DrawString(150, 450, "---右クリックを次のステージへ---", 0xffffff, 0);
//*/
//}
///***********************************************
// *ゲームオーバー処理
// ***********************************************/
//void DrawGameOver(void) {
//	static int GameOverFlg = 0;
//
//	//ゲームオーバー効果音を再生
//	if (CheckSoundMem(g_GameOverSE) == 0) {
//		if (GameOverFlg++ == 0) {
//			PlaySoundMem(g_GameOverSE, DX_PLAYTYPE_BACK);
//		}
//		else {
//			g_GameState = GAME_TITLE;
//			GameOverFlg = 0;
//		}
//	}
//
//	//ゲームオーバー画像処理
//	DrawGraph(0, 0, g_GameOverImage, FALSE);
///*
//	//右クリックでメニューに戻る
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);
//	DrawString(150, 450, "---右クリックを押してタイトルへ戻る---", 0xffffff, 0);
//*/
//}
///***********************************************
// *ステージにブロックを描画
// ***********************************************/
//void DrawStage(void) {
//	//レベルを描画
//	int TmpLevel = g_Level;
//	int PosX = 600;
//	
//	do {
//		DrawRotaGraph(PosX, 80, 0.5f, 0, g_NumberImage[TmpLevel % 10], TRUE);
//		TmpLevel /= 10;
//		PosX -= 30;
//	} while (TmpLevel > 0);
//
//	//スコアを描画
//	int TmpScore = g_Score;
//	PosX = 620;
//	do {
//		DrawRotaGraph(PosX, 160, 0.3f, 0, g_NumberImage[TmpScore % 10], TRUE);
//		TmpScore /= 10;
//		PosX -= 20;
//	} while (TmpScore > 0);
//
//	//ミッションを描画
//	SetFontSize(20);
//	DrawFormatString(590, 211, 0xFFFFFF, "%3d", g_Mission);
//
//	//アイテムの取得個数を描画
//	for (int i = 0; i < ITEM_MAX; i++) {
//		DrawRotaGraph(540, 245 + i * 30, 0.5f, 0, g_BlockImage[i + 1], TRUE, 0);
//		DrawFormatString(580, 235 + i * 30, 0xFFFFFF, "%3d", g_Item[i]);
//	}
//
//
//	//ブロックを描画
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Block[i][j].flg != 0 && g_Block[i][j].image != 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
//			}
//		}
//	}
//	//タイムバーを描画
//	DrawBox(491, 469, 509, 469 - g_Time / 60 * 2, 0x0033ff, TRUE);
//}
///***********************************************
// *ステージの初期処理
// ***********************************************/
//void StageInit(void) {
//	int Result = 0;
//
//	//空のブロックを生成する処理
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				g_Block[i][j].image = GetRand(7) + 1;
//			}
//		}
//	}
//	//ブロック連鎖チェック
//	/*for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			Result += RensaCheck(i, j);
//		}
//	}*/
//	
//	if (Result == 0) {
//
//		g_GameState = GAME_MAIN;
//
//		//レベル
//		g_Level += 1;
//		//ミッション
//		g_Mission += 1;
//		//制限時間
//		g_Time = TIMELIMIT;
//
//		//カウント配列の初期化
//		for (int i = 0; i < ITEM_MAX; i++) {
//			g_Item[i] = 0;
//		}
//	}
//
//}
///***********************************************
// *隣接している同色の個数を調べる
// * 引数:現在のx座標,y:現在のy座標
// * 戻り値:1…3つ以上の連鎖、0…連鎖なし
// ***********************************************/
//int RensaCheck(int y, int x) {
//	int CountH = 0;
//	int ColorH = 0;
//
//	SaveBlock();//ブロックをバックアップする
//	RensaCheckH(y, x, &CountH, &ColorH);
//	if (CountH < 3) {
//		RestoreBlock();//ブロックの連鎖が3個未満ならブロックを戻す
//	}
//
//	int CountW = 0;
//	int ColorW = 0;
//	SaveBlock();//ブロックをバックアップする
//	RensaCheckW(y, x, &CountW, &ColorW);
//	if (CountW < 3) {
//		RestoreBlock();//ブロックの連鎖が3個未満ならブロックを戻す
//	}
//	if ((CountH >= 3 || CountW >= 3)) {
//		if (CountH >= 3) {
//			g_Item[ColorH - 1] += CountH;
//			g_Score += CountH * 10;
//			g_Time += 60;
//		}
//		if (CountW >= 3) {
//			g_Item[ColorW - 1] += CountW;
//			g_Score += CountW * 10;
//			g_Time += 60;
//		}
//		return 1;
//	}
//	return 0;
//}
///***********************************************
// *縦の隣接している同色の個数を調べる
// * 引数:x:x座標,y:y座標,cnt個数,col:色
// * 戻り値:縦の隣接している同色の個数
// ***********************************************/
//int RensaCheckH(int y, int x, int* cnt, int* col) {
//	//対象ブロックが外枠の場合
//	if (g_Block[y][x].image == 0)return 0;
//
//	*col = g_Block[y][x].image;
//	int c = g_Block[y][x].image;//色を取得
//	g_Block[y][x].image = 0;
//	(*cnt)++;
//
//	if (g_Block[y + 1][x].image == c)RensaCheckH(y + 1, x, cnt, col);
//	if (g_Block[y - 1][x].image == c)RensaCheckH(y - 1, x, cnt, col);
//
//	return 0;
//}
///***********************************************
// *横の隣接している同色の個数を調べる
// * 引数:x:x座標,y:y座標,cnt個数,col:色
// * 戻り値:横の隣接している同色の個数
// ***********************************************/
//int RensaCheckW(int y, int x, int* cnt, int* col) {
//	//対象ブロックが外側の場合　return で処理を抜ける
//	if (g_Block[y][x].image == 0)return 0;
//
//	*col = g_Block[y][x].image;
//	int c = g_Block[y][x].image;//色を取得
//	g_Block[y][x].image = 0;
//	(*cnt)++;
//
//	if (g_Block[y][x + 1].image == c)RensaCheckW(y, x + 1, cnt, col);
//	if (g_Block[y][x - 1].image == c)RensaCheckW(y, x - 1, cnt, col);
//
//	return 0;
//}
///***********************************************
// *ブロックをバックアップする
// ***********************************************/
//void SaveBlock(void) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].backup = g_Block[i][j].image;
//		}
//	}
//}
///***********************************************
// *バックアップを戻す
// ***********************************************/
//void RestoreBlock(void) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].image = g_Block[i][j].backup;
//		}
//	}
//}
///***********************************************
// *ブロックを選択
// ***********************************************/
//void SelectBlock(void) {
//	static int ClickFlg = 0;
//
//	int SelectX = g_MouseX / BLOCKSIZE;
//	int SelectY = g_MouseY / BLOCKSIZE;
//
//    //選択ブロックの範囲を制御
//	if (SelectX < 0)SelectX = 0;
//	if (SelectX > WIDTH - 3)SelectX = WIDTH - 3;
//	if (SelectY < 0)SelectY = 0;
//	if (SelectY > HEIGHT - 3)SelectY = HEIGHT - 3;
//
//	//クリックでブロックを選択
//	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//		//クリック時の効果音を再生
//		PlaySoundMem(g_ClickSE, DX_PLAYTYPE_BACK);
//
//		if (ClickFlg == 0) {
//			g_SelectX1 = SelectX;
//			g_SelectY1 = SelectY;
//			ClickFlg = 1;
//		}
//		else if (ClickFlg == 1&&((abs(g_SelectX1-SelectX)==1&&abs(g_SelectY1-SelectY)==0)||(abs(g_SelectX1-SelectX)==0&&abs(g_SelectY1-SelectY)==1))) {
//			g_SelectX2 = SelectX;
//			g_SelectY2 = SelectY;
//			ClickFlg = 2;
//		}
//	}
//	//選択ブロックを描画
//	DrawGraph(SelectX * BLOCKSIZE, SelectY * BLOCKSIZE, g_BlockImage[9], TRUE);
//	if (ClickFlg >= 1) {
//		DrawGraph(g_SelectX1 * BLOCKSIZE, g_SelectY1 * BLOCKSIZE, g_BlockImage[9], TRUE);
//	}
//	//選択ブロックを交換
//	if (ClickFlg == 2) {
//		int TmpBlock = g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image;
//		g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image = g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image;
//		g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image = TmpBlock;
//
//		//連鎖が3つ以上かを調べる
//		int Result = 0;
//		Result += RensaCheck(g_SelectY1 + 1, g_SelectX1 + 1);
//		Result += RensaCheck(g_SelectY2 + 1, g_SelectX2 + 1);
//
//		//連鎖が3未満なら選択ブロックを元に戻す
//		if (Result == 0) {
//			int TmpBlock = g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image;
//			g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image = g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image;
//			g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image = TmpBlock;
//		}
//		else {
//			//連鎖が3つ以上ならブロックを消し、ブロック移動処理へ移行する
//			g_Status = 1;
//		}
//
//		//次にクリックできるように、ClickFlgを0にする
//		ClickFlg = 0;
//	}
//
//}
///***********************************************
// *ブロック移動
// ***********************************************/
//void MoveBlock(void) {
//	//ブロック移動時効果音を再生
//	PlaySoundMem(g_MoveBlockSE, DX_PLAYTYPE_BACK);
//
//	//↓へ移動する処理
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				for (int k = i; k > 0; k--) {
//					g_Block[k][j].image = g_Block[k - 1][j].image;
//					g_Block[k - 1][j].image = 0;
//				}
//			}
//		}
//	}
//	//空のブロックを生成する処理
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				g_Block[i][j].image = GetRand(7) + 1;
//			}
//		}
//	}
//	//ブロック選択処理へ移行する
//	//g_Status = 0;
//
//	//ブロック連鎖チェック処理へ移動する
//	g_Status = 3;
//}
///***********************************************
// *ブロック連鎖チェック
// ***********************************************/
//void CheckBlock(void) {
//	int Result = 0;
//
//	//ブロック連鎖チェック
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			Result += RensaCheck(i, j);
//		}
//	}
//	//連鎖がなくなれば、ブロック選択へ移行する
//	//そうでなければ、ブロック移動へ移行して連鎖チェックを継続する
//	if (Result == 0) {
//		//ブロック選択処理へ移行する
//		//g_Status = 0;
//		//クリア条件のチェック処理へ移行する
//		g_Status = 4;
//	}
//	else {
//		//連鎖が3つ以上ならブロックを消し、ブロック移行処理へ移行する
//		g_Status = 1;
//	}
//}
///***********************************************
// *クリア条件のチェック
// ***********************************************/
//void CheckClear(void) {
//	int ClearFlg = 0;
//	for (int i = 0; i < ITEM_MAX; i++) {
//		if (g_Item[i] < g_Mission) {
//			ClearFlg = 1;
//			break;
//		}
//	}
//	if (ClearFlg == 0) {
//		g_GameState = GAME_CLEAR;
//	}
//	else {
//		g_Status = 0;
//	}
//}
///***********************************************
// *消去するブロックをフェードアウトする
// ***********************************************/
//void FadeOutBlock(void) {
//	//フェードアウト時効果音を再生
//	if (CheckSoundMem(g_FadeOutSE) == 0) {
//		PlaySoundMem(g_FadeOutSE, DX_PLAYTYPE_BACK);
//	}
//
//	static int BlendMode = 255;
//	//描画ブレンドモードをアルファブレンドにする
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendMode);
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].backup], TRUE);
//			}
//		}
//	}
//	//描画ブレンドモードをノーブレンドにする
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	BlendMode -= 5;
//	if (BlendMode <= 0) {
//		BlendMode = 255;
//		g_Status = 2;
//		//フェードアウト時効果音を再生
//		StopSoundMem(g_FadeOutSE);
//	}
//}
///***********************************************
// *サウンド読み込み
// ***********************************************/
//int LoadSounds(void) {
//	//タイトルBGM
//	if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
//
//	//ゲームクリア
//	if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//
//	//ゲームオーバー
//	if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
//
//	//マウスクリック効果音
//	if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
//
//	//ブロック消去効果音
//	if ((g_FadeOutSE = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
//
//	//ブロック移動時効果音
//	if ((g_MoveBlockSE = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;
//}
///***********************************************
// *画像読み込み
// ***********************************************/
//int LoadImages() {
//	//タイトル
//	if ((g_TitleImage = LoadGraph("images/chapter8/title.png")) == -1)return -1;
//
//	//ステージ画像の読み込み
//	if ((g_StageImage = LoadGraph("images/chapter8/stage.png")) == -1)return -1;
//
//	//ゲームクリア画像の読み込み
//	if ((g_GameClearImage = LoadGraph("images/chapter8/gameclear.png")) == -1)return -1;
//
//	//ゲームオーバー画像の読み込み
//	if ((g_GameOverImage = LoadGraph("images/chapter8/gameover.png")) == -1)return -1;
//
//	//ブロック画像の読み込み
//	if (LoadDivGraph("images/chapter8/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
//
//	return 0;
//}