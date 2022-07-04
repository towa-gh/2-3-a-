/****************************************************************************************************************
*** �@��T�́@�~�j�Q�[�������i�Q�j
***
*** �@���[�X�������Q�[
*****************************************************************************************************************/
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#define RANKING_DATA 5

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�萔�̐錾
***
*****************************************************************************************************************/

//��ʗ̈�̑傫��
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//���@�̏����l
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
//const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;

//�G�@�̍ő吔
const int ENEMY_MAX = 4;


/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�ϐ��̐錾
***
*****************************************************************************************************************/
int g_OldKey;     //�O��̓��̓L�[
int g_NowKey;     //����̓��̓L�[
int g_KeyFlg;     //���̓L�[���

int g_GameState = 0;  //�Q�[�����[�h

int g_TitleImage;     //�摜�p�ϐ�
int g_Menu, g_Cone;   //���j���摜�ϐ�













int g_StageImage;

int g_Player, g_PlayerRight, g_PlayerLeft, g_Barrier;          //�L�����摜�ϐ�

int saigo = g_PlayerLeft;

//���@�̍\����
struct PLAYER {

	int flg;          //�g�p�t���O
	int x, y;          //���W��.��
	int w, h;          //�����@������
	double angle;     //�@�̂̌���
	int count;          //�^�C�~���O�p
	int speed;          //�ړ����x
	

};

//���@
struct PLAYER g_player;


struct PLAYERRIGHT {

	int flg;          //�g�p�t���O
	int x, y;          //���W��.��
	int w, h;          //�����@������
	double angle;     //�@�̂̌���
	int count;          //�^�C�~���O�p
	int speed;          //�ړ����x

};

//���@
struct PLAYER g_playerright;


struct PLAYERLEFT {

	int flg;          //�g�p�t���O
	int x, y;          //���W��.��
	int w, h;          //�����@������
	double angle;     //�@�̂̌���
	int count;          //�^�C�~���O�p
	int speed;          //�ړ����x

};

//���@
struct PLAYER g_playerleft;



/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�֐��̃v���g�^�C�v�錾
***
*****************************************************************************************************************/
void GameInit(void);           //�Q�[������������
void GameMain(void);           //�Q�[�����C������

void DrawGameTitle(void);      //�^�C�g���`�揈��

int LoadImages();              //�摜�ǂݍ���

void PlayerControl();          //���@����






/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�v���O�����̊J�n
***
*****************************************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// �^�C�g���ݒ�
	SetMainWindowText("Drive&Avoid");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return-1;  //�摜�ǂݍ��݊֐����Ăяo��

	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

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
	
		case 5:
			GameMain();     //�Q�[�����C������
			break;
	
		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[���^�C�g���\���i���j���[��ʁj
***
****************************************************************************************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;

	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		/*if (++MenuNo > 3)MenuNo = 0;*/
		MenuNo++;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		/*if (--MenuNo < 0)MenuNo = 3;*/
		MenuNo--;
	}

	//�y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//���j���[
	DrawGraph(120, 300, g_Menu, TRUE);

	//���j���[�J�[�\��
	DrawRotaGraph(90, 320 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[����������
***
*****************************************************************************************************************/
void GameInit(void)
{

	//�v���C���[�̏����ݒ�
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;

	//�Q�[�����C��������
	g_GameState = 5;



}



/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[�����C��
***
*****************************************************************************************************************/
void GameMain(void)
{

	PlayerControl();

	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);
	DrawString(150, 450, "--- �X�y�[�X�L�[�������ă^�C�g���ɔ�� ---", 0xffffff, 0);

}



/****************************************************************************************************************
***                            �v���C���[�̈ړ�����

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F �Ȃ�
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F �Ȃ�

*****************************************************************************************************************/
void PlayerControl()
{




	/*int PlayerPojishonRihght= DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);*/
	int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);
	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, saigo, TRUE, FALSE);

	//�v���C���[�̕\��
	//�㉺���E�ړ�
	if (g_player.flg == TRUE) {




		if (g_NowKey & PAD_INPUT_RIGHT) {

			int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);

			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);
			g_player.x += g_player.speed;


			saigo = g_PlayerRight;


		}



		if (g_NowKey & PAD_INPUT_LEFT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / -20, g_PlayerLeft, TRUE, FALSE);
			g_player.x -= g_player.speed;


			saigo = g_PlayerLeft;

		}




		//	if (g_player.x -= !g_player.speed) {
		//		if (g_NowKey & PAD_INPUT_RIGHT) {


		//			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);
		//			/*g_player.x += g_player.speed;*/



		//		}

		//	}

	}

	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > SCREEN_WIDTH - 50)  g_player.x = SCREEN_WIDTH - 50;




}


/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�摜�ǂݍ���
***
*****************************************************************************************************************/
int LoadImages()
{
	//�^�C�g��
	if ((g_TitleImage = LoadGraph("images/Chapter5/io__________.bmp")) == -1)return-1;

	//���j���[
	if ((g_Menu = LoadGraph("images/Chapter5/start_m.bmp")) == -1)return-1;
	if ((g_Cone = LoadGraph("images/Chapter5/cone.bmp")) == -1)return-1;


	//�v���C���[
	if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.bmp")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	return 0;
}




