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
int g_StartTime; //スタート時間
int Ringo[4]; //リンゴ別の画像変数
int RingoScore[4]; //リンゴ別のスコア
int Score; //リンゴの総合スコア
int Time; //時間


const  int TIMELIMIT = 15000;

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
void Pause(void); //ポーズ処理
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

		case 2:
			Pause();
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
	if (g_NowKey & PAD_INPUT_RIGHT || g_NowKey & PAD_INPUT_LEFT)g_GameState = 1;

	//現在経過時間を得る
	g_StartTime = GetNowCount();

	//制限時間の初期設定
	 Time = TIMELIMIT * 2 - (GetNowCount() - g_StartTime);

	SetFontSize(43);
	DrawString(00, 200, "左右に動かしてください", 0xffffff, 0);

	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME：", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);


	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);


	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);


	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);


	SetFontSize(20);
	DrawString(515, 202, "SCORE：", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]);
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]);
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]);
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]);
}
/***********************************************
 *ゲームメイン
***********************************************/
void GameMain(void) {
	moveplayer.PlayerControl(g_PlayerRight, g_PlayerLeft);
	moveapple.AppleControl();

	//スペースキーを押したらポーズへ
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 2;

	if (g_KeyFlg == !PAD_INPUT_M) {

		//計測時間を過ぎたらゲームオーバー
		Time = TIMELIMIT * 2 - (GetNowCount() - g_StartTime);

		if (Time <= 0) {
			//g_GameState = GAME_OVER;
			Time = 0;
		}
	}

	//スコア等表示領域
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME：", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);  //赤リンゴの描画

	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);  //緑リンゴの描画
	
	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);  //黄リンゴの描画

	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);  //毒リンゴの描画

	SetFontSize(20);
	DrawString(515, 202, "SCORE：", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]); //赤リンゴのスコア
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]); //緑リンゴのスコア
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]); //黄リンゴのスコア
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]); //毒リンゴのスコア
}

/***********************************************
 *ポーズ
***********************************************/
void Pause() {

	////スペースキーを押したらゲームメイン処理へ
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 1;

	SetFontSize(50);
	DrawString(170, 200, "ポーズ", 0xffffff, 0);

	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME：", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);

	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);

	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);

	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);


	SetFontSize(20);
	DrawString(515, 202, "SCORE：", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]);
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]);
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]);
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]);

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

	//リンゴ
	Ringo[0] = LoadGraph("images/apple.png"); //赤リンゴ
	Ringo[1] = LoadGraph("images/GreenApple1.png"); //緑リンゴ
	Ringo[2] = LoadGraph("images/YellowApple1.png"); //黄リンゴ
	Ringo[3] = LoadGraph("images/PoisonApple.png"); //毒リンゴ

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

