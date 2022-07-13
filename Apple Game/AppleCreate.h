#pragma once
class Create{
private:
	int SCREEN_HEIGHT = 480;
	
	int g_Apple;//キャラ画像変数
	int g_GreenApple;//キャラ画像変数
	int g_YellowApple;//キャラ画像変数
	//int g_PoisonApple;//キャラ画像変数

	int ENEMY_MAX = 10;
	
public:
	Create();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern Create create;