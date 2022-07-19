/***********************************************
 ** 　第5章　ミニゲームをつくる(2)
 **　　　　　　　レース＆避けゲー
 ***********************************************/
#include "DxLib.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include"main.h"
#include"BaseAP.h"
#include"Hitbox.h"
#include"MovePlayer.h"
#include"MoveApple.h"
#define RANKING_DATA 5
 /***********************************************
  *変数宣言
  ***********************************************/
AppleGame applegame;
BaseAP baseap;

int g_OldKey;//前回の入力キー
int g_NowKey;//今回の入力キー
int g_KeyFlg;//入力キー情報
int g_GameState = 0;//ゲームモード
int g_TitleImage;//画像用変数
int g_Score = 0;//スコア
int g_WaitTime = 0;//待ち時間
int g_EndImage;
int g_Mileage;//走行距離
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;//敵カウント
int g_Appleimage;//キャラ画像変数
int g_Player, g_PlayerRight, g_PlayerLeft;          //キャラ画像変数
int g_StageImage;

/***********************************************
 *定数を宣言
 ***********************************************/

 //自機の初期化

// ランキングデータ（構造体）
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
// ランキングデータ変数宣言
struct	RankingData		g_Ranking[10];

/***********************************************
 *関数のプロトタイプ宣言
 ***********************************************/

void GameInit(void);//ゲーム初期化処理
void GameMain(void);//ゲームメイン処理
int LoadImages();
/***********************************************
 *プログラムの開始
 ***********************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Drive&Avoid");//タイトルを設定
	ChangeWindowMode(TRUE);//ウィンドウモードで起動
	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
	if (LoadImages() == -1)return -1;//画像読み込み関数を呼び出し

	//ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
		ClearDrawScreen();//画像の初期化

		switch (g_GameState) {
		case 0:
			GameInit();		//ゲーム初期処理
			break;
		case 1:
			GameMain();     //ゲームメイン処理
			break;
		}
		ScreenFlip();     //裏画面の内容を表画面に反映
	}
	DxLib_End();

	return 0;
}
/***********************************************
 *ゲーム初期処理
 ***********************************************/

void GameInit(void) {
	//スコアの初期化
	g_Score = 0;

	//走行距離を初期化
	g_Mileage = 0;

	//敵1を避けた数を初期化
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;

	//プレイヤーの初期設定
	baseap.PlayerInit();

	//エネミーの初期設定
	baseap.AppleInit();

	//ゲームメイン処理へ
	g_GameState = 1;
}
/***********************************************
 *ゲームメイン
***********************************************/
void GameMain(void) {
	moveplayer.PlayerControl(g_PlayerRight, g_PlayerLeft);
	moveapple.AppleControl();
}


/***********************************************
*画像読み込み
***********************************************/

int LoadImages() {
	//敵
	if ((g_Appleimage = LoadGraph("images/apple.png")) == -1)return-1;
	//if ((g_Appleimage[1] = LoadGraph("images/GreenApple1.png")) == -1)return-1;
	//if ((g_Appleimage[2] = LoadGraph("images/YellowApple1.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp")) == -1)return-1;

	//ステージ背景
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//プレイヤー
	if ((g_PlayerRight = LoadGraph("images/Right.png")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Left.bmp")) == -1)return -1;

	return 0;
}

int AppleGame::getg_Appleimage() {
	return g_Appleimage;
}
int AppleGame::getMileage() {
	return g_Mileage;
}
int AppleGame::getNowKey() {
	return g_NowKey;
}
int AppleGame::getSCREEN_WIDTH() {
	return SCREEN_WIDTH;
}
int AppleGame::getSCREEN_HEIGHT() {
	return SCREEN_HEIGHT;
}
int AppleGame::getg_PlayerLeft(int a) {
	return g_PlayerLeft;
}
int AppleGame::getg_PlayerRight(int b) {
	return g_PlayerRight;
}

