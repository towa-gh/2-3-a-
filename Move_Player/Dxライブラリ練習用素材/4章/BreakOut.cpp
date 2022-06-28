/********************************************************************
**	��S�́@�Q�[���v���O���~���O�̊�{
**	�@�u���b�N�����Q�[���̍쐬(2018)
********************************************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define		HEIGHT	10
#define		WIDTH	16
#define		STAGE	5

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

int	g_Score = 0;			// �X�R�A

int	g_GameState = 0;		// �Q�[���X�e�[�^�X

int g_BallX, g_BallY;
int g_MoveX, g_MoveY;
int g_Speed;
float g_BallAngle;
int g_BarX, g_BarY;
int g_MouseX, g_MouseY;		//�}�E�X�̍��W
int g_BallFlg;		//�{�[���̏��
int g_BlockImage[8];		//�u���b�N�摜�p�ϐ�
int g_RestBall;		//count ball
int g_Stage;		//stage
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

// �����L���O�f�[�^�i�\���́j
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
// �����L���O�f�[�^�ϐ��錾
struct	RankingData		g_Ranking[10];

//�u���b�N�f�[�^
struct ObjectBlock {
	int flg;
	int x, y;
	int w, h;
	int mx, my;
	int image;
	int score;
};
//�u���b�N�f�[�^�̐錾
struct ObjectBlock	g_Block[HEIGHT][WIDTH];


/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/
void GameInit(void);		//�Q�[������������
void GameMain(void);		//�Q�[�����C������

void DrawGameTitle(void);	//�Q�[���^�C�g������
void DrawEnd(void);			//�Q�[���G���h����

void DrawRanking(void);		//�����L���O�`��
void InputRanking(void);	//�����L���O����
void SortRanking(void);		//�����L���O���בւ�
int  SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
int  ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���

void DrawBall(void);
void MoveBall(void);
void ChangeAngl(void);
void DrawBar(void);
void MoveBar(void);
void HitBar(void);
void DrawGameOver(void);
void InitBlock(void);
void DrawBlock(void);
void HitBlock(void);
void DrawScore(void);
void DrawGameClear(void);
int CheckBlock(void);


/***********************************************
 * �v���O�����̊J�n
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// �^�C�g���� test �ɕύX
	SetMainWindowText("�u���b�N����");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	//�^�C�g���摜�f�[�^�̓ǂݍ���
	if ((g_TitleImage = LoadGraph("images/Chapter4/Title.bmp")) == -1) return -1;
	//�����L���O�摜�f�[�^�̓ǂݍ���
	if ((g_RankingImage = LoadGraph("images/Chapter4/Ranking.bmp")) == -1) return -1;
	//�G���h�摜�f�[�^�̓ǂݍ���
	if ((g_EndImage = LoadGraph("images/Chapter4/End.bmp")) == -1) return -1;
	//�u���b�N�摜�f�[�^�̓ǂݍ���
	if (LoadDivGraph("images/Chapter4/Block.bmp", 8, 8, 1, 40, 8, g_BlockImage) == -1)return-1;

	if (ReadRanking() == -1)  return  -1;    //�����L���O�f�[�^�̓ǂݍ���

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	SetFontSize(20);		// �����T�C�Y��ݒ�

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99) {

		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// ��ʂ̏�����

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//�Q�[���^�C�g������
			break;
		case 1:
			GameInit();		//�Q�[����������
			break;
		case 2:
			DrawRanking();	//�����L���O�`�揈��
			break;
		case 3:
			DrawEnd();		//�G���h��ʕ`�揈��
			break;
		case 4:
			GameMain();		//�Q�[�����C������
			break;
		case 5:
			DrawGameOver();
			break;
		case 6:
			DrawGameClear();		//�Q�[���N���A�`�揈��
			break;
		case 7:
			InputRanking();
			break;
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}

/***********************************************
 * �����L���O�`�揈��
 ***********************************************/
