//#include "DxLib.h"
//
///*****************/
///*列挙体の宣言*/
///*****************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_END,
//	GAME_MAIN,
//	GAME_CLEAR,
//	GAME_OVER,
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
//int g_Count; //ブロックをクリックしたカウント
//
//int g_GameClearImage; //ゲームクリア画像
//int g_GameOverImage; //ゲームオーバー画像
//
//int g_BlockImage[5]; //ブロック画像
//
//int g_Rensa; //ブロックの連鎖をカウント
//
//int g_Status; //ステージのステータス(0..プレイヤー操作中、1..ブロック落下)
//
//int g_Color = 2; //ブロックの色の数
//
//int g_StartTime; //スタート時間
//
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
//const  int HEIGHT = 22; 
//const  int WIDTH = 22; 
//const  int BLOCKSIZE = 24; 
//const  int MARGIN = 160; 
//const  int BLOCKMAX = 4;
//const  int TIMELIMIT = 60000;
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
//
///************************/
///*関数のプロトタイプ宣言*/
///************************/
//void GameInit(void); //ゲーム初期化処理
//void GameMain(void); //ゲームメイン処理
//void DrawGameTitle(void); //ゲームタイトル処理
//void DrawEnd(void); //ゲームエンド処理
//void DrawGameClear(void); //ゲームクリア処理
//void DrawGameOver(void); //ゲームオーバー処理
//
//int LoadImages(void); //画像読み込み
//
//int LoadSounds(void); //BGM読み込み
//
//void DrawStage(void); //Block[][]の中身で、画像を描画
//void EraseBlock(void); //Blockを消去
//
//int RensaCheck(int y, int x, int* cnt); //ブロックの連鎖チェック
//
//void MoveBlock(void); //ブロック移動
//
//void SaveBlock(void); //ブロックをバックアップする
//void RestoreBlock(void); //バックアップブロックを戻す
//
///******************/
///*プログラムの開始*/
///******************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	SetMainWindowText("SameGame(さめがめ)"); //タイトルを設定
//	ChangeWindowMode(TRUE); //ウィンドウモードで起動
//	if (DxLib_Init() == -1)return -1; //DXライブラリの初期化処理
//	SetDrawScreen(DX_SCREEN_BACK); //描画先画面を裏にする
//
//	if (LoadImages() == -1)return -1; //画面読込み関数呼び出し
//
//	if (LoadSounds() == -1)return -1; //サウンド読込み関数呼び出し
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
//		case GAME_TITLE:
//			DrawGameTitle(); //ゲームタイトル処理
//			break;
//		case GAME_INIT:  //ゲーム初期処理
//			GameInit();
//			break;
//		case GAME_END: //ゲームエンド処理
//			DrawEnd();
//			break;
//		case GAME_MAIN: //ゲームメイン処理
//			GameMain();
//			break;
//		case GAME_CLEAR://ゲームクリア処理
//			DrawGameClear();
//			break;
//		case GAME_OVER:
//			DrawGameOver();//ゲームオーバー処理
//			break;
//		
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
///*************************************/
///*ゲームタイトル表示（メニュー画面）*/
///************************************/
//void DrawGameTitle(void) {
//	
//	//タイトルBGMをスタート
//	if(CheckSoundMem(g_TitleBGM) == 0){
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
//	else if (g_KeyFlg & MOUSE_INPUT_RIGHT) {
//		if (++g_Color > BLOCKMAX)g_Color = 2;
//	}
//
//	SetFontSize(64);
//	DrawFormatString(340, 260, 0xffffff, "Color:%d", g_Color);
//}
//
///********************/
///*ゲーム初期処理*/
///********************/
//void GameInit(void) {
//
//	//ゲームメイン処理へ
//	g_GameState = GAME_MAIN;
//
//	//カウントの初期化
//	g_Count = 0;
//
//	//ステージステータスの初期化
//	g_Status = 0;
//
//	//現在経過時間を得る
//	g_StartTime = GetNowCount();
//
//	//ブロック初期処理
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
//				g_Block[i][j].image = GetRand(g_Color - 1) + 1;
//			}
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
///***************************************************/
///*消去するブロックをフェードアウトする
///***************************************************/
//void FadeOutBlock(void)
//{
//	//フェードアウトＳＥをスタート
//	if (CheckSoundMem(g_FadeOutSE) == 0) {
//		PlaySoundMem(g_FadeOutSE, DX_PLAYTYPE_BACK);
//	}
//
//	static int BlendMode = 255;
//	//描画ブレンドモードをアルファブレンドにする
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendMode);
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0 && g_Block[i][j].backup != 0) {
//
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y,
//					g_BlockImage[g_Block[i][j].backup], TRUE);
//
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
//	}
//
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
//	//ブロック消去
//	switch (g_Status) {
//	    case 0:
//		     EraseBlock();
//		     break;
//	    case 1:
//		     FadeOutBlock();
//		     break;
//		case 2:
//			MoveBlock();
//			 break;
//	}
//}
//	////左クリックでゲームクリアに移行
//	//if (g_KeyFlg & MOUSE_INPUT_LEFT)g_GameState = GAME_CLEAR;
//	////右クリックでゲームオーバーに移行
//	//if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_OVER;
//
//	//SetFontSize(16);
//	//DrawString(150, 420, "---- 左クリックでゲームクリアへ　----", 0xffffff, 0);
//	//DrawString(150, 450, "---- 右クリックでゲームオーバーへ　----", 0xffffff, 0);
//	
//
//
///***********************/
///*ゲームクリア描画処理*/
///**********************/
//void DrawGameClear(void) {
//
//	static int GameClearFlg = 0;
//
//	//ゲームクリアSEをスタート
//	if (CheckSoundMem(g_GameClearSE) == 0) {
//		if (GameClearFlg++ == 0) {
//			PlaySoundMem(g_GameClearSE, DX_PLAYTYPE_BACK);
//		}
//		else {
//			g_GameState = GAME_TITLE;
//			GameClearFlg = 0;
//		}
//	}
//
//	//ゲームクリア画像表示
//	DrawGraph(0, 0, g_GameClearImage, FALSE);
//
//	//右クリックでメニューに戻る
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);
//	DrawString(150, 450, "---- 右クリックを押してタイトルへ戻る　----", 0xffffff, 0);
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
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);
//	DrawString(150, 450, "---- 右クリックを押してタイトルへ戻る　----", 0xffffff, 0);
//
//}
//
///*************************/
///*画像読み込み*/
///************************/
//int LoadImages() {
//
//	//タイトル
//	if ((g_TitleImage = LoadGraph("images/Chapter7/Title.png")) == -1)return -1;
//
//	//ステージ画像の読み込み
//	if ((g_StageImage = LoadGraph("images/Chapter7/stage.png")) == -1)return -1;
//	//ゲームクリア画像読み込み
//	if ((g_GameClearImage = LoadGraph("images/Chapter7/gameclear.png")) == -1)return -1;
//	//ゲームオーバー画像読み込み
//	if ((g_GameOverImage = LoadGraph("images/Chapter7/gameover.png")) == -1)return -1;
//	//ブロック画像読み込み（分割読み込み）
//	if (LoadDivGraph("images/Chapter7/block.png", 5, 5, 1, 24, 24, g_BlockImage) == -1)return -1;
//
//	return 0;
//
//}
//
///*************************/
///*サウンド読み込み*/
///************************/
//int LoadSounds() {
//
//	//タイトルBGM
//	if ((g_TitleBGM = LoadSoundMem("sounds/muci_action_r01.mp3")) == -1)return -1;
//	//ゲームクリア
//	if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//	//ゲームオーバー
//	if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
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
///*************************/
///*ステージのブロックを描画*/
///*************************/
//void DrawStage(void) {
//
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Block[i][j].flg != 0 && g_Block[i][j].image != 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
//			}
//		}
//	}
//	SetFontSize(64);
//	DrawFormatString(40, 100, 0xffffff, "%3d", g_Count);
//	//デバック用
//	DrawFormatString(40, 400, 0xffffff, "%3d", g_Rensa);
//
//	//計測時間を過ぎたらゲームオーバー
//	int Time = TIMELIMIT * g_Color - (GetNowCount() - g_StartTime);
//	if (Time <= 0) {
//		g_GameState = GAME_OVER;
//	}
//	DrawFormatString(40, 270, 0xffffff, "%3d", Time / 1000);
//}
//
//
///*************************/
///*ブロックを消去*/
///*************************/
//void EraseBlock(void) {
//
//	//クリックでブロックを消去
//	if(g_KeyFlg & MOUSE_INPUT_LEFT){
//		PlaySoundMem(g_ClickSE, DX_PLAYTYPE_BACK);
//		int i = g_MouseY / BLOCKSIZE + 1;
//		int j = (g_MouseX - MARGIN) / BLOCKSIZE + 1;
//
//
//		if (g_Block[i][j].image != 0) {
//			//ブロックの連鎖カウントをゼロにする
//			/*g_Block[i][j].image = 0;*/
//			g_Rensa = 0;
//			//ブロックをバックアップする
//			SaveBlock();
//			//ブロックの連鎖チェック
//			RensaCheck(i, j, &g_Rensa);
//			if (g_Rensa < 2) {
//				//ブロックの連鎖が1個以下ならブロックを戻す
//				RestoreBlock();
//			}
//			else {
//				//クリックしてブロックを消した回数
//				g_Count++;
//				g_Status = 1; //ブロックを下へ移動
//			}
//
//
//		}
//	}
//}
//
///***************************************************/
///*隣接している同色の個数を調べる(探索後に消す)
//* 引数：ｘ：現在のｘ座標,y:現在のｙ座標,*cnt:連鎖数
//* 戻り値：隣接している同色の個数
///***************************************************/
//int RensaCheck(int y,int x, int *cnt)
//{
//
//	    //対象ブロックが外枠の場合returnで処理を抜ける
//	    if (x == 0 || x == WIDTH - 1 || y == HEIGHT - 1 || y == 0)return 0;
//		
//		int c = g_Block[y][x].image; ///色を取得
//		g_Block[y][x].image = 0;
//		(*cnt)++;
//
//		if (g_Block[y + 1][x].image == c)RensaCheck(y + 1, x, cnt);
//		if (g_Block[y - 1][x].image == c)RensaCheck(y - 1, x, cnt);
//		if (g_Block[y][x+1].image == c)RensaCheck(y, x+1, cnt);
//		if (g_Block[y][x-1].image == c)RensaCheck(y, x-1, cnt);
//	    
//		return 0;
//
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
///*ブロック状態のチェック
///***************************************************/
//int CheckBlock(void)
//{
//	//連鎖チェックの結果を格納する変数
//	int Result = 0;
//
//	//左下から右へ、ブロックがあれば連鎖しているかチェックする
//	for (int i = HEIGHT - 1;i > 0; i--) {
//		for (int j = 1; j < WIDTH; j++) {
//			if (g_Block[i][j].image != 0) {
//				//連鎖チェックの結果を格納
//				Result = 0;
//				RensaCheck(i, j, &Result);
//				//連鎖チェックの結果が連鎖有りの場合
//				if (Result > 1) {
//					return 2; //連鎖しているブロック有
//				}
//			}
//		}
//	}
//	//連鎖しているブロック無し、または、ブロック無し
//	if (Result == 1) {
//		return 1; //連鎖しているブロック無し
//	}
//	else {
//		return 0; //ブロック無し
//	}
//}
//
///***************************************************/
///*ブロック移動
///***************************************************/
//void MoveBlock(void)
//{
//	PlaySoundMem(g_MoveBlockSE, DX_PLAYTYPE_BACK);
//	//↓へ移動する処理
//	for (int i = 0; i < HEIGHT - 1; i++) {
//		for (int j = 0; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				for (int k = i; k > 0; k--) {
//					g_Block[k][j].image = g_Block[k - 1][j].image;
//					g_Block[k - 1][j].image = 0;
//				}
//			}
//		}
//	}
//
//	//←へ移動する処理
//	for (int j = WIDTH - 1; j > 1; j--) {   //横20→1
//		//一番下のブロックが零(ゼロ)かチェックしている
//		if (g_Block[HEIGHT - 2][j - 1].image == 0) {
//			for (int k = 0; k < HEIGHT; k++) { //縦0→20
//				for (int x = j; x < WIDTH; x++) { //横X→21
//				  //該当箇所から右側のブロックをすべて移動
//					g_Block[k][x - 1].image = g_Block[k][x].image;
//					//移動したブロックを0にしてブロックを消す
//					g_Block[k][x].image = 0;
//				}
//			}
//		}
//	}
//	g_Status = 0;
//
//	//ブロックをバックアップする
//	SaveBlock();
//	//消去できるブロックがあるかチェックする
//	int Result = CheckBlock();
//
//	if (Result == 1) { //消去できるブロックがない
//		g_GameState = GAME_OVER;
//	}
//	else if (Result == 0) { //ブロックがない
//		g_GameState = GAME_CLEAR;
//	}
//
//	//バックアップのブロックのブロックを戻す
//	RestoreBlock();
//}
//
