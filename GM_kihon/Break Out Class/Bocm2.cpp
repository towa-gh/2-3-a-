#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Bar.h"
#include "Ball.h"
#include "Block.h"
#include "Ranking.h"
#include "GameM.h"

#define HEIGHT 10
#define WIDTH 16
#define STAGE 5

extern int g_Score;
extern int g_GameState;

/*�����L���O�f�[�^�i�\���́j*/
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
extern  RankingData g_Ranking[10];

//<�ꕔ�ȗ�>
//�u���b�N�f�[�^(�\���̂̒�`)
struct ObjectBlock {
	int flg;
	int x, y;
	int w, h;
	int mx, my;
	int image;
	int score;
};

//�u���b�N�f�[�^�̐錾
extern ObjectBlock g_Block[HEIGHT][WIDTH];

int CheckBlock();



Bar bar;
Ball ball;
Block block;
Ranking ranking;
GameM gameM;

Bar::Bar(){
	g_BarX = 0;
	g_BarY = 0;
	height = 8;
	width = 60;

}

Ball::Ball() {

	g_BallFlg = 0; //�{�[���̏��(0...�ړ����@1...�o�[�ڐG)
	g_BallAngle = 0;//�{�[���̊p�x 
	g_BallX = 0;
	g_BallY = 0; //�{�[���̍��W
	g_MoveX = 0;
	g_MoveY = 0;//�{�[���̈ړ���
	//g_MouseX = 0;
	//g_MouseY = 0; //�}�E�X�̍��W
	g_RestBall = 0; //�c��̃{�[����
	height = 8;
	width = 60;
	/*g_GameState = 0;*/
	radius = 4;
	g_Speed = 0;
	g_Score = 0;
	g_Stage = 0; //�X�e�[�W�p�ϐ�
}

Block::Block() {

	g_BlockX = 0;
	g_BlockY = 0; //�o�[�̍��W
	height = 8;//8
	width = 60;//60
	g_BlockImage[8] = 0;//�u���b�N�摜�p�ϐ�
	g_Score = 0;	// �X�R�A
	g_RestBall = 0;

}

Ranking::Ranking() {

	g_RankingImage = 0;	// �摜�p�ϐ�
	g_GameState = 0;	// �Q�[���X�e�[�^�X
	g_KeyFlg = 0;				// ���̓L�[���
	g_WaitTime = 0;			// �҂�����
	g_Score = 0;
	
}

GameM::GameM(){
	
	g_PosY = 0;					// �X�N���[�����̂x���W
	g_OldKey = 0;				// �O��̓��̓L�[
	g_NowKey = 0;				// ����̓��̓L�[

	g_MenuNumber = 0;		// ���j���[�J�[�\���ʒu
	g_MenuY = 0;				// ���j���[�J�[�\���̂x���W

	g_GameState = 0;		// �Q�[���X�e�[�^�X

	g_Stage = 0;

}

