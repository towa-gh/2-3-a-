#pragma once
#include"BaseAP.h"
class MovePlayer : public BaseAP {
private:
	////自機の初期値
	int saigo;
public:
	MovePlayer();
	void PlayerControl(int a, int b);
};
extern MovePlayer moveplayer;