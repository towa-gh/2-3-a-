#include "DxLib.h"
#include"Hitbox.h"

/***********************************************
 *���@�ƓG�@�̓����蔻��(�l�p)
 * �����FPLAYER �|�C���^
 * �߂�l�FTRUE:������@FALSE:�Ȃ�
***********************************************/

int HitBox::HitBoxPlayer(Apple* a) {
	//x,y�͒��S���W�Ƃ���
	int sx1 = p_x - (p_w / 2);
	int sy1 = p_y - (p_h / 2);
	int sx2 = sx1 + p_w;
	int sy2 = sy1 + p_h;

	int dx1 = a->x - (a->w / 2);
	int dy1 = a->y - (a->h / 2);
	int dx2 = dx1 + a->w;
	int dy2 = dy1 + a->h;

	//�Z�`
	if (sx1 + 30 < dx2 && dx1 < sx2 - 30 && sy1 + 30 < dy2 && dy1 < sy2 - 30) {
		return TRUE;
	}
	return FALSE;
}