#include"DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include"AppleMove.h"
#include"main.h"

const int APPLE_MAX = 10;
const int PLAYER_SPEED = 5;
//const int SCREEN_HEIGHT = 480;
//const int SCREEN_WIDTH = 640;

//�G�@�\����
struct ENEMY {
	int flg; //�g�p�t���O
	int type; //�^�C�v
	int img; //�摜
	int x, y, w, h; //���Wx,y�@���@w �����@h
	int speed; //�ړ����x
	int point; //�X�R�A���Z
};

struct ENEMY g_enemy[APPLE_MAX];
struct ENEMY g_enemy00 ={ TRUE,0,0,0,-50,63,120,0,1 };
struct ENEMY g_enemyCh ={ TRUE,4,0,0,-50,18,18,0,1 };

AppleMove applemove;

//AppleMove::AppleMove(){
//	
//	g_Mileage = 0;
//	g_apple = 0;
//}


void AppleMove::EnemyControl(void) {
	

	for (int i = 0;i < APPLE_MAX;i++) {
		
		
		g_enemy[i].y += g_enemy[i].speed - PLAYER_SPEED + 1;

		switch (g_enemy[i].flg) {

		case 0: g_enemy[i].y += 2;
			break;
		case 1:g_enemy[i].y += 5;
			break;
		case 2:g_enemy[i].y += 10;
			break;
		case 3:g_enemy[i].y += 1;
			break;

		}

		if (g_enemy[i].flg == TRUE) {
			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			/*if (g_player.flg == FALSE)continue;*/
			//�^���������Ɉړ�

			/*g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;*/
			/*��ʂ��͂ݏo���������*/
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;

			
		}
	}
	//���s�������ƂɓG�o���p�^�[���𐧌�
	if (move.getg_Mileage() / 5 % 50 == 0) {
		CreateEnemy();
	}

}

//int AppleMove::getg_apple() {
//	return g_apple;
//}
//
//int AppleMove::getg_Mileage() {
//	return g_Mileage;
//}

//****************************************/
//�G�@�̐���
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//****************************************/
int AppleMove::CreateEnemy() {

	for (int i = 0; i < APPLE_MAX; i++) {

		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			g_enemy[i].img = move.getg_apple();/*, g_appleB,g_appleC, g_appleD*//*[g_enemy[i].type]*/
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;
			/*����*/
			return TRUE;
		}
	}

	/*���s*/
	return FALSE;
}


