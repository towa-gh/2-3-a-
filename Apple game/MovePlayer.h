#pragma once
#include"BaseAP.h"
class MovePlayer : public BaseAP {
private:
	////���@�̏����l
	int saigo;
public:
	MovePlayer();
	void PlayerControl(int a, int b);
};
extern MovePlayer moveplayer;