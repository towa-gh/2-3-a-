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
const int ENEMY_MAX = 10;
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
int g_WaitTime = 0;			//�҂�����
int g_EndImage;
int g_Mileage;				//���s����
int g_StageImage;
int g_Mileage1;
int StartTime;
//�G�L�����J�E���g
int g_EnemyCount1;
int g_Teki;
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
struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,63,0,1 };
struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };
/***********************************************
 * �֐��̃v���g�^�C�v�錾
 ***********************************************/
void GameInit(void);		//�Q�[������������
void GameMain(void);		//�Q�[�����C������
int LoadImages();			//�摜�ǂݍ���
void PlayerControl();		//���@����
void EnemyControl();		//�G�@����
int CreateEnemy();			//�G�@��������
int HitBoxPlayer(PLAYER* p, ENEMY* e);			//�����蔻��
 /***********************************************
  * �v���O�����̊J�n
  ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow)
{

	// �^�C�g���� Drive&Avoid �ɕύX
	SetMainWindowText("Apple Game");

	ChangeWindowMode(TRUE);		// �E�B���h�E���[�h�ŋN��

	if (DxLib_Init() == -1) return -1;	// DX���C�u�����̏���������

	SetDrawScreen(DX_SCREEN_BACK);	// �`����ʂ𗠂ɂ���

	if (LoadImages() == -1)return-1;


	// �Q�[�����[�v
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		// ���̓L�[�擾
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// ��ʂ̏�����

		switch (g_GameState) {
		case 0:
			GameInit();		//�Q�[����������
			break;
		case 1:
			GameMain();
			break;
		}
		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
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

	//�v���C���[�����ݒ�
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;

	//�G�l�~�[�̏�������
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}

	//�Q�[�����C��������
	g_GameState = 1;
}
/***********************************************
 * �Q�[�����C��
 ***********************************************/
void GameMain(void)
{
	EnemyControl();

	PlayerControl();
}
/***********************************************
 * �摜�Ǎ���
 ***********************************************/
int LoadImages()
{
	//�G
	if (g_Teki = LoadGraph("images/chapter5/images/apple.bmp") == -1)return-1;
	//�v���C���[
	if ((g_Car = LoadGraph("images/chapter5/images/Right.bmp")) == -1)return-1;
	return 0;
}
/***********************************************
 * �v���C���[�̈ړ�
 * ���@���F�Ȃ�
 * �߂�l�F�Ȃ�
 ***********************************************/
void PlayerControl() {
	////�Q�[���I�[�o�[������
	//if (g_player.fuel <= 0)g_GameState = 6;
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
	DrawRotaGraph(523, 120, 0.3f, 0, g_Teki, TRUE, FALSE);

	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
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

			//�܂��������Ɉړ�
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;
			//��ʂ��͂ݏo���������
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h)g_enemy[i].flg = FALSE;
			//�G�@��ǂ��z������J�E���g����
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {
				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0)g_EnemyCount1++;
			}
			//�����蔻��
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE) {
				g_player.flg = FALSE;
				g_player.speed = PLAYER_SPEED;
				g_player.count = 0;
				g_enemy[i].flg = FALSE;
			}
		}
	}
	//���s�������ƂɓG�o���p�^�[���𐧌䂷��
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}
/**********************************************
 * �G�@�̐���
 * ���@���F�Ȃ�
 * �߂�l�FTRUE:���� FALSE:���s
 ***********************************************/
int CreateEnemy() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {
			g_enemy[i] = g_enemy00;
			g_enemy[i].type = g_Teki;
			g_enemy[i].img = g_Teki;
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
