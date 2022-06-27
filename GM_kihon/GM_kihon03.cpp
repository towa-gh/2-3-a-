//#include"DxLib.h"
//
//int g_OldKey;			//前回の入力キー
//int g_NowKey;		    //今回の入力キー
//int g_KeyFlg;			//入力キー情報
//int g_MenuNumber = 0;	//メニューカーソル位置
//
//int g_MouseX;            //メニューカーソルのXY座標
//int g_MouseY;
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
//	if ((g_TitleImage = LoadGraph("images/Title2.bmp")) == -1)return-1;
//
//	//描画画面を裏にする
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//マウスカーソル表示
//	SetMouseDispFlag(TRUE);
//
//	//ゲームループ
//	while (ProcessMessage() == 0){
//	
//		//入力キー取得
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//メニューカーソルの移動処理
//		if (g_KeyFlg & MOUSE_INPUT_LEFT)
//		{
//			//マウスから座標を読み取る
//			GetMousePoint(&g_MouseX, &g_MouseY);
//			g_MenuNumber = 9;
//			
//			//タイトル画面での選択(スタート)
//			if (g_MouseX > 120 && g_MouseX < 210 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 0;
//			}
//			//タイトル画面での選択(ランキング)
//			if (g_MouseX > 300 && g_MouseX < 410 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 1;
//			}
//			//タイトル画面での選択(エンド)
//			if (g_MouseX > 510 && g_MouseX < 555 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 2;
//			}
//		}
//
//		//画面の初期化
//		ClearDrawScreen();
//
//		//画像表示
//		DrawGraph(0, 0, g_TitleImage, FALSE);
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "MenuNumber = %d", g_MenuNumber);
//
//
//		//裏画面の内容を表画面に表示
//		ScreenFlip();
//	}
//	//終了処理
//	DxLib_End();
//	return 0;
//}