//#include "DxLib.h"
//
////*�ϐ��̐錾
//int g_OldKey; //�O��̓��̓L�[
//int g_NowKey; //����̓��̓L�[
//int g_KeyFlg; //���̓L�[���
//
//int g_RankingImage;//�摜�p�ϐ�
//
//int g_WaitTime = 0;//�҂�����
//
//int g_Score = 3500;//�X�R�A
//
////�����L���O�f�[�^(�\����)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////�����L���O�f�[�^������
//struct RankingData  g_Ranking[10] = {
//	{1,"**********",100000},
//	{2,"**********",50000},
//	{3,"**********",10000},
//	{4,"**********",5000},
//	{5,"**********",1000},
//	{6,"**********",500},
//	{7,"**********",100},
//	{8,"**********",50},
//	{9,"**********",10},
//	{10,"**********",5},
//};
//
////*�֐��v���g�R���^�C�v�錾
//void InputRanking(void);//�����L���O���͏���
//
////*�v���O�����̊J�n
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
//	if (DxLib_Init() == -1)return -1;//DX���C�u�����̏���������
//
//	//�����L���O�摜�f�[�^�̓ǂݍ���
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	SetDrawScreen(DX_SCREEN_BACK);//�`���ʂ𗠂ɂ���
//
//	SetFontSize(20);//�����T�C�Y��ݒ�
//	//�Q�[�����[�v
//
//	while (ProcessMessage() == 0) {
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		if (g_KeyFlg & PAD_INPUT_M)break; //�X�y�[�X�L�[�ŋ����I��
//
//		ClearDrawScreen();//��ʂ̏�����
//
//		InputRanking();//�����L���O���͏���
//
//		ScreenFlip();//����ʂ̓��e��\��ʂɔ��f
//	}
//	DxLib_End();//DX���C�u�����g�p�̏I������
//
//	return 0; //�\�t�g�̏I��
//}
//
////*�����L���O���͏���
//void InputRanking(void)
//{
//	//�����L���O��ʕ\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//�t�H���g�T�C�Y�̐ݒ�
//	SetFontSize(20);
//
//	//���O���͕�����̕`��
//	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0x000000);
//	DrawString(150, 270, "���O���p���œ���", 0x000000);
//
//
//	//���O����
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//
//	//�e�X�g�p�ϐ��\��
//	DrawFormatString(0, 0, 0x000000, "Ranking[9].no =%2d", g_Ranking[9].no);
//	DrawFormatString(0, 20, 0x000000, "Ranking[9].name =%10s", g_Ranking[9].name);
//	DrawFormatString(0, 40, 0x000000, "Ranking[9].score =%10d", g_Ranking[9].score);
//
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score; //�����L���O�f�[�^��10�ԖڂɃX�R�A��o�^
//	}
//}
//
//
