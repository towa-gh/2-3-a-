#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"MovePlayer.h"
#include"Main.h"

MovePlayer moveplayer;
void MovePlayer::PlayerInit() {
	player.flg = TRUE;
	player.x = 320;
	player.y = 380;
	player.w = 60;
	player.h = 100;
	player.angle = 0.0;
	player.count = 0;
	player.speed = 5;
}
MovePlayer::MovePlayer() {
	PlayerInit();
	saigo = 0;

	//kasoku = 0.43f; // ‰Á‘¬

	////speed = 0;  // ‘¬“x

	//moobX = 0.0f; // ˆÚ“®—Ê	  

	//angle = 0;  // ”ÍˆÍ

	//cosT[360] = 0;  // ‰~”ÍˆÍ
}

void MovePlayer::PlayerControl(int a, int b)
{
	//DrawGraph(player.x, player.y, a, TRUE);

	//ˆÚ“®”ÍˆÍ
	//for (moob = 0; moob < 360; moob++) {
	//	//‰~Žü—¦
	//	cosT[moob] = (float)cos(moob * M_PI / 180);  //‚R‚U‚O“x‚©‚ç‚P‚W‚O“x‚ÌŠÔ‚ÌˆÚ“®•ÏX
	//}

	//angle = -1; //‚Æ‚è‚ ‚¦‚¸Šp“x‚ð-1‚É‚µ‚Ä‚¨‚­

	//¶‰EˆÚ“®
	if (player.flg == TRUE) {
		saigo = a;
		//¶ˆÚ“®
		if (applegame.getNowKey() & PAD_INPUT_LEFT) {
			//angle = 180;
			saigo = b;
			DrawGraph(player.x, player.y, saigo, TRUE);
			player.x -= player.speed;
		}
		//‰EˆÚ“®
		if (applegame.getNowKey() & PAD_INPUT_RIGHT) {
			//angle = 0;
			saigo = a;
			DrawGraph(player.x, player.y, saigo, TRUE);
			player.x += player.speed;
		}
		else
			DrawGraph(player.x, player.y, saigo, TRUE);
	}
	//	if (angle != -1) {//ˆÚ“®”»’f angle‚Ì’l‚ª•Ï‚í‚Á‚Ä‚¢‚½‚çˆÚ“®—Ê‚ð•ÏX‚·‚é
	//		moobX += cosT[angle + 1] * kasoku;
	//	}
	//	if (angle == -1) {   //angle‚Ì’l‚ª•Ï‚í‚Á‚Ä‚¢‚½‚çˆÚ“®—Ê‚ð•ÏX‚·‚é
	//		moobX -= cosT[angle - 1] * kasoku;
	//	}
	//	player.x += moobX;
	//}

	//ƒvƒŒƒCƒ„[‚Ì•\Ž¦
	//¶‰EˆÚ“®

	//‰æ–Ê‚ð‚Í‚Ýo‚³‚È‚¢‚æ‚¤‚É‚·‚é
	if (player.x < -30)  player.x = -30;
	if (player.x > applegame.getSCREEN_WIDTH() - 90)  player.x = applegame.getSCREEN_WIDTH() - 90;
}