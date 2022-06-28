/******************************************************************** 
** 第３章 ゲームプログラミングの基本 
** （３）メニュー画面の作成（マウス操作でメニュー選択） 
********************************************************************/ 
#include "DxLib.h" 
 
/*********************************************** 
 * 変数の宣言 
 ***********************************************/ 
int g_OldKey;  // 前回の入力キー 
int g_NowKey;  // 今回の入力キー 
int g_KeyFlg;  // 入力キー情報 
int g_MenuNumber = 0;  // メニューカーソル位置 
 
int  g_MouseX;  // マウスＸ座標 
int  g_MouseY;  // マウスＹ座標 
 
int g_TitleImage; // 画像用変数 
/*********************************************** 
 * プログラムの開始 
 ***********************************************/ 
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,  
     LPSTR lpCmdLine, int nCmdShow ) 
{ 
 // ウィンドウモードで起動する 
 ChangeWindowMode(TRUE); 
 
 // DX ライブラリの初期化処理:エラーが起きたら直ちに終了 
 if ( DxLib_Init() == -1 ) return -1; 
 
 //タイトル画像データの読み込み 
 if ((g_TitleImage = LoadGraph("images/Title2.bmp")) == -1) return -1; 
 
 // 描画先画面を裏にする 
 SetDrawScreen( DX_SCREEN_BACK ); 
 
 // マウスカーソル表示 
 SetMouseDispFlag(TRUE); 
 
 
 
//9 
 
 // ゲームループ 
 while ( ProcessMessage() == 0 ){ 
  // キー入力取得 
  g_OldKey = g_NowKey; 
  g_NowKey = GetMouseInput(); 
  g_KeyFlg = g_NowKey & ~ g_OldKey; 
   
  //マウスクリックでゲームモードを各画面に切り替える 
  if (g_KeyFlg & MOUSE_INPUT_LEFT ) { 
   // マウスから座標読み取る 
   GetMousePoint(&g_MouseX , & g_MouseY); 
   g_MenuNumber = 9; 
   // タイトル画面での選択（スタート） 
   if (g_MouseX > 120 && g_MouseX < 210 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 0; 
   } 
   // タイトル画面での選択（ランキング）  
   if (g_MouseX > 300 && g_MouseX < 410 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 1; 
   } 
   // タイトル画面での選択(エンド） 
   if (g_MouseX > 510 && g_MouseX < 555 && g_MouseY > 410 && g_MouseY < 440 ) { 
    g_MenuNumber = 2; 
   }  
  } 
  // 画面の初期化 
  ClearDrawScreen(); 
 
  //タイトル画像表示 
  DrawGraph( 0 , 0 , g_TitleImage, FALSE ) ; 
  DrawFormatString( 0, 0, GetColor( 255 , 255 , 255 ),  "MenuNumber = %d ", g_MenuNumber ); 
 
  // 裏画面の内容を表画面に反映します 
  ScreenFlip(); 
 } 
 // DX ライブラリ使用の終了処理 
 DxLib_End(); 
 
 // ソフトの終了 
 return 0; 
} 
 