#include"DxLib.h"
#include"MoveApple.h"
#include"Hitbox.h"
#include"main.h"
#include"CreateApple.h"

MoveApple moveapple;
/***********************************************
 *�G�l�~�[�̈ړ�
 * �����F�Ȃ�
 * �߂�l�F�Ȃ�
***********************************************/
void MoveApple::AppleControl() {
	for (int i = 0; i < APPLE_MAX; i++) {
		switch (g_Apple[i].type) {
		case 0: g_Apple[i].y += 2;
			break;
		case 1: g_Apple[i].y += 5;
			break;
		case 2: g_Apple[i].y += 10;
			break;
		case 3: g_Apple[i].y += 1;
			break;
		}

		if (g_Apple[i].flg == FALSE) {

			//�G�̕\��
			DrawRotaGraph(150, g_Apple[i].y, 1.0f, 0, applegame.getg_Appleimage()/*g_Apple[i].img*/, TRUE, FALSE);

			//if (g_Player.flg == FALSE)continue;

			//��ʂ��͂ݏo���������
			if (g_Apple[i].y > applegame.getSCREEN_HEIGHT() + g_Apple[i].h)g_Apple[i].flg = TRUE;
			if (hitbox.HitBoxPlayer(&g_Apple[i]) == TRUE) {
				p_flg = FALSE;
				g_Apple[i].flg = TRUE;
			}
		}
	}

	if (applegame.getMileage() / 5 % 50 == 0) {
		create.CreateEnemy();
	}
}

