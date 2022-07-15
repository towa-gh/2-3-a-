#pragma once
#include"BaseAP.h"
class Create : public BaseApple {
private:
	int g_Apple;//キャラ画像変数
	int g_GreenApple;//キャラ画像変数
	int g_YellowApple;//キャラ画像変数
	//int g_PoisonApple;//キャラ画像変数
public:
	Create();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern Create create;