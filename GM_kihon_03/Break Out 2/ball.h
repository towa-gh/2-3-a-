#pragma once

class Ball {
private:
	int  g_BallX, g_BallY;  //�{�[���̍��W
	int g_MoveX, g_MoveY;   //�{�[���̈ړ���
	int radius;             //���a
	float g_BallAngle;      //�{�[���̊p�x
	int g_RestBall;         //�c��{�[����
	int g_BallFlg;          //�{�[���̏��
	int g_Speed;            //�{�[���̃X�s�[�h

public:
	Ball();
	void DrawBall(void);
	void MoveBall(void);
	void ChangeAngle(void);
	void HitBar(void);
	void HitBlock(void);

};
extern Ball ball;