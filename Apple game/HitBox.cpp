#include "DxLib.h"
#include"Hitbox.h"

/***********************************************
 *自機と敵機の当たり判定(四角)
 * 引数：PLAYER ポインタ
 * 戻り値：TRUE:当たり　FALSE:なし
***********************************************/
HitBox hitbox;
int HitBox::HitBoxPlayer(Player* p,Apple* a) {
	//x,yは中心座標とする
	int sx1 = p->x+30;
	int sy1 = p->y+20;
	int sx2 = sx1 + p->w;
	int sy2 = sy1 + p->h;

	int dx1 = a->x - (a->w / 2);//0
	int dy1 = a->y - (a->h / 2);//2ずつ増える
	int dx2 = dx1 + a->w;//0
	int dy2 = dy1 + a->h;//2ずつ増える
	DrawBox(sx1, sy1, sx2, sy2, 0xff0000, FALSE);
	DrawBox(dx1, dy1, dx2, dy2, 0xff0000, FALSE);
	//短形
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}