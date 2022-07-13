#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#define RANKING_DATA 5
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
int g_WaitTime = 0;//�҂�����
int g_EndImage;
int g_Mileage;//���s����
//�G�J�E���g
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;
int g_Apple[3];//�L�����摜�ϐ�
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int g_StageImage;
int g_Car;//�L�����摜�ϐ�


/***********************************************
 *�萔��錾
 ***********************************************/

 //���@�̏�����
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 1000;

//�G�@�̍ő吔
const int ENEMY_MAX = 8;

//�A�C�e���̍ő�l
const int ITEM_MAX = 3;

//�G�@�̍\����

struct ENEMY {
	int flg;//�g�p�^�C�~���O
	int type;//�^�C�v
	int img;//�摜
	int x, y, w, h;//���Wx,y ��w�@����h
	int speed;//�ړ����x
	int point;//�X�R�A���Z
};
//�G�@

struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
struct ENEMY g_enemyCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

//���@�̍\����

struct PLAYER {
	int flg;//�g�p�t���O
	int x, y;//���Wx,y
	int w, h;//��w ����h
	double angle;//�@�̂̌���
	int count;//�^�C�~���O�p
	int speed;//�ړ����x
};
//���@
struct PLAYER g_Player;

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
int LoadImages();//�摜�ǂݍ���
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
			GameInit();		//�Q�[����������
			break;
		case 1:
			GameMain();     //�Q�[�����C������
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
	g_Player.flg = TRUE;
	g_Player.x = PLAYER_POS_X;
	g_Player.y = PLAYER_POS_Y;
	g_Player.w = PLAYER_WIDTH;
	g_Player.h = PLAYER_HEIGHT;
	g_Player.angle = 0.0;
	g_Player.count = 0;
	g_Player.speed = PLAYER_SPEED;

	//�G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}

	//�Q�[�����C��������
	g_GameState = 1;
}
/***********************************************
 *�Q�[�����C��
***********************************************/
void GameMain(void) {
}
/***********************************************
*�摜�ǂݍ���
***********************************************/

int LoadImages() {
	//�G
	if ((g_Apple[0] = LoadGraph("images/Apple.png")) == -1)return-1;
	if ((g_Apple[1] = LoadGraph("images/GreenApple1.png")) == -1)return-1;
	if ((g_Apple[2] = LoadGraph("images/YellowApple1.png")) == -1)return-1;
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp", )) == -1)return-1;

	//�X�e�[�W�w�i
	if ((g_StageImage = LoadGraph("images/bg_natural_mori.jpg")) == -1) return -1;

	//�v���C���[
	if ((g_Car = LoadGraph("images/Right.png")) == -1) return -1;

	return 0;
}