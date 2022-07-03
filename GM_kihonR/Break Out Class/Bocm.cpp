#include "DxLib.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Bar.h"
#include"Ball.h"
#include "Block.h"
#include "Ranking.h"
#include"GameM.h"

#define HEIGHT 10
#define WIDTH 16
#define STAGE 5
/***********************************************
 * 変数の宣言
 ***********************************************/

int	g_OldKey;				// 前回の入力キー
int	g_NowKey;				// 今回の入力キー
int	g_KeyFlg;				// 入力キー情報

int	g_MenuNumber = 0;		// メニューカーソル位置

int g_MenuY;				// メニューカーソルのＹ座標

int	g_TitleImage;			// 画像用変数
int	g_RankingImage;			// 画像用変数
int	g_EndImage;				// 画像用変数

int	g_WaitTime = 0;			// 待ち時間
int g_PosY;					// スクロール時のＹ座標


int	g_GameState = 0;		// ゲームステータス

int g_BlockImage[8]; //ブロック画像用変数

int g_BallFlg;

int g_Stage = 0; //ステージ用変数




/***********************************************
 * 関数のプロトタイプ宣言
 ***********************************************/
void DrawGameOver(void);
void DrawGameClear(void);

void DrawGameTitle(void);	//ゲームタイトル処理
void DrawEnd(void);			//ゲームエンド処理


/***********************************************
 * プログラムの開始
 ***********************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow)
{

	/*タイトルを test に変更*/
	SetMainWindowText("ブロック崩し");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	/*タイトル画像データの読み込み*/
	if ((g_TitleImage = LoadGraph("images/Chapter4/Title.bmp")) == -1) return -1;
	/*ランキング画像データの読み込み*/
	if ((g_RankingImage = LoadGraph("images/Chapter4/Ranking.bmp")) == -1) return -1;
	/*エンド画像データの読み込み*/
	if ((g_EndImage = LoadGraph("images/Chapter4/End.bmp")) == -1) return -1;
	/*ブロックデータの画像データ読み込み*/
	if (LoadDivGraph("images/Chapter4/Block.bmp", 8, 8, 1, 40, 8, g_BlockImage) == -1)return -1;

	if (ranking.ReadRanking() == -1)  return  -1;    //ランキングデータの読み込み

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	SetFontSize(20);		// 文字サイズを設定

	 /*ゲームループ*/
	while (ProcessMessage() == 0 && g_GameState != 99) {

		/* 入力キー取得*/
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//ゲームタイトル処理
			break;
		case 1:
			ball.GameInit();		//ゲーム初期処理
			break;
		case 2:
			ranking.DrawRanking();	//ランキング描画処理
			break;
		case 3:
			DrawEnd();		//エンド画面描画処理
			break;
		case 4:
			gameM.GameMain();		//ゲームメイン処理
			break;

			switch (g_GameState) {
			case 5:
				DrawGameOver(); //ゲームオーバー描画処理
				break;
			}
		case 6:
			DrawGameClear();		//ゲームクリア処理
			break;
		}
		switch (g_GameState) {
		case 7:
			ranking.InputRanking(); //ランキング入力処理
			break;
		}

		SetFontSize(48);
		DrawFormatString(100, 100, 0xffffff, "%d", g_BallFlg);
		DrawFormatString(100, 100, 0xffffff, "%d", g_GameState);
		ScreenFlip();			// 裏画面の内容を表画面に反映
	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}



/***********************************************
 * ゲームタイトル表示（メニュー画面）
 ***********************************************/
void DrawGameTitle(void)
{
	/*メニューカーソル移動処理*/
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++g_MenuNumber > 2) g_MenuNumber = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--g_MenuNumber < 0) g_MenuNumber = 2;
	}

	/*Ｚキーでメニュー選択*/
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = g_MenuNumber + 1;

	/*タイトル画像表示*/
	DrawGraph(0, 0, g_TitleImage, FALSE);

	/*メニューカーソル（三角形）の表示*/
	g_MenuY = g_MenuNumber * 52;
	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);

}


/***********************************************
 * ゲームクリア画面描画処理
 ***********************************************/
void DrawGameClear(void)
{
	int g_Stage = 0;

	/*スペースでNEXTステージへ*/
	if (g_KeyFlg & PAD_INPUT_M) {
		g_GameState = 4;
		if (++g_Stage > 4)g_Stage = 0;
		ball.InitBlock();
	}

	SetFontSize(48);
	DrawString(120, 200, "Congratulations", 0x7F00F0);

	/*文字の表示(点滅)*/
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "-- Press[SPACE] Key --", GetColor(255, 0, 0));
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}


/***********************************************
* ゲームオーバー画面描画処理
***********************************************/
void DrawGameOver(void){
	/*スペースキーでメニューに戻る*/
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 4;
	ball.InitBlock();

	SetFontSize(48);
	DrawString(200, 200, "Game Over", GetColor(255, 0, 0));

	/*文字表示の点滅*/
	if (++g_WaitTime < 30) {
		SetFontSize(24);
		DrawString(150, 450, "-- Press[SPACE] Key --", GetColor(255, 0, 0));
	}
	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}
}




/***********************************************
 * ゲームエンド描画処理（エンドロール）
 ***********************************************/
void DrawEnd(void)
{
	//エンド画像表示
	DrawGraph(0, 0, g_EndImage, FALSE);

	//エンディング表示
	if (++g_WaitTime < 600) g_PosY = 300 - g_WaitTime / 2;

	SetFontSize(24);
	DrawString(100, 170 + g_PosY, "タイトル　　　Game　Title", 0xFFFFFF);
	DrawString(100, 200 + g_PosY, "バージョン　　1.0", 0xFFFFFF);
	DrawString(100, 230 + g_PosY, "最終更新日　　201x年xx月xx日", 0xFFFFFF);
	DrawString(100, 260 + g_PosY, "制作者　　　　国際電子ビジネス専門学校", 0xFFFFFF);
	DrawString(100, 290 + g_PosY, "　　　　　　　ＸＸＸ　ＸＸ", 0xFFFFFF);
	DrawString(100, 310 + g_PosY, "素材利用", 0xFFFFFF);
	DrawString(100, 340 + g_PosY, "　BGM　　　 　ＸＸＸＸ", 0xFFFFFF);
	DrawString(100, 365 + g_PosY, "　SE　　　　　ＸＸＸＸＸＸＸＸ", 0xFFFFFF);

	//タイムの加算処理＆終了
	if (++g_WaitTime > 900) g_GameState = 99;
}



