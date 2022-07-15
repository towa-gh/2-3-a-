#pragma once
#include"DxLib.h"
class BaseAP {
private:

public:
	const int PLAYER_POS_X = 320;
	const int PLAYER_POS_Y = 380;
	const int PLAYER_WIDTH = 63;
	const int PLAYER_HEIGHT = 120;
	const int PLAYER_SPEED = 5;
	int p_flg;//�g�p�t���O
	int p_x, p_y;//���Wx,y
	int p_w, p_h;//��w ����h
	double p_angle;//�@�̂̌���
	int p_count;//�^�C�~���O�p
	int p_speed;//�ړ����x
	BaseAP();
	void PlayerInit() {
		p_flg = TRUE;
		p_x = PLAYER_POS_X;
		p_y = PLAYER_POS_Y;
		p_w = PLAYER_WIDTH;
		p_h = PLAYER_HEIGHT;
		p_angle = 0.0;
		p_count = 0;
		p_speed = PLAYER_SPEED;
	}
	struct Apple {
		int flg;//�g�p�^�C�~���O
		int type;//�^�C�v
		int img;//�摜
		int x, y, w, h;//���Wx,y ��w�@����h
		int speed;//�ړ����x
		int point;//�X�R�A���Z
	};
	int APPLE_MAX = 10;
	static Apple g_Apple[10];
	struct Apple g_Apple00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
	struct Apple g_AppleCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

	void AppleInit() {
		for (int i = 0; i < APPLE_MAX; i++) {
			g_Apple[i].flg = FALSE;
		}
	}
};

extern BaseAP baseap;