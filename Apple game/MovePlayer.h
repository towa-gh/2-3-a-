#pragma once

struct Player {
	int flg;//使用フラグ
	int x, y;//座標x,y
	int w, h;//幅w 高さh
	double angle;//機体の向き
	int count;//タイミング用
	int speed;//移動速度
};
class MovePlayer{
private:
	////自機の初期値
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