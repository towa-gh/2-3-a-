//#include"DxLib.h"
//
//int g_OldKey;			//前回の入力キー
//int g_NowKey;		    //今回の入力キー
//int g_KeyFlg;			//入力キー情報
//int g_MenuNumber = 0;	//メニューカーソル位置
//int g_MenuY;            //メニューカーソルのY座標
//
//
//int g_TitleImage;		//画像用変数
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)	return -1;
//
//	//画像読み込み
//	if ((g_TitleImage = LoadGraph("kadaiTitle.bmp")) == -1)return-1;
//
//	//描画画面を裏にする
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//ゲームループ
//	while (ProcessMessage() == 0)
//	{
//		//入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//メニューカーソルの移動処理
//		if (g_KeyFlg & PAD_INPUT_DOWN)
//		{
//			if (++g_MenuNumber > 2)	g_MenuNumber = 0;
//		}
//		if (g_KeyFlg & PAD_INPUT_UP)
//		{
//			if (--g_MenuNumber < 0)	g_MenuNumber = 2;
//		}
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		//画像表示
//		DrawGraph(0, 0, g_TitleImage, FALSE);
//
//
//		//変数を利用した場合のカーソル表示
//
//		g_MenuY = g_MenuNumber * 52;
//		DrawCircle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY,
//		                                            GetColor(255,0,0),TRUE);
//
//		//裏画面の内容を表画面に表示
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();
//	return 0;
//}