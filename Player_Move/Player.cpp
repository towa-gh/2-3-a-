#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Player.h"
#include"Main.h"



////自機の初期値
const int PLAYER_POS_X = moveplayer.getSCREEN_WIDTH() / 2;
const int PLAYER_POS_Y = moveplayer.getSCREEN_HEIGHT() - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;

Player player;

//Main main;


void Player::PlayerControl()
{
	
	//Main main;

	 saigo = moveplayer.getg_PlayerLeft();

	/*int PlayerPojishonRihght= DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);*/
	/*int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);*/
	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, saigo, TRUE, FALSE);


	//プレイヤーの表示
	//上下左右移動
	if (g_player.flg == TRUE) {

		DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, saigo, TRUE, FALSE);

		if (moveplayer.getNowKey() & PAD_INPUT_RIGHT) {

			saigo = moveplayer.getg_PlayerRight();

			/*int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);*/

			/*DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, g_PlayerRight, TRUE, FALSE);*/

			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 20, saigo, TRUE, FALSE);
			g_player.x += g_player.speed;


			saigo = moveplayer.getg_PlayerRight();


		}




		if (moveplayer.getNowKey() & PAD_INPUT_LEFT) {

			saigo = moveplayer.getg_PlayerLeft();

			/*DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / -20, g_PlayerLeft, TRUE, FALSE);*/

			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / -20, saigo, TRUE, FALSE);
			g_player.x -= g_player.speed;


			saigo = moveplayer.getg_PlayerLeft();

		}




	}

	//画面をはみ出さないようにする
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > moveplayer.getSCREEN_WIDTH() - 50)  g_player.x = moveplayer.getSCREEN_WIDTH() - 50;




}

void Player::getPlayer() {

	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.speed = PLAYER_SPEED;
}