int	g_BlockData[STAGE][HEIGHT][WIDTH] = {	// �u���b�N�z��
	{	// 0�ð��
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
	},
	{	// 1�ð��
		{ 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 2 , 3 , 3 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 2 , 2 , 3 , 4 , 4 , 4 , 4 , 3 , 2 , 2 , 0 , 0 , 0 },
		{ 0 , 2 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 4 , 3 , 3 , 2 , 2 , 0 },
		{ 2 , 3 , 3 , 4 , 4 , 5 , 0 , 0 , 0 , 0 , 5 , 4 , 4 , 3 , 3 , 2 },
		{ 2 , 3 , 3 , 4 , 4 , 5 , 0 , 0 , 0 , 0 , 5 , 4 , 4 , 3 , 3 , 2 },
		{ 0 , 2 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 4 , 3 , 3 , 2 , 2 , 0 },
		{ 0 , 0 , 0 , 2 , 2 , 3 , 4 , 4 , 4 , 4 , 3 , 2 , 2 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 2 , 3 , 3 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{	// 2�ð��
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 },
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 },
		{ 0 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 0 },
		{ 0 , 0 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 0 , 0 },
		{ 0 , 0 , 0 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 4 , 4 , 4 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 4 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{	// 3�ð��
		{ 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 }
	},
	{	// 4�ð��
		{ 7 , 1 , 0 , 0 , 1 , 7 , 3 , 3 , 3 , 0 , 7 , 0 , 4 , 4 , 0 , 7 },
		{ 7 , 1 , 0 , 1 , 1 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 4 , 4 , 4 , 7 },
		{ 7 , 1 , 1 , 1 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 4 , 7 },
		{ 7 , 1 , 1 , 0 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 0 , 0 , 0 , 7 , 3 , 3 , 3 , 0 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 1 , 0 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 1 , 1 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 4 , 7 },
		{ 7 , 1 , 0 , 1 , 1 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 4 , 4 , 4 , 7 },
		{ 7 , 1 , 0 , 0 , 1 , 7 , 3 , 3 , 3 , 0 , 7 , 0 , 4 , 4 , 0 , 7 },
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 }
	}
};

/***********************************************
 * �o�[�̈ړ�����
 ***********************************************/
void Bar::MoveBar(void) {

	int g_MouseX, g_MouseY; //�}�E�X�̍��W

	/*�}�E�X������W��ǂݎ��*/
	GetMousePoint(&g_MouseX, &g_MouseY);

	g_BarX = g_MouseX;
	if (g_BarX < 0) {
		g_BarX = 0;
	}
	else if (g_BarX > 640 - width) {
		g_BarX = 580;
	}

}



/***********************************************
 * �o�[�̕`�揈��
 ***********************************************/
void Bar::DrawBar(void) {
	/*�o�[�̕`��*/
	DrawBox(g_BarX, g_BarY, g_BarX + width, g_BarY + height, 0xFFD700, TRUE);
}

void Bar::Init(){
	g_BarX = 290;
	g_BarY = 440;
}

int Bar::getX(){
	return g_BarX;
}

int Bar::getY(){
	return g_BarY;
}

int Bar::getheight() {
	return height;
}

int Bar::getwidth() {
	return width;
}


/***********************************************
 * �Q�[����������
 ***********************************************/
void Ball::GameInit(void) {


	int g_GameState;

	bar.Init();
	/*g_BarX = 290;
	g_BarY = 440;*/
	g_GameState = 4; //�Q�[�����C��������

	/*<�ꕔ�ȗ�>
�u���b�N�z��̏�����*/
	ball.InitBlock();
	
}

void Ball::Init() {

	g_BallX = 320;
	g_BallY = 440 - 5;
	g_RestBall = 2; //�c��̃{�[���̐ݒ�
	InitBallFlg();
	
}

void Ball::InitBallFlg() {
	g_BallFlg = 2;
}

int Ball::getRestBall(){

	return g_RestBall;

}
/***********************************************
 * �u���b�N��������
 ***********************************************/
 void Ball::InitBlock(void)
 {

 	/*�u���b�N�z��̏�����*/
 	for (int i = 0; i < HEIGHT; i++) {
 		for (int j = 0; j < WIDTH; j++) {
 			if (g_BlockData[g_Stage][i][j] != 0) {
 				g_Block[i][j].flg = 1;
 				g_Block[i][j].x = j * 40;
 				g_Block[i][j].y = i * 16 + 80;
 				g_Block[i][j].w = 40;
 				g_Block[i][j].h = 8;
 				g_Block[i][j].score = g_Block[i][j].image * 10;
 			}
 
 		}
 	}
 	/*�{�[���X�^�[�g���*/
 	g_BallFlg = 2;
 }



int Ball::getX()
{
	return g_BallX;
}

int Ball::getY()
{
	return g_BallY;
}
/***********************************************
 * �{�[���̕`�揈��
 ***********************************************/
void Ball::DrawBall(void) {
	/*�{�[���̕`��*/
	DrawCircle(g_BallX, g_BallY, 4, 0xFFD700, TRUE);
}



/***********************************************
* �{�[���̈ړ�����
/***********************************************/
void Ball::MoveBall(void) {


	/*�}�E�X���N���b�N�ŃQ�[���X�^�[�g*/
	if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && g_BallFlg == 2) {

		g_BallFlg = 0;
		/*�X�s�[�h�ƃA���O���ɂ��ړ��ʌv�Z*/
		g_Speed = 5;
		g_BallAngle = 0.625f;
		ball.ChangeAngle();
	}

	/*�{�[���̈ړ�*/
	g_BallX += g_MoveX;
	g_BallY += g_MoveY;

	/*�ǁE�V��ł̔���*/
	if (g_BallX < radius || g_BallX > 640 - radius) { //���̕�
		if (g_BallX < radius) {
			g_BallX = radius;
		}
		else {
			g_BallX = 640 - radius;
		}
		g_BallAngle = (1 - g_BallAngle) + 0.5f;
		if (g_BallAngle > 1)g_BallAngle -= 1.0f;
		ChangeAngle();
	}

	if (g_BallY < radius) {
		g_BallAngle = (1 - g_BallAngle); //��̕�
		ChangeAngle();
	}

	/*g_BarX = g_BallX;*/

	if (g_BallFlg != 2) {
		g_BallX += g_MoveX;
		g_BallY += g_MoveY;
	}
	else {
		g_BallX = bar.getX() + 30;
		g_BallY = bar.getY() - 6;
	}

	if (g_BallY > 480 + radius) {
		g_BallFlg = 2; //�{�[���X�^�[�g���
		if (--g_RestBall < 0) {
			if (g_Score >= g_Ranking[9].score) {
				g_GameState = 7; //�����L���O���͏���

			}
			else {
				g_GameState = 5; //�Q�[���I�[�o�[����

			}
		}
	}
	if (g_BallY > 480 + radius) {

		if (g_Score >= g_Ranking[9].score) {
			g_GameState = 7; //�����L���O���͏�����
		}
		else {
			g_GameState = 5; //�Q�[���I�[�o�[������
		}
	}
}

