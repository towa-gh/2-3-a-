#pragma once

class AppleGame {
private:
	const int SCREEN_WIDTH = 640;
	const int SCREEN_HEIGHT = 480;
public:
	int getg_Appleimage();
	int getMileage();
	int getNowKey();
	int getg_PlayerRight(int b);
	int getg_PlayerLeft(int a);
	int getSCREEN_WIDTH();
	int getSCREEN_HEIGHT();
};

extern AppleGame applegame;
