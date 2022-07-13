#pragma once

class Bar {
private:
	int g_BarX;
	int g_BarY; //ƒo[‚ÌÀ•W
	int height;//8
	int width;//60

public:
	Bar();

	void MoveBar();
	void DrawBar();
	void Init();

	int getX();
	int getY();
	int getheight();
	int getwidth();

};

extern Bar bar;
