#pragma once
class Move {
private:
	int SCREEN_HEIGHT = 480;

	int g_Apple;//�L�����摜�ϐ�
	//int g_GreenApple;//�L�����摜�ϐ�
	//int g_YellowApple;//�L�����摜�ϐ�
	//int g_PoisonApple;//�L�����摜�ϐ�

	int ENEMY_MAX = 10;

public:
	Move();
	void EnemyControl();
	int CreateEnemy();
	void Init();
};
extern Move move;