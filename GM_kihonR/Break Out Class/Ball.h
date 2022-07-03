#pragma once


class Ball {
private:
	int g_BallFlg; //ボールの状態(0...移動中　1...バー接触)
	float g_BallAngle;//ボールの角度 
	int g_BallX, g_BallY; //ボールの座標
	int radius; //半径
	int g_MoveX, g_MoveY; //ボールの移動量
	//int g_MouseX, g_MouseY; //マウスの座標
	int g_RestBall; //残りのボール数
	int height;//8
	int width;//60
	int g_Speed; //ボールのスピード
	int g_Stage; //ステージ用変数

public:
	Ball();

	void GameInit();
	

    void Init();
	void InitBallFlg();
	int getRestBall();


	void InitBlock();
	int getX();
	int getY();

	void DrawBall();
	void MoveBall();
	
	void HitBlock();
	void ChangeAngle();
	void HitBar();
	/*int CheckBlock();*/
	
};

extern Ball ball;//ほかのソースファイルで使用可能