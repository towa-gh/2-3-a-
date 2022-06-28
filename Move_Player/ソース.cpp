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

int g_Score = 0;     //�X�R�A

int g_RankingImage;  //�摜�p�ϐ�

int g_Item[2];

int g_WaitTime = 0;  //�҂�����

int g_EndImage;

int g_Mileage;       //���s����

int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;  //�G�J�E���g

int g_Teki[3];

int g_Ringo;

//int g_Ringo[3];

int g_StageImage;

int g_Player, g_PlayerRight, g_PlayerLeft, g_Barrier;          //�L�����摜�ϐ�



//���@�̍\����
struct PLAYER {

	int flg;          //�g�p�t���O
	int x, y;          //���W��.��
	int w, h;          //�����@������
	double angle;     //�@�̂̌���
	int count;          //�^�C�~���O�p
	int speed;          //�ړ����x
	//int hp;          //�̗�
	int fuel;          //�R��
	int bari;          //�o���A��
	int baricnt;          //�o���A�p������
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
	//int hp;          //�̗�
	int fuel;          //�R��
	int bari;          //�o���A��
	int baricnt;          //�o���A�p������
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
	//int hp;          //�̗�
	int fuel;          //�R��
	int bari;          //�o���A��
	int baricnt;          //�o���A�p������
};

//���@
struct PLAYER g_playerleft;

//�����L���O�f�[�^�i�\���́j
struct RankingData {

	int no;

	char name[11];

	long score;
};

//�����L���O�f�[�^�ϐ��錾
struct RankingData  g_Ranking[RANKING_DATA];

//�G�@�̍\����
struct ENEMY {

	int flg;  //�g�p�t���O
	int type; //�^�C�v
	int img;  //�摜
	int x, y, w, h;  //���Wxy ��w ����h
	int speed; //�ړ����x
	int point; //�X�R�A���Z

};

//�G�@
struct ENEMY g_enemy[ENEMY_MAX];

struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };

struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };

struct ENEMY g_item00 = { TRUE,0,0,0,-50,50,50,0,1 };

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�֐��̃v���g�^�C�v�錾
***
*****************************************************************************************************************/
void GameInit(void);           //�Q�[������������
void GameMain(void);           //�Q�[�����C������

void DrawGameTitle(void);      //�^�C�g���`�揈��
void DrawGameOver(void);       //�Q�[���I�[�o�[��ʕ`�揈��
void DrawEnd(void);            //�Q�[���G���h�`�揈��
void DrawHelp(void);           //�Q�[���w���v�`�揈��

void DrawRanking(void);        //�����L���O�`�揈��
void InputRanking(void);       //�����L���O����
void SortRanking(void);        //�����L���O���בւ�
int  SaveRanking(void);        //�����L���O�f�[�^�̕ۑ�
int  ReadRanking(void);        //�����L���O�f�[�^�ǂݍ���

int LoadImages();              //�摜�ǂݍ���

void BackScrool();             //�w�i�摜�X�N���[������

void PlayerControl();          //���@����

void EnemyControl();           //�G�@����
int CreateEnemy();             //�G�@��������

int HitBoxPlayer(PLAYER* p, ENEMY* e);  //�����蔻��

void DrawRanking(void);        //�����L���O�`��

void SortRanking(void);        //�����L���O���ёւ�

int  SaveRanking(void);        //�����L���O�ۑ�

