#include "DxLib.h"
#include"Hitbox.h"

/***********************************************
 *���@�ƓG�@�̓����蔻��(�l�p)
 * �����FPLAYER �|�C���^
 * �߂�l�FTRUE:������@FALSE:�Ȃ�
***********************************************/
HitBox hitbox;
int HitBox::HitBoxPlayer(Player* p,Apple* a) {
	//x,y�͒��S���W�Ƃ���
	int sx1 = p->x+30;
	int sy1 = p->y+20;
	int sx2 = sx1 + p->w;
	int sy2 = sy1 + p->h;

	int dx1 = a->x - (a->w / 2);//0
	int dy1 = a->y - (a->h / 2);//2��������
	int dx2 = dx1 + a->w;//0
	int dy2 = dy1 + a->h;//2��������
	DrawBox(sx1, sy1, sx2, sy2, 0xff0000, FALSE);
	DrawBox(dx1, dy1, dx2, dy2, 0xff0000, FALSE);
	//�Z�`
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}