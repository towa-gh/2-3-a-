#pragma once

class MovePlayer {

private:

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	int g_Player, g_PlayerRight, g_PlayerLeft;          //キャラ画像変数

public:

	MovePlayer();

	int getNowKey();

	int getg_Player();

	int getg_PlayerRight();

	int getg_PlayerLeft();

	int getSCREEN_WIDTH();

	int getSCREEN_HEIGHT();

};

extern MovePlayer moveplayer;
