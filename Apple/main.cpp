/***********************************************
 * 第5章　ミニゲームレースを作る（２）
 *        レース＆避けゲー
 ***********************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define RANKING_DATA 5
 /***********************************************
  * 定数の宣言
 ***********************************************/
 //画面の大きさ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;
//敵機の最大数
const int ENEMY_MAX = 10;
/***********************************************
 * 変数の宣言
 ***********************************************/

int g_OldKey;				//前回の入力キー
int g_NowKey;				//今回の入力キー
int g_KeyFlg;				//入力キー情報
int g_GameState = 0;		//ゲームモード
int g_TitleImage;			//画像用変数
int g_Menu, g_Cone;			//メニュー画面変数
int g_Score = 0;			//スコア
int g_RankingImage;			//画像用変数
int g_WaitTime = 0;			//待ち時間
int g_EndImage;
int g_Mileage;				//走行距離
int g_StageImage;
int g_Mileage1;
int StartTime;
//敵キャラカウント
int g_EnemyCount1;
int g_Teki;
int g_Car, g_Barrier;		//キャラ画像変数
//ランキングデータ（構造体）
struct RankingData {
	int no;
	char name[11];
	long score;
};
//ランキングデータ変数宣言
struct RankingData	g_Ranking[RANKING_DATA];

//時期の構造体
struct PLAYER {
	int flg;
	int x, y;
	int w, h;
	double angle;
	int count;
	int speed;
};
//自機
struct PLAYER g_player;
//敵機の構造体
struct ENEMY {
	int flg;			//使用フラグ
	int type;			//タイプ
	int img;			//画像
	int x, y, w, h;		//座標x,y、幅 w、高さ h
	int speed;			//移動速度
	int point;			//スコア加算
	double angle;		//角度
	double first_x;		//最初に出てきた時のｘ
	double next_x;		//最初に出てきた時のｘ
};
//敵機
struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,63,0,1 };
struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };
/***********************************************
 * 関数のプロトタイプ宣言
 ***********************************************/
void GameInit(void);		//ゲーム初期化処理
void GameMain(void);		//ゲームメイン処理
int LoadImages();			//画像読み込み
void PlayerControl();		//自機処理
void EnemyControl();		//敵機処理
int CreateEnemy();			//敵機生成処理
int HitBoxPlayer(PLAYER* p, ENEMY* e);			//当たり判定
 /***********************************************
  * プログラムの開始
  ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// タイトルを Drive&Avoid に変更
	SetMainWindowText("Apple Game");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return-1;


	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化

		switch (g_GameState) {
		case 0:
			GameInit();		//ゲーム初期処理
			break;
		case 1:
			GameMain();
			break;
		}
		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}

/***********************************************
 * ゲーム初期処理
 ***********************************************/
void GameInit(void)
{
	//スコアの初期化
	g_Score = 0;

	//走行距離を初期化
	g_Mileage = 0;

	//敵１をよけた数の初期設定
	g_EnemyCount1 = 0;

	//プレイヤー初期設定
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;

	//エネミーの初期処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}

	//ゲームメイン処理へ
	g_GameState = 1;
}
/***********************************************
 * ゲームメイン
 ***********************************************/
void GameMain(void)
{
	EnemyControl();

	PlayerControl();
}
/***********************************************
 * 画像読込み
 ***********************************************/
int LoadImages()
{
	//敵
	if (g_Teki = LoadGraph("images/chapter5/images/apple.bmp") == -1)return-1;
	//プレイヤー
	if ((g_Car = LoadGraph("images/chapter5/images/Right.bmp")) == -1)return-1;
	return 0;
}
/***********************************************
 * プレイヤーの移動
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void PlayerControl() {
	////ゲームオーバー処理へ
	//if (g_player.fuel <= 0)g_GameState = 6;
	//Ｚキーで加速
	if (g_KeyFlg & PAD_INPUT_A && g_player.speed < 10)g_player.speed += 1;
	//Ⅹキーで減速
	if (g_KeyFlg & PAD_INPUT_B && g_player.speed > 1)g_player.speed -= 1;

	//上下左右移動
	if (g_player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_UP)g_player.y -= g_player.speed;
		if (g_NowKey & PAD_INPUT_DOWN)g_player.y += g_player.speed;
		if (g_NowKey & PAD_INPUT_LEFT)g_player.x -= g_player.speed;
		if (g_NowKey & PAD_INPUT_RIGHT)g_player.x += g_player.speed;
	}
	//画像をはみ出さないようにする
	if (g_player.x < 32)g_player.x = 32;
	if (g_player.x > SCREEN_WIDTH - 180)g_player.x = SCREEN_WIDTH - 180;
	if (g_player.y < 60)g_player.y = 60;
	if (g_player.y > SCREEN_HEIGHT - 60)g_player.y = SCREEN_HEIGHT - 180;

	//プレイヤーの表示
	if (g_player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, -M_PI / 18, g_Car, TRUE, FALSE);
		}
		else if (g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);
		}
		else {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Car, TRUE, FALSE);
		}
	}
	else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 8 * (++g_player.count / 5), g_Car, TRUE, FALSE);
		if (g_player.count >= 80)g_player.flg = TRUE;
	}
	//敵をよけた数を表示
	SetFontSize(16);
	DrawFormatString(510, 20, 0x000000, "ハイスコア");
	DrawFormatString(560, 40, 0xFFFFFF, "%08d", g_Ranking[0].score);
	DrawFormatString(510, 80, 0x000000, "避けた数");
	DrawRotaGraph(523, 120, 0.3f, 0, g_Teki, TRUE, FALSE);

	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
}
/***********************************************
 * エネミーの移動
 * 引　数：なし
 * 戻り値：なし
 ***********************************************/
void EnemyControl()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//敵の表示
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);
			if (g_player.flg == FALSE)continue;

			//まっすぐ下に移動
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;
			//画面をはみ出したら消去
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
			//敵機を追い越したらカウントする
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {
				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0)g_EnemyCount1++;
			}
			//当たり判定
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE) {
				g_player.flg = FALSE;
				g_player.speed = PLAYER_SPEED;
				g_player.count = 0;
				g_enemy[i].flg = FALSE;
			}
		}
	}
	//走行距離ごとに敵出現パターンを制御する
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}
/**********************************************
 * 敵機の生成
 * 引　数：なし
 * 戻り値：TRUE:成功 FALSE:失敗
 ***********************************************/
int CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = g_Teki;
			g_enemy[i].img = g_Teki;
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].first_x = g_enemy[i].x;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//成功
			return TRUE;
		}
	}
	return FALSE;
}
/***********************************************
 * 自機と敵機の当たり判定(四角)
 * 引　数：PLAYERポインタ
 * 戻り値：TRUE:当たり FALSE:なし
 ***********************************************/
int HitBoxPlayer(PLAYER* p, ENEMY* e) {
	//x,yは中心座標とする
	int sx1 = p->x - (p->w / 2);
	int sy1 = p->y - (p->h / 2);
	int sx2 = sx1 + p->w - 7;
	int sy2 = sy1 + p->h - 13;

	int dx1 = e->x - (e->w / 2);
	int dy1 = e->y - (e->h / 2);
	int dx2 = dx1 + e->w - 7;
	int dy2 = dy1 + e->h - 13;

	//短形が重なっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}
