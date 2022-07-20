/***********************************************
 ** �@��5�́@�~�j�Q�[��������(2)
 **�@�@�@�@�@�@�@���[�X�������Q�[
 ***********************************************/
#include "DxLib.h"
#include<stdio.h>
#define _USE_MATH_DEFINES
#include"main.h"
#include"BaseAP.h"
#include"Hitbox.h"
#include"MovePlayer.h"
#include"MoveApple.h"
#define RANKING_DATA 5
 /***********************************************
  *�ϐ��錾
  ***********************************************/
AppleGame applegame;
BaseAP baseap;

int g_OldKey;//�O��̓��̓L�[
int g_NowKey;//����̓��̓L�[
int g_KeyFlg;//���̓L�[���
int g_GameState = 0;//�Q�[�����[�h
int g_TitleImage;//�摜�p�ϐ�
int g_Score = 0;//�X�R�A
int g_WaitTime = 0;//�҂�����
int g_EndImage;
int g_Mileage;//���s����
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;//�G�J�E���g
int g_Appleimage;//�L�����摜�ϐ�
int g_Player, g_PlayerRight, g_PlayerLeft;          //�L�����摜�ϐ�
int g_StageImage;
int g_StartTime; //�X�^�[�g����
int Ringo[4]; //�����S�ʂ̉摜�ϐ�
int RingoScore[4]; //�����S�ʂ̃X�R�A
int Score; //�����S�̑����X�R�A
int Time; //����


const  int TIMELIMIT = 15000;

/***********************************************
 *�萔��錾
 ***********************************************/

 //���@�̏�����

// �����L���O�f�[�^�i�\���́j
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
// �����L���O�f�[�^�ϐ��錾
struct	RankingData		g_Ranking[10];

/***********************************************
 *�֐��̃v���g�^�C�v�錾
 ***********************************************/

void GameInit(void);//�Q�[������������
void GameMain(void);//�Q�[�����C������
int LoadImages();
void Pause(void); //�|�[�Y����
/***********************************************
 *�v���O�����̊J�n
 ***********************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("AppleGame");//�^�C�g����ݒ�
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
	if (DxLib_Init() == -1)return -1;//DX���C�u�����̏���������
	SetDrawScreen(DX_SCREEN_BACK);//�`����ʂ𗠂ɂ���
	if (LoadImages() == -1)return -1;//�摜�ǂݍ��݊֐����Ăяo��

	//�Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
		ClearDrawScreen();//�摜�̏�����

		switch (g_GameState) {
		case 0:
			GameInit();		//�Q�[����������
			break;
		case 1:
			GameMain();     //�Q�[�����C������
			break;

		case 2:
			Pause();
			break;
		}
		ScreenFlip();     //����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End();

	return 0;
}
/***********************************************
 *�Q�[����������
 ***********************************************/

void GameInit(void) {
	//�X�R�A�̏�����
	g_Score = 0;

	//���s������������
	g_Mileage = 0;

	//�G1�����������������
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;

	//�v���C���[�̏����ݒ�
	baseap.PlayerInit();

	//�G�l�~�[�̏����ݒ�
	baseap.AppleInit();

	//�Q�[�����C��������
	if (g_NowKey & PAD_INPUT_RIGHT || g_NowKey & PAD_INPUT_LEFT)g_GameState = 1;

	//���݌o�ߎ��Ԃ𓾂�
	g_StartTime = GetNowCount();

	//�������Ԃ̏����ݒ�
	 Time = TIMELIMIT * 2 - (GetNowCount() - g_StartTime);

	SetFontSize(43);
	DrawString(00, 200, "���E�ɓ������Ă�������", 0xffffff, 0);

	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME�F", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);


	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);


	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);


	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);


	SetFontSize(20);
	DrawString(515, 202, "SCORE�F", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]);
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]);
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]);
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]);
}
/***********************************************
 *�Q�[�����C��
***********************************************/
void GameMain(void) {
	moveplayer.PlayerControl(g_PlayerRight, g_PlayerLeft);
	moveapple.AppleControl();

	//�X�y�[�X�L�[����������|�[�Y��
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 2;

	if (g_KeyFlg == !PAD_INPUT_M) {

		//�v�����Ԃ��߂�����Q�[���I�[�o�[
		Time = TIMELIMIT * 2 - (GetNowCount() - g_StartTime);

		if (Time <= 0) {
			//g_GameState = GAME_OVER;
			Time = 0;
		}
	}

	//�X�R�A���\���̈�
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME�F", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);  //�ԃ����S�̕`��

	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);  //�΃����S�̕`��
	
	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);  //�������S�̕`��

	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);  //�Ń����S�̕`��

	SetFontSize(20);
	DrawString(515, 202, "SCORE�F", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]); //�ԃ����S�̃X�R�A
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]); //�΃����S�̃X�R�A
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]); //�������S�̃X�R�A
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]); //�Ń����S�̃X�R�A
}

