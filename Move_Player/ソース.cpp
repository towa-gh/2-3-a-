/****************************************************************************************************************
*** 　第５章　ミニゲームを作る（２）
***
*** 　レース＆避けゲー
*****************************************************************************************************************/
#include"DxLib.h"
#define _USE_MATH_DEFINES
#include<math.h>

#define RANKING_DATA 5

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　定数の宣言
***
*****************************************************************************************************************/

//画面領域の大きさ
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//自機の初期値
const int PLAYER_POS_X = SCREEN_WIDTH / 2;
const int PLAYER_POS_Y = SCREEN_HEIGHT - 100;
const int PLAYER_WIDTH = 63;
const int PLAYER_HEIGHT = 120;
const int PLAYER_SPEED = 5;
//const int PLAYER_HP = 1000;
const int PLAYER_FUEL = 20000;
const int PLAYER_BARRIER = 3;
const int PLAYER_BARRIERUP = 10;

//敵機の最大数
const int ENEMY_MAX = 4;


/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　変数の宣言
***
*****************************************************************************************************************/
int g_OldKey;     //前回の入力キー
int g_NowKey;     //今回の入力キー
int g_KeyFlg;     //入力キー情報

int g_GameState = 0;  //ゲームモード

int g_TitleImage;     //画像用変数
int g_Menu, g_Cone;   //メニュ画像変数

int g_Score = 0;     //スコア

int g_RankingImage;  //画像用変数

int g_Item[2];

int g_WaitTime = 0;  //待ち時間

int g_EndImage;

int g_Mileage;       //走行距離

int g_EnemyCount1, g_EnemyCount2, g_EnemyCount3;  //敵カウント

int g_Teki[3];

int g_Ringo;

//int g_Ringo[3];

int g_StageImage;

int g_Player, g_PlayerRight, g_PlayerLeft, g_Barrier;          //キャラ画像変数



//自機の構造体
struct PLAYER {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度
	//int hp;          //体力
	int fuel;          //燃料
	int bari;          //バリア回数
	int baricnt;          //バリア継続時間
};

//自機
struct PLAYER g_player;


struct PLAYERRIGHT {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度
	//int hp;          //体力
	int fuel;          //燃料
	int bari;          //バリア回数
	int baricnt;          //バリア継続時間
};

//自機
struct PLAYER g_playerright;


struct PLAYERLEFT {

	int flg;          //使用フラグ
	int x, y;          //座標ｘ.ｙ
	int w, h;          //幅ｗ　高さｈ
	double angle;     //機体の向き
	int count;          //タイミング用
	int speed;          //移動速度
	//int hp;          //体力
	int fuel;          //燃料
	int bari;          //バリア回数
	int baricnt;          //バリア継続時間
};

//自機
struct PLAYER g_playerleft;

//ランキングデータ（構造体）
struct RankingData {

	int no;

	char name[11];

	long score;
};

//ランキングデータ変数宣言
struct RankingData  g_Ranking[RANKING_DATA];

//敵機の構造体
struct ENEMY {

	int flg;  //使用フラグ
	int type; //タイプ
	int img;  //画像
	int x, y, w, h;  //座標xy 幅w 高さh
	int speed; //移動速度
	int point; //スコア加算

};

//敵機
struct ENEMY g_enemy[ENEMY_MAX];

struct ENEMY g_enemy00 = { TRUE,0,0,0,-50,63,120,0,1 };

struct ENEMY g_enemyCn = { TRUE,4,0,0,-50,18,18,0,1 };

struct ENEMY g_item00 = { TRUE,0,0,0,-50,50,50,0,1 };

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　　関数のプロトタイプ宣言
***
*****************************************************************************************************************/
void GameInit(void);           //ゲーム初期化処理
void GameMain(void);           //ゲームメイン処理

void DrawGameTitle(void);      //タイトル描画処理
void DrawGameOver(void);       //ゲームオーバー画面描画処理
void DrawEnd(void);            //ゲームエンド描画処理
void DrawHelp(void);           //ゲームヘルプ描画処理

