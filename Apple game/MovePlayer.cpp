#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
MovePlayer::MovePlayer() {

	saigo = 0;

	playerX = 320.f - 16; // X���W

	//playerY = 240.0f - 16; // Y���W

	kasoku = 0.43f; // ����

	//speed = 0;  // ���x

	moobX = 0.0f; // �ړ���	  

	moob; // �ړ��͈�

	angle = 0;  // �͈�

	cosT[360];  // �~�͈�
}
void MovePlayer::PlayerControl(int a, int b)
{

	//�ړ��͈�
	for (moob = 0; moob < 360; moob++) {

		//�~����
		cosT[moob] = (float)cos(moob * M_PI / 180);  //�R�U�O�x����P�W�O�x�̊Ԃ̈ړ��ύX
	}

	angle = -1; //�Ƃ肠�����p�x��-1�ɂ��Ă���


	//���E�ړ�
	if (p_flg == TRUE) {


		//���ړ�
		if (applegame.getNowKey() & PAD_INPUT_LEFT) angle = 180;


		//�E�ړ�
		if (applegame.getNowKey() & PAD_INPUT_RIGHT) angle = 0;

		//�ړ����f angle�̒l���ς���Ă�����ړ��ʂ�ύX����
		if (angle != -1) {

			moobX += cosT[angle] * kasoku;

		}
		else /*if (angle == -1)*/ {   //angle�̒l���ς���Ă�����ړ��ʂ�ύX����

			moobX -= cosT[angle - 1] * kasoku;


		}

		p_x += moobX;



	}

	//�v���C���[�̕\��
	//���E�ړ�
	if (p_flg == TRUE) {

		if (applegame.getNowKey() & PAD_INPUT_RIGHT) {
			saigo = a;
			DrawGraph(p_x, p_y, saigo, TRUE);
		}

		if (applegame.getNowKey() & PAD_INPUT_LEFT) {
			saigo = b;
			DrawGraph(p_x, p_y, saigo, TRUE);
		}
		else
			DrawGraph(p_x, p_y, saigo, TRUE);
	}
	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (p_x < 0)  p_x = 0;
	if (p_x > applegame.getSCREEN_WIDTH() - 90)  p_x = applegame.getSCREEN_WIDTH() - 90;
}