#pragma once
#include"BaseAP.h"
class MoveApple : public BaseAP {
private:
	int SCREEN_HEIGHT = 480;

	int g_Apple;//キャラ画像変数
	//int g_GreenApple;//キャラ画像変数
	//int g_YellowApple;//キャラ画像変数
	//int g_PoisonApple;//キャラ画像変数

public:
	Move();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern MoveApple moveapple;