#pragma once

class Block {
private:
		int x, y;
		int w, h;
		int image;
		int score;
		bool isShow;
		int g_BlockImage[8];
	
	//ブロックデータの宣言
	//struct ObjectBlock g_Block[HEIGHT][WIDTH];

public:
	void DrawBlock(void);   //描画処理
	void ChangeColor(int);     //色変更
	

};