int ReadRanking(void);         //�����L���O�ǂݍ���

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
		case 2:
			DrawRanking();	//�����L���O�`�揈��
			break;
		case 3:
			DrawHelp();		//�Q�[���w���v�`�揈��
			break;
		case 4:
			DrawEnd();		//�Q�[���G���h����
			break;
		case 5:
			GameMain();     //�Q�[�����C������
			break;
		case 6:
			DrawGameOver();		//�Q�[���N���A�`�揈��
			break;
		case 7:
			InputRanking();    //�����L���O���͏���
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
*****************************************************************************************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;

	//���j���[�J�[�\���ړ�����
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;

	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
	}

	//�y�L�[�Ń��j���[�I��
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//���j���[
	DrawGraph(120, 200, g_Menu, TRUE);

	//���j���[�J�[�\��
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[����������
***
*****************************************************************************************************************/
void GameInit(void)
{
	//�X�R�A�̏�����
	g_Score = 0;

	//���s������������
	g_Mileage = 0;

	//�G�P������Đ��̏����ݒ�
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;

	//�v���C���[�̏����ݒ�
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;
	//g_player.hp = PLAYER_HP;
	g_player.fuel = PLAYER_FUEL;
	g_player.bari = PLAYER_BARRIER;
	/*g_player.bariup = PLAYER_BARRIERUP;*/

	//�Q�[�����C��������
	g_GameState = 5;

	//�G�l�~�[�̏����ݒ�
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}


}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[�������L���O�`��\��
***
*****************************************************************************************************************/
void DrawRanking(void)
{
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	//�����L���O�摜�\��
	DrawGraph(0, 0, g_RankingImage, FALSE);

	//�����L���O�ꗗ��\��
	SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	DrawString(100, 450, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);

}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[���w���v�`�揈��
***
*****************************************************************************************************************/
void DrawHelp(void)
{
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;

	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);
	SetFontSize(16);

	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);

	DrawString(20, 180, "���葱����Q�[���ł��B", 0xffffff, 0);

	DrawString(20, 200, "�R�����s���邩��Q���ɐ��񓖂����", 0xffffff, 0);

	DrawString(20, 220, "�Q�[���I�[�o�[", 0xffffff, 0);

	DrawString(20, 250, "�A�C�e���ꗗ", 0xffffff, 0);

	DrawGraph(20, 260, g_Item[0], TRUE);

	DrawString(20, 315, "���ƔR�����񕜂����", 0xffffff, 0);

	DrawGraph(20, 335, g_Item[1], TRUE);

	DrawString(20, 385, "�_���[�W���󂯂Ă��鎞�Ɏ��Ƒϋv��", 0xffffff, 0);

	DrawString(20, 405, "�ϋv�������Ă��Ȃ�������R���������񕜂����", 0xffffff, 0);

	DrawString(20, 450, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[���G���h�`�揈��
***
*****************************************************************************************************************/
void DrawEnd(void)
{
	//�G���h�摜�\��
	DrawGraph(0, 0, g_EndImage, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//�^�C���̉ΎR����&�I���i�R�b��j
	if (++g_WaitTime > 180)g_GameState = 99;
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[�����C��
***
*****************************************************************************************************************/
void GameMain(void)
{

	BackScrool();

	EnemyControl();

	PlayerControl();

	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 6;

	SetFontSize(16);
	DrawString(20, 20, "�Q�[�����C��", 0xffffff, 0);
	DrawString(150, 450, "--- �X�y�[�X�L�[�������ăQ�[���I�[�o�[�� ---", 0xffffff, 0);

}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[���I�[�o�[��ʕ`�揈��
***
*****************************************************************************************************************/
void DrawGameOver(void)
{

	//�`��\�G���A��ݒ�
	SetDrawArea(0, 0, 500, 480);

	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);

	//�G���A��߂�
	SetDrawArea(0, 0, 640, 480);

	//�X�R�A���\���̈�
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);




	/*g_Score = (g_Mileage / 10 * 10) + g_EnemyCount3 * 50 + g_EnemyCount2 * 100 + g_EnemyCount1 * 200;*/


	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M) {
		if (g_Ranking[RANKING_DATA - 1].score >= g_Score) {
			g_GameState = 0;


		}
		else {
			g_GameState = 7;
		}
	}

	DrawBox(150, 150, 490, 330, 0x009900, TRUE);
	DrawBox(150, 150, 490, 330, 0x000000, FALSE);

	SetFontSize(20);
	DrawString(220, 170, "�Q�[���I�[�o�[", 0xcc0000);
	SetFontSize(16);
	/*DrawRotaGraph(230, 230, 0.3f, M_PI / 2, g_Teki[2], TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, g_Teki[0], TRUE, FALSE);*/

	DrawRotaGraph(230, 230, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);



	/*DrawFormatString(260, 200, 0xFFFFFF, "%6d x  10 = %6d", g_Mileage / 10, g_Mileage / 10 * 10);*/
	DrawFormatString(260, 220, 0xFFFFFF, "%6d x  50 = %6d", g_EnemyCount3, g_EnemyCount3 * 50);
	DrawFormatString(260, 243, 0xFFFFFF, "%6d x  100 = %6d", g_EnemyCount2, g_EnemyCount2 * 100);
	DrawFormatString(260, 264, 0xFFFFFF, "%6d x  200 = %6d", g_EnemyCount1, g_EnemyCount1 * 200);

	//DrawString(310, 290, "�X�R�A", 0x000000);

	DrawFormatString(260, 290, 0xFFFFFF, "             =%6d", g_Score);

	DrawString(150, 450, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);
}

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�����L���O���͏���
***
*****************************************************************************************************************/

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
	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[4].name, FALSE) == 1) {
		g_Ranking[4].score = g_Score;	// �����L���O�f�[�^�̂P�O�ԖڂɃX�R�A��o�^
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
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	// ���ʕt��
	for (i = 0; i < 5; i++) {
		g_Ranking[i].no = 1;
	}

	// ���_�������ꍇ�́A�������ʂƂ���
	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
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
	for (int i = 0; i < 4; i++) {
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
	for (int i = 0; i < 4; i++) {
		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	//�t�@�C���N���[�Y
	fclose(fp);

	return 0;
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
	/*if ((g_TitleImage = LoadGraph("images/Chapter5/Title.bmp")) == -1)return-1;*/

	//���j���[
	if ((g_Menu = LoadGraph("images/Chapter5/menu.bmp")) == -1)return-1;
	if ((g_Cone = LoadGraph("images/Chapter5/cone.bmp")) == -1)return-1;

	//�����L���O�f�[�^�̓ǂݍ���
	if (ReadRanking() == -1)return -1;

	//�����L���O�摜�f�[�^�̓ǂݍ���
	if ((g_RankingImage = LoadGraph("images/Chapter5/Ranking.bmp")) == -1)return -1;

	//�A�C�e��
	if ((g_Item[0] = LoadGraph("images/Chapter5/gasoLine.bmp")) == -1)return -1;
	if ((g_Item[1] = LoadGraph("images/Chapter5/supana.bmp")) == -1)return -1;

	//�G���f�B���O
	if ((g_EndImage = LoadGraph("images/Chapter5/End.bmp")) == -1)return -1;

	//�G
	if ((g_Ringo = LoadGraph("images/Chapter5/ios__________.bmp")) == -1)return -1;

	//�X�e�[�W�w�i
	if ((g_StageImage = LoadGraph("images/Chapter5/bg_natural_mori.bmp")) == -1)return -1;

	//�v���C���[
	if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.bmp")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	return 0;
}



/****************************************************************************************************************
***                            �w�i�摜�X�N���[������

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F �Ȃ�
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F �Ȃ�

*****************************************************************************************************************/
void BackScrool()
{
	//g_Mileage += 5;
	//g_Mileage += g_player.speed;

	//�X�e�[�W�摜�\��

	//�`��\�G���A��ݒ�
	SetDrawArea(0, 0, 500, 480);

	//DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	//DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
	DrawGraph(0, 0, g_StageImage, TRUE);

	//�G���A��߂�
	SetDrawArea(0, 0, 640, 480);

	//�X�R�A���\���̈�
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
}

/****************************************************************************************************************
***                            �v���C���[�̈ړ�����

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F �Ȃ�
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F �Ȃ�

****************************************************************************************************************/
void PlayerControl()
{
	

	//�Q�[���I�[�o�[������
	if (g_player.fuel <= 0)  g_GameState = 6;

	int PlayerPojishonRihght= DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);
	int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);

	//�v���C���[�̕\��
	//�㉺���E�ړ�
	if (g_player.flg == TRUE) {

	/*	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Player, TRUE, FALSE);*/

		if (g_NowKey & PAD_INPUT_RIGHT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);
			g_player.x += g_player.speed;


		}


		if (g_NowKey & PAD_INPUT_LEFT) {

			
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);
			g_player.x -= g_player.speed;

		}

		



	}

	//��ʂ��͂ݏo���Ȃ��悤�ɂ���
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > SCREEN_WIDTH - 180)  g_player.x = SCREEN_WIDTH - 180;

	if (g_player.y < 60)    g_player.y = 60;

	if (g_player.y > SCREEN_HEIGHT - 60)   g_player.y = SCREEN_HEIGHT - 60;




	//�v���C���[�̕\��
	/*if (g_player.flg == TRUE) {*/
		/*if (g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);

		}*/
		/*else if (g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);

		}*/


		/*DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Player, TRUE, FALSE);*/




	/*else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Car, TRUE, FALSE);

	}*/

	/*if (g_KeyFlg & PAD_INPUT_C && g_player.bari > 0 && g_player.baricnt <= 0) {

		g_player.bari--;
		g_player.baricnt = 1000;
	}*/

	/*if (g_player.baricnt > 0) {

		g_player.baricnt -= g_player.speed;
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Barrier, TRUE, FALSE);

	}
	else {

		g_player.baricnt = 0;

	}*/

	/*}*/
	/*else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 8 * (++g_player.count / 5), g_Car, TRUE, FALSE);

		if (g_player.count >= 80) g_player.flg = TRUE;
	}*/

	//�G�����������\��
	SetFontSize(16);

	DrawFormatString(510, 800, 0x000000, "��������");

	/*DrawRotaGraph(523, 120, 0.3f, 0, g_Teki[0], TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Teki[2], TRUE, FALSE);*/

	DrawRotaGraph(523, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);


	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
	DrawFormatString(560, 140, 0xFFFFFF, "%03d", g_EnemyCount2);
	DrawFormatString(610, 140, 0xFFFFFF, "%03d", g_EnemyCount3);


}


