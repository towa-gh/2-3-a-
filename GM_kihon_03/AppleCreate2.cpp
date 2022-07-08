#include"DxLib.h"
#include"AppleCreate.h"

Create create;

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

Create::Create() {
	ENEMY_MAX = 10;
	g_Apple = 10;
	g_GreenApple;
	g_YellowApple;
}

/***********************************************
 *�G�l�~�[�̈ړ�
 * �����F�Ȃ�
 * �߂�l�F�Ȃ�
***********************************************/
void Create::EnemyControl() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			//if (g_Player.flg == FALSE)continue;

			//�^���������Ɉړ�
			g_enemy[i].y += g_enemy[i].speed + g_Player.speed - PLAYER_SPEED + 1;

			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
		}
	}
}

/***********************************************
 *�����S�̐���
 * �����F�Ȃ�
 * �߂�l�FTRUE:�����@FALSE:���s
***********************************************/
int Create::CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			g_enemy[i].img = g_Apple;//[g_enemy[i].type];
			/*g_enemy[i].img = g_GreenApple;
			g_enemy[i].img = g_YellowApple;*/
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//����
			return TRUE;
		}
	}
	//���s
	return FALSE;
}
void Create::Init() {

	//�G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}
}