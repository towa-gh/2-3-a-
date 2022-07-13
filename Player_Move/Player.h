#pragma once

class Player {

private:


	int saigo;
	
	int kansei;

	//int playerX;

	//int playerY;


	//自機の構造体
	struct PLAYER {

		int flg;          //使用フラグ
		int x, y;          //座標ｘ.ｙ
		int speed;          //移動速度
	};

	//自機
	struct PLAYER g_player;

public:

	//Player();

	void getPlayer();

	void PlayerControl(int L,int R);

	void getsaigo();

};

extern Player player;