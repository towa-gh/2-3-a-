
#include "DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>
#define RANKING_DATA 5
#include "AppleMove.h"
#include"main.h"

 Apple apple;

/***********************************************
 *変数宣言
 ***********************************************/

int g_OldKey;//前回の入力キー
int g_NowKey;//今回の入力キー
int g_KeyFlg;//入力キー情報

int g_GameState = 0;//ゲームモード

int g_TitleImage;//画像用変数
int g_Menu, g_Cone;//メニュー画像変数

int g_Score = 0;//スコア
int g_RankingImage;//画像用変数

//int g_Item[2];//アイテム画像変数

//int g_WaitTime = 0;//待ち時間
//int g_EndImage;

int g_Mileage;//走行距離
//敵カウント
int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;

int g_Apple;//キャラ画像変数
//int g_GreenApple;//キャラ画像変数
//int g_YellowApple;//キャラ画像変数
//int g_PoisonApple[4];//キャラ画像変数


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int g_StageImage;


/***********************************************
 *関数のプロトタイプ宣言
 ***********************************************/

void GameInit(void);//ゲーム初期化処理
void GameMain(void);//ゲームメイン処理

void DrawGameTitle(void);//タイトル描画処理

int LoadImages();//画像読み込み

void DrawHelp();

//void BackScrool();

//void PlayerControl();//自機処理

//void EnemyControl();//敵機処理
//int CreateEnemy();//敵機生成処理

/***********************************************
 *プログラムの開始
 ***********************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow) {

	SetMainWindowText("リンゴゲーム");//タイトルを設定
	ChangeWindowMode(TRUE);//ウィンドウモードで起動
	if (DxLib_Init() == -1)return -1;//DXライブラリの初期化処理
	SetDrawScreen(DX_SCREEN_BACK);//描画先画面を裏にする
	if (LoadImages() == -1)return -1;//画像読み込み関数を呼び出し




	//ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;
		ClearDrawScreen();//画像の初期化

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//ゲームタイトル描画処理
			break;
		case 1:
			GameInit();		//ゲーム初期処理
			break;
			//case 2:
			//	DrawRanking();	//ランキング描画処理
			//	break;
			case 3:
				DrawHelp();		//ゲームヘルプ描画処理
				break;
			//case 4:
			//	DrawEnd();		//ゲームエンド描画処理
			//	break;
		case 5:
			GameMain();     //ゲームメイン処理
			break;
			//case 6:
			//	DrawGameOver(); //ゲームオーバー描画処理
			//	break;
			//case 7:
			//	InputRanking(); //ランキング入力処理
			//	break;
		}
		ScreenFlip();     //裏画面の内容を表画面に反映
	}
	DxLib_End();

	return 0;
}
/***********************************************
 *ゲームタイトル表示(メニュー画面)
 ***********************************************/
void DrawGameTitle(void) {
	static int MenuNo = 0;
	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;
	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
	}
	//Zキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A)g_GameState = MenuNo + 1;
	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);
	//メニュー
	DrawGraph(120, 200, g_Menu, TRUE);
	//メニューカーソル
	DrawRotaGraph(125, 220 + MenuNo * 35, 0.7f, M_PI / 50, g_Apple, TRUE);
}
/***********************************************
 *ゲーム初期処理
 ***********************************************/
void GameInit(void) {
	//スコアの初期化
	g_Score = 0;

	//走行距離を初期化
	g_Mileage = 0;

	//敵1を避けた数を初期化
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;



	//エネミーの初期設定
	//for (int i = 0; i < ENEMY_MAX; i++) {
	//	g_enemy[i].flg = FALSE;
	//}

	move.Init();


	//ゲームメイン処理へ
	g_GameState = 5;
}
/***********************************************
 *ゲームメイン
***********************************************/
void GameMain(void) {
	//BackScrool();

	move.EnemyControl();

}
/***********************************************
 *背景画像スクロール処理
 * 引数：なし
 * 戻り値：なし
***********************************************/
//void BackScrool() {
//	////ステージ画像表示
//	/*g_Mileage += 5;
//	g_Mileage += g_Player.speed;*/
//
//	//描画可能エリアを認定
//	SetDrawArea(0, 0, 500, 480);
//	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
//	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
//	//エリアを戻す
//	SetDrawArea(0, 0, 640, 480);
//	//ステージ背景
//	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
//
//}
/***********************************************
*画像読み込み
***********************************************/
int LoadImages() {
	//タイトル
	if ((g_TitleImage = LoadGraph("images/Apple/Title1.png")) == -1)return -1;
	//メニュー
	if ((g_Menu = LoadGraph("images/Apple/menu2.png")) == -1) return -1;
	if ((g_Cone = LoadGraph("images/Apple/Red.png")) == -1) return-1;


	//ランキング画像データの読み込み
	//if ((g_RankingImage = LoadGraph("images/chapter5/Ranking.bmp")) == -1) return -1;

	//エンディング
	//if ((g_EndImage = LoadGraph("images/chapter5/End.bmp")) == -1) return -1;

	//敵
	if ((g_Apple = LoadGraph("images/Apple/Green.png")) == -1)return-1;
	/*if ((g_GreenApple = LoadGraph("images/chapter5/GreenApple.png")) == -1)return-1;
	if ((g_YellowApple = LoadGraph("images/chapter5/YellowApple.png")) == -1)return-1;*/
	//if ((g_Apple[4] = LoadGraph("images/chapter5/Apple.bmp" )) == -1)return-1;

	//ステージ背景
	if ((g_StageImage = LoadGraph("images/Apple/mori.png")) == -1) return -1;

	return 0;
}


int Apple::GetApple() {

	return g_Apple;
}

int Apple::GetMileage() {

	return g_Mileage;
}

///****************************************/
//ゲームヘルプ描画処理
//****************************************/
void DrawHelp(void) {

	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);
	SetFontSize(16);
	DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);

	DrawString(20, 160, "これは障害物を避けながら", 0xffffff, 0);
	DrawString(20, 180, "走り続けるゲームです", 0xffffff, 0);
	DrawString(20, 200, "燃料が尽きるか障害物に", 0xffffff, 0);
	DrawString(20, 220, "数回当たるとゲームオーバーです", 0xffffff, 0);
	DrawString(20, 250, "アイテム一覧", 0xffffff, 0);
	/*DrawGraph(20, 260, g_Item[0], TRUE);*/
	DrawString(20, 315, "取ると燃料が回復するよ。", 0xffffff, 0);
	/*DrawGraph(20, 335, g_Item[1], TRUE);*/
	DrawString(20, 385, "ダメージを受けている時に取ると耐久回復", 0xffffff, 0);
	DrawString(20, 405, "耐久が減っていなかったら燃料が少し回復するよ。", 0xffffff, 0);
	DrawString(20, 450, "---- スペースキーを押してタイトルへ戻る ----", 0xffffff, 0);
}