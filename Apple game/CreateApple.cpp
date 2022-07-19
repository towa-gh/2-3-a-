#include"DxLib.h"
#include"CreateApple.h"
#include"main.h"

Create create;

/***********************************************
 *ƒŠƒ“ƒS‚Ì¶¬
 * ˆø”F‚È‚µ
 * –ß‚è’lFTRUE:¬Œ÷@FALSE:¸”s
***********************************************/
int Create::CreateEnemy() {
	for (int i = 0; i < APPLE_MAX; i++) {
		if (g_Apple[i].flg == FALSE) {
			g_Apple[i] = g_Apple00;
			g_Apple[i].type = GetRand(2);
			g_Apple[i].img = applegame.getg_Appleimage();//[g_enemy[i].type];
			g_Apple[i].x = GetRand(6) * 70 + 40;
			g_Apple[i].speed = g_Apple[i].type * 2;
			//¬Œ÷
			return FALSE;
		}
	}
	//¸”s
	return TRUE;
}
