#pragma once

class Block {
private:
	int g_BlockX;
	int g_BlockY; //バーの座標
	int height;//8
	int width;//60
	int g_BlockImage[8]; //ブロック画像用変数
	int	g_Score;			// スコア
	int g_RestBall;

public:
	Block();

	void DrawBlock();
	/*void Init();*/
	void DrawScore();

	int getX();
	int getY();
	int getheight();
	int getwidth();


};

extern Block block;
