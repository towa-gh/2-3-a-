#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"Bar.h"
#include "Ball.h"
#include "Block.h"
#include "Ranking.h"
#include "GameM.h"

#define HEIGHT 10
#define WIDTH 16
#define STAGE 5

extern int g_Score;
extern int g_GameState;

/*ランキングデータ（構造体）*/
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
extern  RankingData g_Ranking[10];

//<一部省略>
//ブロックデータ(構造体の定義)
struct ObjectBlock {
	int flg;
	int x, y;
	int w, h;
	int mx, my;
	int image;
	int score;
};

//ブロックデータの宣言
extern ObjectBlock g_Block[HEIGHT][WIDTH];

int CheckBlock();



Bar bar;
Ball ball;
Block block;
Ranking ranking;
GameM gameM;

Bar::Bar(){
	g_BarX = 0;
	g_BarY = 0;
	height = 8;
	width = 60;

}

Ball::Ball() {

	g_BallFlg = 0; //ボールの状態(0...移動中　1...バー接触)
	g_BallAngle = 0;//ボールの角度 
	g_BallX = 0;
	g_BallY = 0; //ボールの座標
	g_MoveX = 0;
	g_MoveY = 0;//ボールの移動量
	//g_MouseX = 0;
	//g_MouseY = 0; //マウスの座標
	g_RestBall = 0; //残りのボール数
	height = 8;
	width = 60;
	/*g_GameState = 0;*/
	radius = 4;
	g_Speed = 0;
	g_Score = 0;
	g_Stage = 0; //ステージ用変数
}

Block::Block() {

	g_BlockX = 0;
	g_BlockY = 0; //バーの座標
	height = 8;//8
	width = 60;//60
	g_BlockImage[8] = 0;//ブロック画像用変数
	g_Score = 0;	// スコア
	g_RestBall = 0;

}

Ranking::Ranking() {

	g_RankingImage = 0;	// 画像用変数
	g_GameState = 0;	// ゲームステータス
	g_KeyFlg = 0;				// 入力キー情報
	g_WaitTime = 0;			// 待ち時間
	g_Score = 0;
	
}

GameM::GameM(){
	
	g_PosY = 0;					// スクロール時のＹ座標
	g_OldKey = 0;				// 前回の入力キー
	g_NowKey = 0;				// 今回の入力キー

	g_MenuNumber = 0;		// メニューカーソル位置
	g_MenuY = 0;				// メニューカーソルのＹ座標

	g_GameState = 0;		// ゲームステータス

	g_Stage = 0;

}

int	g_BlockData[STAGE][HEIGHT][WIDTH] = {	// ブロック配列
	{	// 0ｽﾃｰｼﾞ
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 },
		{ 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 }
	},
	{	// 1ｽﾃｰｼﾞ
		{ 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 2 , 3 , 3 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 2 , 2 , 3 , 4 , 4 , 4 , 4 , 3 , 2 , 2 , 0 , 0 , 0 },
		{ 0 , 2 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 4 , 3 , 3 , 2 , 2 , 0 },
		{ 2 , 3 , 3 , 4 , 4 , 5 , 0 , 0 , 0 , 0 , 5 , 4 , 4 , 3 , 3 , 2 },
		{ 2 , 3 , 3 , 4 , 4 , 5 , 0 , 0 , 0 , 0 , 5 , 4 , 4 , 3 , 3 , 2 },
		{ 0 , 2 , 2 , 3 , 3 , 4 , 5 , 5 , 5 , 5 , 4 , 3 , 3 , 2 , 2 , 0 },
		{ 0 , 0 , 0 , 2 , 2 , 3 , 4 , 4 , 4 , 4 , 3 , 2 , 2 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 2 , 3 , 3 , 3 , 3 , 2 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 2 , 2 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{	// 2ｽﾃｰｼﾞ
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 },
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 },
		{ 0 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 0 },
		{ 0 , 0 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 6 , 0 , 0 },
		{ 0 , 0 , 0 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 5 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 4 , 4 , 4 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 4 , 4 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 0 , 0 , 0 , 0 , 0 , 0 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 }
	},
	{	// 3ｽﾃｰｼﾞ
		{ 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 0 , 0 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 0 , 0 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 0 , 0 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 },
		{ 0 , 1 , 1 , 2 , 2 , 3 , 3 , 4 , 4 , 5 , 5 , 6 , 6 , 7 , 7 , 0 }
	},
	{	// 4ｽﾃｰｼﾞ
		{ 7 , 1 , 0 , 0 , 1 , 7 , 3 , 3 , 3 , 0 , 7 , 0 , 4 , 4 , 0 , 7 },
		{ 7 , 1 , 0 , 1 , 1 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 4 , 4 , 4 , 7 },
		{ 7 , 1 , 1 , 1 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 4 , 7 },
		{ 7 , 1 , 1 , 0 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 0 , 0 , 0 , 7 , 3 , 3 , 3 , 0 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 1 , 0 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 0 , 7 },
		{ 7 , 1 , 1 , 1 , 0 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 0 , 0 , 4 , 7 },
		{ 7 , 1 , 0 , 1 , 1 , 7 , 3 , 0 , 0 , 3 , 7 , 4 , 4 , 4 , 4 , 7 },
		{ 7 , 1 , 0 , 0 , 1 , 7 , 3 , 3 , 3 , 0 , 7 , 0 , 4 , 4 , 0 , 7 },
		{ 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 , 7 }
	}
};

