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
	void PlayerInit();

	struct Apple {
		int flg;//�g�p�^�C�~���O
		int type;//�^�C�v
		int img;//�摜
		int x, y, w, h;//���Wx,y ��w�@����h
		int speed;//�ړ����x
		int point;//�X�R�A���Z
	};
	const static int APPLE_MAX = 10;
	struct Apple g_Apple[APPLE_MAX];
	struct Apple g_Apple00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
	//struct Apple g_AppleCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

	void AppleInit();
};

extern BaseAP baseap;