void DrawRanking(void);        //ランキング描画処理
void InputRanking(void);       //ランキング入力
void SortRanking(void);        //ランキング並べ替え
int  SaveRanking(void);        //ランキングデータの保存
int  ReadRanking(void);        //ランキングデータ読み込み

int LoadImages();              //画像読み込み

void BackScrool();             //背景画像スクロール処理

void PlayerControl();          //自機処理

void EnemyControl();           //敵機処理
int CreateEnemy();             //敵機生成処理

int HitBoxPlayer(PLAYER* p, ENEMY* e);  //当たり判定

void DrawRanking(void);        //ランキング描画

void SortRanking(void);        //ランキング並び替え

int  SaveRanking(void);        //ランキング保存

int ReadRanking(void);         //ランキング読み込み

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　プログラムの開始
***
*****************************************************************************************************************/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	// タイトル設定
	SetMainWindowText("Drive&Avoid");

	ChangeWindowMode(TRUE);		// ウィンドウモードで起動

	if (DxLib_Init() == -1) return -1;	// DXライブラリの初期化処理

	SetDrawScreen(DX_SCREEN_BACK);	// 描画先画面を裏にする

	if (LoadImages() == -1)return-1;  //画像読み込み関数を呼び出し

	// ゲームループ
	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {

		// 入力キー取得
		g_OldKey = g_NowKey;
		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
		g_KeyFlg = g_NowKey & ~g_OldKey;

		ClearDrawScreen();		// 画面の初期化

		switch (g_GameState) {
		case 0:
			DrawGameTitle();	//ゲームタイトル処理
			break;
		case 1:
			GameInit();		//ゲーム初期処理
			break;
		case 2:
			DrawRanking();	//ランキング描画処理
			break;
		case 3:
			DrawHelp();		//ゲームヘルプ描画処理
			break;
		case 4:
			DrawEnd();		//ゲームエンド処理
			break;
		case 5:
			GameMain();     //ゲームメイン処理
			break;
		case 6:
			DrawGameOver();		//ゲームクリア描画処理
			break;
		case 7:
			InputRanking();    //ランキング入力処理
			break;
		}

		ScreenFlip();			// 裏画面の内容を表画面に反映

	}

	DxLib_End();	// DXライブラリ使用の終了処理

	return 0;	// ソフトの終了
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームタイトル表示（メニュー画面）
***
*****************************************************************************************************************/
void DrawGameTitle(void)
{
	static int MenuNo = 0;

	//メニューカーソル移動処理
	if (g_KeyFlg & PAD_INPUT_DOWN) {
		if (++MenuNo > 3)MenuNo = 0;

	}
	if (g_KeyFlg & PAD_INPUT_UP) {
		if (--MenuNo < 0)MenuNo = 3;
	}

	//Ｚキーでメニュー選択
	if (g_KeyFlg & PAD_INPUT_A) g_GameState = MenuNo + 1;

	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);

	//メニュー
	DrawGraph(120, 200, g_Menu, TRUE);

	//メニューカーソル
	DrawRotaGraph(90, 220 + MenuNo * 40, 0.7f, M_PI / 2, g_Cone, TRUE);
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲーム初期処理
***
*****************************************************************************************************************/
void GameInit(void)
{
	//スコアの初期化
	g_Score = 0;

	//走行距離を初期化
	g_Mileage = 0;

	//敵１を避けて数の初期設定
	g_EnemyCount1 = 0;
	g_EnemyCount2 = 0;
	g_EnemyCount3 = 0;

	//プレイヤーの初期設定
	g_player.flg = TRUE;
	g_player.x = PLAYER_POS_X;
	g_player.y = PLAYER_POS_Y;
	g_player.w = PLAYER_WIDTH;
	g_player.h = PLAYER_HEIGHT;
	g_player.angle = 0.0;
	g_player.count = 0;
	g_player.speed = PLAYER_SPEED;
	//g_player.hp = PLAYER_HP;
	g_player.fuel = PLAYER_FUEL;
	g_player.bari = PLAYER_BARRIER;
	/*g_player.bariup = PLAYER_BARRIERUP;*/

	//ゲームメイン処理へ
	g_GameState = 5;

	//エネミーの初期設定
	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemy[i].flg = FALSE;
	}


}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームランキング描画表示
***
*****************************************************************************************************************/
void DrawRanking(void)
{
	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M) g_GameState = 0;

	//ランキング画像表示
	DrawGraph(0, 0, g_RankingImage, FALSE);

	//ランキング一覧を表示
	SetFontSize(18);
	for (int i = 0; i < RANKING_DATA; i++) {
		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %-10s %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	DrawString(100, 450, "--- スペースキーを押してタイトルへ戻る ---", 0xffffff, 0);

}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームヘルプ描画処理
***
*****************************************************************************************************************/
void DrawHelp(void)
{
	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 0;

	//タイトル画像表示
	DrawGraph(0, 0, g_TitleImage, FALSE);
	SetFontSize(16);

	DrawString(20, 120, "ヘルプ画面", 0xffffff, 0);

	DrawString(20, 160, "これは障害物を避けながら", 0xffffff, 0);

	DrawString(20, 180, "走り続けるゲームです。", 0xffffff, 0);

	DrawString(20, 200, "燃料が尽きるか障害物に数回当たると", 0xffffff, 0);

	DrawString(20, 220, "ゲームオーバー", 0xffffff, 0);

	DrawString(20, 250, "アイテム一覧", 0xffffff, 0);

	DrawGraph(20, 260, g_Item[0], TRUE);

	DrawString(20, 315, "取ると燃料が回復するよ", 0xffffff, 0);

	DrawGraph(20, 335, g_Item[1], TRUE);

	DrawString(20, 385, "ダメージを受けている時に取ると耐久回復", 0xffffff, 0);

	DrawString(20, 405, "耐久が減っていなかったら燃料が少し回復するよ", 0xffffff, 0);

	DrawString(20, 450, "--- スペースキーを押してタイトルへ戻る ---", 0xffffff, 0);
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームエンド描画処理
***
*****************************************************************************************************************/
void DrawEnd(void)
{
	//エンド画像表示
	DrawGraph(0, 0, g_EndImage, FALSE);

	SetFontSize(24);
	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);

	//タイムの火山処理&終了（３秒後）
	if (++g_WaitTime > 180)g_GameState = 99;
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームメイン
***
*****************************************************************************************************************/
void GameMain(void)
{

	BackScrool();

	EnemyControl();

	PlayerControl();

	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M)g_GameState = 6;

	SetFontSize(16);
	DrawString(20, 20, "ゲームメイン", 0xffffff, 0);
	DrawString(150, 450, "--- スペースキーを押してゲームオーバーへ ---", 0xffffff, 0);

}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ゲームオーバー画面描画処理
***
*****************************************************************************************************************/
void DrawGameOver(void)
{

	//描画可能エリアを設定
	SetDrawArea(0, 0, 500, 480);

	DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);

	//エリアを戻す
	SetDrawArea(0, 0, 640, 480);

	//スコア等表示領域
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);




	/*g_Score = (g_Mileage / 10 * 10) + g_EnemyCount3 * 50 + g_EnemyCount2 * 100 + g_EnemyCount1 * 200;*/


	//スペースキーでメニューに戻る
	if (g_KeyFlg & PAD_INPUT_M) {
		if (g_Ranking[RANKING_DATA - 1].score >= g_Score) {
			g_GameState = 0;


		}
		else {
			g_GameState = 7;
		}
	}

	DrawBox(150, 150, 490, 330, 0x009900, TRUE);
	DrawBox(150, 150, 490, 330, 0x000000, FALSE);

	SetFontSize(20);
	DrawString(220, 170, "ゲームオーバー", 0xcc0000);
	SetFontSize(16);
	/*DrawRotaGraph(230, 230, 0.3f, M_PI / 2, g_Teki[2], TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, g_Teki[0], TRUE, FALSE);*/

	DrawRotaGraph(230, 230, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(230, 250, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(230, 270, 0.3f, M_PI / 2, g_Ringo, TRUE, FALSE);



	/*DrawFormatString(260, 200, 0xFFFFFF, "%6d x  10 = %6d", g_Mileage / 10, g_Mileage / 10 * 10);*/
	DrawFormatString(260, 220, 0xFFFFFF, "%6d x  50 = %6d", g_EnemyCount3, g_EnemyCount3 * 50);
	DrawFormatString(260, 243, 0xFFFFFF, "%6d x  100 = %6d", g_EnemyCount2, g_EnemyCount2 * 100);
	DrawFormatString(260, 264, 0xFFFFFF, "%6d x  200 = %6d", g_EnemyCount1, g_EnemyCount1 * 200);

	//DrawString(310, 290, "スコア", 0x000000);

	DrawFormatString(260, 290, 0xFFFFFF, "             =%6d", g_Score);

	DrawString(150, 450, "--- スペースキーを押してタイトルへ戻る ---", 0xffffff, 0);
}

/****************************************************************************************************************
***
***　　　　　　　　　　　　　　ランキング入力処理
***
*****************************************************************************************************************/

/***********************************************
 * ランキング入力処理
 ***********************************************/
void InputRanking(void)
{
	//ランキング画像表示
	DrawGraph(0, 0, g_RankingImage, FALSE);

	// フォントサイズの設定
	SetFontSize(20);

	// 名前入力指示文字列の描画
	DrawString(150, 240, "ランキングに登録します", 0xFFFFFF);
	DrawString(150, 270, "名前を英字で入力してください", 0xFFFFFF);

	// 名前の入力
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[4].name, FALSE) == 1) {
		g_Ranking[4].score = g_Score;	// ランキングデータの１０番目にスコアを登録
		SortRanking();		// ランキング並べ替え
		SaveRanking();		// ランキングデータの保存
		g_GameState = 2;		// ゲームモードの変更
	}

}