/***********************************************
 * �{�[���ƃu���b�N�̓����蔻��
 ***********************************************/
void Ball::HitBlock(void) {


	/*�{�[���ƃu���b�N�̓����蔻��*/
	int x = g_BallX / 40;
	int y = (g_BallY - 80) / 16;

	if (x >= 0 && x < width &&
		y >= 0 && y < height &&
		g_Block[y][x].flg != 0) {

		g_Block[y][x].flg = 0;
		g_Score += g_Block[y][x].score;

		g_BallAngle = (1 - g_BallAngle);
		ChangeAngle();
		if (CheckBlock() == 0) g_GameState = 6;
	}
}

/***********************************************
 * �p�x�ύX����
 ***********************************************/
void Ball::ChangeAngle(void)
{
	float rad = g_BallAngle * (float)M_PI * 2;
	g_MoveX = (int)(g_Speed * cosf(rad));
	g_MoveY = (int)(g_Speed * sinf(rad));
}

/***************************************/
/*�{�[���ƃo�[�̓����蔻��
/**************************************/
void Ball::HitBar(void) {
	int  mx0, mx1, my0, my1, sx0, sx1, sy0, sy1;


	/*���W�̎��O�v�Z*/
	mx0 = ball.getX() - radius;
	mx1 = ball.getY() + radius;
	my0 = ball.getX() - radius;
	my1 = ball.getY() + radius;
	sx0 = bar.getX();
	sx1 = sx0 + bar.getwidth();
	sy0 = bar.getY();
	sy1 = sy0 + bar.getheight();

	/*�{�[���ƃo�[�̓����蔻��*/
	if (sx0 <= mx1 && sx1 >= mx0 &&
		sy0 <= my1 && sy1 >= my0) {

		if (g_BallFlg == 0) {

			g_BallAngle = (0.3f / 60) * (mx1 - sx0) + 0.6f;
			ChangeAngle();
			g_BallFlg = 1;
		}
	}
	else {
		//BallFlg = 0;
		if (g_BallFlg != 2)g_BallFlg = 0;
	}
}

/***********************************************
 * �u���b�N�`�F�b�N����
 ***********************************************/
int CheckBlock(void) {

	/*�u���b�N�̔z��̏�����*/
	for (int i = 0; i < HEIGHT;i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1)return -1;
		}
	}
	return 0;
}

///***********************************************
// * �u���b�N�`�揈��
// ***********************************************/
void Block::DrawBlock(void) {


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1) {
				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
			}
		}
	}
}