/***********************************************
 *�|�[�Y
***********************************************/
void Pause() {

	////�X�y�[�X�L�[����������Q�[�����C��������
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 1;

	SetFontSize(50);
	DrawString(170, 200, "�|�[�Y", 0xffffff, 0);

	DrawBox(500, 0, 640, 480, 0x009900, TRUE);

	SetFontSize(20);
	DrawString(525, 20, "TIME�F", 0xffffff, 0);

	SetFontSize(20);
	DrawFormatString(580, 20, 0xffffff, "%3d", Time / 1000);

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);

	DrawRotaGraph(540, 60, 0.3f, 0, Ringo[0], TRUE, FALSE);

	DrawRotaGraph(540, 95, 0.3f, 0, Ringo[1], TRUE, FALSE);

	DrawRotaGraph(540, 132, 0.3f, 0, Ringo[2], TRUE, FALSE);

	DrawRotaGraph(540, 172, 0.3f, 0, Ringo[3], TRUE, FALSE);


	SetFontSize(20);
	DrawString(515, 202, "SCORE�F", 0xffffff, 0);
	DrawFormatString(590, 202, 0xFFFFFF, "%04d", Score);


	DrawFormatString(575, 50, 0xFFFFFF, "%04d", RingoScore[0]);
	DrawFormatString(575, 85, 0xFFFFFF, "%04d", RingoScore[1]);
	DrawFormatString(575, 122, 0xFFFFFF, "%04d", RingoScore[2]);
	DrawFormatString(575, 162, 0xFFFFFF, "%04d", RingoScore[3]);

}

/***********************************************
*�摜�ǂݍ���
***********************************************/

int LoadImages() {
	//�G
	if ((g_Appleimage = LoadGraph("images/apple.png")) == -1)return-1;
	//if ((g_Appleimage[1] = LoadGraph("images/GreenApple1.png")) == -1)return-1;
	//if ((g_Appleimage[2] = LoadGraph("images/YellowApple1.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp")) == -1)return-1;

	//�����S
	Ringo[0] = LoadGraph("images/apple.png"); //�ԃ����S
	Ringo[1] = LoadGraph("images/GreenApple1.png"); //�΃����S
	Ringo[2] = LoadGraph("images/YellowApple1.png"); //�������S
	Ringo[3] = LoadGraph("images/PoisonApple.png"); //�Ń����S

	//�X�e�[�W�w�i
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//�v���C���[
	if ((g_PlayerRight = LoadGraph("images/Right.png")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Left.bmp")) == -1)return -1;

	return 0;
}

int AppleGame::getg_Appleimage() {
	return g_Appleimage;
}
int AppleGame::getMileage() {
	return g_Mileage;
}
int AppleGame::getNowKey() {
	return g_NowKey;
}
int AppleGame::getSCREEN_WIDTH() {
	return SCREEN_WIDTH;
}
int AppleGame::getSCREEN_HEIGHT() {
	return SCREEN_HEIGHT;
}
int AppleGame::getg_PlayerLeft(int a) {
	return g_PlayerLeft;
}
int AppleGame::getg_PlayerRight(int b) {
	return g_PlayerRight;
}