void DrawRanking(void)
{
	// �X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	//�����L���O�摜�\��
	DrawGraph(0, 0, g_RankingImage, FALSE);

	// �����L���O�ꗗ��\��
	SetFontSize(30);
	for (int i = 0; i < 10; i++) {
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s     %10d",
			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	// �����̕\��(�_��)
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
void InputRanking(void)
{
	//�����L���O�摜�\��
	DrawGraph(0, 0, g_RankingImage, FALSE);

	// �t�H���g�T�C�Y�̐ݒ�
	SetFontSize(20);

	// ���O���͎w��������̕`��
	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0xFFFFFF);
	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0xFFFFFF);

	// ���O�̓���
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
void SortRanking(void)
{
	int i, j;
	RankingData work;

	// �I��@�\�[�g
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	// ���ʕt��
	for (i = 0; i < 10; i++) {
		g_Ranking[i].no = 1;
	}
	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
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
int  SaveRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// �t�@�C���I�[�v��
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "w")) == NULL) {
		/* �G���[���� */
		printf("Ranking Data Error\n");
		return -1;
	}

	// �����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;

}

/*************************************
 * �����L���O�f�[�^�ǂݍ���
 *************************************/
int ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	//�t�@�C���I�[�v��
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "r")) == NULL) {
		//�G���[����
		printf("Ranking Data Error\n");
		return -1;
	}

	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
}

/***********************************************
 * �Q�[���^�C�g���\���i���j���[��ʁj
 ***********************************************/
void DrawGameTitle(void)
{
	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 2) g_MenuNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 2;
	}

	// �y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = g_MenuNumber + 1;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//���j���[�J�[�\���i�O�p�`�j�̕\��
	g_MenuY = g_MenuNumber * 52;
	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);

}

/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit(void)
{
	// �ϐ��̏����ݒ�
	g_BallX = 320;
	g_BallY = 440 - 5;
	/*g_MoveX = 1;
	g_MoveY = -2;*/		//�ړ��ʌv�Z�̂���
	g_BarX = 290;
	g_BarY = 440;

	g_GameState = 4;	// �Q�[�����C��������

	//�u���b�N�̔z��̏�����
	InitBlock();

	g_RestBall = 2;
}

/***********************************************
 * �Q�[�����C��
 ***********************************************/
void GameMain(void)
{
	MoveBar();		//�o�[�̈ړ�����
	MoveBall();		//�{�[���̈ړ�
	HitBar();		//�{�[���ƃo�[�̓����蔻��
	HitBlock();		//�{�[���ƃu���b�N�̓����蔻��
	DrawBall();		//�{�[���̕`��
	DrawBar();		//�o�[�̕`��
	DrawBlock();		//�u���b�N��`�悷��
	DrawScore();		//�X�R�A��`�悷��

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

/***********************************************
 * �{�[���̕`�揈��
 ***********************************************/
void DrawBall(void) {
	//�{�[���̕`��
	DrawCircle(g_BallX, g_BallY, 4, 0xffd700, TRUE);
}
/***********************************************
 * �{�[���̈ړ�����
 ***********************************************/
void MoveBall(void) {
	g_BallX += g_MoveX;
	g_BallY += g_MoveY;



	//�ǂ�V��ł̔���
	if (g_BallX < 4 || g_BallX>640 - 4) {
		if (g_BallX < 4) {
			g_BallX = 4;
		}
		else {
			g_BallX = 640 - 4;
		}g_BallAngle = (1 - g_BallAngle) + 0.5f;
		if (g_BallAngle > 1)g_BallAngle -= 1.0f;
		ChangeAngl();
	}

	if (g_BallY < 8) {
		g_BallAngle = (1 - g_BallAngle);
		ChangeAngl();
	}

	//��ʉ��𒴂�����Q�[���I�[�o�[
	if (g_BallY > 480 + 4) {
		g_BallFlg = 2;
		if (--g_RestBall < 0) {
			if (g_Score >= g_Ranking[9].score) {
				g_GameState = 7;  //�����L���O���͏���
			}
			else {
				g_GameState = 5;
			}
		}
	}

	if (g_BallFlg != 2) {
		g_BallX += g_MoveX;
		g_BallY += g_MoveY;
	}
	else {
		g_BallX = g_BarX + 30;
		g_BallY = g_BarY - 6;
	}
}

/***********************************************
 *�p�x�ύX����
 ***********************************************/
void ChangeAngl(void) {
	float rad = g_BallAngle * (float)M_PI * 2;
	g_MoveX = (int)(g_Speed * cosf(rad));
	g_MoveY = (int)(g_Speed * sinf(rad));
}
/***********************************************
 *�o�[�̕`�揈��
 ***********************************************/
void DrawBar(void) {
	//�o�[�̕`��
	DrawBox(g_BarX, g_BarY, g_BarX + , g_BarY + 8, 0xFFD700, TRUE);
}
/***********************************************
 *�o�[�̈ړ�����
 ***********************************************/
void MoveBar(void) {

	//�}�E�X������W��ǂݎ��
	GetMousePoint(&g_MouseX, &g_MouseY);

	g_BarX = g_MouseX;
	if (g_BarX < 0) {
		g_BarX = 0;
	}
	else if (g_BarX > 640 - 60) {
		g_BarX = 580;
	}

	//leftmouse
	if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && g_BallFlg == 2) {
		g_BallFlg = 0;
		//speed&angle
		g_Speed = 5;
		g_BallAngle = 0.625f;
		ChangeAngl();
	}
}
/***********************************************
 *�{�[���ƃo�[�̓����蔻��
 ***********************************************/
