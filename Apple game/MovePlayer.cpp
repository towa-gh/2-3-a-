#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
void MovePlayer::PlayerInit() {
	player.flg = TRUE;
	player.x = 320;
	player.y = 380;
	player.w = 60;
	player.h = 100;
	player.angle = 0.0;
	player.count = 0;
	player.speed = 5;
}
MovePlayer::MovePlayer() {
	PlayerInit();
	saigo = 0;

	//kasoku = 0.43f; // ����

	////speed = 0;  // ���x

	//moobX = 0.0f; // �ړ���	  

	//angle = 0;  // �͈�

	//cosT[360] = 0;  // �~�͈�
}

void MovePlayer::PlayerControl(int a, int b)
{
	//DrawGraph(player.x, player.y, a, TRUE);

	//�ړ��͈�
	//for (moob = 0; moob < 360; moob++) {
	//	//�~����
	//	cosT[moob] = (float)cos(moob * M_PI / 180);  //�R�U�O�x����P�W�O�x�̊Ԃ̈ړ��ύX
	//}

	//angle = -1; //�Ƃ肠�����p�x��-1�ɂ��Ă���

	//���E�ړ�
	if (player.flg == TRUE) {
		saigo = a;
		//���ړ�
		if (applegame.getNowKey() & PAD_INPUT_LEFT) {
			//angle = 180;
			saigo = b;
			DrawGraph(player.x, player.y, saigo, TRUE);
			player.x -= player.speed;
		}
		//�E�ړ�
		if (applegame.getNowKey() & PAD_INPUT_RIGHT) {
			//angle = 0;
			saigo = a;
			DrawGraph(player.x, player.y, saigo, TRUE);
			player.x += player.speed;
		}
		else
			DrawGraph(player.x, player.y, saigo, TRUE);
	}
	//	if (angle != -1) {//�ړ����f angle�̒l���ς���Ă�����ړ��ʂ�ύX����
	//		moobX += cosT[angle + 1] * kasoku;
	//	}
	//	if (angle == -1) {   //angle�̒l���ς���Ă�����ړ��ʂ�ύX����
	//		moobX -= cosT[angle - 1] * kasoku;
	//	}
	//	player.x += moobX;
	//}

	//�v���C���[�̕\��
	//���E�ړ�

	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (player.x < -30)  player.x = -30;
	if (player.x > applegame.getSCREEN_WIDTH() - 90)  player.x = applegame.getSCREEN_WIDTH() - 90;
}