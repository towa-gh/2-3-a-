//#include"DxLib.h"
////�v���O������WinMain����n�܂�܂�
//int g_OldKey;
//int g_NowKey;
//int g_KeyFlg;
//int g_EndImage;
//int g_WaitTime = 0;
//int g_FadeIn = 0;
//
//void DrawEnd(void);
//int WINAPI WinMain(HINSTANCE hlnstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdshow) {
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)return-1;
//
//	if ((g_EndImage = LoadGraph("images/KadaiEnd.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	while (ProcessMessage() == 0 && ++g_WaitTime < 900) {
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen();
//		DrawEnd();
//		ScreenFlip();
//	}
//	
//	
//
//
//
//	DxLib_End();    //DX���C�u�����g�p�̏I������
//
//	return 0;     //�\�t�g�̏I��
//}
//void DrawEnd(void) {
//	if (++g_FadeIn >= 255) g_FadeIn = 255;
//
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	SetFontSize(20);
//
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, g_FadeIn);
//
//	DrawString(110, 170 , "�^�C�g���@�@�@�Z�Z�Z Game", 0x000000);
//	DrawString(110, 200 , "�o�[�W�����@�@�@2,0", 0x000000);
//	DrawString(110, 230 , "�ŏI�X�V���@�@�@2018�N07��01��", 0x000000);
//	DrawString(110, 260 , "����ҁ@�@�@���ۓd�q�r�W�l�X���w�Z", 0x000000);
//	DrawString(110, 290 , "�@�@�@�@   ���ۑ��Y", 0x000000);
//	DrawString(110, 310 , "�f�ޗ��p", 0x000000);
//	DrawString(110, 340 , "�@BGM�@�@�@�@������", 0x000000);
//	DrawString(110, 365 , "�@SE�@�@�@�@�����뉀", 0x000000);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}