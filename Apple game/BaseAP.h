#pragma once
#include"DxLib.h"
class BasePlayer {
private:
	//const int PLAYER_POS_X = 320;
	//const int PLAYER_POS_Y = 380;
	//const int PLAYER_WIDTH = 63;
	//const int PLAYER_HEIGHT = 120;
	//const int PLAYER_SPEED = 5;
	//int flg;//�g�p�t���O
	//int x, y;//���Wx,y
	//int w, h;//��w ����h
	//double angle;//�@�̂̌���
	//int count;//�^�C�~���O�p
	//int speed;//�ړ����x
public:
	const int PLAYER_POS_X = 320;
	const int PLAYER_POS_Y = 380;
	const int PLAYER_WIDTH = 63;
	const int PLAYER_HEIGHT = 120;
	const int PLAYER_SPEED = 5;
	int flg;//�g�p�t���O
	int x, y;//���Wx,y
	int w, h;//��w ����h
	double angle;//�@�̂̌���
	int count;//�^�C�~���O�p
	int speed;//�ړ����x
	void PlayerInit() {
		flg = TRUE;
		x = PLAYER_POS_X;
		y = PLAYER_POS_Y;
		w = PLAYER_WIDTH;
		h = PLAYER_HEIGHT;
		angle = 0.0;
		count = 0;
		speed = PLAYER_SPEED;
	}
};
//class BaseApple {
//private:
//	struct Apple{
//		int flg;//�g�p�^�C�~���O
//		int type;//�^�C�v
//		int img;//�摜
//		int x, y, w, h;//���Wx,y ��w�@����h
//		int speed;//�ړ����x
//		int point;//�X�R�A���Z
//	};
//	int APPLE_MAX = 10;
//public:
//	static Apple g_Apple[APPLE_MAX];
//	struct Apple g_Apple00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
//	struct Apple g_AppleCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };
//
//	void AppleInit() {
//		for (int i = 0; i < APPLE_MAX; i++) {
//			g_Apple[i].flg = FALSE;
//		}
//	}
//};
extern BasePlayer bp;
//extern BaseApple ba;



