#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#define RANKING_DATA 5
 /***********************************************
  *変数宣言
  ***********************************************/

int g_OldKey;//前回の入力キー
int g_NowKey;//今回の入力キー
int g_KeyFlg;//入力キー情報
int g_GameState = 0;//ゲームモード
int g_TitleImage;//画像用変数
int g_Menu, g_Cone;//メニュー画像変数
int g_Score = 0;//スコア
int g_WaitTime = 0;//待ち時間
int g_EndImage;
int g_Mileage;//走行距離
//敵カウント
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;
int g_Apple[3];//キャラ画像変数
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int g_StageImage;
int g_Car;//キャラ画像変数


/***********************************************
 *定数を宣言
 ***********************************************/

 //自機の初期化
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 1000;

//敵機の最大数
const int ENEMY_MAX = 8;

//アイテムの最大値
const int ITEM_MAX = 3;

//敵機の構造体

struct ENEMY {
	int flg;//使用タイミング
	int type;//タイプ
	int img;//画像
	int x, y, w, h;//座標x,y 幅w　高さh
	int speed;//移動速度
	int point;//スコア加算
};
//敵機

struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
struct ENEMY g_enemyCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

//自機の構造体

struct PLAYER {
	int flg;//使用フラグ
	int x, y;//座標x,y
	int w, h;//幅w 高さh
	double angle;//機体の向き
	int count;//タイミング用
	int speed;//移動速度
};
//自機
struct PLAYER g_Player;

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
int LoadImages();//画像読み込み
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
	g_Player.flg = TRUE;
	g_Player.x = PLAYER_POS_X;
	g_Player.y = PLAYER_POS_Y;
	g_Player.w = PLAYER_WIDTH;
	g_Player.h = PLAYER_HEIGHT;
	g_Player.angle = 0.0;
	g_Player.count = 0;
	g_Player.speed = PLAYER_SPEED;

	//エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}

	//ゲームメイン処理へ
	g_GameState = 1;
}
/***********************************************
 *ゲームメイン
***********************************************/
void GameMain(void) {
}
/***********************************************
*画像読み込み
***********************************************/

int LoadImages() {
	//敵
	if ((g_Apple[0] = LoadGraph("images/Apple.png")) == -1)return-1;
	if ((g_Apple[1] = LoadGraph("images/GreenApple1.png")) == -1)return-1;
	if ((g_Apple[2] = LoadGraph("images/YellowApple1.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp", )) == -1)return-1;

	//ステージ背景
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//プレイヤー
	if ((g_Car = LoadGraph("images/Right.png")) == -1) return -1;

	return 0;
}