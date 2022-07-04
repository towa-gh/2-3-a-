///***********************************************
// ** �@��6�́@�~�j�Q�[��������(3)
// **�@�@�@�@�@�@�@�{�����X(�e�g���X)
// ***********************************************/
//#include "DxLib.h"
//#include<math.h>
// /***********************************************
//  *�񋓑̂̐錾
//  ***********************************************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_RANKING,
//	GAME_END,
//	GAME_MAIN,
//	GAME_OVER,
//	INPUT_RANKING,
//	END=99
//};
// /***********************************************
//  *�ϐ��錾
//  ***********************************************/
//int g_OldKey;//�O��̓��̓L�[
//int g_NowKey;//����̓��̓L�[
//int g_KeyFlg;//���̓L�[���
//
//int g_GameState = GAME_TITLE;//�Q�[�����[�h
//
//int g_TitleImage;//�^�C�g���摜
//
//int g_Score = 0;//�X�R�A
//int g_RankingImage;//�摜�p�ϐ�
//
//int g_WaitTime = 0;//�҂�����
//int g_EndImage;
//
//int g_StageImage;//�X�e�[�W�摜
//
//int g_GameOverImage;//�Q�[���I�[�o�[�摜
//
//const int HEIGHT = 21;
//const int WIDTH = 12;
//const int BLOCKSIZE = 24;
//
//int g_BlockImage[10];//�u���b�N�摜
////�u���b�N�z��
//int g_Field[HEIGHT][WIDTH];//�X�e�[�W�p
//
//int g_Block[4][4] = { 0 };//�V�����u���b�N�p
//int g_Next[4][4] = { 0 };//���̃u���b�N�p
//int g_Stock[4][4] = { 0 };//�X�g�b�N�̃u���b�N�p
//int g_StockFlg = 0;//�X�g�b�N�̃t���O
//
//int g_Blocklist[7][4][4] = {
//	{
//		{0,0,0,0},
//        {0,1,1,0},
//	    {0,1,1,0},
//	    {0,0,0,0},
//},
//    {
//		{0,0,0,0},
//	    {0,0,0,0},
//	    {2,2,2,2},
//	    {0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{1,0,0,0},
//		{1,1,1,0},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,0,0,2},
//		{0,2,2,2},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,1,1,0},
//		{0,0,1,1},
//		{0,0,0,0},
//},
//{
//		{0,0,0,0},
//		{0,2,2,0},
//		{2,2,0,0},
//		{0,0,0,0},
//},
//	{
//		{0,0,0,0},
//	    {0,7,0,0},
//	    {7,7,7,0},
//	    {0,0,0,0},
//}
//
//
//};
//int g_x = 6;//�ړ��\�u���b�N(x)
//int g_y = 0;//�ړ��\�u���b�N(y)
//
//int g_NumberImage[10];//�����摜
//
//int g_Level;//���x���A�b�v
//int g_Speed[5] = { 50,40,30,20,10 };//�����X�s�[�h�z��
////int g_Speed = 60;//�����X�s�[�h
//
//int g_BomCnt;//�{���c��
//int g_BomFlg;
//int g_BomX, g_BomY;
//int g_BomImg;
//int g_BomAddScore;
//const int BOM_ADD_SCORE = 5000;
//
//int g_TitleBGM;
//int g_stageBGM;
//int g_GameOverSE;
//int g_SE1;
//int g_SE2;
//int g_SE3;
//int g_SE4;
//int g_SE5;
//
// /***********************************************
//  *�萔�̐錾
//  ***********************************************/
//const int RANK_MAX = 5;
//
//
///***********************************************
// *�\���̂̐錾
// ***********************************************/
////�����L���O�f�[�^(�\����)
//struct RankingData {
//	int no;
//	char name[11];
//	long score;
//};
////�����L���O�f�[�^�ϐ��錾
//struct RankingData g_Ranking[RANK_MAX];
//
///***********************************************
// *�֐��̃v���g�^�C�v�錾
// ***********************************************/
//void GameInit(void);//�Q�[������������
//void GameMain(void);//�Q�[�����C������
//
//void DrawGameTitle(void);//�Q�[���^�C�g���`�揈��
//void DrawGameOver(void);//�Q�[���I�[�o�[�摜�`�揈��
//void DrawEnd(void);//�Q�[���G���h�`�揈��
//
//void DrawRanking(void);//�����L���O�`�揈��
//void InputRanking(void);//�����L���O����
//
//int LoadImages();  //�摜�ǂݍ���
//
//void SortRanking(void);//�����L���O���בւ�
//int SaveRanking(void);//�����L���O�f�[�^�̕ۑ�
//int ReadRanking(void);//�����L���O�f�[�^�̓ǂݍ���
//
//void BlockInit(void);
//void DrawStage(void);
//
//void CreateBlock(void);//�u���b�N������Next�u���b�N�̈ړ�
//
//void ControlBlock(void);//�u���b�N�̈ړ�����
//
//int CheckOverlap(int x2, int y2);//�u���b�N�̈ړ��\�`�F�b�N����
//
//void TurnBlock(void);//�u���b�N�̉�]����
//
//void LockBlock(int x2, int y2);//���n�����u���b�N���Œ�ς݃u���b�N�ɉ�����
//
//void CheckLines(void);//�u���b�N�������ɂȂ�Ώ����A��̃u���b�N�����낷
//
//void ChangeBlock(void);//�u���b�N�̌�������
//
//void BomStage(void);//�{���̈ړ�����
//
//int LoadSounds();
//
///***********************************************
// *�v���O�����̊J�n
// ***********************************************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
//	LPSTR lpCmdLine, int nCmdShow) {
//
//	SetMainWindowText("�{ �� �� �X");//�^�C�g����ݒ�
//	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ŋN��
//	if (DxLib_Init() == -1)return -1;//DX���C�u�����̏���������
//	SetDrawScreen(DX_SCREEN_BACK);//�`����ʂ𗠂ɂ���
//	if (LoadImages() == -1)return -1;//�摜�ǂݍ��݊֐����Ăяo��
//	if (LoadSounds() == -1)return -1;//�T�E���h�ǂݍ��݊֐����Ăяo��
//	if (ReadRanking() == -1) return -1;//�����L���O�f�[�^�̓ǂݍ���
//
//	while (ProcessMessage() == 0 && g_GameState != 99 && !(g_KeyFlg & PAD_INPUT_START)) {
//		// ���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetJoypadInputState(DX_INPUT_KEY_PAD1);
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//		ClearDrawScreen();//�摜�̏�����
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle();	//�Q�[���^�C�g���`�揈��
//			break;
//		case GAME_INIT:
//			GameInit();		//�Q�[����������
//			break;
//		case GAME_RANKING:
//			DrawRanking();	//�����L���O�`�揈��
//			break;
//		case GAME_END:
//			DrawEnd();		//�G���h�`�揈��
//			break;
//		case GAME_MAIN:
//			GameMain();     //�Q�[�����C������
//			break;
//		case GAME_OVER:
//			DrawGameOver(); //�Q�[���I�[�o�[�`�揈��
//			break;
//		case INPUT_RANKING:
//			InputRanking(); //�����L���O���͏���
//			break;
//		}
//		ScreenFlip();     //����ʂ̓��e��\��ʂɔ��f
//	}
//	DxLib_End();
//
//	return 0;
//}
///***********************************************
// *�Q�[���^�C�g���`�揈��(���j���[���)
// ***********************************************/
//void DrawGameTitle(void) {
//	static int MenuNo = 0;
//	int PosY;
//	PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_BACK, FALSE);
//
//	//���j���[�J�[�\���ړ�����
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		PlaySoundMem(g_SE1, DX_PLAYTYPE_BACK, TRUE);
//		if (++MenuNo > 2)MenuNo = 0;
//	}
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		PlaySoundMem(g_SE1, DX_PLAYTYPE_BACK, TRUE);
//		if (--MenuNo < 0)MenuNo = 2;
//	}
//	//Z�L�[�Ń��j���[�I��
//	if (g_KeyFlg & PAD_INPUT_A) {
//		StopSoundMem(g_TitleBGM);
//		PlaySoundMem(g_SE2, DX_PLAYTYPE_BACK, TRUE);
//		g_GameState = MenuNo + 1;
//	}
//	//�^�C�g���摜�\��
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//	
//	//���j���[�J�[�\��(�O�p�`)�̕\��
//	PosY = MenuNo * 45;
//	DrawTriangle(140, 210 + PosY, 170, 230 + PosY, 140, 250 + PosY, GetColor(255, 0, 0), TRUE);
//}
///***********************************************
// *�Q�[����������
// ***********************************************/
//void GameInit(void){
//	//�Q�[�����C��������
//	g_GameState = GAME_MAIN;
//	//�X�R�A�̏�����
//	g_Score = 0;
//	//�X�e�[�W�p�z��̏�����
//	BlockInit();
//
//	//�u���b�N������Next�u���b�N�̈ړ�
//	CreateBlock();
//	CreateBlock();
//
//	//���x���̏�����
//	g_Level = 1;
//
//	//�{���c���̏�����
//	g_BomCnt = 3;
//	//�{���g�p�t���O
//	g_BomFlg = 0;
//	//�{���ǉ��X�R�A
//	g_BomAddScore = BOM_ADD_SCORE;
//}
///***********************************************
// * �����L���O���͏���
// ***********************************************/
//void InputRanking(void)
//{
//	//�����L���O�摜�\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	// �t�H���g�T�C�Y�̐ݒ�
//	SetFontSize(16);
//
//	// ���O���͎w��������̕`��
//	DrawString(80,150,"�����L���O�ɓo�^���܂�", 0xFFFF00);
//	DrawString(80,170, "���O���p���œ��͂��Ă�������", 0xFFFF00);
//
//	// ���O�̓���
//	DrawString(80, 200, "> ", 0xFFFF00);
//	DrawBox(90, 195, 200, 220, 0xFFFF00, FALSE);
//	if (KeyInputSingleCharString(90, 200, 10, g_Ranking[RANK_MAX - 1].name, FALSE) == 1) {
//		g_Ranking[RANK_MAX - 1].score = g_Score;	// �����L���O�f�[�^��5�ԖڂɃX�R�A��o�^
//		SortRanking();		// �����L���O���בւ�
//		SaveRanking();		// �����L���O�f�[�^�̕ۑ�
//		g_GameState = GAME_RANKING;		// �Q�[�����[�h�̕ύX
//	}
//}
///***********************************************
// * �����L���O���בւ�
// ***********************************************/
//void SortRanking(void)
//{
//	int i, j;
//	RankingData work;
//	// �I��@�\�[�g
//	for (int i = 0; i < RANK_MAX-1; i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score <= g_Ranking[i].score) {
//				work = g_Ranking[i];
//				g_Ranking[i] = g_Ranking[j];
//				g_Ranking[j] = work;
//			}
//		}
//	}
//	// ���ʕt��
//	for (int i = 0; i < RANK_MAX; i++) {
//		g_Ranking[i].no = 1;
//	}
//	// ���_�������ꍇ�́A�������ʂƂ���
//	// �����ʂ��������ꍇ�̎��̏��ʂ̓f�[�^�������Z���ꂽ���ʂƂ���
//	for (int i = 0; i < RANK_MAX-1; i++) {
//		for (int j = i + 1; j < RANK_MAX; j++) {
//			if (g_Ranking[i].score > g_Ranking[j].score) {
//				g_Ranking[j].no++;
//			}
//		}
//	}
//}
///***********************************************
// * �����L���O�f�[�^�̕ۑ�
// ***********************************************/
//int  SaveRanking(void)
//{
//	FILE* fp;
//#pragma warning(disable:4996)
//
//	// �t�@�C���I�[�v��
//	if ((fp = fopen("dat/chapter5/rankingdata.txt", "w")) == NULL) {
//		/* �G���[���� */
//		printf("Ranking Data Error\n");
//		return -1;
//	}
//	// �����L���O�f�[�^���z��f�[�^����������
//	for (int i = 0; i < RANK_MAX; i++) {
//		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
//	}
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
///*************************************
// * �����L���O�f�[�^�ǂݍ���
// *************************************/
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
//	//�����L���O�f�[�^�z����f�[�^��ǂݍ���
//	for (int i = 0; i < RANK_MAX; i++) {
//		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//	//�t�@�C���N���[�Y
//	fclose(fp);
//
//	return 0;
//}
///***********************************************
//*�Q�[�������L���O�`�揈��
//***********************************************/
//void DrawRanking(void) {
//	//�X�y�[�X�Ń��j���[�ɖ߂�
//	if (g_KeyFlg & PAD_INPUT_M)g_GameState = GAME_TITLE;
//	//�����L���O�摜�\��
//	DrawGraph(0, 0, g_RankingImage, FALSE);
//
//	//�����L���O�ꗗ��\��
//	SetFontSize(18);
//	for (int i = 0; i < RANK_MAX; i++) {
//		DrawFormatString(50, 170 + i * 25, 0xffffff, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name, &g_Ranking[i].score);
//	}
//	DrawString(100, 450, "---�X�y�[�X�L�[�������ă^�C�g���ɖ߂�---", 0xffffff, 0);
//
//}
///***********************************************
// * �Q�[���G���h����
// ***********************************************/
//void DrawEnd(void) {
//	//�G���h�摜�\��
//	DrawGraph(0, 0, g_EndImage, FALSE);
//
//	SetFontSize(24);
//	DrawString(360, 480 - 24, "Thank you for Playing", 0xffffff, 0);
//
//	//�^�C���̉��Z�������I��
//	if (++g_WaitTime > 180)g_GameState = END;
//}
///***********************************************
// * �Q�[�����C��
// ***********************************************/
//void GameMain(void) {
//	//�X�e�[�W�摜�\��
//	DrawGraph(0, 0, g_StageImage, FALSE);
//
//	//�u���b�N�`��
//	DrawStage();
//
//	//�u���b�N�̈ړ�����
//	ControlBlock();
//
//	PlaySoundMem(g_stageBGM, DX_PLAYTYPE_BACK, FALSE);
//
//	if (g_BomFlg == 0) {
//		//��������
//		g_WaitTime++;
//		if (g_WaitTime > g_Speed[g_Level - 1]) {
//			if (CheckOverlap(g_x, g_y + 1) == 0) {
//				g_y++;
//			}
//			else {
//				//�u���b�N�̌Œ�
//				LockBlock(g_x, g_y);
//				//�u���b�N�̏������u���b�N�����낷����
//				CheckLines();
//				//�V�����u���b�N�쐬
//				CreateBlock();
//				//���x���A�b�v���f����
//				if (g_Score / 1000 > g_Level && g_Level < 5) {
//					g_Level++;
//				}
//			}
//			//���ԊǗ��ϐ��̏�����
//			g_WaitTime = 0;
//		}
//	}
//	else {
//		BomStage();
//	}
//}
///***********************************************
//*�Q�[���I�[�o�[�`�揈��
//***********************************************/
//void DrawGameOver(void) {
//	//�Q�[���I�[�o�[�摜�\��
//	DrawGraph(0, 0, g_GameOverImage, FALSE);
//
//	PlaySoundMem(g_GameOverSE, DX_PLAYTYPE_BACK, FALSE);
//
//	//�X�y�[�X�L�[�Ń��j���[�ɖ߂�
//	if (g_KeyFlg & PAD_INPUT_M) {
//		if (g_Ranking[RANK_MAX].score >= g_Score) {
//			g_GameState = GAME_TITLE;
//		}
//		else {
//			g_GameState = INPUT_RANKING;
//		}
//	}
//	DrawString(150, 450, "---�X�y�[�X�L�[�������ă^�C�g���֖߂�---", 0xffffff, 0);
//}
///***********************************************
// * �u���b�N�z��̏�����
// ***********************************************/
//void BlockInit(void) {
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1) {
//				g_Field[i][j] = 9;
//			}
//			else {
//				g_Field[i][j] = 0;
//			}
//		}
//	}
//}
///***********************************************
// * �X�e�[�W�Ƀu���b�N��`��
// ***********************************************/
//void DrawStage(void) {
//	int PosX, TmpScore;
//	//���x���\��
//	DrawGraph(400, 140, g_NumberImage[g_Level], TRUE);
//
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Field[i][j] != 9) {
//				DrawGraph(BLOCKSIZE * j, BLOCKSIZE * i, g_BlockImage[g_Field[i][j]], TRUE);
//			}
//		}
//	}
//	//�ړ��\�u���b�N��`��
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				DrawGraph(BLOCKSIZE * (j+g_x), BLOCKSIZE * (i+g_y), g_BlockImage[g_Block[i][j]], TRUE);
//			}
//		}
//	}
//	//Next�u���b�N��`��
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			DrawGraph(BLOCKSIZE * j + 480, BLOCKSIZE * i + 350, g_BlockImage[g_Next[i][j]], TRUE);
//			DrawGraph(BLOCKSIZE * j + 360, BLOCKSIZE * i + 240, g_BlockImage[g_Stock[i][j]], TRUE);
//		}
//	}
//
//	PosX = 600;
//	TmpScore = g_Score;
//	do {
//		DrawGraph(PosX, 30, g_NumberImage[TmpScore % 10], TRUE);
//		TmpScore /= 10;
//		PosX -= 30;
//	} while (TmpScore > 0);
//	for (int i = 0; i < g_BomCnt; i++) {
//		DrawGraph(40 * i + 440, 440, g_BomImg, TRUE);
//	}
//}
///***********************************************
// * �u���b�N������Next�u���b�N�̈ړ�
// ***********************************************/
//void CreateBlock(void) {
//	//�����_���I��
//	int r = GetRand(6);
//
//	//�V�����u���b�N���Z�b�g�����̃u���b�N�̈ړ�
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			g_Block[i][j] = g_Next[i][j];
//			g_Next[i][j] = g_Blocklist[r][i][j];
//		}
//	}
//	//�V�����u���b�N�̏o���ʒu���Z�b�g
//	g_x = 4;
//	g_y = -1;
//
//	if (CheckOverlap(g_x, g_y) != 0) {
//		g_GameState = GAME_OVER;
//		StopSoundMem(g_stageBGM);
//	}
//}
///***********************************************
// * �u���b�N�̃L�[�ړ�����
// ***********************************************/
//void ControlBlock(void) {
//	//�L�[����͂����獶�ړ�
//	if (g_KeyFlg & PAD_INPUT_LEFT) {
//		if (CheckOverlap(g_x - 1, g_y) == 0) {
//			g_x--;
//		}
//	}
//	//�L�[����͂�����E�ړ�
//	if (g_KeyFlg & PAD_INPUT_RIGHT) {
//		if (CheckOverlap(g_x + 1, g_y) == 0) {
//			g_x++;
//		}
//	}
//	//�L�[����͂����炵���ړ�
//	if (g_NowKey & PAD_INPUT_DOWN) {
//		if (CheckOverlap(g_x, g_y + 1) == 0) {
//			PlaySoundMem(g_SE4, DX_PLAYTYPE_BACK, TRUE);
//			g_y++;
//			WaitTimer(60);
//		}
//	}
//	//���L�[����͂�����E�ɉ�]
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		PlaySoundMem(g_SE5, DX_PLAYTYPE_BACK, TRUE);
//		TurnBlock();
//	}
//	//Z�L�[����͂�����u���b�N�̌���
//	if (g_KeyFlg & PAD_INPUT_A) {
//		ChangeBlock();
//	}
//	//X�L�[����͂�����{�����g�p����
//	if (g_KeyFlg & PAD_INPUT_B && g_BomCnt > 0 && g_BomFlg == 0) {
//		g_BomCnt--;
//		g_BomFlg = 1;
//		g_BomX = WIDTH / 2 - 1;
//		g_BomY = HEIGHT / 2 - 1;
//	}
//}
///***********************************************
// * �u���b�N�̈ړ��\�`�F�b�N����
// ***********************************************/
//int CheckOverlap(int x2, int y2) {
//	int i, j;
//	//�ڐG�̊m�F
//	for (i = 0; i < 4; i++) {
//		for (j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				if (g_Field[y2 + i][x2 + j] != 0) {
//					return 1;
//				}
//			}
//		}
//	}
//	return 0;
//}
///***********************************************
// * �u���b�N�̉�]����
// ***********************************************/
//void TurnBlock(void) {
//	int Temp[4][4] = { 0 };
//
//	do {
//
//		//�u���b�N�ꎞ�ێ�
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				Temp[j][3 - i] = g_Block[i][j];
//			}
//		}
//		//�u���b�N��]
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				g_Block[i][j] = Temp[i][j];
//			}
//		}
//		//�Ǒ��̕␳����
//		if (CheckOverlap(g_x, g_y) == 1 && g_x >= 9)g_x--;
//		if (CheckOverlap(g_x, g_y) == 1 && g_x <= 0)g_x++;
//	} while (CheckOverlap(g_x, g_y) == 1);
//}
///***********************************************
// * ���n�����u���b�N���Œ�ς݃u���b�N��������
// ***********************************************/
//void LockBlock(int x2, int y2) {
//	PlaySoundMem(g_SE4, DX_PLAYTYPE_BACK, TRUE);
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			if (g_Block[i][j] != 0) {
//				g_Field[y2 + i][x2 + j] = g_Block[i][j];
//			}
//		}
//	}
//}
///***********************************************
// * �u���b�N�������ɂȂ�Ώ����A��̃u���b�N�����낷
// ***********************************************/
//void CheckLines(void) {
//	int Linecnt = 0, Flg;
//
//	//�u���b�N������񂾂�����t���O0
//	for (int i = 0; i < HEIGHT - 1; i++) {
//		Flg = 0;
//		//�u���b�N������񂶂�Ȃ���΃t���O1
//		for (int j = 1; j < WIDTH - 1; j++) {
//			if (g_Field[i][j] == 0) {
//				Flg = 1;
//				break;
//			}
//		}
//		//�t���O��0�Ȃ���Z
//		if (Flg == 0) {
//			Linecnt++;
//			//�Œ�ς݃u���b�N�����낷
//			for (int k = i; k > 0; k--) {
//				for (int j = 1; j < WIDTH - 1; j++) {
//					g_Field[k][j] = g_Field[k - 1][j];
//				}
//				PlaySoundMem(g_SE3, DX_PLAYTYPE_BACK, TRUE);
//			}
//			g_Score += 1000;
//		}
//	}
//	//�X�R�A���Z����
//	if (Linecnt != 0) {
//		g_Score += (long)(100 * pow(2.0, (Linecnt - 1.0)));
//		if (g_Score > g_BomAddScore) {
//			if (g_BomCnt < 5)g_BomCnt++;
//			g_BomAddScore += BOM_ADD_SCORE;
//		}
//	}
//}
///***********************************************
// * �u���b�N�̌�������
// ***********************************************/
//void ChangeBlock(void) {
//	int Temp[4][4] = { 0 };
//	if (g_StockFlg == 0) {
//		g_StockFlg = 1;
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				g_Stock[i][j] = g_Block[i][j];
//			}
//		}
//		//�V�����u���b�N�̃Z�b�g�A�b�v�����̃u���b�N�𐶐�
//		CreateBlock();
//	}
//	else {
//		//�u���b�N�̌���
//		for (int i = 0; i < 4; i++) {
//			for (int j = 0; j < 4; j++) {
//				Temp[i][j] = g_Block[i][j];
//				g_Block[i][j] = g_Stock[i][j];
//				g_Stock[i][j] = Temp[i][j];
//			}
//		}
//	}
//}
///***********************************************
// * �{���̈ړ�����
// ***********************************************/
//void BomStage(void) {
//	DrawGraph(BLOCKSIZE * g_BomX + 4, BLOCKSIZE * g_BomY + 4, g_BomImg, TRUE);
//	//�L�[����͂����獶�ړ�
//	if (g_KeyFlg & PAD_INPUT_LEFT) {
//		if (g_BomX > 1)g_BomX--;
//	}
//	//�L�[����͂�����E�ړ�
//	if (g_KeyFlg & PAD_INPUT_RIGHT) {
//		if (g_BomX < WIDTH - 3)g_BomX++;
//	}
//	//�L�[����͂����牺�ړ�
//	if (g_KeyFlg & PAD_INPUT_DOWN) {
//		if (g_BomY < HEIGHT - 3)g_BomY++;
//	}
//	//�L�[����͂������ړ�
//	if (g_KeyFlg & PAD_INPUT_UP) {
//		if (g_BomY > 0)g_BomY--;
//	}
//	//Z�L�[����͂�����u���b�N�̌���
//	if (g_KeyFlg & PAD_INPUT_C) {
//		g_BomFlg = 0;
//		g_Field[g_BomY][g_BomX] = 0;
//		g_Field[g_BomY][g_BomX + 1] = 0;
//		g_Field[g_BomY + 1][g_BomX] = 0;
//		g_Field[g_BomY + 1][g_BomX + 1] = 0;
//	}
//}
///***********************************************
// * �T�E���h�ǂݍ���
// ***********************************************/
//int LoadSounds() {
//	//�^�C�g��BGM�f�[�^�̓ǂݍ���
//	if ((g_TitleBGM = LoadSoundMem("sounds/BGM041.ogg")) == -1) return -1;
//
//	//�X�e�[�WBGM�f�[�^�̓ǂݍ���
//	if ((g_stageBGM = LoadSoundMem("sounds/BGM017.ogg")) == -1) return -1;
//
//	//�Q�[���I�[�o�[���f�[�^�̓ǂݍ���
//	if ((g_GameOverSE = LoadSoundMem("sounds/GameOver.mp3")) == -1) return -1;
//
//	//SE1 �f�[�^�̓ǂݍ���
//	if ((g_SE1 = LoadSoundMem("sounds/SE1.mp3")) == -1) return -1;
//
//	//SE2 �f�[�^�̓ǂݍ���
//	if ((g_SE2 = LoadSoundMem("sounds/SE2.mp3")) == -1) return -1;
//
//	//SE3 �f�[�^�̓ǂݍ���
//	if ((g_SE3 = LoadSoundMem("sounds/SE3.mp3")) == -1) return -1;
//
//	//SE4 �f�[�^�̓ǂݍ���
//	if ((g_SE4 = LoadSoundMem("sounds/SE6.mp3")) == -1) return -1;
//
//	//SE5 �f�[�^�̓ǂݍ���
//	if ((g_SE5 = LoadSoundMem("sounds/SE5.wav")) == -1) return -1;
//
//	//SE�̉��ʒ���
//	ChangeVolumeSoundMem(80, g_SE2);
//	ChangeVolumeSoundMem(150, g_SE3);
//	ChangeVolumeSoundMem(120, g_SE1);
//	ChangeVolumeSoundMem(150, g_SE4);
//	ChangeVolumeSoundMem(130, g_SE5);
//}
//
//
///***********************************************
//*�摜�ǂݍ���
//***********************************************/
//int LoadImages() {
//	//�^�C�g��
//	if ((g_TitleImage = LoadGraph("images/chapter6/Title.bmp")) == -1)return -1;
//
//	//�����L���O
//	if ((g_RankingImage = LoadGraph("images/chapter6/ranking.bmp")) == -1)return -1;
//
//	//�G���h�摜�̓ǂݍ���
//	if ((g_EndImage = LoadGraph("images/chapter6/end.bmp")) == -1)return -1;
//
//	//�X�e�[�W�摜�̓ǂݍ���
//	if ((g_StageImage = LoadGraph("images/chapter6/stage.bmp")) == -1)return -1;
//
//	//�Q�[���I�[�o�[�摜�̓ǂݍ���
//	if ((g_GameOverImage = LoadGraph("images/chapter6/GameOver.bmp")) == -1)return -1;
//
//	//�u���b�N�摜�̓ǂݍ���
//	if (LoadDivGraph("images/chapter6/block.bmp", 10, 10, 1, 24, 24, g_BlockImage) == -1) return -1;
//
//	//�����摜�ǂݍ���
//	if (LoadDivGraph("images/chapter6/number.bmp", 10, 10, 1, 24, 37, g_NumberImage) == -1) return -1;
//
//	if (LoadDivGraph("images/chapter6/number.bmp", 10, 10, 1, 24, 37, g_NumberImage) == -1) {
//		return -1;
//	}
//	//�{���摜�̓ǂݍ���
//	if ((g_BomImg = LoadGraph("images/chapter6/bom.bmp")) == -1)return -1;
//
//	return 0;
//}