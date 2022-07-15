#pragma once
#include"DxLib.h"
class BaseAP {
private:

public:
	const int PLAYER_POS_X = 320;
	const int PLAYER_POS_Y = 380;
	const int PLAYER_WIDTH = 63;
	const int PLAYER_HEIGHT = 120;
	const int PLAYER_SPEED = 5;
	int p_flg;//使用フラグ
	int p_x, p_y;//座標x,y
	int p_w, p_h;//幅w 高さh
	double p_angle;//機体の向き
	int p_count;//タイミング用
	int p_speed;//移動速度
	BaseAP();
	void PlayerInit() {
		p_flg = TRUE;
		p_x = PLAYER_POS_X;
		p_y = PLAYER_POS_Y;
		p_w = PLAYER_WIDTH;
		p_h = PLAYER_HEIGHT;
		p_angle = 0.0;
		p_count = 0;
		p_speed = PLAYER_SPEED;
	}
	struct Apple {
		int flg;//使用タイミング
		int type;//タイプ
		int img;//画像
		int x, y, w, h;//座標x,y 幅w　高さh
		int speed;//移動速度
		int point;//スコア加算
	};
	int APPLE_MAX = 10;
	static Apple g_Apple[10];
	struct Apple g_Apple00 { TRUE, 0, 0, 0, -50, 63, 120, 0, 1 };
	struct Apple g_AppleCn { TRUE, 4, 0, 0, -50, 18, 18, 0, 1 };

	void AppleInit() {
		for (int i = 0; i < APPLE_MAX; i++) {
			g_Apple[i].flg = FALSE;
		}
	}
};

extern BaseAP baseap;