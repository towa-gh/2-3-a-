#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "AppleMove.h"
#include "main.h"

Move move;


/********************************/
 /*  変数の宣言*/
/*********************************/
int	g_OldKey;				// 前回の入力キー
int	g_NowKey;				// 今回の入力キー
int	g_KeyFlg;				// 入力キー情報

int g_GameState = 0;	// ゲームモード

int	g_TitleImage;		// 画像用変数

//int g_WaitTime = 0; //待ち時間

//int g_StageImage;

int g_apple;
//
//int g_Mileage;

/********************************/
 /*  定数の宣言*/
/*********************************/
//画面領域の大きさ
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

//自機の初期値
//const int PLAYER_POS_X = SCREEN_WIDTH / 2;
//const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
//const int PLAYER_WIDTH = 63;
//const int PLAYER_HEIGHT = 120;
//const int PLAYER_SPEED = 5;


//敵機の最大数
//const int APPLE_MAX = 10;//20 //もと8



////敵機構造体
//struct ENEMY {
//	int flg; //使用フラグ
//	int type; //タイプ
//	int img; //画像
//	int x, y, w, h; //座標x,y　幅　w 高さ　h
//	int speed; //移動速度
//	int point; //スコア加算
//
//
//};

//敵機
//struct ENEMY g_enemy[APPLE_MAX];
//struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };
//struct ENEMY g_enemyCh = { TRUE,4,0,0,-50,18,18,0,1 };

///***********************************************
// * 関数のプロトタイプ宣言
// ***********************************************/
void GameInit(void);		//ゲーム初期化処理
void GameMain(void);		//ゲームメイン処理

int  LoadImages();		//画像読み込み

//void BackScrool(); //背景画面スクロール処理

//void EnemyControl(); //敵機処理

//int CreateEnemy(); //敵機生成処理


///***********************************************
// * プログラムの開始
// ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	SetMainWindowText("りんごゲーム");//タイトル設定

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理


	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return -1;// 画像読み込み関数を呼び出し

	 /*ゲームループ*/
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		//入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();//画面の初期化

		switch (g_GameState) {
		//case GAME_TITLE:
		//	DrawGameTitle(); //ゲームタイトル描画処理
		//	break;
		case 0 /*GAME_INIT*/:
			/*applemove.*/GameInit(); //ゲームタイトル初期処理
			break;
		//case  DRAW_RANKING:
		//	DrawRanking();//ランキング描画処理
		//	break;
		//case 3:
		//	DrawHelp();//ゲームヘルプ描画処理
		//	break;
		//case 4:
		//	DrawEnd();//ゲームエンド描画処理
		//	break;
		case 5/*GAME_MAIN*/:
			GameMain();//ゲームメイン処理
			break;
		//case 6:
		//	DrawGameOver();//ゲームオーバー描画処理
		//	break;
		//case INPUT_RANKING:
		//	InputRanking();//ランキング入力処理
		//	break;
		}
		ScreenFlip(); //裏画面の内容を表画面に反映
	}
	DxLib_End(); //DX ライブラリ使用の終了処理

	return 0; //ソフトの終了
}

///////****************************************/
//////ゲーム初期処理
//////****************************************/
void GameInit(void) {

	//ゲームメイン処理へ
	g_GameState = 5;//5;

	///*///***エネミーの初期設定***/
	//for (int i = 0; i < APPLE_MAX; i++) {

	//	g_enemy[i].flg = FALSE;

	//}
}



///****************************************/
//ゲームメイン
//****************************************/
void GameMain(void) {

	/*BackScrool();*/
	applemove.EnemyControl();
	/*PlayerControl();*/

	
}

///****************************************/
//背景画面スクロール処理
// 引数：なし
// 戻り値：なし
//****************************************/
//void BackScrool() {
//	/*g_Mileage += g_player.speed;*/
//
//	/*ステージ画像表示*/
//
//	//描画可能エリアを設定
//	SetDrawArea(0, 0, 500, 480);
//
//	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
//
//
//	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
//
//	/*エリアを戻す*/
//	SetDrawArea(0, 0, 640, 480);
//
//	//スコア等表示領域
//	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
//}



///****************************************/
//画像読み込み
//****************************************/
int LoadImages() {
	////タイトル
	//if ((g_TitleImage = LoadGraph("images/Apple/AppleT.png")) == -1)return -1;
	////メニュー
	//if ((g_Menu = LoadGraph("images/Apple/menu.bmp")) == -1)return -1;
	//if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1; 
	////ランキングデータに読み込みz
	//if (ReadRanking() == -1) return -1;
	///*ランキング画像データの読み込み*/
	//if ((g_RankingImage = LoadGraph("images/Apple/Ranking.bmp")) == -1)return -1;
	 
	////エンディング
	//if ((g_EndImage = LoadGraph("images/Apple/End.bmp")) == -1) return -1;
	//りんご
	if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1;
	
	//ステージ背景
	/*if ((g_StageImage = LoadGraph("images/Apple/mori.png")) == -1)return -1;*/
	////プレイヤー
	//if ((g_Player = LoadGraph("images/Apple/player1.png")) == -1)return -1;

	return 0;
}

int Move::getg_apple() {
	if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1;
	return 0;
}

int Move::getg_Mileage() {
	return g_Mileage;
}