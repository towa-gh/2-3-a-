//#include "DxLib.h"
//#include"Hitbox.h"
///***********************************************
// *���@�ƓG�@�̓����蔻��(�l�p)
// * �����FPLAYER �|�C���^
// * �߂�l�FTRUE:������@FALSE:�Ȃ�
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
// *���@�ƓG�@�̓����蔻��(�l�p)
// * �����FPLAYER �|�C���^
// * �߂�l�FTRUE:������@FALSE:�Ȃ�
//***********************************************/
//
//int HitBoxPlayer(PLAYER* p, ENEMY* e) {
//	//x,y�͒��S���W�Ƃ���
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
//	//�Z�`
//	if (sx1 + 30 < dx2 && dx1 < sx2 - 30 && sy1 + 30 < dy2 && dy1 < sy2 - 30) {
//		return TRUE;
//	}
//	return FALSE;
//}