/***********************************************
 * ランキング並べ替え
 ***********************************************/
void SortRanking(void)
{
	int i, j;
	RankingData work;

	// 選択法ソート
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}

	// 順位付け
	for (i = 0; i < 5; i++) {
		g_Ranking[i].no = 1;
	}

	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < 4; i++) {
		for (j = i + 1; j < 5; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}

/***********************************************
 * ランキングデータの保存
 ***********************************************/
int  SaveRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	// ファイルオープン
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "w")) == NULL) {

		/* エラー処理 */
		printf("Ranking Data Error\n");
		return -1;
	}

	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < 4; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;

}

/*************************************
 * ランキングデータ読み込み
 *************************************/
int ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	//ファイルオープン
	if ((fp = fopen("dat/Chapter4/rankingdata.txt", "r")) == NULL) {
		//エラー処理
		printf("Ranking Data Error\n");
		return -1;
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < 4; i++) {
		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}




/****************************************************************************************************************
***
***　　　　　　　　　　　　　　画像読み込み
***
*****************************************************************************************************************/
int LoadImages()
{
	//タイトル
	if ((g_TitleImage = LoadGraph("images/Chapter5/io__________.bmp")) == -1)return-1;
	/*if ((g_TitleImage = LoadGraph("images/Chapter5/Title.bmp")) == -1)return-1;*/

	//メニュー
	if ((g_Menu = LoadGraph("images/Chapter5/menu.bmp")) == -1)return-1;
	if ((g_Cone = LoadGraph("images/Chapter5/cone.bmp")) == -1)return-1;

	//ランキングデータの読み込み
	if (ReadRanking() == -1)return -1;

	//ランキング画像データの読み込み
	if ((g_RankingImage = LoadGraph("images/Chapter5/Ranking.bmp")) == -1)return -1;

	//アイテム
	if ((g_Item[0] = LoadGraph("images/Chapter5/gasoLine.bmp")) == -1)return -1;
	if ((g_Item[1] = LoadGraph("images/Chapter5/supana.bmp")) == -1)return -1;

	//エンディング
	if ((g_EndImage = LoadGraph("images/Chapter5/End.bmp")) == -1)return -1;

	//敵
	if ((g_Ringo = LoadGraph("images/Chapter5/ios__________.bmp")) == -1)return -1;

	//ステージ背景
	if ((g_StageImage = LoadGraph("images/Chapter5/bg_natural_mori.bmp")) == -1)return -1;

	//プレイヤー
	if ((g_Player = LoadGraph("images/Chapter5/22782619.bmp")) == -1)return -1;
	if ((g_PlayerRight = LoadGraph("images/Chapter5/Right.bmp")) == -1)return -1;
	if ((g_PlayerLeft = LoadGraph("images/Chapter5/Left.bmp")) == -1)return -1;

	return 0;
}



