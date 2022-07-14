#include "DxLib.h"
#include"Hitbox.h"
/***********************************************
 *自機と敵機の当たり判定(四角)
 * 引数：PLAYER ポインタ
 * 戻り値：TRUE:当たり　FALSE:なし
***********************************************/
Box box;

bool Box::CheckHit(const PBOX& pbox, const ABOX& abox)
{
	if ((pbox.right > abox.left) &&
		(pbox.left < abox.right))
	{
		if ((pbox.bottom > abox.top) &&
			(pbox.top < abox.bottom))
		{
			return true;
		}
	}

	return false;
}