#pragma once

class Bar {
private :
	int g_BarX;
	int g_BarY;

	int height;//8
	int width;//60

public:
	Bar();//コンストラクト
	void DrawBar(void);//バーの描画
	void MoveBar(void);//バーの移動処理
	void Init();
	
	int getX();
	int getY();
	int getheight();
	int getwidth();
};
extern Bar bar;