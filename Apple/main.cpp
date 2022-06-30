/***********************************************
 * ��5�́@�~�j�Q�[�����[�X�����i�Q�j
 *        ���[�X�������Q�[
 ***********************************************/
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#define RANKING_DATA 5
 /***********************************************
  * �萔�̐錾
 ***********************************************/
 //��ʂ̑傫��
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;
//�G�@�̍ő吔
const int ENEMY_MAX = 8;
//�A�C�e���̍ő吔
const int ITEM_MAX = 3;
/***********************************************
 * �ϐ��̐錾
 ***********************************************/

int g_OldKey;				//�O��̓��̓L�[
int g_NowKey;				//����̓��̓L�[
int g_KeyFlg;				//���̓L�[���
int g_GameState = 0;		//�Q�[�����[�h
int g_TitleImage;			//�摜�p�ϐ�
int g_Menu, g_Cone;			//���j���[��ʕϐ�
int g_Score = 0;			//�X�R�A
int g_RankingImage;			//�摜�p�ϐ�
int g_Item[2];				//�A�C�e���摜�ϐ�
int g_WaitTime = 0;			//�҂�����
int g_EndImage;
int g_Mileage;				//���s����
int g_StageImage;
int g_Mileage1;
int StartTime;
//�G�L�����J�E���g
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;
int g_Teki[4];
int g_Car, g_Barrier;		//�L�����摜�ϐ�
//�����L���O�f�[�^�i�\���́j
struct RankingData {
	int no;
	char name[11];
	long score;
};
//�����L���O�f�[�^�ϐ��錾
struct RankingData	g_Ranking[RANKING_DATA];

