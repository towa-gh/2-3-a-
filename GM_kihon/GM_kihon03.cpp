//#include"DxLib.h"
//
//int g_OldKey;			//�O��̓��̓L�[
//int g_NowKey;		    //����̓��̓L�[
//int g_KeyFlg;			//���̓L�[���
//int g_MenuNumber = 0;	//���j���[�J�[�\���ʒu
//
//int g_MouseX;            //���j���[�J�[�\����XY���W
//int g_MouseY;
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
//	if ((g_TitleImage = LoadGraph("images/Title2.bmp")) == -1)return-1;
//
//	//�`���ʂ𗠂ɂ���
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//�}�E�X�J�[�\���\��
//	SetMouseDispFlag(TRUE);
//
//	//�Q�[�����[�v
//	while (ProcessMessage() == 0){
//	
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//���j���[�J�[�\���̈ړ�����
//		if (g_KeyFlg & MOUSE_INPUT_LEFT)
//		{
//			//�}�E�X������W��ǂݎ��
//			GetMousePoint(&g_MouseX, &g_MouseY);
//			g_MenuNumber = 9;
//			
//			//�^�C�g����ʂł̑I��(�X�^�[�g)
//			if (g_MouseX > 120 && g_MouseX < 210 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 0;
//			}
//			//�^�C�g����ʂł̑I��(�����L���O)
//			if (g_MouseX > 300 && g_MouseX < 410 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 1;
//			}
//			//�^�C�g����ʂł̑I��(�G���h)
//			if (g_MouseX > 510 && g_MouseX < 555 && g_MouseY > 410 && g_MouseY < 440) {
//				g_MenuNumber = 2;
//			}
//		}
//
//		//��ʂ̏�����
//		ClearDrawScreen();
//
//		//�摜�\��
//		DrawGraph(0, 0, g_TitleImage, FALSE);
//		DrawFormatString(0, 0, GetColor(255, 255, 255), "MenuNumber = %d", g_MenuNumber);
//
//
//		//����ʂ̓��e��\��ʂɕ\��
//		ScreenFlip();
//	}
//	//�I������
//	DxLib_End();
//	return 0;
//}