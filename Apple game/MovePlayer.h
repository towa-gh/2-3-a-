#pragma once
#include"BaseAP.h"
class MovePlayer : public BasePlayer {

private:
	////���@�̏����l
	int saigo;
public:
	MovePlayer();
	void getPlayer();
	void PlayerControl(int a, int b);
};

extern MovePlayer moveplayer;