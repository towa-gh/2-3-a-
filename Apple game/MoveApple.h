#pragma once
#include"MovePlayer.h"
//#include"Fps.h"
struct Apple {
	int flg;//�g�p�^�C�~���O
	int type;//�^�C�v
	int img;//�摜
	int x, y, w, h;//���Wx,y ��w�@����h
	int speed;//�ړ����x
	int point;//�X�R�A���Z
};
class MoveApple{
private:
	const static int APPLE_MAX = 10;
	struct Apple g_Apple[APPLE_MAX];
public:
	void AppleControl(Player player);
	void AppleInit();
	int CreateEnemy();
};
extern MoveApple moveapple;