/***********************************************
 * �X�R�A�`�揈��
 ***********************************************/
void Block::DrawScore() {
	DrawFormatString(20, 20, 0xFFFFFF, "SCORE:%06d", g_Score);

	/*�c��̃{�[���̕`��*/
	SetFontSize(10);
	DrawFormatString(600, 460, 0xFFD700, "���@x %d", g_RestBall);
}

int Block::getX()
{
	return g_BlockX;
}

int Block::getY()
{
	return g_BlockY;
}

int Block::getheight() {
	return height;
}

int Block::getwidth() {
	return width;
}



//***********************************************
//*�����L���O�`�揈��
//*********************************************** /
void Ranking::DrawRanking(void)
{

	/*�X�y�[�X�L�[�Ń��j���[�ɖ߂�*/
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	/*�����L���O�摜�\��*/
	DrawGraph(0, 0, g_RankingImage, FALSE);

	/*�����L���O�ꗗ��\��*/
	SetFontSize(30);
	for (int i = 0; i < 10; i++) {
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s   %10d",
			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*�����̕\��(�_��)*/
	if (++g_WaitTime < 30) {

		SetFontSize(24);
		DrawString(150, 450, "--  Press [SPACE] Key  --", 0xFF0000);
	}

	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}

}

/***********************************************
 * �����L���O���͏���
 ***********************************************/
void Ranking::InputRanking()
{
	
	/*�����L���O�摜�\��*/
	DrawGraph(0, 0, g_RankingImage, FALSE);

	/*�t�H���g�T�C�Y�̐ݒ�*/
	SetFontSize(20);

	/*���O���͎w��������̕`��*/
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);

	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);

	/*���O�̓���*/
	DrawString(150, 310, "> ", 0xFFFFFF);

	DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {

		g_Ranking[9].score = g_Score;	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
		SortRanking();		// �����L���O���בւ�
		SaveRanking();		// �����L���O�f�[�^�̕ۑ�
		g_GameState = 2;		// �Q�[�����[�h�̕ύX
	}

}

/***********************************************
 * �����L���O���בւ�
 ***********************************************/
void Ranking::SortRanking()
{
	int i, j;
	RankingData work;

	/*�I��@�\�[�g*/
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	/*���ʕt��*/
	for (i = 0; i < 10; i++) {
		g_Ranking[i].no = 1;
	}
	/*���_�������ꍇ�́A�������ʂƂ���
	�����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���*/
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}

/***********************************************
 * �����L���O�f�[�^�̕ۑ�
 ***********************************************/
int Ranking::SaveRanking()
{
	FILE* fp;
#pragma warning(disable:4996)

	/*�t�@�C���I�[�v��*/
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "w")) == NULL) {
		/* �G���[���� */
		printf("Ranking Data Error\n");
		return -1;
	}

	/*�����L���O�f�[�^���z��f�[�^����������*/
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*�t�@�C���N���[�Y*/
	fclose(fp);

	return 0;
}

/*************************************
 * �����L���O�f�[�^�ǂݍ���
 *************************************/
int Ranking::ReadRanking()
{
	FILE* fp;
#pragma warning(disable:4996)

	/*�t�@�C���I�[�v��*/
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "r")) == NULL) {
		/*�G���[����*/
		printf("Ranking Data Error\n");
		return -1;
	}

	/*�����L���O�f�[�^�z����f�[�^��ǂݍ���*/
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*�t�@�C���N���[�Y*/
	fclose(fp);

	return 0;
}

/***********************************************
 * �Q�[�����C��
 ***********************************************/
void GameM::GameMain()
{
	bar.MoveBar();//�o�[�̈ړ�����
	ball.MoveBall();//�{�[���̈ړ�
	ball.HitBar();//�{�[���ƃo�[�̓����蔻��
	ball.HitBlock(); //�{�[���ƃu���b�N�̓����蔻��
	ball.DrawBall(); //�{�[���̕`��
	bar.DrawBar(); //�o�[�̕`��
	block.DrawBlock(); //�u���b�N��`��
	block.DrawScore(); //�X�R�A��`��
}