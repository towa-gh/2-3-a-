#pragma once


class Ball {
private:
	int g_BallFlg; //�{�[���̏��(0...�ړ����@1...�o�[�ڐG)
	float g_BallAngle;//�{�[���̊p�x 
	int g_BallX, g_BallY; //�{�[���̍��W
	int radius; //���a
	int g_MoveX, g_MoveY; //�{�[���̈ړ���
	//int g_MouseX, g_MouseY; //�}�E�X�̍��W
	int g_RestBall; //�c��̃{�[����
	int height;//8
	int width;//60
	int g_Speed; //�{�[���̃X�s�[�h
	int g_Stage; //�X�e�[�W�p�ϐ�

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

extern Ball ball;//�ق��̃\�[�X�t�@�C���Ŏg�p�\