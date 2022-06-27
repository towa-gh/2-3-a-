#pragma once

class GameM {
private:
	
	int g_PosY;					// スクロール時のＹ座標
	int g_OldKey;				// 前回の入力キー
	int g_NowKey;				// 今回の入力キー
	int g_GameState;
	int g_MenuNumber;		// メニューカーソル位置
	int g_MenuY;				// メニューカーソルのＹ座標
	int g_Stage;
	

public:

	GameM();

	

	void GameMain();

};

extern GameM gameM;
