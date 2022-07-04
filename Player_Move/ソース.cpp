/****************************************************************************************************************
*** 　第５章　ミニゲームを作る（２）
***
*** 　レース＆避けゲー
*****************************************************************************************************************/
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#define RANKING_DATA 5

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　定数の宣言
***
*****************************************************************************************************************/

//画面領域の大きさ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//自機の初期値
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
//const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;

//敵機の最大数
const int ENEMY_MAX = 4;


/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　変数の宣言
***
*****************************************************************************************************************/
int g_OldKey;     //前回の入力キー
int g_NowKey;     //今回の入力キー
int g_KeyFlg;     //入力キー情報

int g_GameState = 0;  //ゲームモード

int g_TitleImage;     //画像用変数
int g_Menu, g_Cone;   //メニュ画像変数













int g_StageImage;

int g_Player, g_PlayerRight, g_PlayerLeft, g_Barrier;          //キャラ画像変数

int saigo = g_PlayerLeft;

//自機の構造体
struct PLAYER {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度
	

};

//自機
struct PLAYER g_player;


struct PLAYERRIGHT {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度

};

//自機
struct PLAYER g_playerright;


struct PLAYERLEFT {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度

};

//自機
struct PLAYER g_playerleft;



/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　関数のプロトタイプ宣言
***
*****************************************************************************************************************/
void GameInit(void);           //ゲーム初期化処理
void GameMain(void);           //ゲームメイン処理

void DrawGameTitle(void);      //タイトル描画処理

int LoadImages();              //画像読み込み

void PlayerControl();          //自機処理






/****************************************************************************************************************
***
***　　　　　　　　　　　　　　プログラムの開始
***
*****************************************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// タイトル設定
	SetMainWindowText("Drive&Avoid");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return-1;  //画像読み込み関数を呼び出し

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//ゲームタイトル処理
			break;
		case 1:
			GameInit();		//ゲーム初期処理
			break;
	
		case 5:
			GameMain();     //ゲームメイン処理
			break;
	
		}

		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームタイトル表示（メニュー画面）
***
****************************************************************************************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;

	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		/*if (++MenuNo > 3)MenuNo = 0;*/
		MenuNo++;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		/*if (--MenuNo < 0)MenuNo = 3;*/
		MenuNo--;
	}

	//Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;

	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//メニュー
	DrawGraph(120, 300, g_Menu, TRUE);

	//メニューカーソル
	DrawRotaGraph(90, 320 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲーム初期処理
***
*****************************************************************************************************************/
void GameInit(void)
{

	//プレイヤーの初期設定
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;

	//ゲームメイン処理へ
	g_GameState = 5;



}



/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームメイン
***
*****************************************************************************************************************/
void GameMain(void)
{

	PlayerControl();

	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);
	DrawString(150, 450, "--- スペースキーを押してタイトルに飛ぶ ---", 0xffffff, 0);

}



/****************************************************************************************************************
***                            プレイヤーの移動処理

***　　　　　　　　　　　　　　引 数  ： なし
　
***　　　　　　　　　　　　　  戻り値 ： なし

*****************************************************************************************************************/
void PlayerControl()
{




	/*int PlayerPojishonRihght= DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);*/
	int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);
	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, saigo, TRUE, FALSE);

	//プレイヤーの表示
	//上下左右移動
	if (g_player.flg == TRUE) {




		if (g_NowKey & PAD_INPUT_RIGHT) {

			int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);

			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);
			g_player.x += g_player.speed;


			saigo = g_PlayerRight;


		}



		if (g_NowKey & PAD_INPUT_LEFT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / -20, g_PlayerLeft, TRUE, FALSE);
			g_player.x -= g_player.speed;


			saigo = g_PlayerLeft;

		}




		//	if (g_player.x -= !g_player.speed) {
		//		if (g_NowKey & PAD_INPUT_RIGHT) {


		//			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);
		//			/*g_player.x += g_player.speed;*/



		//		}

		//	}

	}

	//画面をはみ出さないようにする
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > SCREEN_WIDTH - 50)  g_player.x = SCREEN_WIDTH - 50;




}


/****************************************************************************************************************
***
***　　　　　　　　　　　　　　画像読み込み
***
*****************************************************************************************************************/
int LoadImages()
{
	//タイトル
	if ((g_TitleImage = LoadGraph("images/Chapter5/io__________.bmp")) == -1)return-1;

	//メニュー
	if ((g_Menu = LoadGraph("images/Chapter5/start_m.bmp")) == -1)return-1;
	if ((g_Cone = LoadGraph("images/Chapter5/cone.bmp")) == -1)return-1;


	//プレイヤー
	if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.bmp")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	return 0;
}




