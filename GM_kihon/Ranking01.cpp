//#include "DxLib.h"
//
////*�ϐ��̐錾
//int g_OldKey; //�O��̓��̓L�[
//int g_NowKey; //����̓��̓L�[
//int g_KeyFlg; //���̓L�[���
//
//int g_RankingImage;//�摜�p�ϐ�
//
//int g_WaitTime = 0; //�摜�p�ϐ�
//
////�����L���O�f�[�^(�\����)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////�����L���O�f�[�^������
//struct RankingData g_Ranking[10] = {
//
//	{1,"**********",100000},
//	{2,"**********",50000},
//	{3,"**********",10000},
//	{4,"**********",5000},
//	{5,"**********",1000},
//	{6,"**********",500},
//	{7,"**********",100},
//	{8,"**********",50},
//	{9,"**********",10},
//	{10,"**********",5}
//};
////*�֐��̃v���g�R���錾
//void DrawRanking(void);//�����L���O�`�揈��
////*�v���O�����J�n
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
//	
//	if (DxLib_Init() == -1)return -1; //DX���C�u�����̏���������
//
//	//�����L���O�摜�f�[�^�ǂݍ���
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1) return -1;
//
//		SetDrawScreen(DX_SCREEN_BACK);//�`����ʂ𗠂ɂ���
//
//		//�Q�[�����[�v
//		while (ProcessMessage() == 0) {
//			//���̓L�[�擾
//			g_OldKey = g_NowKey;
//			g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//			g_KeyFlg = g_NowKey & ~g_OldKey;
//
//			if (g_KeyFlg & PAD_INPUT_M)break;//�X�y�[�X�L�[�ŋ����I��
//			
//			ClearDrawScreen();//��ʂ̏�����
//
//			DrawRanking();//�����L���O�`�揈��
//			
//			ScreenFlip(); //����ʂ̓��e��\��ʂɔ��f
//		}
//
//	DxLib_End(); //DX���C�u�����g�p�̏I������
//	return 0; //�\�t�g�̏I��
//}
////*�����L���O�`�揈��
//void DrawRanking(void) {
//	
//	//�����L���O��ʕ\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//	
//	//�����L���O�ꗗ�\��
//	SetFontSize(30);
//	for (int i = 0; i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d  %10s  %10d",
//			g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//	//�����̕\��(�_��)
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "-- Press[SPACE]key --", 0xFF0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}
//
//