/****************************************************************************************************************
***                            背景画像スクロール処理

***　　　　　　　　　　　　　　引 数  ： なし
　
***　　　　　　　　　　　　　  戻り値 ： なし

*****************************************************************************************************************/
void BackScrool()
{
	//g_Mileage += 5;
	//g_Mileage += g_player.speed;

	//ステージ画像表示

	//描画可能エリアを設定
	SetDrawArea(0, 0, 500, 480);

	//DrawGraph(0, g_Mileage % 480 - 480, g_StageImage, FALSE);
	//DrawGraph(0, g_Mileage % 480, g_StageImage, FALSE);
	DrawGraph(0, 0, g_StageImage, TRUE);

	//エリアを戻す
	SetDrawArea(0, 0, 640, 480);

	//スコア等表示領域
	DrawBox(500, 0, 640, 480, 0x009900, TRUE);
}

/****************************************************************************************************************
***                            プレイヤーの移動処理

***　　　　　　　　　　　　　　引 数  ： なし
　
***　　　　　　　　　　　　　  戻り値 ： なし

****************************************************************************************************************/
void PlayerControl()
{
	

	//ゲームオーバー処理へ
	if (g_player.fuel <= 0)  g_GameState = 6;

	int PlayerPojishonRihght= DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);
	int PlayerPojishonLeft = DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);

	//プレイヤーの表示
	//上下左右移動
	if (g_player.flg == TRUE) {

	/*	DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Player, TRUE, FALSE);*/

		if (g_NowKey & PAD_INPUT_RIGHT) {


			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerRight, TRUE, FALSE);
			g_player.x += g_player.speed;


		}


		if (g_NowKey & PAD_INPUT_LEFT) {

			
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_PlayerLeft, TRUE, FALSE);
			g_player.x -= g_player.speed;

		}

		



	}

	//画面をはみ出さないようにする
	if (g_player.x < 32)  g_player.x = 32;

	if (g_player.x > SCREEN_WIDTH - 180)  g_player.x = SCREEN_WIDTH - 180;

	if (g_player.y < 60)    g_player.y = 60;

	if (g_player.y > SCREEN_HEIGHT - 60)   g_player.y = SCREEN_HEIGHT - 60;




	//プレイヤーの表示
	/*if (g_player.flg == TRUE) {*/
		/*if (g_NowKey & PAD_INPUT_LEFT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);

		}*/
		/*else if (g_NowKey & PAD_INPUT_RIGHT) {
			DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 18, g_Car, TRUE, FALSE);

		}*/


		/*DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Player, TRUE, FALSE);*/




	/*else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Car, TRUE, FALSE);

	}*/

	/*if (g_KeyFlg & PAD_INPUT_C && g_player.bari > 0 && g_player.baricnt <= 0) {

		g_player.bari--;
		g_player.baricnt = 1000;
	}*/

	/*if (g_player.baricnt > 0) {

		g_player.baricnt -= g_player.speed;
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, 0, g_Barrier, TRUE, FALSE);

	}
	else {

		g_player.baricnt = 0;

	}*/

	/*}*/
	/*else {
		DrawRotaGraph(g_player.x, g_player.y, 1.0f, M_PI / 8 * (++g_player.count / 5), g_Car, TRUE, FALSE);

		if (g_player.count >= 80) g_player.flg = TRUE;
	}*/

	//敵を避けた数を表示
	SetFontSize(16);

	DrawFormatString(510, 800, 0x000000, "避けた数");

	/*DrawRotaGraph(523, 120, 0.3f, 0, g_Teki[0], TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Teki[1], TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Teki[2], TRUE, FALSE);*/

	DrawRotaGraph(523, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(573, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);
	DrawRotaGraph(623, 120, 0.3f, 0, g_Ringo, TRUE, FALSE);


	DrawFormatString(510, 140, 0xFFFFFF, "%03d", g_EnemyCount1);
	DrawFormatString(560, 140, 0xFFFFFF, "%03d", g_EnemyCount2);
	DrawFormatString(610, 140, 0xFFFFFF, "%03d", g_EnemyCount3);


}


