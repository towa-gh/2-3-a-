#pragma once
extern struct PBOX {
	float left, top, right, bottom;
};
extern struct ABOX {
	float left, top, right, bottom;
};
class Box {

public:
	bool CheckHit(const PBOX& player, const ABOX& apple);			//�����蔻��

};
extern Box box;