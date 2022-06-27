//#include "DxLib.h"
//#include <stdlib.h>
///*****************/
///*列挙体の宣言*/
///*****************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_RANKING,
//	GAME_END,
//	GAME_MAIN,
//	GAME_CLEAR,
//	GAME_OVER,
//	INPUT_RANKING,
//	END = 99
//};
//
///******************/
///*変数の宣言*/
///******************/
//int g_OldKey; //前回の入力キー
//int g_NowKey; //今回の入力キー
//int g_KeyFlg; //入力キー情報
//int g_MouseX; //マウスX座標
//int g_MouseY; //マウスY座標
//
//int g_GameState = GAME_TITLE; //ゲームモード
//
//int g_TitleImage; //タイトル画像
//
//int g_StageImage; //ステージ画像
//
//int g_GameClearImage; //ゲームクリア画像
//
//int g_GameOverImage; //ゲームオーバー画像
//
//int g_BlockImage[10]; //ブロック画像
//
//int g_NumberImage[10]; //ナンバー画像
//
//int g_RankingImage;//画像用変数
//
//
//
//int g_Status = 0; //ステージのステータス(0..プレイヤー操作中など)
//int g_SelectX1; //一回目に選択したブロックの二次元配列(横)
//int g_SelectY1; //一回目に選択したブロックの二次元配列(縦)
//int g_SelectX2; //二回目に選択したブロックの二次元配列(横)
//int g_SelectY2; //二回目に選択したブロックの二次元配列(縦)
//
////サウンド用変数
//int g_TitleBGM; //タイトルBGM
//int g_GameClearSE; //ゲームクリア
//int g_GameOverSE; //ゲームオーバー
//int g_ClickSE; //マウスクリック効果音
//int g_FadeOutSE; //ブロック消去効果音
//int g_MoveBlockSE; //ブロック移動時効果音
//
///******************/
///*定数の宣言*/
///******************/
//const  int HEIGHT = 12;
//const  int WIDTH = 12;
//const  int BLOCKSIZE = 48;
//const  int MARGIN = 0;
//const  int ITEM_MAX = 8;
//const  int TIMELIMIT = 3600 * 3;
//const  int RANK_MAX = 5;
//
//int g_Score; //スコア
//int g_Level; //レベル
//int g_Mission; //ミッション
//int g_Item[ITEM_MAX]; //ステージクリア用の変数
//int g_Time; //制限時間
//
///******************/
///*構造体の宣言*/
///******************/
//struct Object
//{
//	int flg; //フラグ(0:表示しない　,1:表示)
//	int x, y; //座標x,y
//	int w, h; //幅w 高さh
//	int image; //画像
//	int backup; //画像バックアップ
//};
//struct Object g_Block[HEIGHT][WIDTH];
//
//
///**************************************/
////構造体の宣言
///**************************************/
////ランキングデータ(構造体)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////ランキング変数宣言
//struct RankingData g_Ranking[RANK_MAX];
//
///************************/
///*関数のプロトタイプ宣言*/
///************************/
//void GameInit(void); //ゲーム初期化処理
//void GameMain(void); //ゲームメイン処理
//void DrawGameTitle(void); //ゲームタイトル処理
//void DrawGameClear(void); //ゲームクリア処理
//void DrawGameOver(void); //ゲームオーバー処理
//void DrawEnd(void); //ゲームエンド処理
//
//int LoadImages(void); //画像読み込み
//int LoadSounds(void); //BGM読み込み
//
//void DrawStage(void); //Block[][]の中身で、画面を描画
//
//void StageInit(void); //ステージ初期処理
//
//int RensaCheck(int y, int x); //ブロック連鎖チェック
//int RensaCheckH(int y, int x, int* cnt, int* col); //ブロック連鎖チェック(縦)
//int RensaCheckW(int y, int x, int* cnt, int* col); //ブロック連鎖チェック(横)
//
//void SaveBlock(void); //ブロックをバックアップ
//void RestoreBlock(void); //バックアップブロックを戻す
//
//void SelectBlock(void); //Blockを選択
//void MoveBlock(void); //ブロック移動
//void CheckBlock(void); //ブロック連鎖をチェックする
//void CheckClear(void); //クリア条件のチェック
//
//void FadeOutBlock(void); //消去するブロックをフェードアウトする
//
//void DrawRanking(void); //ランキング描画処理
//void InputRanking(void); //ランキング入力
//
//void SortRanking(void); //ランキング並べ替え
//
//int SaveRanking(void); //ランキングデータの保存
//
//int ReadRanking(void); //ランキングデータ読込み
//
///******************/
///*プログラムの開始*/
///******************/
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	SetMainWindowText("Match 3 Puzzle(マッチパズル"); //タイトルを設定
//	ChangeWindowMode(TRUE); //ウィンドウモードで起動
//	if (DxLib_Init() == -1)return -1; //DXライブラリの初期化処理
//	SetDrawScreen(DX_SCREEN_BACK); //描画先画面を裏にする
//	if (LoadImages() == -1)return -1; //画面読込み関数呼び出し
//	if (LoadSounds() == -1)return -1; //サウンド読込み関数呼び出し
//	//ランキングデータの読み込み
//	if (ReadRanking() == -1) return -1;
//
//	//ゲームループ
//	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {
//
//		//入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//マウスの位置を取得
//		GetMousePoint(&g_MouseX, &g_MouseY);
//
//		ClearDrawScreen(); //画面の初期化
//
//		switch (g_GameState) {
//		   case GAME_TITLE:
//				DrawGameTitle(); //ゲームタイトル処理
//				break;
//		   case GAME_INIT:  //ゲーム初期処理
//				GameInit();
//				break;
//		   case GAME_RANKING:
//				DrawRanking(); //ランキング描画処理
//				break;
//		   case GAME_END: //ゲームエンド処理
//				DrawEnd();
//				break;
//		   case GAME_MAIN: //ゲームメイン処理
//				GameMain();
//				break;
//		   case GAME_CLEAR://ゲームクリア処理
//				DrawGameClear();
//				break;
//		   case GAME_OVER:
//				DrawGameOver();//ゲームオーバー処理
//				break;
//		   case INPUT_RANKING:
//			   InputRanking(); //ランキング入力処理
//			   break;
//		}
//
//		ScreenFlip(); //DXライブラリ使用の終了処理
//	}
//
//	DxLib_End(); //DXライブラリ使用の終了処理
//
//	return 0; //ソフトの終了
//}
//
//
//
///*************************************/
///*ゲームタイトル表示（メニュー画面）*/
///************************************/
//void DrawGameTitle(void) {
//
//	//タイトルBGMをスタート
//	if (CheckSoundMem(g_TitleBGM) == 0) {
//		PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_BACK);
//	}
//
//	//タイトル画像表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	//ゲームモードを切り替える
//	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//		if (g_MouseX > 120 && g_MouseX < 290 && g_MouseY > 260 && g_MouseY < 315) {
//			g_GameState = GAME_INIT; //ゲームスタートの選択
//			StopSoundMem(g_TitleBGM); //タイトルBGMをストップ
//		}
//		else if (g_MouseX > 120 && g_MouseX < 220 && g_MouseY > 345 && g_MouseY < 400) {
//			g_GameState = GAME_END; //ゲームエンドの選択
//			StopSoundMem(g_TitleBGM); //タイトルBGMをストップ
//		}
//	}	
//}
//
///********************/
///*ゲーム初期処理*/
///********************/
//void GameInit(void) {
//
//	//ゲームメイン処理へ
//	/*g_GameState = GAME_MAIN;*/
//
//	//スコアの初期化
//	g_Score = 0;
//	//レベルの初期化
//	g_Level = 0;
//	//ミッションの初期化(レベル1は消去するブロック数が3からスタート)
//	g_Mission = 2;
//
//	//ブロック初期化
//	for (int i = 0; i < HEIGHT;i++) {
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
//				g_Block[i][j].image = GetRand(7) + 1; //1～8までの乱数を発生
//			}
//		}
//	}
//	//ステージ初期処理
//	StageInit();
//}
//
///*************************/
///*ステージにブロックを描画*/
///*************************/
//void DrawStage(void) {
//
//	//レベルを描画
//	int TmpLevel = g_Level;
//	int PosX = 600;
//	do {
//			DrawRotaGraph(PosX, 80 , 0.5f , 0 ,g_NumberImage[TmpLevel % 10], TRUE);
//			TmpLevel /= 10;
//			PosX -= 30;
//	} while (TmpLevel > 0);
//
//	//スコアを描画
//	int TmpScore = g_Score;
//	PosX = 620;
//	do {
//			DrawRotaGraph(PosX, 160 , 0.3f , 0 , g_NumberImage[TmpScore % 10], TRUE);
//			TmpScore /= 10;
//			PosX -= 20;
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
//	//ブロックを描画
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Block[i][j].flg != 0 && g_Block[i][j].image != 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y,
//					g_BlockImage[g_Block[i][j].image], TRUE);
//			}
//		}
//	}
//
//	//タイムバー描画
//	DrawBox(491, 469, 509, 469 - g_Time / 60 * 2, 0x0033ff, TRUE);
//}
//
//
//
///*************************/
///*ステージ初期処理*/
///*************************/
//void StageInit(void) {
//
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
//
//	//ブロック連鎖チェック
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			Result += RensaCheck(i, j);
//		}
//	}
//
//	if (Result == 0) {
//
//		//ゲームメイン処理へ
//		g_GameState = GAME_MAIN;
//
//		//レベル
//		g_Level += 1;
//		//ミッション
//		g_Mission += 1;
//		//制限時間
//		g_Time = TIMELIMIT;
//
//		//カウント配列初期化
//		for (int i = 0; i < ITEM_MAX; i++) {
//			g_Item[i] = 0;
//		}
//	}
//}
///********************/
///*エンド描画処理*/
///********************/
//void DrawEnd(void) {
//
//	static int WaitTime = 0;
//
//	//タイトル画像表示
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	SetFontSize(24);
//	DrawString(360, 480 - 24, "Thank you for Playing", 0x003333, 0);
//
//	//タイムの加算処理＆終了（３秒後）
//	if (++WaitTime > 180)g_GameState = END;
//}
//
///********************/
///*ゲームメイン*/
///********************/
//void GameMain(void) {
//
//	//ステージ画像表示
//	DrawGraph(0, 0, g_StageImage, FALSE);
//
//	//ブロック描画
//	DrawStage();
//
//	//ステータスにより処理を分ける
//	switch (g_Status) {
//	  case 0:
//		SelectBlock(); //Blockを選択
//		break;
//	  case 1:
//		FadeOutBlock(); //Blockをフェードアウトして消す
//		break;
//	  case 2:
//		MoveBlock(); //Blockの移動
//		break;
//	  case 3:
//		CheckBlock(); //Blockの連鎖チェック
//		break;
//	  case 4:
//		CheckClear(); //クリア条件の連鎖チェック
//		break;
//	}
//	//タイム変数をデクリメントして、0未満ならゲームオーバーへ移行する
//	if (--g_Time < 0) {
//		g_GameState = GAME_OVER;
//	}
//}
//
///***********************/
///*ゲームクリア描画処理*/
///**********************/
//void DrawGameClear(void) {
//
//	static int GameClearFlg = 0;
//
//	//ゲームクリア効果音再生
//	if (CheckSoundMem(g_GameClearSE) == 0) {
//		if (GameClearFlg++ == 0) {
//			PlaySoundMem(g_GameClearSE, DX_PLAYTYPE_BACK);
//
//		}
//		else {
//			/*g_GameState = GAME_TITLE;*/
//			//ステージ初期処理
//			StageInit();
//			g_GameState = GAME_MAIN;
//			GameClearFlg = 0;
//		}
//	}
//
//	//ゲームクリア画像表示
//	DrawGraph(0, 0, g_GameClearImage, FALSE);
//
//	////右クリックでメニューに戻る
//	//if (g_KeyFlg & MOUSE_INPUT_RIGHT) {
//	//	/*g_GameState = GAME_TITLE;*/
//
//	//	//ステージ初期処理
//	//	StageInit();
//	//	g_GameState = GAME_MAIN;
//
//	//}
//
//	///*DrawString(150, 450, "---- 右クリックを押してタイトルへ戻る　----", 0xffffff, 0);*/
//
//	/*SetFontSize(20);
//	DrawString(150, 450, "---- 右クリックで次のステージへ　----", 0xffffff, 0);*/
//
//}
//
///*************************/
///*ゲームオーバー描画処理*/
///************************/
//void DrawGameOver(void) {
//
//	static int GameOverFlg = 0;
//
//	//ゲームオーバーSEをスタート
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
//	//ゲームオーバー画像表示
//	DrawGraph(0, 0, g_GameOverImage, FALSE);
//
//	//右クリックでメニューに戻る
//	/*if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);*/
//	/*DrawString(150, 450, "---- 右クリックを押してタイトルへ戻る　----", 0xffffff, 0);*/
//
//}
//
///*************************/
///*画像読み込み*/
///************************/
//int LoadImages() {
//
//	//タイトル
//	if ((g_TitleImage = LoadGraph("images/Chapter8/title.png")) == -1)return -1;
//	//ランキング
//	if ((g_RankingImage = LoadGraph("images/Chapter8/ranking.bmp")) == -1)return -1;
//	//ステージ画像の読み込み
//	if ((g_StageImage = LoadGraph("images/Chapter8/stage.png")) == -1)return -1;
//	//ゲームクリア画像読み込み
//	if ((g_GameClearImage = LoadGraph("images/Chapter8/gameclear.png")) == -1)return -1;
//	//ゲームオーバー画像の読み込み
//	if ((g_GameOverImage = LoadGraph("images/Chapter8/gameover.png")) == -1) return -1;
//	
//	//ブロック画像読み込み（分割読み込み）
//	if (LoadDivGraph("images/Chapter8/block.png", 10, 10, 1, 48, 48, g_BlockImage) == -1)return -1;
//
//	return 0;
//
//}
//
///*************************/
///*サウンド読み込み*/
///************************/
//int LoadSounds(){
//
//	//タイトルBGM
//	if ((g_TitleBGM = LoadSoundMem("sounds/muci_hono_r01.mp3")) == -1)return -1;
//	//ゲームクリア
//	if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//	//ゲームオーバー
//	if ((g_GameClearImage = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
//
//	//マウスクリック効果音
//	if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
//	//ブロック消去効果音
//	if ((g_FadeOutSE = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
//
//	//ブロック移動効果音
//	if ((g_MoveBlockSE = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;
//
//
//	return 0;
//
//}
//
//
//
//
//
////***************************************************/
////*隣接している同色の個数を調べる(探索後に消す)
////* 引数：ｘ：現在のｘ座標,y:現在のｙ座標
////* 戻り値：1・・・3つ以上の連鎖、0・・・連鎖なし
////***************************************************/
//int RensaCheck(int y, int x) {
//	
//	int CountH = 0;
//	int ColorH = 0;
//
//	SaveBlock(); //ブロックをバックアップ
//	RensaCheckH(y, x, &CountH, &ColorH);
//	if (CountH < 3) {
//		RestoreBlock(); //ブロックの連鎖が3個未満ならブロックを戻す
//	}
//
//
//   int CountW = 0;
//   int ColorW = 0;
//    SaveBlock(); //ブロックをバックアップ
//    RensaCheckW(y, x, &CountW, &ColorW);
//      if (CountW < 3) {
//	     RestoreBlock();//ブロックの連鎖が3個未満ならブロックを戻す
//      }
//
//      if ((CountH >= 3 || CountW >= 3)) {
//	      if (CountH >= 3) {
//		       g_Item[ColorH - 1] += CountH;
//		       g_Score += CountH * 10;
//		       g_Time += 60;
//	      }
//	      if (CountW >= 3) {
//		       g_Item[ColorW - 1] += CountW;
//               g_Score += CountW * 10;
//		       g_Time += 60;
//	      }
//	      return 1;
//      }
//      return 0;
//}
//
////***************************************************/
////*縦の隣接している同色の個数を調べる(探索後に消す)
////* 引数：ｘ：ｘ座標,y:現在のｙ座標,cnt個数,col:色
////* 戻り値：縦の隣接している同色の個数
////***************************************************/
//int RensaCheckH(int y, int x, int* cnt, int* col) {
//
//	//対象ブロックが外枠の場合　return　で処理を抜ける
//	if (g_Block[y][x].image == 0) return 0;
//
//	*col = g_Block[y][x].image;
//	int c = g_Block[y][x].image; ///色を取得
//	g_Block[y][x].image = 0;
//	(*cnt)++;
//
//	if (g_Block[y + 1][x].image == c)RensaCheckH(y + 1, x, cnt, col);
//	if (g_Block[y - 1][x].image == c)RensaCheckH(y - 1, x, cnt, col);
//
//	return 0;
//}
//
////***************************************************/
////*横の隣接している同色の個数を調べる(探索後に消す)
////* 引数：ｘ：ｘ座標,y:現在のｙ座標,cnt個数,col:色
////* 戻り値：横の隣接している同色の個数
////***************************************************/
//int RensaCheckW(int y, int x, int* cnt, int* col) {
//
//	//対象ブロックが外枠の場合　return　で処理を抜ける
//	if (g_Block[y][x].image == 0) return 0;
//
//	*col = g_Block[y][x].image;
//	int c = g_Block[y][x].image; ///色を取得
//	g_Block[y][x].image = 0;
//	(*cnt)++;
//
//	if (g_Block[y][x+1].image == c)RensaCheckW(y, x+1, cnt, col);
//	if (g_Block[y][x-1].image == c)RensaCheckW(y , x-1, cnt, col);
//
//	return 0;
//}
//
///***************************************************/
///*ブロックをバックアップする
///***************************************************/
//void SaveBlock(void)
//{
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].backup = g_Block[i][j].image;
//		}
//	}
//}
//
///***************************************************/
///*バックアップブロックを表す
///***************************************************/
//void RestoreBlock(void)
//{
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].image = g_Block[i][j].backup;
//		}
//	}
//}
//
///***************************************************/
///*ブロックを選択
///***************************************************/
//void SelectBlock(void)
//{
//	static int ClickFlg = 0;
//
//	int SelectX = g_MouseX / BLOCKSIZE;
//	int SelectY = g_MouseY / BLOCKSIZE;
//
//	//選択ブロックの範囲を制御
//	if (SelectX < 0)SelectX = 0;
//	if (SelectX > WIDTH - 3)SelectX = WIDTH - 3;
//	if (SelectY < 0)SelectY = 0;
//	if (SelectY > HEIGHT - 3)SelectY = HEIGHT - 3;
//
//	//クリックでブロック選択
//	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//		//クリック時の効果音
//		PlaySoundMem(g_ClickSE, DX_PLAYTYPE_BACK);
//		if (ClickFlg == 0) {
//			g_SelectX1 = SelectX;
//			g_SelectY1 = SelectY;
//			ClickFlg = 1;
//
//			/*else if (ClickFlg == 1)*/
//		}
//		else if (ClickFlg == 1 && ((abs(g_SelectX1 - SelectX) == 1 && abs(g_SelectY1 - SelectY) == 0) || (abs(g_SelectX1 - SelectX) == 0 && abs(g_SelectY1 - SelectY) == 1))) {
//
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
//
//	//選択ブロック交換
//	if (ClickFlg == 2) {
//		int TmpBlock = g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image;
//		g_Block[g_SelectY1 + 1][g_SelectX1 + 1].image = g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image;
//		g_Block[g_SelectY2 + 1][g_SelectX2 + 1].image = TmpBlock;
//		
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
//			//連鎖が3つ以上ならブロックを消し、ブロック移動処理へ移行
//			g_Status = 1;
//		}
//		//次にクリックができるように、ClickFlgを0にする。
//		ClickFlg = 0;
//	}
//}
//
////***************************************************/
///*ブロック連鎖チェック
///***************************************************/
//void CheckBlock(void)
//{
//	int Result = 0;
//
//	//ブロック連鎖チェック
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1;j++) {
//			Result += RensaCheck(i, j);
//		}
//	}
//
//	//連鎖がなくなれば、ブロック選択へ移行する。
//	//そうでなければ、ブロック移動へ移行して連鎖チェックを継続する
//	if (Result == 0){
//	       //ブロック選択処理へ移行する。
//	       /*g_Status = 0;*/
//
//		//クリア条件のチェック処理へ移行
//		g_Status = 4;
//	}
//	else {
//		//連鎖が3つ以上ならブロックを消し、ブロック移動処理へ移行する。
//		g_Status = 1;
//	}
//}
//
//
////***************************************************/
///*クリア条件のチェック
///***************************************************/
//void CheckClear(void)
//{   
//	//クリア条件
//	//クリア条件フラグを0(ゼロ)とし、各スクールの消去ブロックが
//	//レベルよりも数が少なかったら、チェック処理を中断してゲームを続行する
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
//
////***************************************************/
///*消去するブロックをフェードアウトする
///***************************************************/
//void FadeOutBlock(void)
//{
//	//フェードアウト時効果音を再生
//	if (CheckSoundMem(g_FadeOutSE) == 0) {
//		PlaySoundMem(g_FadeOutSE, DX_PLAYTYPE_BACK);
//	}
//	static int BlendMode = 255; 
//	//描画ブレンドモードをアルファブレンドにする
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendMode);
//	for (int i = 1; i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, 
//					g_BlockImage[g_Block[i][j].backup], TRUE);
//			}
//		}
//	}
//	//描画ブレンドモードをノーマルブレンドにする
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
//
///***************************************************/
///*ブロック移動
///***************************************************/
//void MoveBlock(void)
//{
//	//ブロック効果音を再生
//	PlaySoundMem(g_MoveBlockSE, DX_PLAYTYPE_BACK);
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
//
//	//空のブロックを生成する処理
//	for (int i = 1;i < HEIGHT - 1; i++) {
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				g_Block[i][j].image = GetRand(7) + 1;
//			}
//		}
//	}
//
//	//ブロック選択処理へ移行
//	//Status = 0;
//	//ブロック連鎖チェック処理へ移行
//	g_Status = 3;
//}
//
///**************************************/
////ゲームランキング描画処理
///**************************************/
//void DrawRanking(void) {
//
//	//スペースキーでメニューに戻る
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//
//	//ランキング画像表示
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//ランキング一覧を表示
//	SetFontSize(18);
//	for (int i = 0; i < RANK_MAX; i++) {
//		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-10s %10d",
//			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	DrawString(100, 450, "---- スペースキーを押してタイトルへ戻る　----", 0xffffff, 0);
//}
//
//
///**************************************/
////ランキング入力処理
///**************************************/
//void InputRanking(void) {
//	//ランキング
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//名前の入力指示文字列の描画
//	SetFontSize(16);
//	DrawString(80, 150, "ランキングに登録します", 0xFFFF00);
//	DrawString(80, 170, "名前を英字で入力", 0xFFFF00);
//
//	//名前の入力
//	DrawString(80, 200, ">", 0xFFFF00);
//	DrawBox(90, 195, 200, 220, 0xFFFF00, FALSE);
//	if (KeyInputSingleCharString(95, 200, 10, g_Ranking[RANK_MAX - 1].name, FALSE) == 1) {
//		g_Ranking[RANK_MAX - 1].score = g_Score; //データの5番目に登録
//		SortRanking(); //ランキング並べ替え
//		SaveRanking();//ランキングデータの保存
//		g_GameState = GAME_RANKING; //ゲームモードの変更
//	}
//}
//
///**************************************/
////ランキング並べ替え
///**************************************/
//void SortRanking(void) {
//
//	RankingData work;
//
//	//選択法ソート
//	for (int i = 0; i < RANK_MAX - 1;i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score <= g_Ranking[j].score) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//
//	//順位付け
//	for (int i = 0; i < RANK_MAX; i++) {
//		g_Ranking[i].no = 1;
//	}
//	//得点が同じ場合は、同じ順位とする
//	//同順位があった場合の次の順位はデータ個数が加算された順位とする
//	for (int i = 0; i < RANK_MAX - 1; i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
//
///**************************************/
////ランキングデータの保存
///**************************************/
//int SaveRanking(void) {
//
//	FILE* fp;
//	#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/Chapter8/rankingdata.txt", "w")) == NULL) {
//		//エラー処理//
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ分配列データを書き込む
//	for (int i = 0; i < RANK_MAX; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}
//
///**************************************/
////ランキングデータ読み込み
///**************************************/
//int ReadRanking(void) {
//
//	FILE* fp;
//	#pragma warning(disable:4996)
//
//	//ファイルオープン
//	if ((fp = fopen("dat/Chapter8/rankingdata.txt", "r")) == NULL) {
//		//エラー処理//
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//ランキングデータ分配列データを書き込む
//	for (int i = 0; i < RANK_MAX; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//
//	//ファイルクローズ
//	fclose(fp);
//
//	return 0;
//}