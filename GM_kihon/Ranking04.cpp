//#include "DxLib.h"
//
////�񋓑�
//
//typedef enum MENU_MODE {
//	GAME_TITLE,
//	GAME_MAIN,
//	GAME_RANKING,
//	GAME_END,
//	INPUT_RANKING,
//	END = 99
//};
////�ϐ��̐錾
//
//int g_OldKey; //�O��̓��̓L�[
//int g_NowKey; //����̓��̓L�[
//int g_KeyFlg; //���̓L�[���
//
//int g_MenuNumber = 0; //���j���[�J�[�\���ʒu
//int g_MenuY; //���j���[�J�[�\��Y���W
//
//int g_TitleImage; //�摜�p�ϐ�
//int g_RankingImage; //�摜�p�ϐ�
//int g_EndImage; //�摜�p�ϐ�
//
//int g_WaitTime = 0; //�҂�����
//int g_PosY; //�X�N���[������Y���W
//
//int g_Score = 3500; //�X�R�A
//
//int g_GameState = GAME_TITLE; //�Q�[�����[�h
//
////�����L���O�f�[�^(�\����)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////�����L���O�f�[�^�̕ϐ��錾
//struct RankingData g_Ranking[10];
//
////�֐��̃v���g�R���^�C�v�錾
//void DrawGameTitle(void); //�Q�[���^�C�g������
//void DrawGameMain(void); //�Q�[�����C������
//void DrawEnd(void); //�Q�[���G���h����
//
//void DrawRanking(void); //�Q�[�������L���O����
//void InputRanking(void); //�����L���O����
//void SortRanking(void); //�����L���O���בւ�
//int SaveRanking(void); //�����L���O�f�[�^�̕ۑ�
//int ReadRanking(void); //�����L���O�f�[�^�ǂݍ���
//
//
////�v���O�����̊J�n
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ŋN��
//	if (DxLib_Init() == -1) return -1; //DX���C�u�����̏���������
//
//	//�^�C�g���摜�f�[�^�ǂݍ���
//	if ((g_TitleImage = LoadGraph("images/Title.bmp")) == -1) return -1;
//
//	//�����L���O�摜�f�[�^�̓ǂݍ���
//	if ((g_RankingImage = LoadGraph("images/Ranking.bmp")) == -1)return -1;
//
//	//�G���h��ʃf�[�^�ǂݍ���
//	if ((g_EndImage = LoadGraph("images/End.bmp")) == -1) return -1;
//
//	if (ReadRanking() == -1) return -1; //�����L���O�f�[�^�̓ǂݍ���
//
//	SetDrawScreen(DX_SCREEN_BACK);//�`���𗠂ɂ���
//
//	//�Q�[�����[�v
//	while (ProcessMessage() == 0 && g_GameState != END) {
//
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		ClearDrawScreen(); //��ʂ̏�����
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();//�Q�[���^�C�g������
//			break;
//		case GAME_MAIN:
//			DrawGameMain(); //�Q�[�����C������
//			break;
//		case GAME_RANKING:
//			DrawRanking(); //�Q�[�������L���O����
//			break;
//		case GAME_END:
//			DrawEnd(); //�Q�[���G���h����
//			break;
//		}
//
//		ScreenFlip(); //����ʂ̓��e��\��ʂɔ��f
//	}
//
//	DxLib_End(); //DX���C�u�����g�p�̏I������
//
//	return 0;//�\�t�g�̏I��
//}
//
////�����L���O���בւ�
//void SortRanking(void)
//{
//	int i, j;
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
////�����L���O�`�揈��
//void DrawRanking(void)
//{
//	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//
//	//�����L���O�摜�\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//�����L���O�ꗗ�\��
//	SetFontSize(30);
//	for (int i = 0;i < 10; i++) {
//		DrawFormatString(80, 170 + i * 25, 0x000000, "%2d  %10s   %10d", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	//�����̕\��(�_��)
//	if (++g_WaitTime < 30) {
//		SetFontSize(24);
//		DrawString(150, 450, "-- Press[SPACE]Key --", 0xFF0000);
//	}
//	else if (g_WaitTime > 60) {
//		g_WaitTime = 0;
//	}
//}
//
////�����L���O���͏���
//void InputRanking(void)
//{
//	//�����L���O�摜�\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//�t�H���g�T�C�Y�̐ݒ�
//	SetFontSize(20);
//
//	//���O���͎w��������̕`��
//	DrawString(150, 240, "�����L���O�ɓo�^���܂�", 0x000000);
//	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0x000000);
//
//	//���O����
//	DrawString(150, 310, ">", 0x000000);
//	DrawBox(160, 305, 300, 335, 0x000000, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, g_Ranking[9].name, FALSE) == 1) {
//		g_Ranking[9].score = g_Score; //�����L���O�f�[�^��10�ԖڂɃX�R�A��o�^
//		SortRanking(); //�����L���O���בւ�
//		SaveRanking(); //�����L���O�f�[�^�̕ۑ�
//		g_GameState = GAME_RANKING; //�Q�[�����[�h�̕ύX
//	}
//
//}
////�����L���O�f�[�^�̕ۑ�
//
//int SaveRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//�t�@�C���I�[�v��
//	if ((fp = fopen("dat/rankingdata.txt", "w")) == NULL) {
//		//�G���[����
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//�����L���O�f�[�^���z��f�[�^����������
//	for (int i = 0; i < 10; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
//
////�����L���O�f�[�^�ǂݍ���
//int ReadRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	//�t�@�C���I�[�v��
//	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL) {
//		//�G���[����
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//
//	//�����L���O�f�[�^���z��f�[�^��ǂݍ���
//	for (int i = 0; i < 10; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
////�Q�[���^�C�g���\��(���j���[���)
//
//void DrawGameTitle(void)
//{
//	//���j���[�J�[�\���ړ�����
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		if (++g_MenuNumber > 2)g_MenuNumber = 0;
//	}
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		if (--g_MenuNumber < 0)g_MenuNumber = 2;
//	}
//
//	//Z�L�[�Ń��j���[�I��
//	if (g_KeyFlg & PAD_INPUT_A)g_GameState = g_MenuNumber + 1;
//
//	//�^�C�g����ʕ\��
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	//���j���[�J�[�\��(�O�p�`)�̕\��
//	g_MenuY = g_MenuNumber * 52;
//	DrawTriangle(240, 255 + g_MenuY, 260, 270 + g_MenuY, 240, 285 + g_MenuY, GetColor(255, 0, 0), TRUE);
//}
////�Q�[�����C��
//void DrawGameMain(void)
//{
//	//�����L���O����
//	InputRanking();
//}
////�Q�[���G���h����(�G���h���[��)
//
//void DrawEnd(void)
//{
//	//�G���h�摜�\��
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	//�G���f�B���O�\��
//	if (++g_WaitTime < 600)g_PosY = 300 - g_WaitTime / 2;
//
//	SetFontSize(24);
//	DrawString(110, 170 + g_PosY, "�^�C�g���@�@�Z�Z�Z�@Game", 0x000000);
//	DrawString(110, 200 + g_PosY, "�o�[�W�����@�@2.0", 0x000000);
//	DrawString(110, 230 + g_PosY, "�ŐV�X�V���@2018�N07��01��", 0x000000);
//	DrawString(110, 260 + g_PosY, "����ҁ@�@���ۓd�q�r�W�l�X���w�Z", 0x000000);
//	DrawString(110, 290 + g_PosY, "���ہ@���Y", 0x000000);
//	DrawString(110, 310 + g_PosY, "�f�ޗ��p", 0x000000);
//	DrawString(110, 340 + g_PosY, "BGM      ������", 0x000000);
//	DrawString(110, 365 + g_PosY, "SE   �����뉀", 0x000000);
//
//	//�^�C���̉��Z����&�I��
//	if (++g_WaitTime > 900)g_GameState = END;
//}
