////<�����L���O�f�[�^�̕��בւ��֐�>)
//
////*�����L���O�f�[�^�̕��בւ�
//#include "DxLib.h"
//
//
////�ϐ��̐錾
//int g_OldKey; //�O��̓��̓L�[
//
//int g_NowKey; //����̓��̓L�[
//
//int g_KeyFlg; //���̓L�[���
//
//int g_RankingImage; //�摜�p�ϐ�
//
//int g_WaitTime = 0; //�҂�����
//
//int g_Score = 3500; //�X�R�A
//
//int g_GameState = 1; //�Q�[���X�e�[�^�X(���)
//
////�@�����L���O�f�[�^(�\����)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////�����L���O�f�[�^������
//struct RankingData g_Ranking[10]={
//		{1,"**********",100000},
//		{2,"**********",50000},
//		{3,"**********",10000},
//		{4,"**********",5000},
//		{5,"**********",1000},
//		{6,"**********",500},
//		{7,"**********",100},
//		{8,"**********",50},
//		{9,"**********",10},
//		{10,"**********",5}
//	};
////�֐��̃v���g�R���^�C�v�錾
//void DrawRanking(void); //�����L���O�`��
//
//void InputRanking(void);//�����L���O�̓���
//
//void SortRanking(void);//�����L���O�̕��בւ�
//
//
////�v���O�����̊J�n
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//
//	//�E�B���h�E���[�h�ŋN��
//	ChangeWindowMode(TRUE);
//
//	//DX���C�u�����̏���������
//	if (DxLib_Init() == -1)return -1;
//
//	//�����L���O�摜�f�[�^�̓ǂݍ���
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return-1;
//
//	//�`���𗠂ɂ���
//	SetDrawScreen(DX_SCREEN_BACK);
//
//	//�Q�[�����[�v
//	while (ProcessMessage() == 0) {
//
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//�X�y�[�X�L�[�ŋ����I��
//		if (g_KeyFlg & PAD_INPUT_M)break;
//
//		//��ʂ̏�����
//		ClearDrawScreen();
//
//		switch (g_GameState) {
//		case 0:
//			DrawRanking();//�����L���O�`�揈��
//			break;
//		case 1:
//			InputRanking();//�����L���O���͏���
//			break;
//		}
//
//		//����ʂ̓��e��\��ʂɔ��f
//		ScreenFlip();
//	}
//
//	//DX���C�u�����g�p�̏I������
//	DxLib_End();
//
//	return 0; //�\�t�g�̏I��
//}
//
//
//    void SortRanking(void)
//{
//	RankingData work;
//
//	//�I��@�\�[�g
//	for (int i = 0; i < 9; i++) {
//		for (int j = i + 1; j < 10; j++) {
//			if (g_Ranking[i].score <= g_Ranking[j].score) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//
//	//���ʕt��
//	for (int i = 0; i < 10; i++) {
//		g_Ranking[i].no = 1;
//	}
//	//���_�������ꍇ�͓������ʂƂ���
//	//�����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
//	for (int i = 0; i < 9; i++) {
//		for (int j = i + 1;j < 10; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
//	//�����L���O�`�揈��
//	void DrawRanking(void)
//	{
//		//�����L���O�摜�\��
//		DrawGraph(0, 0, g_RankingImage, FALSE);
//
//		//�����L���O�ꗗ�\��
//		SetFontSize(30);
//		for (int i = 0;i < 10; i++) {
//			DrawFormatString(80, 170 + i * 25, 0x000000, "%2d %10s  %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//		}
//
//		//�����̕\��(�_��)
//		if (++g_WaitTime < 30) {
//			SetFontSize(24);
//			DrawString(150, 450, "-- Press[SPACE]Key --", 0xFF0000);
//		}
//		else if (g_WaitTime > 60) {
//			g_WaitTime = 0;
//		}
//	}
//	//�����L���O���͏���
//
//	void InputRanking(void)
//	{
//		//�����L���O�摜�\��
//		DrawGraph(0, 0, g_RankingImage, FALSE);
//
//		//�t�H���g�T�C�Y�̐ݒ�
//		SetFontSize(20);
//
//		//���O���͎w��������̕`��
//		DrawString(150, 240, "�����L���O�ɓo�^", 0x000000);
//		DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0x000000);
//
//		//���O����
//		DrawString(150, 310, ">",0x000000);
//		DrawBox(160, 305, 300, 335, 0x000000,TRUE);
//		if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//			g_Ranking[9].score = g_Score;//�����L���O�f�[�^��10�ԖڂɃX�R�A��o�^
//			SortRanking();//�����L���O���בւ�
//			g_GameState = 0;//�Q�[���X�e�[�^�X�̕ύX
//		}
//	}
//
