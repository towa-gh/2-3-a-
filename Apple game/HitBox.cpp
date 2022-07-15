#include "DxLib.h"
#include"Hitbox.h"

/***********************************************
 *自機と敵機の当たり判定(四角)
 * 引数：PLAYER ポインタ
 * 戻り値：TRUE:当たり　FALSE:なし
***********************************************/

int HitBox::HitBoxPlayer(Apple* a) {
	//x,yは中心座標とする
	int sx1 = p_x - (p_w / 2);
	int sy1 = p_y - (p_h / 2);
	int sx2 = sx1 + p_w;
	int sy2 = sy1 + p_h;

	int dx1 = a->x - (a->w / 2);
	int dy1 = a->y - (a->h / 2);
	int dx2 = dx1 + a->w;
	int dy2 = dy1 + a->h;

	//短形
	if (sx1 + 30 < dx2 && dx1 < sx2 - 30 && sy1 + 30 < dy2 && dy1 < sy2 - 30) {
		return TRUE;
	}
	return FALSE;
}