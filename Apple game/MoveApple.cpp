#include"DxLib.h"
#include"AppleMove.h"
#include"main.h"

Move move;

//���@�̏�����
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;

//���@�̍\����
struct PLAYER {
	int flg;//�g�p�t���O
	int x, y;//���Wx,y
	int w, h;//��w ����h
	double angle;//�@�̂̌���
	int count;//�^�C�~���O�p
	int speed;//�ړ����x
};

//���@
struct PLAYER g_Player;

//�G�@�̍\����
struct ENEMY {
	int flg;         //�g�p�^�C�~���O
	int type;        //�^�C�v
	int img;         //�摜
	int x, y, w, h;  //���Wx,y ��w�@����h
	int speed;       //�ړ����x
	int point;       //�X�R�A���Z
	//int g_Apple;

};
const int ENEMY_MAX = 10;

//�G�@
struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
struct ENEMY g_enemyCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

Move::Move() {

	ENEMY_MAX = 10;
	g_Apple = 10;
	/*g_GreenApple;
	g_YellowApple;*/
}

/***********************************************
 *�G�l�~�[�̈ړ�
 * �����F�Ȃ�
 * �߂�l�F�Ȃ�
***********************************************/
void Move::EnemyControl() {
	for (int i = 0; i < ENEMY_MAX; i++) {

		g_enemy[i].y += g_enemy[i].speed - PLAYER_SPEED + 1;

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
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
		}
	}
	if (apple.GetMileage() / 5 % 50 == 0) {
		CreateEnemy();
	}
}

/***********************************************
 *�����S�̐���
 * �����F�Ȃ�
 * �߂�l�FTRUE:�����@FALSE:���s
***********************************************/
int Move::CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);//2
			g_enemy[i].img = apple.GetApple();//[g_enemy[i].type];
			/*g_enemy[i].img = g_GreenApple;
			g_enemy[i].img = g_YellowApple;*/
			g_enemy[i].x = GetRand(7) * 100 + 20/*105 + 40*/;//4 Get Rand
			g_enemy[i].speed = g_enemy[i].type * 2;
			//����
			return TRUE;
		}
	}
	//���s
	return FALSE;
}
void Move::Init() {

	//�G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = TRUE;
	}
}