//#include"DxLib.h"
//
//int g_OldKey;			//前回の入力キー
//int g_NowKey;		    //今回の入力キー
//int g_KeyFlg;			//入力キー情報
//
//int g_EndImage;         //画像用変数
//int g_WaitTime = 0;     //待ち時間
//int g_PosY;            //スクロール時のY座標
//
//void DrawEnd(void); //ゲームエンド描画処理
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)	return -1;
//
//	//画像読み込み
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1)return-1;
//
//	//描画画面を裏にする
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//ゲームループ(15秒後終了)
//	while (ProcessMessage() == 0 && g_WaitTime < 900)
//	{
//		//入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//メニューカーソルの移動処理
//		ClearDrawScreen();
//
//		//ゲームエンド描画処理
//		DrawEnd();
//
//		//裏画面の内容を表画面に反映
//		ScreenFlip();
//
//	}
//	DxLib_End();
//	return 0;
//}
////* ゲームエンド描画処理
//
//void DrawEnd(void)
//{
//	//エンド画像表示
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	//文字サイズ設定
//	SetFontSize(20);
//
//	//エンディング表示
//	if (++g_WaitTime < 600) g_PosY = 300 - g_WaitTime / 2;
//	DrawString(110, 170 + g_PosY, "タイトル　　〇〇〇　Game", 0x000000);
//	DrawString(110, 200 + g_PosY, "バージョン　　2.0", 0x000000);
//	DrawString(110, 230 + g_PosY, "最終更新日　　2018年7月01日", 0x000000);
//	DrawString(110, 260 + g_PosY, "制作者　　国際電子ビジネス専門学校", 0x000000);
//	DrawString(110, 290 + g_PosY, "　　　　　国際　太郎", 0x000000);
//	DrawString(110, 310 + g_PosY, "素材利用", 0x000000);
//	DrawString(110, 340 + g_PosY, "BGM　　　　魔王伝説", 0x000000);
//	DrawString(110, 365 + g_PosY, "SE　　　　　煉獄庭園", 0x000000);
//}