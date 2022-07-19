#pragma once
#include"BaseAP.h"
class MovePlayer : public BaseAP {
private:
	////©‹@‚Ì‰Šú’l
	int saigo;

	int playerX;

    float kasoku;

	float speed;

	float max;

	int moob;

	float moobX;

	int angle;

	float cosT[360];

public:
	MovePlayer();
	void PlayerControl(int a, int b);
};
extern MovePlayer moveplayer;