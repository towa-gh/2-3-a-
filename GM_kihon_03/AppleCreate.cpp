/***********************************************
 ** �@��5�́@�~�j�Q�[��������(2)
 **�@�@�@�@�@�@�@���[�X�������Q�[
 ***********************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#define RANKING_DATA 5
#include "AppleCreate.h"
#include"main.h"
Apple apple;

 /***********************************************
  *�ϐ��錾
  ***********************************************/

int g_OldKey;//�O��̓��̓L�[
int g_NowKey;//����̓��̓L�[
int g_KeyFlg;//���̓L�[���

int g_GameState = 0;//�Q�[�����[�h

int g_TitleImage;//�摜�p�ϐ�
int g_Menu, g_Cone;//���j���[�摜�ϐ�

int g_Score = 0;//�X�R�A
int g_RankingImage;//�摜�p�ϐ�

//int g_Item[2];//�A�C�e���摜�ϐ�

//int g_WaitTime = 0;//�҂�����
//int g_EndImage;

int g_Mileage;//���s����
//�G�J�E���g
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;

int g_Apple;//�L�����摜�ϐ�
int g_GreenApple;//�L�����摜�ϐ�
int g_YellowApple;//�L�����摜�ϐ�
//int g_PoisonApple[4];//�L�����摜�ϐ�


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int g_StageImage;


/***********************************************
 *�֐��̃v���g�^�C�v�錾
 ***********************************************/

void GameInit(void);//�Q�[������������
void GameMain(void);//�Q�[�����C������

void DrawGameTitle(void);//�^�C�g���`�揈��

int LoadImages();//�摜�ǂݍ���


void BackScrool();

//void PlayerControl();//���@����

//void EnemyControl();//�G�@����
//int CreateEnemy();//�G�@��������

/***********************************************
 *�v���O�����̊J�n
 ***********************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("Drive&Avoid");//�^�C�g����ݒ�
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
			DrawGameTitle();	//�Q�[���^�C�g���`�揈��
			break;
		case 1:
			GameInit();		//�Q�[����������
			break;
		//case 2:
		//	DrawRanking();	//�����L���O�`�揈��
		//	break;
		//case 3:
		//	DrawHelp();		//�Q�[���w���v�`�揈��
		//	break;
		//case 4:
		//	DrawEnd();		//�Q�[���G���h�`�揈��
		//	break;
		case 5:
			GameMain();     //�Q�[�����C������
			break;
		//case 6:
		//	DrawGameOver(); //�Q�[���I�[�o�[�`�揈��
		//	break;
		//case 7:
		//	InputRanking(); //�����L���O���͏���
		//	break;
		}
		ScreenFlip();     //����ʂ̓��e��\��ʂɔ��f
	}
	DxLib_End();

	return 0;
}
/***********************************************
 *�Q�[���^�C�g���\��(���j���[���)
 ***********************************************/
void DrawGameTitle(void) {
	static int MenuNo = 0;
	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
	}
	//Z�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A)g_GameState = MenuNo + 1;
	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);
	//���j���[
	DrawGraph(120, 200, g_Menu, TRUE);
	//���j���[�J�[�\��
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Apple, TRUE);
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



	//�G�l�~�[�̏����ݒ�
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//	g_enemy[i].flg = FALSE;
	//}

	create.Init();
	

	//�Q�[�����C��������
	g_GameState = 5;
}
/***********************************************
 *�Q�[�����C��
***********************************************/
void GameMain(void) {
	BackScrool();

	create.EnemyControl();

}
/***********************************************
 *�w�i�摜�X�N���[������
 * �����F�Ȃ�
 * �߂�l�F�Ȃ�
***********************************************/
void BackScrool() {
	////�X�e�[�W�摜�\��
	/*g_Mileage += 5;
	g_Mileage += g_Player.speed;*/

	//�`��\�G���A��F��
	SetDrawArea(0, 0, 500, 480);
	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	DrawGraph(0, g_Mileage % 480 , g_StageImage, FALSE);
	//�G���A��߂�
	SetDrawArea(0, 0, 640, 480);
	//�X�e�[�W�w�i
	DrawBox(500,0,640,480,0x009900,TRUE);
	
}
/***********************************************
*�摜�ǂݍ���
***********************************************/
int LoadImages() {
	//�^�C�g��
	if ((g_TitleImage = LoadGraph("images/chapter5/Title.bmp")) == -1)return - 1;
	//���j���[
	if ((g_Menu = LoadGraph("images/chapter5/menu.bmp")) == -1) return -1;
	if ((g_Cone = LoadGraph("images/chapter5/cone.bmp")) == -1) return-1;
	

	//�����L���O�摜�f�[�^�̓ǂݍ���
	//if ((g_RankingImage = LoadGraph("images/chapter5/Ranking.bmp")) == -1) return -1;

	//�G���f�B���O
	//if ((g_EndImage = LoadGraph("images/chapter5/End.bmp")) == -1) return -1;

	//�G
	if ((g_Apple=LoadGraph("images/chapter5/Apple.bmp")) == -1)return-1;
	if ((g_GreenApple = LoadGraph("images/chapter5/GreenApple.png")) == -1)return-1;
	if ((g_YellowApple = LoadGraph("images/chapter5/YellowApple.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp" )) == -1)return-1;

	//�X�e�[�W�w�i
	if ((g_StageImage = LoadGraph("images/chapter5/bg_natural_mori.jpg")) == -1) return -1;

	return 0;
}
int Apple::GetApple() {

	return g_Apple;
}

int Apple::GetMileage() {

	return g_Mileage;
}