#pragma once
#include"MovePlayer.h"
//#include"Fps.h"
struct Apple {
	int flg;//使用タイミング
	int type;//タイプ
	int img;//画像
	int x, y, w, h;//座標x,y 幅w　高さh
	int speed;//移動速度
	int point;//スコア加算
};
class MoveApple{
private:
	const static int APPLE_MAX = 10;
	struct Apple g_Apple[APPLE_MAX];
public:
	void AppleControl(Player player);
	void AppleInit();
	int CreateEnemy();
};
extern MoveApple moveapple;