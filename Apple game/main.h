#pragma once

class AppleGame {
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
public:
	int getNowKey();
	int getg_Player();
	int getg_PlayerRight(int b);
	int getg_PlayerLeft(int a);
	int getSCREEN_WIDTH();
	int getSCREEN_HEIGHT();
};

extern AppleGame applegame;
