#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"MovePlayer.h"

MovePlayer moveplayer;

///****************************************************************************************************************
//***
//***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�萔�̐錾
//***
//*****************************************************************************************************************/
//

int MovePlayer::getSCREEN_HEIGHT() {

	return SCREEN_HEIGHT;
}

int MovePlayer::getSCREEN_WIDTH() {

	return SCREEN_WIDTH;
}



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

int g_Player, g_PlayerRight, g_PlayerLeft;          //�L�����摜�ϐ�

int playerX;

int playerY;

int MovePlayer::getNowKey() {

	return  g_NowKey;

}


/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�֐��̃v���g�^�C�v�錾
***
*****************************************************************************************************************/
void GameInit(void);           //�Q�[������������
void GameMain(void);           //�Q�[�����C������
//void GamePlayer(void);


int LoadImages();              //�摜�ǂݍ���

/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�v���O�����̊J�n
***
*****************************************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// �^�C�g���ݒ�
	SetMainWindowText("�����S���Ƃ�");

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
			GameInit();		//�Q�[����������
			break;

		//case 1:
		//	player.getPlayer();		//�Q�[����������
		//	break;

		case 2:
			GameMain();     //�Q�[�����C������
			break;

		//case 3:
			//player.PlayerControl();
			//break;

		}

		ScreenFlip();			// ����ʂ̓��e��\��ʂɔ��f

	}

	DxLib_End();	// DX���C�u�����g�p�̏I������

	return 0;	// �\�t�g�̏I��
}


///****************************************************************************************************************
//***
//***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[����������
//***
//*****************************************************************************************************************/
void GameInit(void)
{
	

	//�v���C���[�̏����ݒ�
	
	player.getPlayer();
	

	//�Q�[�����C��������
	g_GameState = 2;



}



/****************************************************************************************************************
***
***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�Q�[�����C��
***
*****************************************************************************************************************/
void  GameMain(void)
{

	//DrawGraph(player.DrawPlayerLeft(), 20, g_PlayerRight, TRUE);
	//DrawGraph(playerX, playerY, g_PlayerLeft, TRUE);
	
	player.PlayerControl(g_PlayerLeft, g_PlayerRight);

	//DrawGraph(300, 300, g_PlayerLeft, TRUE);

	//if (moveplayer.getNowKey() & PAD_INPUT_RIGHT) {


		/*int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);*/

		/*DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);*/

		//DrawRotaGraph(player.getPlayerX(), player.getPlayerY(), 1.0f, M_PI / 20, g_PlayerLeft, TRUE, FALSE);
		//player.getPlayerX() += 10;



	//}

	SetFontSize(16);
	DrawString(20, 20, "GAME MEIN", 0xffffff, 0);
	
}

MovePlayer::MovePlayer(){
	g_Player = 0;
	g_PlayerRight = 0;
	g_PlayerLeft = 0;
}

int MovePlayer::getg_Player() {

	return g_Player;
}

int MovePlayer::getg_PlayerRight(int b) {

	return b;
}

int MovePlayer::getg_PlayerLeft(int a) {
	return a;
}

//int MovePlayer::getPlayerX() {
//
//	playerX = 300;
//	return 0;
//}
//
//int MovePlayer::getPlayerY() {
//
//	playerY = 400;
//	return 0;
//}


///****************************************************************************************************************
//***
//***�@�@�@�@�@�@�@�@�@�@�@�@�@�@�摜�ǂݍ���
//***
//*****************************************************************************************************************/
int LoadImages()
{


	//�v���C���[
	//if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	//if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.png")) == -1)return -1;
	//if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	g_PlayerRight = LoadGraph("images/Chapter5/Right.bmp");
	g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp");

	return 0;

}
