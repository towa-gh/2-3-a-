#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"MovePlayer.h"




////自機の初期値
const int PLAYER_POS_X = moveplayer.getSCREEN_WIDTH() / 2;
const int PLAYER_POS_Y = moveplayer.getSCREEN_HEIGHT() - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;

Player player;


//Player Plyaer() {
//
//	int playerX = 300;
//
//	int playerY = 400;
//
//}



void Player::PlayerControl(int L, int R)
{

	//DrawGraph(g_player.x, g_player.y, saigo, TRUE);
	
	//プレイヤーの表示
	//上下左右移動
	if (g_player.flg == TRUE) {

		DrawRotaGraph(g_player.x, g_player.y, 1.0f,0, saigo, TRUE, FALSE);

		if (moveplayer.getNowKey() & PAD_INPUT_RIGHT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, R, TRUE, FALSE);
			g_player.x += g_player.speed;

			saigo = R;

		}



		 if (moveplayer.getNowKey() & PAD_INPUT_LEFT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / -20, L, TRUE, FALSE);
			g_player.x -= g_player.speed;

			saigo = L;

		}




	}

	//画面をはみ出さないようにする
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > moveplayer.getSCREEN_WIDTH() - 50)  g_player.x = moveplayer.getSCREEN_WIDTH() - 50;


}

void Player::getPlayer() {

	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = 380; //PLAYER_POS_Y;
	g_player.speed = PLAYER_SPEED;
}

