#include"DxLib.h"
#include"MoveApple.h"
#include"main.h"
#include"MoveApple.h"

MoveApple moveapple;

/***********************************************
 *�G�l�~�[�̈ړ�
 * �����F�Ȃ�
 * �߂�l�F�Ȃ�
***********************************************/
void MoveApple::EnemyControl() {
	for (int i = 0; i < APPLE_MAX; i++) {

		g_Apple[i].y += g_enemy[i].speed - PLAYER_SPEED + 1;

		switch (g_enemy[i].flg) {
		case 0: g_enemy[i].y += 2;
			break;
		case 1: g_enemy[i].y += 5;
			break;
		case 2: g_enemy[i].y += 10;
			break;
		case 3: g_enemy[i].y += 1;
			break;
		}

		if (g_enemy[i].flg == TRUE) {


			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, apple.GetApple(), TRUE, FALSE);

			//if (g_Player.flg == FALSE)continue;

			//�^���������Ɉړ�
			/*g_enemy[i].y -= g_enemy[i].speed + g_Player.speed - PLAYER_SPEED + 1;*/

			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > applegame.getSCREEN_HEIGHT() + g_enemy[i].h)g_enemy[i].flg = FALSE;
		}
	}
	if (applegame.GetMileage() / 5 % 50 == 0) {
		CreateEnemy();
	}
}