/***********************************************
 * バーの移動処理
 ***********************************************/
void Bar::MoveBar(void) {

	int g_MouseX, g_MouseY; //マウスの座標

	/*マウスから座標を読み取る*/
	GetMousePoint(&g_MouseX, &g_MouseY);

	g_BarX = g_MouseX;
	if (g_BarX < 0) {
		g_BarX = 0;
	}
	else if (g_BarX > 640 - width) {
		g_BarX = 580;
	}

}



/***********************************************
 * バーの描画処理
 ***********************************************/
void Bar::DrawBar(void) {
	/*バーの描画*/
	DrawBox(g_BarX, g_BarY, g_BarX + width, g_BarY + height, 0xFFD700, TRUE);
}

void Bar::Init(){
	g_BarX = 290;
	g_BarY = 440;
}

int Bar::getX(){
	return g_BarX;
}

int Bar::getY(){
	return g_BarY;
}

int Bar::getheight() {
	return height;
}

int Bar::getwidth() {
	return width;
}


/***********************************************
 * ゲーム初期処理
 ***********************************************/
void Ball::GameInit(void) {


	int g_GameState;

	bar.Init();
	/*g_BarX = 290;
	g_BarY = 440;*/
	g_GameState = 4; //ゲームメイン処理へ

	/*<一部省略>
ブロック配列の初期化*/
	ball.InitBlock();
	
}

void Ball::Init() {

	g_BallX = 320;
	g_BallY = 440 - 5;
	g_RestBall = 2; //残りのボールの設定
	InitBallFlg();
	
}

void Ball::InitBallFlg() {
	g_BallFlg = 2;
}

int Ball::getRestBall(){

	return g_RestBall;

}
/***********************************************
 * ブロック初期処理
 ***********************************************/
 void Ball::InitBlock(void)
 {

 	/*ブロック配列の初期化*/
 	for (int i = 0; i < HEIGHT; i++) {
 		for (int j = 0; j < WIDTH; j++) {
 			if (g_BlockData[g_Stage][i][j] != 0) {
 				g_Block[i][j].flg = 1;
 				g_Block[i][j].x = j * 40;
 				g_Block[i][j].y = i * 16 + 80;
 				g_Block[i][j].w = 40;
 				g_Block[i][j].h = 8;
 				g_Block[i][j].score = g_Block[i][j].image * 10;
 			}
 
 		}
 	}
 	/*ボールスタート状態*/
 	g_BallFlg = 2;
 }



int Ball::getX()
{
	return g_BallX;
}

int Ball::getY()
{
	return g_BallY;
}
/***********************************************
 * ボールの描画処理
 ***********************************************/
void Ball::DrawBall(void) {
	/*ボールの描画*/
	DrawCircle(g_BallX, g_BallY, 4, 0xFFD700, TRUE);
}



