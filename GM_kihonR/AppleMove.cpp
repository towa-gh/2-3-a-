#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "AppleMove.h"
#include "main.h"

Move move;


/********************************/
 /*  �ϐ��̐錾*/
/*********************************/
int	g_OldKey;				// �O��̓��̓L�[
int	g_NowKey;				// ����̓��̓L�[
int	g_KeyFlg;				// ���̓L�[���

int g_GameState = 0;	// �Q�[�����[�h

int	g_TitleImage;		// �摜�p�ϐ�

//int g_WaitTime = 0; //�҂�����

//int g_StageImage;

int g_apple;
//
//int g_Mileage;

/********************************/
 /*  �萔�̐錾*/
/*********************************/
//��ʗ̈�̑傫��
//const int SCREEN_WIDTH = 640;
//const int SCREEN_HEIGHT = 480;

//���@�̏����l
//const int PLAYER_POS_X = SCREEN_WIDTH / 2;
//const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
//const int PLAYER_WIDTH = 63;
//const int PLAYER_HEIGHT = 120;
//const int PLAYER_SPEED = 5;


//�G�@�̍ő吔
//const int APPLE_MAX = 10;//20 //����8



////�G�@�\����
//struct ENEMY {
//	int flg; //�g�p�t���O
//	int type; //�^�C�v
//	int img; //�摜
//	int x, y, w, h; //���Wx,y�@���@w �����@h
//	int speed; //�ړ����x
//	int point; //�X�R�A���Z
//
//
//};

//�G�@
//struct ENEMY g_enemy[APPLE_MAX];
//struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };
//struct ENEMY g_enemyCh = { TRUE,4,0,0,-50,18,18,0,1 };

///***********************************************
// * �֐��̃v���g�^�C�v�錾
// ***********************************************/
void GameInit(void);		//�Q�[������������
void GameMain(void);		//�Q�[�����C������

int  LoadImages();		//�摜�ǂݍ���

//void BackScrool(); //�w�i��ʃX�N���[������

//void EnemyControl(); //�G�@����

//int CreateEnemy(); //�G�@��������


///***********************************************
// * �v���O�����̊J�n
// ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	SetMainWindowText("��񂲃Q�[��");//�^�C�g���ݒ�

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������


	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return -1;// �摜�ǂݍ��݊֐����Ăяo��

	 /*�Q�[�����[�v*/
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		//���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();//��ʂ̏�����

		switch (g_GameState) {
		//case GAME_TITLE:
		//	DrawGameTitle(); //�Q�[���^�C�g���`�揈��
		//	break;
		case 0 /*GAME_INIT*/:
			/*applemove.*/GameInit(); //�Q�[���^�C�g����������
			break;
		//case  DRAW_RANKING:
		//	DrawRanking();//�����L���O�`�揈��
		//	break;
		//case 3:
		//	DrawHelp();//�Q�[���w���v�`�揈��
		//	break;
		//case 4:
		//	DrawEnd();//�Q�[���G���h�`�揈��
		//	break;
		case 5/*GAME_MAIN*/:
			GameMain();//�Q�[�����C������
			break;
		//case 6:
		//	DrawGameOver();//�Q�[���I�[�o�[�`�揈��
		//	break;
		//case INPUT_RANKING:
		//	InputRanking();//�����L���O���͏���
		//	break;
		}
		ScreenFlip(); //����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End(); //DX ���C�u�����g�p�̏I������

	return 0; //�\�t�g�̏I��
}

///////****************************************/
//////�Q�[����������
//////****************************************/
void GameInit(void) {

	//�Q�[�����C��������
	g_GameState = 5;//5;

	///*///***�G�l�~�[�̏����ݒ�***/
	//for (int i = 0; i < APPLE_MAX; i++) {

	//	g_enemy[i].flg = FALSE;

	//}
}



///****************************************/
//�Q�[�����C��
//****************************************/
void GameMain(void) {

	/*BackScrool();*/
	applemove.EnemyControl();
	/*PlayerControl();*/

	
}

///****************************************/
//�w�i��ʃX�N���[������
// �����F�Ȃ�
// �߂�l�F�Ȃ�
//****************************************/
//void BackScrool() {
//	/*g_Mileage += g_player.speed;*/
//
//	/*�X�e�[�W�摜�\��*/
//
//	//�`��\�G���A��ݒ�
//	SetDrawArea(0, 0, 500, 480);
//
//	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
//
//
//	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
//
//	/*�G���A��߂�*/
//	SetDrawArea(0, 0, 640, 480);
//
//	//�X�R�A���\���̈�
//	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
//}



///****************************************/
//�摜�ǂݍ���
//****************************************/
int LoadImages() {
	////�^�C�g��
	//if ((g_TitleImage = LoadGraph("images/Apple/AppleT.png")) == -1)return -1;
	////���j���[
	//if ((g_Menu = LoadGraph("images/Apple/menu.bmp")) == -1)return -1;
	//if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1; 
	////�����L���O�f�[�^�ɓǂݍ���z
	//if (ReadRanking() == -1) return -1;
	///*�����L���O�摜�f�[�^�̓ǂݍ���*/
	//if ((g_RankingImage = LoadGraph("images/Apple/Ranking.bmp")) == -1)return -1;
	 
	////�G���f�B���O
	//if ((g_EndImage = LoadGraph("images/Apple/End.bmp")) == -1) return -1;
	//���
	if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1;
	
	//�X�e�[�W�w�i
	/*if ((g_StageImage = LoadGraph("images/Apple/mori.png")) == -1)return -1;*/
	////�v���C���[
	//if ((g_Player = LoadGraph("images/Apple/player1.png")) == -1)return -1;

	return 0;
}

int Move::getg_apple() {
	if ((g_apple = LoadGraph("images/Apple/apple1.png")) == -1)return -1;
	return 0;
}

int Move::getg_Mileage() {
	return g_Mileage;
}