#pragma once

class Ball {
private:
	int  g_BallX, g_BallY;  //ボールの座標
	int g_MoveX, g_MoveY;   //ボールの移動量
	int radius;             //半径
	float g_BallAngle;      //ボールの角度
	int g_RestBall;         //残りボール数
	int g_BallFlg;          //ボールの状態
	int g_Speed;            //ボールのスピード

public:
	Ball();
	void DrawBall(void);
	void MoveBall(void);
	void ChangeAngle(void);
	void HitBar(void);
	void HitBlock(void);

};
extern Ball ball;