/****************************************************************************************************************
***                            �G�l�~�[�̈ړ�

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F �Ȃ�
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F �Ȃ�

*****************************************************************************************************************/
void EnemyControl()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {

			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			if (g_player.flg == FALSE)continue;

			//�^���������Ɉړ�
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;

			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h) g_enemy[i].flg = FALSE;

			//�G�@��ǂ��z������J�E���g����
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {

				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0) g_EnemyCount1++;
				if (g_enemy[i].type == 1) g_EnemyCount2++;
				if (g_enemy[i].type == 2) g_EnemyCount3++;
			}

			//�����蔻��
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE && g_player.baricnt <= 0) {

				g_player.flg = TRUE;
				g_player.speed = PLAYER_SPEED;
				//g_player.count = 0;
				g_enemy[i].flg = FALSE;

				//if (g_player.hp <= 0)  g_GameState = 6;
			}

		}
	}

	//���s�������ƂɓG�o���p�^�[���𐧌䂷��
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}

/****************************************************************************************************************
***                            �G�@�̐���

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F �Ȃ�
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F TRUE : �����@�@FALSE : ���s

*****************************************************************************************************************/
int CreateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {

			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			/*g_enemy[i].img = g_Teki[g_enemy[i].type];*/
			g_enemy[i].img = g_Ringo;
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;

			//����
			return TRUE;

		}
	}

	//���s
	return FALSE;
}

/****************************************************************************************************************
***                            ���@�ƓG�@�̓����蔻��i�l�p�j

***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�� ��  �F PLAYER�|�C���^
�@
***�@�@�@�@�@�@�@�@�@�@�@�@�@  �߂�l �F TRUE : ������@�@FALSE : �Ȃ�

*****************************************************************************************************************/
int HitBoxPlayer(PLAYER* p, ENEMY* e)
{
	//x,y�͒��S���W�Ƃ���
	int sx1 = p->x - (p->w / 2);
	int sy1 = p->y - (p->h / 2);

	int sx2 = sx1 + p->w;
	int sy2 = sy1 + p->h;

	int dx1 = e->x - (e->w / 2);
	int dy1 = e->y - (e->h / 2);

	int dx2 = dx1 + e->w;
	int dy2 = dy1 + e->h;

	//��`���d�Ȃ肠���Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;

	}
	return FALSE;
}



