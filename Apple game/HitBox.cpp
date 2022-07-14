#include "DxLib.h"
#include"Hitbox.h"
/***********************************************
 *���@�ƓG�@�̓����蔻��(�l�p)
 * �����FPLAYER �|�C���^
 * �߂�l�FTRUE:������@FALSE:�Ȃ�
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