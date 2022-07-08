#include"DxLib.h"
#include"AppleCreate.h"

Create create;

//自機の初期化
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;

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

//敵機の構造体
struct ENEMY {
	int flg;         //使用タイミング
	int type;        //タイプ
	int img;         //画像
	int x, y, w, h;  //座標x,y 幅w　高さh
	int speed;       //移動速度
	int point;       //スコア加算
	//int g_Apple;

};
const int ENEMY_MAX = 10;

//敵機
struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
struct ENEMY g_enemyCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

Create::Create() {
	ENEMY_MAX = 10;
	g_Apple = 10;
	g_GreenApple;
	g_YellowApple;
}

/***********************************************
 *エネミーの移動
 * 引数：なし
 * 戻り値：なし
***********************************************/
void Create::EnemyControl() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//敵の表示
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			//if (g_Player.flg == FALSE)continue;

			//真っすぐ下に移動
			g_enemy[i].y += g_enemy[i].speed + g_Player.speed - PLAYER_SPEED + 1;

			//画面をはみ出したら消去
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
		}
	}
}

/***********************************************
 *リンゴの生成
 * 引数：なし
 * 戻り値：TRUE:成功　FALSE:失敗
***********************************************/
int Create::CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			g_enemy[i].img = g_Apple;//[g_enemy[i].type];
			/*g_enemy[i].img = g_GreenApple;
			g_enemy[i].img = g_YellowApple;*/
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//成功
			return TRUE;
		}
	}
	//失敗
	return FALSE;
}
void Create::Init() {

	//エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}
}