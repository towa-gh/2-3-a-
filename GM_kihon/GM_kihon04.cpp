//#include"DxLib.h"
//
//int g_OldKey;			//�O��̓��̓L�[
//int g_NowKey;		    //����̓��̓L�[
//int g_KeyFlg;			//���̓L�[���
//
//int g_EndImage;         //�摜�p�ϐ�
//int g_WaitTime = 0;     //�҂�����
//int g_PosY;            //�X�N���[������Y���W
//
//void DrawEnd(void); //�Q�[���G���h�`�揈��
//
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	ChangeWindowMode(TRUE);
//
//	if (DxLib_Init() == -1)	return -1;
//
//	//�摜�ǂݍ���
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1)return-1;
//
//	//�`���ʂ𗠂ɂ���
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//�Q�[�����[�v(15�b��I��)
//	while (ProcessMessage() == 0 && g_WaitTime < 900)
//	{
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//���j���[�J�[�\���̈ړ�����
//		ClearDrawScreen();
//
//		//�Q�[���G���h�`�揈��
//		DrawEnd();
//
//		//����ʂ̓��e��\��ʂɔ��f
//		ScreenFlip();
//
//	}
//	DxLib_End();
//	return 0;
//}
////* �Q�[���G���h�`�揈��
//
//void DrawEnd(void)
//{
//	//�G���h�摜�\��
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	//�����T�C�Y�ݒ�
//	SetFontSize(20);
//
//	//�G���f�B���O�\��
//	if (++g_WaitTime < 600) g_PosY = 300 - g_WaitTime / 2;
//	DrawString(110, 170 + g_PosY, "�^�C�g���@�@�Z�Z�Z�@Game", 0x000000);
//	DrawString(110, 200 + g_PosY, "�o�[�W�����@�@2.0", 0x000000);
//	DrawString(110, 230 + g_PosY, "�ŏI�X�V���@�@2018�N7��01��", 0x000000);
//	DrawString(110, 260 + g_PosY, "����ҁ@�@���ۓd�q�r�W�l�X���w�Z", 0x000000);
//	DrawString(110, 290 + g_PosY, "�@�@�@�@�@���ہ@���Y", 0x000000);
//	DrawString(110, 310 + g_PosY, "�f�ޗ��p", 0x000000);
//	DrawString(110, 340 + g_PosY, "BGM�@�@�@�@�����`��", 0x000000);
//	DrawString(110, 365 + g_PosY, "SE�@�@�@�@�@�����뉀", 0x000000);
//}