void HitBar(void) {
	int mx0, mx1, my0, my1, sx0, sx1, sy0, sy1;

	//���W�ʒu�̎��O�v�Z
	mx0 = g_BallX - 4;
	mx1 = g_BallX + 4;
	my0 = g_BallY - 4;
	my1 = g_BallY + 4;
	sx0 = g_BarX;
	sx1 = g_BarX + 60;
	sy0 = g_BarY;
	sy1 = g_BarY + 8;

	//�{�[���ƃo�[�̓����蔻��
	if (sx0 <= mx1 && sx1 >= mx0 && sy0 <= my1 && sy1 >= my0) {

		if (g_BallFlg == 0) {
			g_BallAngle = (0.3f / 60) * (mx1 - sx0) + 0.6f;
			ChangeAngl();

			g_BallFlg = 1;
		}
	}
	else {
		if (g_BallFlg != 2)g_BallFlg = 0;
	}
}
void DrawGameOver(void) {

	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;

	SetFontSize(48);
	DrawString(200, 200, "Game Over", GetColor(255, 0, 0));

	//�����̕\��(�_��)
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450,
			"-- Press [SPACE]Key --", GetColor(255, 0, 0));
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}
/***********************************************
 *�u���b�N��������
 ***********************************************/
void InitBlock(void) {

	//�u���b�N�z��̏�����
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_BlockData[g_Stage][i][j] != 0) {
				g_Block[i][j].flg = 1;
				g_Block[i][j].x = j * 40;
				g_Block[i][j].y = i * 16 + 80;
				g_Block[i][j].w = 40;
				g_Block[i][j].h = 8;
				g_Block[i][j].image = g_BlockData[g_Stage][i][j];
				g_Block[i][j].score = g_Block[i][j].image * 10;
			}
		}
	}
	g_BallFlg = 2;
}
/***********************************************
 *�u���b�N�`�揈��
 ***********************************************/
void DrawBlock(void) {

	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1) {
				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
			}
		}
	}
}
/***********************************************
 *�{�[���ƃu���b�N�̓����蔻��
 ***********************************************/
void HitBlock(void) {

	//�{�[���ƃu���b�N�̓����蔻��
	int x = g_BallX / 40;
	int y = (g_BallY - 80) / 16;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && g_Block[y][x].flg != 0) {
		g_Block[y][x].flg = 0;

		g_BallAngle = (1 - g_BallAngle);

		g_Score += g_Block[y][x].score;
		ChangeAngl();

		if (CheckBlock() == 0)g_GameState = 6;
	}
}
/***********************************************
 *�X�R�A�`�揈��
 ***********************************************/
void DrawScore(void) {
	DrawFormatString(20, 20, 0xffffff, "SCORE:%06d", g_Score);

	//last ball
	SetFontSize(10);
	DrawFormatString(600, 460, 0xFFD700, "�Z x%d", g_RestBall);
}
/***********************************************
 *�u���b�N�`�F�b�N����
 ***********************************************/
int CheckBlock(void) {

	//�u���b�N�z��̏�����
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1)  return -1;
		}
	}

	return 0;
}
/***********************************************
 *�Q�[���N���A��ʕ`�揈��
 ***********************************************/
void DrawGameClear(void) {

	//�X�y�[�Xkey��NEXT�X�e�[�W��
	if (g_KeyFlg & PAD_INPUT_M) {
		g_GameState = 4;
		if (++g_Stage > 4)g_Stage = 0;
		InitBlock();
	}
	SetFontSize(48);
	DrawString(120, 200, "Congratulation", 0x7f00f0);

	//�����̓_��
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "--  Press[SPACE]Key  --", 0xff0000);
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}