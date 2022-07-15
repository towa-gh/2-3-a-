#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
MovePlayer::MovePlayer() {
	saigo = 0;
}
void MovePlayer::PlayerControl(int a, int b)
{

	if (p_flg == TRUE) {
		if (applegame.getNowKey() & PAD_INPUT_RIGHT)p_x += p_speed;
		if (applegame.getNowKey() & PAD_INPUT_LEFT)p_x -= p_speed;
	}

	//プレイヤーの表示
	//左右移動
	if (p_flg == TRUE) {

		if (applegame.getNowKey() & PAD_INPUT_RIGHT) {
			saigo = a;
			DrawGraph(p_x, p_y, saigo, TRUE);
		}

		if (applegame.getNowKey() & PAD_INPUT_LEFT) {
			saigo = b;
			DrawGraph(p_x, p_y, saigo, TRUE);
		}
		else
			DrawGraph(p_x, p_y, saigo, TRUE);
	}
	//画面をはみ出さないようにする
	if (p_x < 32)  p_x = 32;
	if (p_x > applegame.getSCREEN_WIDTH() - 50)  p_x = applegame.getSCREEN_WIDTH() - 50;
}