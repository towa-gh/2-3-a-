#include"DxLib.h"
#include"CreateApple.h"
#include"main.h"

Create create;

/***********************************************
 *�����S�̐���
 * �����F�Ȃ�
 * �߂�l�FTRUE:�����@FALSE:���s
***********************************************/
int Create::CreateEnemy() {
	for (int i = 0; i < APPLE_MAX; i++) {
		if (g_Apple[i].flg == FALSE) {
			g_Apple[i] = g_Apple00;
			g_Apple[i].type = GetRand(2);
			g_Apple[i].img = apple.GetApple();//[g_enemy[i].type];
			g_Apple[i].x = GetRand(4) * 105 + 40;
			g_Apple[i].speed = g_Apple[i].type * 2;
			//����
			return TRUE;
		}
	}
	//���s
	return FALSE;
}
