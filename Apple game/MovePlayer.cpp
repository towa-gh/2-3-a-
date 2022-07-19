#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
MovePlayer::MovePlayer() {

	saigo = 0;

	playerX = 320.f - 16; // X座標

	//playerY = 240.0f - 16; // Y座標

	kasoku = 0.43f; // 加速

	//speed = 0;  // 速度

	moobX = 0.0f; // 移動量	  

	moob; // 移動範囲

	angle = 0;  // 範囲

	cosT[360];  // 円範囲
}
void MovePlayer::PlayerControl(int a, int b)
{

	//移動範囲
	for (moob = 0; moob < 360; moob++) {

		//円周率
		cosT[moob] = (float)cos(moob * M_PI / 180);  //３６０度から１８０度の間の移動変更
	}

	angle = -1; //とりあえず角度を-1にしておく


	//左右移動
	if (p_flg == TRUE) {


		//左移動
		if (applegame.getNowKey() & PAD_INPUT_LEFT) angle = 180;


		//右移動
		if (applegame.getNowKey() & PAD_INPUT_RIGHT) angle = 0;

		//移動判断 angleの値が変わっていたら移動量を変更する
		if (angle != -1) {

			moobX += cosT[angle] * kasoku;

		}
		else /*if (angle == -1)*/ {   //angleの値が変わっていたら移動量を変更する

			moobX -= cosT[angle - 1] * kasoku;


		}

		p_x += moobX;



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
	if (p_x < 0)  p_x = 0;
	if (p_x > applegame.getSCREEN_WIDTH() - 90)  p_x = applegame.getSCREEN_WIDTH() - 90;
}