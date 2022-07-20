#pragma once
#include"MoveApple.h"
#include"MovePlayer.h"
class HitBox{

public:
	int HitBoxPlayer(Player* p, Apple* a);

};
extern HitBox hitbox;