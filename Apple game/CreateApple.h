#pragma once
#include"BaseAP.h"
class Create : public BaseApple {
private:
	int g_Apple;//�L�����摜�ϐ�
	int g_GreenApple;//�L�����摜�ϐ�
	int g_YellowApple;//�L�����摜�ϐ�
	//int g_PoisonApple;//�L�����摜�ϐ�
public:
	Create();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern Create create;