/***********************************************
* ボールの移動処理
/***********************************************/
void Ball::MoveBall(void) {


	/*マウス左クリックでゲームスタート*/
	if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && g_BallFlg == 2) {

		g_BallFlg = 0;
		/*スピードとアングルによる移動量計算*/
		g_Speed = 5;
		g_BallAngle = 0.625f;
		ball.ChangeAngle();
	}

	/*ボールの移動*/
	g_BallX += g_MoveX;
	g_BallY += g_MoveY;

	/*壁・天井での反射*/
	if (g_BallX < radius || g_BallX > 640 - radius) { //横の壁
		if (g_BallX < radius) {
			g_BallX = radius;
		}
		else {
			g_BallX = 640 - radius;
		}
		g_BallAngle = (1 - g_BallAngle) + 0.5f;
		if (g_BallAngle > 1)g_BallAngle -= 1.0f;
		ChangeAngle();
	}

	if (g_BallY < radius) {
		g_BallAngle = (1 - g_BallAngle); //上の壁
		ChangeAngle();
	}

	/*g_BarX = g_BallX;*/

	if (g_BallFlg != 2) {
		g_BallX += g_MoveX;
		g_BallY += g_MoveY;
	}
	else {
		g_BallX = bar.getX() + 30;
		g_BallY = bar.getY() - 6;
	}

	if (g_BallY > 480 + radius) {
		g_BallFlg = 2; //ボールスタート状態
		if (--g_RestBall < 0) {
			if (g_Score >= g_Ranking[9].score) {
				g_GameState = 7; //ランキング入力処理

			}
			else {
				g_GameState = 5; //ゲームオーバー処理

			}
		}
	}
	if (g_BallY > 480 + radius) {

		if (g_Score >= g_Ranking[9].score) {
			g_GameState = 7; //ランキング入力処理へ
		}
		else {
			g_GameState = 5; //ゲームオーバー処理へ
		}
	}
}

/***********************************************
 * ボールとブロックの当たり判定
 ***********************************************/
void Ball::HitBlock(void) {


	/*ボールとブロックの当たり判定*/
	int x = g_BallX / 40;
	int y = (g_BallY - 80) / 16;

	if (x >= 0 && x < width &&
		y >= 0 && y < height &&
		g_Block[y][x].flg != 0) {

		g_Block[y][x].flg = 0;
		g_Score += g_Block[y][x].score;

		g_BallAngle = (1 - g_BallAngle);
		ChangeAngle();
		if (CheckBlock() == 0) g_GameState = 6;
	}
}

/***********************************************
 * 角度変更処理
 ***********************************************/
void Ball::ChangeAngle(void)
{
	float rad = g_BallAngle * (float)M_PI * 2;
	g_MoveX = (int)(g_Speed * cosf(rad));
	g_MoveY = (int)(g_Speed * sinf(rad));
}

/***************************************/
/*ボールとバーの当たり判定
/**************************************/
void Ball::HitBar(void) {
	int  mx0, mx1, my0, my1, sx0, sx1, sy0, sy1;


	/*座標の事前計算*/
	mx0 = ball.getX() - radius;
	mx1 = ball.getY() + radius;
	my0 = ball.getX() - radius;
	my1 = ball.getY() + radius;
	sx0 = bar.getX();
	sx1 = sx0 + bar.getwidth();
	sy0 = bar.getY();
	sy1 = sy0 + bar.getheight();

	/*ボールとバーの当たり判定*/
	if (sx0 <= mx1 && sx1 >= mx0 &&
		sy0 <= my1 && sy1 >= my0) {

		if (g_BallFlg == 0) {

			g_BallAngle = (0.3f / 60) * (mx1 - sx0) + 0.6f;
			ChangeAngle();
			g_BallFlg = 1;
		}
	}
	else {
		//BallFlg = 0;
		if (g_BallFlg != 2)g_BallFlg = 0;
	}
}

/***********************************************
 * ブロックチェック処理
 ***********************************************/
int CheckBlock(void) {

	/*ブロックの配列の初期化*/
	for (int i = 0; i < HEIGHT;i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1)return -1;
		}
	}
	return 0;
}

