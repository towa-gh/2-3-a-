#pragma once

struct Player {
	int flg;//�g�p�t���O
	int x, y;//���Wx,y
	int w, h;//��w ����h
	double angle;//�@�̂̌���
	int count;//�^�C�~���O�p
	int speed;//�ړ����x
};
class MovePlayer{
private:
	////���@�̏����l
	int saigo;
	struct Player player;
 //   float kasoku;
	//float max;
	//int moob;
	//float moobX;
	//int angle;
	//float cosT[360];
public:
	MovePlayer();
	void PlayerInit();
	void PlayerControl(int a, int b);
	Player getPlayer() {
		return player;
	}
};
extern MovePlayer moveplayer;