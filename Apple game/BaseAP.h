#pragma once
#include"DxLib.h"
class BasePlayer {
private:
	const int PLAYER_POS_X = 320;
	const int PLAYER_POS_Y = 380;
	const int PLAYER_WIDTH = 63;
	const int PLAYER_HEIGHT = 120;
	const int PLAYER_SPEED = 5;
	struct Player {
		int flg;//使用フラグ
		int x, y;//座標x,y
		int w, h;//幅w 高さh
		double angle;//機体の向き
		int count;//タイミング用
		int speed;//移動速度
	};
public:
	struct Player g_player;
};
class BaseApple {
private:
	struct Apple{
		int flg;//使用タイミング
		int type;//タイプ
		int img;//画像
		int x, y, w, h;//座標x,y 幅w　高さh
		int speed;//移動速度
		int point;//スコア加算
	};
	static const int APPLE_MAX = 10;
public:
	const int g_Apple[APPLE_MAX];
	struct Apple g_Apple00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
	struct Apple g_AppleCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };
};



