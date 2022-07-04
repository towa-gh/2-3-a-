#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include"ball.h"
#include "Bar.h"
#include "common.h"

#define HEIGHT 10
#define WIDTH 16

extern int g_Score;
extern int g_GameState;
// ランキングデータ（構造体）
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
extern RankingData g_Ranking[10];

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
int CheckBlock(void);

Ball::Ball() {
     g_BallX=0,g_BallY=0;  
	 g_MoveX=0, g_MoveY=0;   
     radius=4;             
	 g_BallAngle=0;      
	 g_RestBall=0;   
	 g_BallFlg=0;  
     g_Speed=0;
}

/***********************************************
 * ボールの描画処理
 ***********************************************/
void Ball::DrawBall(void) {
	DrawCircle(g_BallX, g_BallY, radius, 0xFFD700, TRUE);
}
/***********************************************
 * ボールの移動処理
 ***********************************************/
void Ball::MoveBall(void) {
	if (((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) && g_BallFlg == 2) {
		g_BallFlg = 0;
		//スピードとアングルによる移動量計算
		g_Speed = 4;
		g_BallAngle = 0.625f;
		ChangeAngle();
	}

	//ボールの移動
	g_BallX += g_MoveX;
	g_BallY += g_MoveY;
	if (g_BallY > 480 + radius) {
		g_BallFlg = 2;//ボールスタート処理
		if (--g_RestBall < 0) {
			if (g_Score >= g_Ranking[9].score) {
				g_GameState = 7;//ランキング入力処理
			}
			else {
				g_GameState = 5;//ゲームオーバー処理へ
			}
		}
	}

	if (g_BallFlg != 2) {
		g_BallX += g_MoveX;
		g_BallY += g_MoveY;
	}
	else {
		g_BallX = bar.getX() + 30;
		g_BallY = bar.getY() - 6;
	}

	//壁・天井での反射
	if (g_BallX < radius || g_BallX > 640 - radius) {  //横の壁
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
	//上の壁
	if (g_BallY < radius) {
		g_BallAngle = (1 - g_BallAngle);
		ChangeAngle();
	}
}

/***********************************************
 * 角度変更処理
 ***********************************************/
void Ball::ChangeAngle(void) {
	int g_MoveX, g_MoveY;//ボールの移動量

	float rad = g_BallAngle * (float)M_PI * 2;
	g_MoveX = (int)(g_Speed * cosf(rad));
	g_MoveY = (int)(g_Speed * sinf(rad));
}
/***********************************************
 * ボールとバーの当たり判定
 ***********************************************/
void Ball::HitBar(void) {
	int mx0, mx1, my0, my1, sx0, sx1, sy0, sy1;

	//座標位置の事前計算
	mx0 = g_BallX - radius;
	mx1 = g_BallX + radius;
	my0 = g_BallY - radius;
	my1 = g_BallY + radius;
	sx0 = bar.getX();
	sx1 = sx0 + bar.getwidth();
	sy0 = bar.getY();
	sy1 = sy0 + bar.getheight();

	// ボールとバーの当たり判定
	if (sx0 <= mx1 && sx1 >= mx0 && sy0 <= my1 && sy1 >= my0) {
		if (g_BallFlg == 0) {
			g_BallAngle = (0.3f / 60) * (mx1 - sx0) + 0.6f;
			ChangeAngle();
			g_BallFlg = 1;
		}
	}
	else {
		if (g_BallFlg != 2)g_BallFlg = 0;
	}
}
/***********************************************
 * ボールとブロックの当たり判定
 ***********************************************/
void Ball::HitBlock(void) {
	//ボールとブロックの当たり判定
	int x = g_BallX / 40;
	int y = (g_BallY - 80) / 16;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && g_Block[y][x].flg != 0) {
		g_Block[y][x].flg = 0;

		g_BallAngle = (1 - g_BallAngle);
		g_Score += g_Block[y][x].score;

		ChangeAngle();
		/*if (CheckBlock() == 0) g_GameState = 6;*/
	}
}