///***********************************************
// * ブロック描画処理
// ***********************************************/
void Block::DrawBlock(void) {


	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (g_Block[i][j].flg == 1) {
				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
			}
		}
	}
}

/***********************************************
 * スコア描画処理
 ***********************************************/
void Block::DrawScore() {
	DrawFormatString(20, 20, 0xFFFFFF, "SCORE:%06d", g_Score);

	/*残りのボールの描画*/
	SetFontSize(10);
	DrawFormatString(600, 460, 0xFFD700, "●　x %d", g_RestBall);
}

int Block::getX()
{
	return g_BlockX;
}

int Block::getY()
{
	return g_BlockY;
}

int Block::getheight() {
	return height;
}

int Block::getwidth() {
	return width;
}



//***********************************************
//*ランキング描画処理
//*********************************************** /
void Ranking::DrawRanking(void)
{

	/*スペースキーでメニューに戻る*/
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	/*ランキング画像表示*/
	DrawGraph(0, 0, g_RankingImage, FALSE);

	/*ランキング一覧を表示*/
	SetFontSize(30);
	for (int i = 0; i < 10; i++) {
		DrawFormatString(80, 170 + i * 25, 0xFFFFFF, "%2d   %10s   %10d",
			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*文字の表示(点滅)*/
	if (++g_WaitTime < 30) {

		SetFontSize(24);
		DrawString(150, 450, "--  Press [SPACE] Key  --", 0xFF0000);
	}

	else if (g_WaitTime > 60) {
		g_WaitTime = 0;
	}

}

/***********************************************
 * ランキング入力処理
 ***********************************************/
void Ranking::InputRanking()
{
	
	/*ランキング画像表示*/
	DrawGraph(0, 0, g_RankingImage, FALSE);

	/*フォントサイズの設定*/
	SetFontSize(20);

	/*名前入力指示文字列の描画*/
	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);

	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);

	/*名前の入力*/
	DrawString(150, 310, "> ", 0xFFFFFF);

	DrawBox(160, 305, 300, 335, 0x000055, TRUE);

	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {

		g_Ranking[9].score = g_Score;	// ランキングデータの１０番目にスコアを登録
		SortRanking();		// ランキング並べ替え
		SaveRanking();		// ランキングデータの保存
		g_GameState = 2;		// ゲームモードの変更
	}

}

/***********************************************
 * ランキング並べ替え
 ***********************************************/
void Ranking::SortRanking()
{
	int i, j;
	RankingData work;

	/*選択法ソート*/
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	/*順位付け*/
	for (i = 0; i < 10; i++) {
		g_Ranking[i].no = 1;
	}
	/*得点が同じ場合は、同じ順位とする
	同順位があった場合の次の順位はデータ個数が加算された順位とする*/
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}

/***********************************************
 * ランキングデータの保存
 ***********************************************/
int Ranking::SaveRanking()
{
	FILE* fp;
#pragma warning(disable:4996)

	/*ファイルオープン*/
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "w")) == NULL) {
		/* エラー処理 */
		printf("Ranking Data Error\n");
		return -1;
	}

	/*ランキングデータ分配列データを書き込む*/
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*ファイルクローズ*/
	fclose(fp);

	return 0;
}

/*************************************
 * ランキングデータ読み込み
 *************************************/
int Ranking::ReadRanking()
{
	FILE* fp;
#pragma warning(disable:4996)

	/*ファイルオープン*/
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "r")) == NULL) {
		/*エラー処理*/
		printf("Ranking Data Error\n");
		return -1;
	}

	/*ランキングデータ配分列データを読み込む*/
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	/*ファイルクローズ*/
	fclose(fp);

	return 0;
}

/***********************************************
 * ゲームメイン
 ***********************************************/
void GameM::GameMain()
{
	bar.MoveBar();//バーの移動処理
	ball.MoveBall();//ボールの移動
	ball.HitBar();//ボールとバーの当たり判定
	ball.HitBlock(); //ボールとブロックの当たり判定
	ball.DrawBall(); //ボールの描画
	bar.DrawBar(); //バーの描画
	block.DrawBlock(); //ブロックを描画
	block.DrawScore(); //スコアを描画
}