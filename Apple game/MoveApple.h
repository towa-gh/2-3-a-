#pragma once
#include"BaseAP.h"
class MoveApple : public BaseAP {
private:
	int SCREEN_HEIGHT = 480;

	int g_Apple;//�L�����摜�ϐ�
	//int g_GreenApple;//�L�����摜�ϐ�
	//int g_YellowApple;//�L�����摜�ϐ�
	//int g_PoisonApple;//�L�����摜�ϐ�

public:
	Move();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern MoveApple moveapple;