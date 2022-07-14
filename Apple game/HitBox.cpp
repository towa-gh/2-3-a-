//#include "DxLib.h"
//#include"Hitbox.h"
///***********************************************
// *自機と敵機の当たり判定(四角)
// * 引数：PLAYER ポインタ
// * 戻り値：TRUE:当たり　FALSE:なし
//***********************************************/
//Box box;
//
//bool Box::CheckHit(const PBOX& pbox, const ABOX& abox)
//{
//	if ((pbox.right > abox.left) &&
//		(pbox.left < abox.right))
//	{
//		if ((pbox.bottom > abox.top) &&
//			(pbox.top < abox.bottom))
//		{
//			return true;
//		}
//	}
//
//	return false;
//}
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