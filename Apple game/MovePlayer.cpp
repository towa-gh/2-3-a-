#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
MovePlayer::MovePlayer() {
	saigo = 0;
	flg = 0;          //�g�p�t���O
	x = 0;
	y = 0;          //���W��.��
	speed = 0;          //�ړ����x
}
void MovePlayer::PlayerControl(int a, int b)
{

	if (flg == TRUE) {
		if (applegame.getNowKey() & PAD_INPUT_RIGHT)x += speed;
		if (applegame.getNowKey() & PAD_INPUT_LEFT)x -= speed;
	}

	//�v���C���[�̕\��
	//�㉺���E�ړ�
	if (flg == TRUE) {

		if (applegame.getNowKey() & PAD_INPUT_RIGHT) {
			saigo = a;
			DrawGraph(x, y, saigo, TRUE);
		}

		if (applegame.getNowKey() & PAD_INPUT_LEFT) {
			saigo = b;
			DrawGraph(x, y, saigo, TRUE);
		}
		else
			DrawGraph(x, y, saigo, TRUE);
	}
	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (x < 32)  x = 32;
	if (x > applegame.getSCREEN_WIDTH() - 50)  x = applegame.getSCREEN_WIDTH() - 50;
}