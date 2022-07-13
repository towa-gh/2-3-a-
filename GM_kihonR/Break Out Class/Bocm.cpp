#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bar.h"
#include"Ball.h"
#include "Block.h"
#include "Ranking.h"
#include"GameM.h"

#define HEIGHT 10
#define WIDTH 16
#define STAGE 5
/***********************************************
 * �ϐ��̐錾
 ***********************************************/

int	g_OldKey;				// �O��̓��̓L�[
int	g_NowKey;				// ����̓��̓L�[
int	g_KeyFlg;				// ���̓L�[���

int	g_MenuNumber = 0;		// ���j���[�J�[�\���ʒu

int g_MenuY;				// ���j���[�J�[�\���̂x���W

int	g_TitleImage;			// �摜�p�ϐ�
int	g_RankingImage;			// �摜�p�ϐ�
int	g_EndImage;				// �摜�p�ϐ�

int	g_WaitTime = 0;			// �҂�����
int g_PosY;					// �X�N���[�����̂x���W


int	g_GameState = 0;		// �Q�[���X�e�[�^�X

int g_BlockImage[8]; //�u���b�N�摜�p�ϐ�

int g_BallFlg;

int g_Stage = 0; //�X�e�[�W�p�ϐ�




/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/
void DrawGameOver(void);
void DrawGameClear(void);

void DrawGameTitle(void);	//�Q�[���^�C�g������
void DrawEnd(void);			//�Q�[���G���h����


/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	/*�^�C�g���� test �ɕύX*/
	SetMainWindowText("�u���b�N����");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	/*�^�C�g���摜�f�[�^�̓ǂݍ���*/
	if ((g_TitleImage = LoadGraph("images/Chapter4/Title.bmp")) == -1) return -1;
	/*�����L���O�摜�f�[�^�̓ǂݍ���*/
	if ((g_RankingImage = LoadGraph("images/Chapter4/Ranking.bmp")) == -1) return -1;
	/*�G���h�摜�f�[�^�̓ǂݍ���*/
	if ((g_EndImage = LoadGraph("images/Chapter4/End.bmp")) == -1) return -1;
	/*�u���b�N�f�[�^�̉摜�f�[�^�ǂݍ���*/
	if (LoadDivGraph("images/Chapter4/Block.bmp", 8, 8, 1, 40, 8, g_BlockImage) == -1)return -1;

	if (ranking.ReadRanking() == -1)  return  -1;    //�����L���O�f�[�^�̓ǂݍ���

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SetFontSize(20);		// �����T�C�Y��ݒ�

	 /*�Q�[�����[�v*/
	while (ProcessMessage() == 0 && g_GameState != 99) {

		/* ���̓L�[�擾*/
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// ��ʂ̏�����

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//�Q�[���^�C�g������
			break;
		case 1:
			ball.GameInit();		//�Q�[����������
			break;
		case 2:
			ranking.DrawRanking();	//�����L���O�`�揈��
			break;
		case 3:
			DrawEnd();		//�G���h��ʕ`�揈��
			break;
		case 4:
			gameM.GameMain();		//�Q�[�����C������
			break;

			switch (g_GameState) {
			case 5:
				DrawGameOver(); //�Q�[���I�[�o�[�`�揈��
				break;
			}
		case 6:
			DrawGameClear();		//�Q�[���N���A����
			break;
		}
		switch (g_GameState) {
		case 7:
			ranking.InputRanking(); //�����L���O���͏���
			break;
		}

		SetFontSize(48);
		DrawFormatString(100, 100, 0xffffff, "%d", g_BallFlg);
		DrawFormatString(100, 100, 0xffffff, "%d", g_GameState);
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f
	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}



/***********************************************
 * �Q�[���^�C�g���\���i���j���[��ʁj
 ***********************************************/
void DrawGameTitle(void)
{
	/*���j���[�J�[�\���ړ�����*/
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 2) g_MenuNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 2;
	}

	/*�y�L�[�Ń��j���[�I��*/
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = g_MenuNumber + 1;

	/*�^�C�g���摜�\��*/
	DrawGraph(0, 0, g_TitleImage, FALSE);

	/*���j���[�J�[�\���i�O�p�`�j�̕\��*/
	g_MenuY = g_MenuNumber * 52;
	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);

}


/***********************************************
 * �Q�[���N���A��ʕ`�揈��
 ***********************************************/
void DrawGameClear(void)
{
	int g_Stage = 0;

	/*�X�y�[�X��NEXT�X�e�[�W��*/
	if (g_KeyFlg & PAD_INPUT_M) {
		g_GameState = 4;
		if (++g_Stage > 4)g_Stage = 0;
		ball.InitBlock();
	}

	SetFontSize(48);
	DrawString(120, 200, "Congratulations", 0x7F00F0);

	/*�����̕\��(�_��)*/
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "-- Press[SPACE] Key --", GetColor(255, 0, 0));
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}


/***********************************************
* �Q�[���I�[�o�[��ʕ`�揈��
***********************************************/
void DrawGameOver(void){
	/*�X�y�[�X�L�[�Ń��j���[�ɖ߂�*/
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 4;
	ball.InitBlock();

	SetFontSize(48);
	DrawString(200, 200, "Game Over", GetColor(255, 0, 0));

	/*�����\���̓_��*/
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "-- Press[SPACE] Key --", GetColor(255, 0, 0));
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}




/***********************************************
 * �Q�[���G���h�`�揈���i�G���h���[���j
 ***********************************************/
void DrawEnd(void)
{
	//�G���h�摜�\��
	DrawGraph(0, 0, g_EndImage, FALSE);

	//�G���f�B���O�\��
	if (++g_WaitTime < 600) g_PosY = 300 - g_WaitTime / 2;

	SetFontSize(24);
	DrawString(100, 170 + g_PosY, "�^�C�g���@�@�@Game�@Title", 0xFFFFFF);
	DrawString(100, 200 + g_PosY, "�o�[�W�����@�@1.0", 0xFFFFFF);
	DrawString(100, 230 + g_PosY, "�ŏI�X�V���@�@201x�Nxx��xx��", 0xFFFFFF);
	DrawString(100, 260 + g_PosY, "����ҁ@�@�@�@���ۓd�q�r�W�l�X���w�Z", 0xFFFFFF);
	DrawString(100, 290 + g_PosY, "�@�@�@�@�@�@�@�w�w�w�@�w�w", 0xFFFFFF);
	DrawString(100, 310 + g_PosY, "�f�ޗ��p", 0xFFFFFF);
	DrawString(100, 340 + g_PosY, "�@BGM�@�@�@ �@�w�w�w�w", 0xFFFFFF);
	DrawString(100, 365 + g_PosY, "�@SE�@�@�@�@�@�w�w�w�w�w�w�w�w", 0xFFFFFF);

	//�^�C���̉��Z�������I��
	if (++g_WaitTime > 900) g_GameState = 99;
}