/****************************************************************************************************************
***                            エネミーの移動

***　　　　　　　　　　　　　　引 数  ： なし
　
***　　　　　　　　　　　　　  戻り値 ： なし

*****************************************************************************************************************/
void EnemyControl()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == TRUE) {

			//敵の表示
			DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 1.0f, 0, g_enemy[i].img, TRUE, FALSE);

			if (g_player.flg == FALSE)continue;

			//真っすぐ下に移動
			g_enemy[i].y += g_enemy[i].speed + g_player.speed - PLAYER_SPEED + 1;

			//画面をはみ出したら消去
			if (g_enemy[i].y > SCREEN_HEIGHT + g_enemy[i].h) g_enemy[i].flg = FALSE;

			//敵機を追い越したらカウントする
			if (g_enemy[i].y > g_player.y && g_enemy[i].point == 1) {

				g_enemy[i].point = 0;
				if (g_enemy[i].type == 0) g_EnemyCount1++;
				if (g_enemy[i].type == 1) g_EnemyCount2++;
				if (g_enemy[i].type == 2) g_EnemyCount3++;
			}

			//当たり判定
			if (HitBoxPlayer(&g_player, &g_enemy[i]) == TRUE && g_player.baricnt <= 0) {

				g_player.flg = TRUE;
				g_player.speed = PLAYER_SPEED;
				//g_player.count = 0;
				g_enemy[i].flg = FALSE;

				//if (g_player.hp <= 0)  g_GameState = 6;
			}

		}
	}

	//走行距離ごとに敵出現パターンを制御する
	if (g_Mileage / 10 % 50 == 0) {
		CreateEnemy();
	}
}

