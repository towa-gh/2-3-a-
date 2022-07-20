/***********************************************
 ** 　第5章　ミニゲームをつくる(2)
 **　　　　　　　レース＆避けゲー
 ***********************************************/
#include "DxLib.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include"main.h"
#include"Hitbox.h"
#include"MovePlayer.h"
#include"MoveApple.h"
#include"Fps.h"
#define RANKING_DATA 5
 /***********************************************
  *変数宣言
  ***********************************************/
AppleGame applegame;
Fps fps;
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
int g_Appleimage[10];//キャラ画像変数
int g_Player, g_PlayerRight, g_PlayerLeft;          //キャラ画像変数
int g_StageImage;
int g_TitleSound;

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
int LoadImages(); //画像
int LoadSounds(); //サウンド

/***********************************************
 *プログラムの開始
 ***********************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("AppleGame");//タイトルを設定
	ChangeWindowMode(TRUE);//ウィンドウモードで起動
	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
	if (LoadImages() == -1)return -1;//画像読み込み関数を呼び出し
	if (LoadSounds() == -1) return -1;   //サウンド読み込み関数を呼び出し

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
		fps.Update();	//更新
		fps.Draw();		//描画
		ScreenFlip();     //裏画面の内容を表画面に反映
		fps.Wait();		//待機
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
	moveplayer.PlayerInit();

	//エネミーの初期設定
	moveapple.AppleInit();

	//ゲームメイン処理へ
	g_GameState = 1;
}
/***********************************************
 *ゲームメイン
***********************************************/
void GameMain(void) {
	moveplayer.PlayerControl(g_PlayerRight, g_PlayerLeft);
	moveapple.AppleControl(moveplayer.getPlayer());
}


/***********************************************
*画像読み込み
***********************************************/
int LoadImages() {
	//ステージ背景
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//プレイヤー
	if ((g_PlayerRight = LoadGraph("images/Right.png")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Left.png")) == -1)return -1;

	return 0;
}


/***********************************************
*サウンド読み込み
***********************************************/
int LoadSounds()
{
	if((g_TitleSound=LoadSoundMem("sounds/Chapter8/sounds/muci_hono_r01.mp3")) == -1)return -1;
}

int AppleGame::getg_Appleimage(int rand) {
	switch (rand)
	{
	case 0:
		return LoadGraph("images/Apple.png");
	case 1:
		return LoadGraph("images/Apple.png");
	case 2:
		return LoadGraph("images/Apple.png");
	case 3:
		return LoadGraph("images/Apple.png");
	case 4:
		return LoadGraph("images/Apple.png");
	case 5:
		return LoadGraph("images/Apple.png");
	case 6:
		return LoadGraph("images/GreenApple.png");
	case 7:
		return LoadGraph("images/GreenApple.png");
	case 8:
		return LoadGraph("images/YellowApple.png");
	case 9:
		return LoadGraph("images/PoisonApple.png");
	}
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

