#include"DxLib.h"
#include"MoveApple.h"
#include"Hitbox.h"
#include"main.h"

MoveApple moveapple;

void MoveApple::AppleInit() {
	for(int i=0;i<APPLE_MAX;i++)
	g_Apple[i].flg = 1;
	g_Apple->type = 0;
	g_Apple->img = 0;
	g_Apple->x = 0;
	g_Apple->y = 0;
	g_Apple->w = 0;
	g_Apple->h = 0;
	g_Apple->speed = 0;
	g_Apple->point = 0;
	for (int i = 0; i < APPLE_MAX; i++) {
		g_Apple[i].flg = FALSE;
	}
}
int MoveApple::CreateEnemy() {
	for (int i = 0; i < APPLE_MAX; i++) {

		if (g_Apple[i].flg == FALSE) {
			g_Apple[i].flg = TRUE;
			g_Apple[i].type = GetRand(2);
			g_Apple[i].img = applegame.getg_Appleimage();//[g_enemy[i].type];
			g_Apple[i].x = GetRand(6) * 70 + 40;
			g_Apple[i].y = -50;
			g_Apple[i].w = 60;
			g_Apple[i].h = 60;
			g_Apple[i].speed = g_Apple[i].type * 2;
			g_Apple[i].point = 1;
			//成功
			return TRUE;
		}
	}
	//失敗
	return FALSE;
}

/***********************************************
 *エネミーの移動
 * 引数：なし
 * 戻り値：なし
***********************************************/
void MoveApple::AppleControl(Player player) {
	for (int i = 0; i < APPLE_MAX; i++) {
		switch (g_Apple[i].type) {
		case 0: g_Apple[i].y += 2;
			break;
		case 1: g_Apple[i].y += 5;
			break;
		case 2: g_Apple[i].y += 10;
			break;
		case 3: g_Apple[i].y += 1;
			break;
		}

		if (g_Apple[i].flg == TRUE) {

			//敵の表示
			DrawRotaGraph(g_Apple[i].x, g_Apple[i].y, 0.7f, 0, applegame.getg_Appleimage()/*g_Apple[i].img*/, TRUE, FALSE);

			//if (p_flg == FALSE)continue;

			//画面をはみ出したら消去
			if (g_Apple[i].y - 50 > applegame.getSCREEN_HEIGHT())g_Apple[i].flg = FALSE;
			if (hitbox.HitBoxPlayer(&player,&g_Apple[i]) == TRUE) {
				player.flg = FALSE;
				g_Apple[i].flg = FALSE;
			}
		}
	}

	if (applegame.getMileage() / 5 % 50 == 0) {
		CreateEnemy();
	}
}