/****************************************************************************************************************
***                            敵機の生成

***　　　　　　　　　　　　　　引 数  ： なし
　
***　　　　　　　　　　　　　  戻り値 ： TRUE : 成功　　FALSE : 失敗

*****************************************************************************************************************/
int CreateEnemy()
{
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (g_enemy[i].flg == FALSE) {

			g_enemy[i] = g_enemy00;
			g_enemy[i].type = GetRand(2);
			/*g_enemy[i].img = g_Teki[g_enemy[i].type];*/
			g_enemy[i].img = g_Ringo;
			g_enemy[i].x = GetRand(4) * 105 + 40;
			g_enemy[i].speed = g_enemy[i].type * 2;

			//成功
			return TRUE;

		}
	}

	//失敗
	return FALSE;
}

/****************************************************************************************************************
***                            自機と敵機の当たり判定（四角）

***　　　　　　　　　　　　　　引 数  ： PLAYERポインタ
　
***　　　　　　　　　　　　　  戻り値 ： TRUE : 当たり　　FALSE : なし

*****************************************************************************************************************/
int HitBoxPlayer(PLAYER* p, ENEMY* e)
{
	//x,yは中心座標とする
	int sx1 = p->x - (p->w / 2);
	int sy1 = p->y - (p->h / 2);

	int sx2 = sx1 + p->w;
	int sy2 = sy1 + p->h;

	int dx1 = e->x - (e->w / 2);
	int dy1 = e->y - (e->h / 2);

	int dx2 = dx1 + e->w;
	int dy2 = dy1 + e->h;

	//矩形が重なりあっていれば当たり
	if (sx1 < dx2 && dx1 < sx2 && sy1 < dy2 && dy1 < sy2) {
		return TRUE;

	}
	return FALSE;
}



