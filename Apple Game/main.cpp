/***********************************************
 ** 　第5章　ミニゲームをつくる(2)
 **　　　　　　　レース＆避けゲー
 ***********************************************/

#include "DxLib.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Hitbox.h"
#define RANKING_DATA 5
 /***********************************************
  *変数宣言
  ***********************************************/

PBOX pbox;
ABOX abox[ENEMY_MAX];

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

void PlayerControl();//自機処理

void EnemyControl();//敵機処理
int CreateEnemy();//敵機生成処理

//int HitBoxPlayer(PLAYERHITBOX* ph, ENEMY* e);//当たり判定

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
	//BackScrool();

	EnemyControl();

	PlayerControl();
}
///***********************************************
// *背景画像スクロール処理
// * 引数：なし
// * 戻り値：なし
//***********************************************/
//
//void BackScrool() {
//
//	g_Mileage += g_Player.speed;
//
//	//描画可能エリアを認定
//	SetDrawArea(0, 0, 500, 480);
//	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
//	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
//	//エリアを戻す
//	SetDrawArea(0, 0, 640, 480);
//	//ステージ背景
//	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
//
//}
/***********************************************
 *プレイヤーの移動
 * 引数：なし
 * 戻り値：なし
 ***********************************************/

void PlayerControl() {

	//左右移動
	if (g_Player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_LEFT) g_Player.x -= g_Player.speed;
		if (g_NowKey & PAD_INPUT_RIGHT) g_Player.x += g_Player.speed;
	}

	//画像をはみ出さないようにする
	if (g_Player.x < 32) g_Player.x = 32;

	if (g_Player.x > SCREEN_WIDTH - 180) g_Player.x = SCREEN_WIDTH - 180;

	if (g_Player.y < 60) g_Player.y = 60;

	if (g_Player.y > SCREEN_HEIGHT - 60) g_Player.y = SCREEN_HEIGHT - 60;

	//プレイヤーの表示
	if (g_Player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_Player.x, g_Player.y, 1.0f, -M_PI / 18, g_Car, TRUE, FALSE);
		}
		else if (g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_Player.x, g_Player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);
		}
		else {
			DrawRotaGraph(g_Player.x, g_Player.y, 1.0f, 0, g_Car, TRUE, FALSE);
		}
	}

	else {
		DrawRotaGraph(g_Player.x, g_Player.y, 1.0f, M_PI / 8 * (++g_Player.count / 5), g_Car, TRUE, FALSE);
		if (g_Player.count >= 80) g_Player.flg = TRUE;
	}

	//敵を避けた数を表示
	SetFontSize(16);
	DrawFormatString(510, 20, 0x000000, "ハイスコア");
	DrawFormatString(560, 40, 0xFFFFFF, "%08d", g_Ranking[0].score);
	DrawFormatString(510, 80, 0x000000, "避けた数");
	DrawRotaGraph(523, 120, 0.3f, 0, g_Apple[0], TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Apple[1], TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Apple[2], TRUE, FALSE);

	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
	DrawFormatString(560, 140, 0xFFFFFF, "%03d", g_EnemyCount2);
	DrawFormatString(610, 140, 0xFFFFFF, "%03d", g_EnemyCount3);
}
/***********************************************
 *エネミーの移動
 * 引数：なし
 * 戻り値：なし
***********************************************/

void EnemyControl() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//敵の表示
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 0.5f, 0, g_enemy[i].img, TRUE, FALSE);

			if (g_Player.flg == FALSE)continue;

			//真っすぐ下に移動
			g_enemy[i].y += g_enemy[i].speed + g_Player.speed - PLAYER_SPEED + 1;

			//画面をはみ出したら消去
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;

			//敵機を追い越したらカウントする
			if (g_enemy[i].y > g_Player.y && g_enemy[i].point == 1) {

				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0)g_EnemyCount1++;
				if (g_enemy[i].type == 1)g_EnemyCount2++;
				if (g_enemy[i].type == 2)g_EnemyCount3++;
			}
			//当たり判定
			if (box.CheckHit(pbox,abox[i]) == TRUE) {
				g_Player.flg = FALSE;
				g_enemy[i].flg = FALSE;
			}

		}
	}
	//走行距離ごとに敵出現パターンを制御する
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}

/***********************************************
 *敵機の生成
 * 引数：なし
 * 戻り値：TRUE:成功　FALSE:失敗
***********************************************/

int CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			g_enemy[i].img = g_Apple[g_enemy[i].type];
			g_enemy[i].x = GetRand(6) * 70 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//成功
			return TRUE;
		}
	}
	//失敗
	return FALSE;
}

///***********************************************
// *自機と敵機の当たり判定(四角)
// * 引数：PLAYER ポインタ
// * 戻り値：TRUE:当たり　FALSE:なし
//***********************************************/
//
//int HitBoxPlayer(PLAYER* p, ENEMY* e) {
//	//x,yは中心座標とする
//	int sx1 = p->x - (p->w / 2);
//	int sy1 = p->y - (p->h / 2);
//	int sx2 = sx1 + p->w;
//	int sy2 = sy1 + p->h;
//
//	int dx1 = e->x - (e->w / 2);
//	int dy1 = e->y - (e->h / 2);
//	int dx2 = dx1 + e->w;
//	int dy2 = dy1 + e->h;
//
//	//短形
//	if (sx1 + 30 < dx2 && dx1 < sx2 - 30 && sy1 + 30 < dy2 && dy1 < sy2 - 30) {
//		return TRUE;
//	}
//	return FALSE;
//}
/***********************************************
*画像読み込み
***********************************************/

int LoadImages() {
	//敵
	if ((g_Apple[0] = LoadGraph("images/Apple.png")) == -1)return-1;
	if ((g_Apple[1] = LoadGraph("images/GreenApple1.png")) == -1)return-1;
	if ((g_Apple[2] = LoadGraph("images/YellowApple1.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp")) == -1)return-1;

	//ステージ背景
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//プレイヤー
	if ((g_Car = LoadGraph("images/Right.png")) == -1) return -1;

	return 0;
}
