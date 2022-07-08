/****************************************************************************************************************
*** 　第５章　ミニゲームを作る（２）
***
*** 　レース＆避けゲー
*****************************************************************************************************************/
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"Main.h"

MovePlayer moveplayer;

///****************************************************************************************************************
//***
//***　　　　　　　　　　　　　　　定数の宣言
//***
//*****************************************************************************************************************/
//

int MovePlayer::getSCREEN_HEIGHT() {

	return SCREEN_HEIGHT;
}

int MovePlayer::getSCREEN_WIDTH() {

	return SCREEN_WIDTH;
}



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

int g_Player, g_PlayerRight, g_PlayerLeft;          //キャラ画像変数


int MovePlayer::getNowKey() {

	return  g_NowKey;

}


/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　関数のプロトタイプ宣言
***
*****************************************************************************************************************/
void GameInit(void);           //ゲーム初期化処理
void GameMain(void);           //ゲームメイン処理


int LoadImages();              //画像読み込み

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

		//// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化


		switch (g_GameState) {
		

		case 0:
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


///****************************************************************************************************************
//***
//***　　　　　　　　　　　　　　ゲーム初期処理
//***
//*****************************************************************************************************************/
void GameInit(void)
{
	

	//プレイヤーの初期設定
	
	player.getPlayer();
	


	//ゲームメイン処理へ
	g_GameState = 5;



}



/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームメイン
***
*****************************************************************************************************************/
void  GameMain(void)
{

	

	player.PlayerControl();


	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);


}
MovePlayer::MovePlayer(){
	g_Player = 0;
	g_PlayerRight = 0;
	g_PlayerLeft = 0;
}
int MovePlayer::getg_Player() {

	return g_Player;
}

int MovePlayer::getg_PlayerRight() {

	return g_PlayerRight;
}

int MovePlayer::getg_PlayerLeft() {

	return g_PlayerLeft;
}



///****************************************************************************************************************
//***
//***　　　　　　　　　　　　　　画像読み込み
//***
//*****************************************************************************************************************/
int LoadImages()
{


	//プレイヤー
	if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.png")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	return 0;


}