//�����̍\����
struct PLAYER {
	int flg;
	int x, y;
	int w, h;
	double angle;
	int count;
	int speed;
	int hp;
	int fuel;
	int bari;
	int baricnt;
	int bariup;
};
//���@
struct PLAYER g_player;
//�G�@�̍\����
struct ENEMY {
	int flg;			//�g�p�t���O
	int type;			//�^�C�v
	int img;			//�摜
	int x, y, w, h;		//���Wx,y�A�� w�A���� h
	int speed;			//�ړ����x
	int point;			//�X�R�A���Z
	double angle;		//�p�x
	double first_x;		//�ŏ��ɏo�Ă������̂�
	double next_x;		//�ŏ��ɏo�Ă������̂�
};
//�G�@
struct ENEMY g_enemy[ENEMY_MAX];
struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };
struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };
struct ENEMY g_item[ITEM_MAX];
struct ENEMY g_item00 = { TRUE,0,0,0,-50,50,50,0,1 };
/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/
void GameInit(void);		//�Q�[������������
void GameMain(void);		//�Q�[�����C������
void DrawGameTitle(void);	//�^�C�g���`�揈��
void DrawGameOver(void);	//�Q�[���I�[�o�[��ʕ`�揈��
void DrawEnd(void);			//�Q�[���G���h�`�揈��
void DrawHelp(void);		//�Q�[���w���v�`�揈��
void DrawRanking(void);		//�����L���O�`�揈��
void InputRanking(void);	//�����L���O����
int LoadImages();			//�摜�ǂݍ���
void SortRanking(void);		//�����L���O���בւ�
int SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
int ReadRanking(void);		//�����L���O�f�[�^�ǂݍ���
void BackScrool();			//�w�i�X�N���[������
void EndBackScrool();		//�w�i�X�N���[������(�Q�[���I�[�o�[��)
void PlayerControl();		//���@����
void EnemyControl();		//�G�@����
int CreateEnemy();			//�G�@��������
int HitBoxPlayer(PLAYER* p, ENEMY* e);			//�����蔻��
void ItemControl();			//�A�C�e������
int CreateItem();			//�A�C�e����������
 /***********************************************
  * �v���O�����̊J�n
  ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// �^�C�g���� Drive&Avoid �ɕύX
	SetMainWindowText("Drive&Avoid");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return-1;

	if (ReadRanking() == -1)return-1;

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
			DrawHelp();		//�G���h��ʕ`�揈��
			break;
		case 4:
			DrawEnd();		//�Q�[�����C������
			break;
		case 5:
			GameMain();
			break;
		case 6:
			DrawGameOver();
			break;
		case 7:
			InputRanking();
			break;
		}
		//SetFontSize(30);
		//DrawFormatString(100, 100 + 1 * 50, 0xffffff, "%d", g_enemy[0].type);
		//DrawFormatString(100, 100 + 2 * 50, 0xffffff, "%d", g_enemy[1].type);
		//DrawFormatString(100, 100 + 3 * 50, 0xffffff, "%d", g_enemy[2].type);
		//DrawFormatString(100, 100 + 4 * 50, 0xffffff, "%d", g_enemy[3].type);
		//DrawFormatString(100, 100 + 5 * 50, 0xffffff, "%d", g_enemy[4].type);
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
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
	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[4].name, FALSE) == 1) {
		g_Ranking[4].score = g_Score;	// �����L���O�f�[�^��4�ԖڂɃX�R�A��o�^
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
	if ((fp = fopen("dat/chapter5/rankingdata.txt", "w")) == NULL) {
		/* �G���[���� */
		printf("Ranking Data Error\n");
		return -1;
	}

	// �����L���O�f�[�^���z��f�[�^����������
	for (int i = 0; i < 5; i++) {
		fprintf(fp, "%2d %-10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
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
	if ((fp = fopen("dat/chapter5/rankingdata.txt", "r")) == NULL) {
		//�G���[����
		printf("Ranking Data Error\n");
		return -1;
	}

	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
	for (int i = 0; i < 5; i++) {
		fscanf(fp, "%2d %-10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
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
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);
}
/***********************************************
 * �Q�[����������
 ***********************************************/
void GameInit(void)
{
	//�X�R�A�̏�����
	g_Score = 0;

	//���s������������
	g_Mileage = 0;

	//�G�P���悯�����̏����ݒ�
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;

	//�v���C���[�����ݒ�
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;
	g_player.hp = PLAYER_HP;
	g_player.fuel = PLAYER_FUEL;
	g_player.bari = PLAYER_BARRIER;
	g_player.bariup = PLAYER_BARRIERUP;

	//�G�l�~�[�̏�������
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}

	//�A�C�e�������ݒ�
	for (int i = 0; i < ITEM_MAX; i++) {
		g_item[i].flg = FALSE;
	}

	//�Q�[�����C��������
	g_GameState = 5;
}
/***********************************************
 * �Q�[�������L���O�`�揈��
 ***********************************************/
void DrawRanking(void)
{
	//
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;
	//
	DrawGraph(0, 0, g_RankingImage, FALSE);

	//
	SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatString(50, 170 + i * 250, 0xffffff, "%2d  %-10s  %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}
	DrawString(100, 450, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);
}
/***********************************************
 * �Q�[���w���v�`�揈��
 ***********************************************/
void DrawHelp(void)
{
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;
	//�^�C�g���摜�\��
	DrawGraph(0, 0, g_TitleImage, FALSE);
	SetFontSize(16);
	DrawString(20, 120, "�w���v���", 0xffffff, 0);

	DrawString(20, 160, "����͏�Q��������Ȃ���", 0xffffff, 0);
	DrawString(20, 180, "���葱����Q�[���ł�", 0xffffff, 0);
	DrawString(20, 200, "�R�����s���邩��Q����", 0xffffff, 0);
	DrawString(20, 220, "���񓖂���ƃQ�[���I�[�o�[�ł�", 0xffffff, 0);
	DrawString(20, 250, "�A�C�e���ꗗ", 0xffffff, 0);
	DrawGraph(20, 260, g_Item[0], TRUE);
	DrawString(20, 315, "���ƔR�����񕜂����", 0xffffff, 0);
	DrawGraph(20, 335, g_Item[1], TRUE);
	DrawString(20, 385, "�_���[�W���󂯂Ă���Ƃ��Ɏ��Ƒϋv��", 0xffffff, 0);
	DrawString(20, 405, "�ϋv�������Ă��Ȃ�������R���������񕜂����B", 0xffffff, 0);
	DrawString(20, 450, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);
}
/***********************************************
 * �Q�[���G���h�`�揈��
 ***********************************************/
void DrawEnd(void)
{
	//�G���h�摜�\��
	DrawGraph(0, 0, g_EndImage, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//�^�C���̉��Z�������I���i3�b��j
	if (++g_WaitTime > 180)g_GameState = 99;
}
/***********************************************
 * �Q�[�����C��
 ***********************************************/
void GameMain(void)
{
	BackScrool();

	EnemyControl();

	ItemControl();

	PlayerControl();
	////�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	//if (g_KeyFlg & PAD_INPUT_M)g_GameState = 6;

	//SetFontSize(16);
	//DrawString(20, 20, "�Q�[�����C��", 0xffffff, 0);
	//DrawString(150, 450, "--- �X�y�[�X�L�[�������ăQ�[���I�[�o�[�� ---", 0xffffff, 0);
}
/***********************************************
 * �Q�[���I�[�o�[��ʕ`�揈��
 ***********************************************/
void DrawGameOver(void)
{
	EndBackScrool();
	g_Score = (g_Mileage / 10 * 10) + g_EnemyCount3 * 50 + g_EnemyCount2 * 100 + g_EnemyCount1 * 200;
	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
	if (g_KeyFlg & PAD_INPUT_M) {
		if (g_Ranking[RANKING_DATA].score >= g_Score) {
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
	DrawString(180, 200, "���s����	", 0x000000);
	DrawRotaGraph(230, 230, 0.3f, M_PI / 2, g_Teki[2], TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, g_Teki[0], TRUE, FALSE);
	DrawFormatString(260, 200, 0xFFFFFF, "%6d x  10 = %6d", g_Mileage / 10, g_Mileage / 10 * 10);
	DrawFormatString(260, 222, 0xFFFFFF, "%6d x  50 = %6d", g_EnemyCount3, g_EnemyCount3 * 50);
	DrawFormatString(260, 243, 0xFFFFFF, "%6d x  100= %6d", g_EnemyCount2, g_EnemyCount2 * 100);
	DrawFormatString(260, 264, 0xFFFFFF, "%6d x  200= %6d", g_EnemyCount1, g_EnemyCount1 * 200);
	DrawString(310, 290, "�X�R�A", 0x000000);
	DrawFormatString(260, 290, 0xFFFFFF, "             =%6d", g_Score);
	DrawFormatString(150, 450, 0xFFFFFF, "--- �X�y�[�X�L�[�������ă^�C�g���֖߂� ---", 0xffffff, 0);

}
/***********************************************
 * �摜�Ǎ���
 ***********************************************/
int LoadImages()
{
	//�^�C�g��
	if ((g_TitleImage = LoadGraph("images/chapter5/images/Title.bmp")) == -1)return -1;
	//���j���[
	if ((g_Menu = LoadGraph("images/chapter5/images/menu.bmp")) == -1)return-1;
	if ((g_Cone = LoadGraph("images/chapter5/images/cone.bmp")) == -1)return-1;
	//�����L���O�摜�f�[�^�̓ǂݍ���
	if ((g_RankingImage = LoadGraph("images/chapter5/images/Ranking.bmp")) == -1)return-1;
	//�A�C�e��
	if ((g_Item[0] = LoadGraph("images/chapter5/images/gasoline.bmp")) == -1)return-1;
	if ((g_Item[1] = LoadGraph("images/chapter5/images/supana.bmp")) == -1)return-1;
	//�G���f�B���O
	if ((g_EndImage = LoadGraph("images/chapter5/images/End.bmp")) == -1)return-1;
	//�G
	if (LoadDivGraph("images/chapter5/images/Car.bmp", 3, 3, 1, 63, 120, g_Teki) == -1)return-1;
	if ((g_Teki[3] = LoadGraph("images/chapter5/images/gentuki.bmp")) == -1)return-1;
	//�X�e�[�W�w�i
	if ((g_StageImage = LoadGraph("images/chapter5/images/back.bmp")) == -1)return-1;
	//�v���C���[
	if ((g_Car = LoadGraph("images/chapter5/images/car1pol.bmp")) == -1)return-1;
	if ((g_Barrier = LoadGraph("images/chapter5/images/barrier.png")) == -1)return-1;
	return 0;
}
/***********************************************
 * �w�i�X�N���[������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void BackScrool() {
	g_Mileage += g_player.speed;
	//�X�e�[�W�摜�\��
	//�`��\�G���A��ݒ�
	SetDrawArea(0, 0, 500, 480);
	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
	//�G���A��߂�
	SetDrawArea(0, 0, 640, 480);
	//�X�R�A�ȂǕ\���̈�
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
}
/***********************************************
 * �w�i�X�N���[������(�Q�[���I�[�o��)
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void EndBackScrool() {
	g_Mileage1 += g_player.speed;
	//�X�e�[�W�摜�\��
	//�`��\�G���A��ݒ�
	SetDrawArea(0, 0, 500, 480);
	DrawGraph(0, g_Mileage1 % 480 - 480, g_StageImage, FALSE);
	DrawGraph(0, g_Mileage1 % 480, g_StageImage, FALSE);
	//�G���A��߂�
	SetDrawArea(0, 0, 640, 480);
	//�X�R�A�ȂǕ\���̈�
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
}
/***********************************************
 * �v���C���[�̈ړ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void PlayerControl() {
	//�R���̏���
	g_player.fuel -= g_player.speed;
	//�Q�[���I�[�o�[������
	if (g_player.fuel <= 0)g_GameState = 6;
	//�y�L�[�ŉ���
	if (g_KeyFlg & PAD_INPUT_A && g_player.speed < 10)g_player.speed += 1;
	//�]�L�[�Ō���
	if (g_KeyFlg & PAD_INPUT_B && g_player.speed > 1)g_player.speed -= 1;

	//�㉺���E�ړ�
	if (g_player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_UP)g_player.y -= g_player.speed;
		if (g_NowKey & PAD_INPUT_DOWN)g_player.y += g_player.speed;
		if (g_NowKey & PAD_INPUT_LEFT)g_player.x -= g_player.speed;
		if (g_NowKey & PAD_INPUT_RIGHT)g_player.x += g_player.speed;
	}
	//�摜���͂ݏo���Ȃ��悤�ɂ���
	if (g_player.x < 32)g_player.x = 32;
	if (g_player.x > SCREEN_WIDTH - 180)g_player.x = SCREEN_WIDTH - 180;
	if (g_player.y < 60)g_player.y = 60;
	if (g_player.y > SCREEN_HEIGHT - 60)g_player.y = SCREEN_HEIGHT - 180;

	//�v���C���[�̕\��
	if (g_player.flg == TRUE) {
		if (g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, -M_PI / 18, g_Car, TRUE, FALSE);
		}
		else if (g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);
		}
		else {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Car, TRUE, FALSE);
		}
		if (g_KeyFlg & PAD_INPUT_C && g_player.bari > 0 && g_player.baricnt <= 0) {
			g_player.bari--;
			g_player.baricnt = 1000;
		}
		if (g_player.baricnt > 0) {
			g_player.baricnt -= g_player.speed;
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Barrier, TRUE, FALSE);
		}
		else {
			g_player.baricnt = 0;
		}
	}
	else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 8 * (++g_player.count / 5), g_Car, TRUE, FALSE);
		if (g_player.count >= 80)g_player.flg = TRUE;
	}
	//�G���悯������\��
	SetFontSize(16);
	DrawFormatString(510, 20, 0x000000, "�n�C�X�R�A");
	DrawFormatString(560, 40, 0xFFFFFF, "%08d", g_Ranking[0].score);
	DrawFormatString(510, 80, 0x000000, "��������");
	DrawRotaGraph(523, 120, 0.3f, 0, g_Teki[0], TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Teki[2], TRUE, FALSE);

	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
	DrawFormatString(560, 140, 0xFFFFFF, "%03d", g_EnemyCount2);
	DrawFormatString(610, 140, 0xFFFFFF, "%03d", g_EnemyCount3);
	DrawFormatString(510, 200, 0x000000, "���s����");
	DrawFormatString(555, 220, 0xFFFFFF, "%08d", g_Mileage / 10);
	DrawFormatString(510, 240, 0x000000, "�X�s�[�h");
	DrawFormatString(555, 260, 0xFFFFFF, "%08d", g_player.speed);

	//�o���A�̕\��
	for (int i = 0; i < g_player.bari; i++) {
		DrawRotaGraph(520 + i * 25, 340, 0.2f, 0, g_Barrier, TRUE, FALSE);
	}
	//�R���Q�[�W�̕\��
	int F_X = 510; int F_Y = 390; int F_W = 100; int F_H = 20;
	DrawString(F_X, F_Y, "FUEL METER", 0x000000, 0);
	//�����̃Q�[�W
	DrawBox(F_X, F_Y + 20, F_X + (int)(g_player.fuel * F_W / PLAYER_FUEL), F_Y + 20 + F_H, 0x0066cc, TRUE);
	//�O���̃Q�[�W�g
	DrawBox(F_X, F_Y + 20, F_X + F_W, F_Y + 20 + F_H, 0x000000, FALSE);
	//�̗̓Q�[�W
	int X = 510; int Y = 430; int W = 100; int H = 20;
	DrawString(X, Y, "PLAYER HP", 0x000000, 0);
	//�����̃Q�[�W
	DrawBox(X, Y + 20, X + (int)(g_player.hp * W / PLAYER_HP), Y + 20 + H, 0xff0000, TRUE);
	//�O���̃Q�[�W�g
	DrawBox(X, Y + 20, X + W, Y + 20 + H, 0x000000, FALSE);
}
/***********************************************
 * �G�l�~�[�̈ړ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void EnemyControl()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {
			//�G�̕\��
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);
			if (g_player.flg == FALSE)continue;
			if (g_enemy[i].type == 3) {
				g_enemy[i].angle += 4;
				g_enemy[i].x = (sin(g_enemy[i].angle * (DX_PI / 180)) * 30) + g_enemy[i].first_x;
			}
			//�܂��������Ɉړ�
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;
			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
			//�G�@��ǂ��z������J�E���g����
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {
				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0)g_EnemyCount1++;
				if (g_enemy[i].type == 1)g_EnemyCount2++;
				if (g_enemy[i].type == 2)g_EnemyCount3++;
			}
			//�����蔻��
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE && g_player.baricnt <= 0) {
				g_player.flg = FALSE;
				g_player.speed = PLAYER_SPEED;
				g_player.count = 0;
				g_player.hp -= 100;
				g_enemy[i].flg = FALSE;
				if (g_player.hp <= 0)g_GameState = 6;
			}
		}
	}
	//���s�������ƂɓG�o���p�^�[���𐧌䂷��
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}
/***********************************************
 * �G�@�̐���
 * ���@���F�Ȃ�
 * �߂�l�FTRUE:���� FALSE:���s
 ***********************************************/
int CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(3);
			g_enemy[i].img = g_Teki[g_enemy[i].type];
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].first_x = g_enemy[i].x;
			g_enemy[i].speed = g_enemy[i].type * 2;
			//����
			return TRUE;
		}
	}
	return FALSE;
}
/***********************************************
 * ���@�ƓG�@�̓����蔻��(�l�p)
 * ���@���FPLAYER�|�C���^
 * �߂�l�FTRUE:������ FALSE:�Ȃ�
 ***********************************************/
int HitBoxPlayer(PLAYER* p, ENEMY* e) {
	//x,y�͒��S���W�Ƃ���
	int sx1 = p->x - (p->w / 2);
	int sy1 = p->y - (p->h / 2);
	int sx2 = sx1 + p->w - 7;
	int sy2 = sy1 + p->h - 13;

	int dx1 = e->x - (e->w / 2);
	int dy1 = e->y - (e->h / 2);
	int dx2 = dx1 + e->w - 7;
	int dy2 = dy1 + e->h - 13;

	//�Z�`���d�Ȃ��Ă���Γ�����
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;
	}
	return FALSE;
}
/***********************************************
 * �A�C�e������
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void ItemControl() {
	for (int i = 0; i < ITEM_MAX; i++) {
		if (g_item[i].flg == TRUE) {
			//�A�C�e���̕\��
			DrawRotaGraph(g_item[i].x, g_item[i].y, 1.0f, 0, g_item[i].img, TRUE);
			if (g_player.flg == FALSE)continue;
			//�܂��������Ɉړ�
			g_item[i].y += g_item[i].speed + g_player.speed - PLAYER_SPEED;
			//��ʂ��͂ݏo���������
			if (g_item[i].y > SCREEN_HEIGHT)g_item[i].flg = FALSE;
			//�����蔻��
			if (HitBoxPlayer(&g_player, &g_item[i]) == TRUE) {
				g_item[i].flg = FALSE;
				if (g_item[i].type == 0)g_player.fuel += g_item[i].point;
				if (g_item[i].type == 1) {
					g_player.hp += g_item[i].point;
					if (g_player.hp > PLAYER_HP)g_player.hp = PLAYER_HP;
				}
			}
		}
	}
	//���s�������ƂɓG�o���p�^�[���𐧌䂷��
	if (g_Mileage / 10 % 500 == 0) {
		CreateItem();
	}
}
/***********************************************
 * �A�C�e������
 * ���@���F�Ȃ�
 * �߂�l�FTRUE:����FALSE:���s
 ***********************************************/
int CreateItem()
{
	for (int i = 0; i < ITEM_MAX; i++) {
		if (g_item[i].flg == FALSE) {
			g_item[i] = g_item00;
			g_item[i].type = GetRand(1);
			g_item[i].img = g_Item[g_item[i].type];
			g_item[i].x = GetRand(4) * 105 + 40;
			g_item[i].speed = 1 + g_item[i].type * 3;
			if (g_item[i].type == 0)g_item[i].point = 500;
			if (g_item[i].type == 1)g_item[i].point = 50;

			//����
			return TRUE;
		}
	}
	//���s
	return FALSE;
}