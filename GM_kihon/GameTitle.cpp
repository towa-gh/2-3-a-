//#include"DxLib.h"
//
//int g_OldKey;			//�O��̓��̓L�[
//int g_NowKey;		    //����̓��̓L�[
//int g_KeyFlg;			//���̓L�[���
//int g_MenuNumber = 0;	//���j���[�J�[�\���ʒu
//int g_MenuY;            //���j���[�J�[�\����Y���W
//
//
//int g_TitleImage;		//�摜�p�ϐ�
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)	return -1;
//
//	//�摜�ǂݍ���
//	if ((g_TitleImage = LoadGraph("kadaiTitle.bmp")) == -1)return-1;
//
//	//�`���ʂ𗠂ɂ���
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//�Q�[�����[�v
//	while (ProcessMessage() == 0)
//	{
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//���j���[�J�[�\���̈ړ�����
//		if (g_KeyFlg & PAD_INPUT_DOWN)
//		{
//			if (++g_MenuNumber > 2)	g_MenuNumber = 0;
//		}
//		if (g_KeyFlg & PAD_INPUT_UP)
//		{
//			if (--g_MenuNumber < 0)	g_MenuNumber = 2;
//		}
//
//		//��ʂ̏�����
//		ClearDrawScreen();
//
//		//�摜�\��
//		DrawGraph(0, 0, g_TitleImage, FALSE);
//
//
//		//�ϐ��𗘗p�����ꍇ�̃J�[�\���\��
//
//		g_MenuY = g_MenuNumber * 52;
//		DrawCircle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY,
//		                                            GetColor(255,0,0),TRUE);
//
//		//����ʂ̓��e��\��ʂɕ\��
//		ScreenFlip();
//	}
//
//
//
//	DxLib_End();
//	return 0;
//}