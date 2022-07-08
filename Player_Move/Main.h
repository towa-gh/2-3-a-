#pragma once

class MovePlayer {

private:

	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;

	int g_Player, g_PlayerRight, g_PlayerLeft;          //ƒLƒƒƒ‰‰æ‘œ•Ï”

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
