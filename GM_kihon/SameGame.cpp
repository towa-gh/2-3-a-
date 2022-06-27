//#include "DxLib.h"
//
///*****************/
///*�񋓑̂̐錾*/
///*****************/
//typedef enum GAME_MODE {
//	GAME_TITLE,
//	GAME_INIT,
//	GAME_END,
//	GAME_MAIN,
//	GAME_CLEAR,
//	GAME_OVER,
//	END = 99
//};
//
///******************/
///*�ϐ��̐錾*/
///******************/
//int g_OldKey; //�O��̓��̓L�[
//int g_NowKey; //����̓��̓L�[
//int g_KeyFlg; //���̓L�[���
//int g_MouseX; //�}�E�XX���W
//int g_MouseY; //�}�E�XY���W
//
//int g_GameState = GAME_TITLE; //�Q�[�����[�h
//
//int g_TitleImage; //�^�C�g���摜
//
//int g_StageImage; //�X�e�[�W�摜
//
//int g_Count; //�u���b�N���N���b�N�����J�E���g
//
//int g_GameClearImage; //�Q�[���N���A�摜
//int g_GameOverImage; //�Q�[���I�[�o�[�摜
//
//int g_BlockImage[5]; //�u���b�N�摜
//
//int g_Rensa; //�u���b�N�̘A�����J�E���g
//
//int g_Status; //�X�e�[�W�̃X�e�[�^�X(0..�v���C���[���쒆�A1..�u���b�N����)
//
//int g_Color = 2; //�u���b�N�̐F�̐�
//
//int g_StartTime; //�X�^�[�g����
//
//
////�T�E���h�p�ϐ�
//int g_TitleBGM; //�^�C�g��BGM
//int g_GameClearSE; //�Q�[���N���A
//int g_GameOverSE; //�Q�[���I�[�o�[
//int g_ClickSE; //�}�E�X�N���b�N���ʉ�
//int g_FadeOutSE; //�u���b�N�������ʉ�
//int g_MoveBlockSE; //�u���b�N�ړ������ʉ�
//
///******************/
///*�萔�̐錾*/
///******************/
//const  int HEIGHT = 22; 
//const  int WIDTH = 22; 
//const  int BLOCKSIZE = 24; 
//const  int MARGIN = 160; 
//const  int BLOCKMAX = 4;
//const  int TIMELIMIT = 60000;
//
///******************/
///*�\���̂̐錾*/
///******************/
//struct Object
//{
//	int flg; //�t���O(0:�\�����Ȃ��@,1:�\��)
//	int x, y; //���Wx,y
//	int w, h; //��w ����h
//	int image; //�摜
//	int backup; //�摜�o�b�N�A�b�v
//};
//struct Object g_Block[HEIGHT][WIDTH];
//
//
//
///************************/
///*�֐��̃v���g�^�C�v�錾*/
///************************/
//void GameInit(void); //�Q�[������������
//void GameMain(void); //�Q�[�����C������
//void DrawGameTitle(void); //�Q�[���^�C�g������
//void DrawEnd(void); //�Q�[���G���h����
//void DrawGameClear(void); //�Q�[���N���A����
//void DrawGameOver(void); //�Q�[���I�[�o�[����
//
//int LoadImages(void); //�摜�ǂݍ���
//
//int LoadSounds(void); //BGM�ǂݍ���
//
//void DrawStage(void); //Block[][]�̒��g�ŁA�摜��`��
//void EraseBlock(void); //Block������
//
//int RensaCheck(int y, int x, int* cnt); //�u���b�N�̘A���`�F�b�N
//
//void MoveBlock(void); //�u���b�N�ړ�
//
//void SaveBlock(void); //�u���b�N���o�b�N�A�b�v����
//void RestoreBlock(void); //�o�b�N�A�b�v�u���b�N��߂�
//
///******************/
///*�v���O�����̊J�n*/
///******************/
//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPevInstance, LPSTR lpCmdLine, int nCmdShow)
//{
//	SetMainWindowText("SameGame(���߂���)"); //�^�C�g����ݒ�
//	ChangeWindowMode(TRUE); //�E�B���h�E���[�h�ŋN��
//	if (DxLib_Init() == -1)return -1; //DX���C�u�����̏���������
//	SetDrawScreen(DX_SCREEN_BACK); //�`����ʂ𗠂ɂ���
//
//	if (LoadImages() == -1)return -1; //��ʓǍ��݊֐��Ăяo��
//
//	if (LoadSounds() == -1)return -1; //�T�E���h�Ǎ��݊֐��Ăяo��
//
//	//�Q�[�����[�v
//	while (ProcessMessage() == 0 && g_GameState != END && !(g_KeyFlg & PAD_INPUT_START)) {
//
//		//���̓L�[�擾
//		g_OldKey = g_NowKey;
//		g_NowKey = GetMouseInput();
//		g_KeyFlg = g_NowKey & ~g_OldKey;
//
//		//�}�E�X�̈ʒu���擾
//		GetMousePoint(&g_MouseX, &g_MouseY);
//
//		ClearDrawScreen(); //��ʂ̏�����
//
//		switch (g_GameState) {
//		case GAME_TITLE:
//			DrawGameTitle(); //�Q�[���^�C�g������
//			break;
//		case GAME_INIT:  //�Q�[����������
//			GameInit();
//			break;
//		case GAME_END: //�Q�[���G���h����
//			DrawEnd();
//			break;
//		case GAME_MAIN: //�Q�[�����C������
//			GameMain();
//			break;
//		case GAME_CLEAR://�Q�[���N���A����
//			DrawGameClear();
//			break;
//		case GAME_OVER:
//			DrawGameOver();//�Q�[���I�[�o�[����
//			break;
//		
//		}
//
//		ScreenFlip(); //DX���C�u�����g�p�̏I������
//	}
//
//	DxLib_End(); //DX���C�u�����g�p�̏I������
//
//	return 0; //�\�t�g�̏I��
//}
//
///*************************************/
///*�Q�[���^�C�g���\���i���j���[��ʁj*/
///************************************/
//void DrawGameTitle(void) {
//	
//	//�^�C�g��BGM���X�^�[�g
//	if(CheckSoundMem(g_TitleBGM) == 0){
//		PlaySoundMem(g_TitleBGM, DX_PLAYTYPE_BACK);
//	}
//	
//	//�^�C�g���摜�\��
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	//�Q�[�����[�h��؂�ւ���
//	if (g_KeyFlg & MOUSE_INPUT_LEFT) {
//		if (g_MouseX > 120 && g_MouseX < 290 && g_MouseY > 260 && g_MouseY < 315) {
//			g_GameState = GAME_INIT; //�Q�[���X�^�[�g�̑I��
//			StopSoundMem(g_TitleBGM); //�^�C�g��BGM���X�g�b�v
//		}
//		else if (g_MouseX > 120 && g_MouseX < 220 && g_MouseY > 345 && g_MouseY < 400) {
//			g_GameState = GAME_END; //�Q�[���G���h�̑I��
//			StopSoundMem(g_TitleBGM); //�^�C�g��BGM���X�g�b�v
//		}
//	}
//	else if (g_KeyFlg & MOUSE_INPUT_RIGHT) {
//		if (++g_Color > BLOCKMAX)g_Color = 2;
//	}
//
//	SetFontSize(64);
//	DrawFormatString(340, 260, 0xffffff, "Color:%d", g_Color);
//}
//
///********************/
///*�Q�[����������*/
///********************/
//void GameInit(void) {
//
//	//�Q�[�����C��������
//	g_GameState = GAME_MAIN;
//
//	//�J�E���g�̏�����
//	g_Count = 0;
//
//	//�X�e�[�W�X�e�[�^�X�̏�����
//	g_Status = 0;
//
//	//���݌o�ߎ��Ԃ𓾂�
//	g_StartTime = GetNowCount();
//
//	//�u���b�N��������
//	for (int i = 0; i < HEIGHT;i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (j == 0 || j == WIDTH - 1 || i == HEIGHT - 1 || i == 0) {
//				g_Block[i][j].flg = 0;
//				g_Block[i][j].image = 0;
//			}
//			else {
//				g_Block[i][j].flg = 1;
//				g_Block[i][j].x = (j - 1) * BLOCKSIZE + MARGIN;
//				g_Block[i][j].y = (i - 1) * BLOCKSIZE;
//				g_Block[i][j].w = BLOCKSIZE;
//				g_Block[i][j].h = BLOCKSIZE;
//				g_Block[i][j].image = GetRand(g_Color - 1) + 1;
//			}
//		}
//	}
//}
///********************/
///*�G���h�`�揈��*/
///********************/
//void DrawEnd(void) {
//
//	static int WaitTime = 0;
//
//	//�^�C�g���摜�\��
//	DrawGraph(0, 0, g_TitleImage, FALSE);
//
//	SetFontSize(24);
//	DrawString(360, 480 - 24, "Thank you for Playing", 0x003333, 0);
//
//	//�^�C���̉��Z�������I���i�R�b��j
//	if (++WaitTime > 180)g_GameState = END;
//}
//
///***************************************************/
///*��������u���b�N���t�F�[�h�A�E�g����
///***************************************************/
//void FadeOutBlock(void)
//{
//	//�t�F�[�h�A�E�g�r�d���X�^�[�g
//	if (CheckSoundMem(g_FadeOutSE) == 0) {
//		PlaySoundMem(g_FadeOutSE, DX_PLAYTYPE_BACK);
//	}
//
//	static int BlendMode = 255;
//	//�`��u�����h���[�h���A���t�@�u�����h�ɂ���
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, BlendMode);
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0 && g_Block[i][j].backup != 0) {
//
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y,
//					g_BlockImage[g_Block[i][j].backup], TRUE);
//
//			}
//		}
//	}
//	//�`��u�����h���[�h���m�[�u�����h�ɂ���
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	BlendMode -= 5;
//	if (BlendMode <= 0) {
//		BlendMode = 255;
//		g_Status = 2;
//	}
//
//}
//
///********************/
///*�Q�[�����C��*/
///********************/
//void GameMain(void) {
//
//	//�X�e�[�W�摜�\��
//	DrawGraph(0, 0, g_StageImage, FALSE);
//
//	//�u���b�N�`��
//	DrawStage();
//
//	//�u���b�N����
//	switch (g_Status) {
//	    case 0:
//		     EraseBlock();
//		     break;
//	    case 1:
//		     FadeOutBlock();
//		     break;
//		case 2:
//			MoveBlock();
//			 break;
//	}
//}
//	////���N���b�N�ŃQ�[���N���A�Ɉڍs
//	//if (g_KeyFlg & MOUSE_INPUT_LEFT)g_GameState = GAME_CLEAR;
//	////�E�N���b�N�ŃQ�[���I�[�o�[�Ɉڍs
//	//if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_OVER;
//
//	//SetFontSize(16);
//	//DrawString(150, 420, "---- ���N���b�N�ŃQ�[���N���A�ց@----", 0xffffff, 0);
//	//DrawString(150, 450, "---- �E�N���b�N�ŃQ�[���I�[�o�[�ց@----", 0xffffff, 0);
//	
//
//
///***********************/
///*�Q�[���N���A�`�揈��*/
///**********************/
//void DrawGameClear(void) {
//
//	static int GameClearFlg = 0;
//
//	//�Q�[���N���ASE���X�^�[�g
//	if (CheckSoundMem(g_GameClearSE) == 0) {
//		if (GameClearFlg++ == 0) {
//			PlaySoundMem(g_GameClearSE, DX_PLAYTYPE_BACK);
//		}
//		else {
//			g_GameState = GAME_TITLE;
//			GameClearFlg = 0;
//		}
//	}
//
//	//�Q�[���N���A�摜�\��
//	DrawGraph(0, 0, g_GameClearImage, FALSE);
//
//	//�E�N���b�N�Ń��j���[�ɖ߂�
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);
//	DrawString(150, 450, "---- �E�N���b�N�������ă^�C�g���֖߂�@----", 0xffffff, 0);
//
//}
//
///*************************/
///*�Q�[���I�[�o�[�`�揈��*/
///************************/
//void DrawGameOver(void) {
//
//	static int GameOverFlg = 0;
//
//	//�Q�[���I�[�o�[SE���X�^�[�g
//	if (CheckSoundMem(g_GameOverSE) == 0) {
//		if (GameOverFlg++ == 0) {
//			PlaySoundMem(g_GameOverSE, DX_PLAYTYPE_BACK);
//		}
//		else {
//			g_GameState = GAME_TITLE;
//			GameOverFlg = 0;
//		}
//	}
//
//	//�Q�[���I�[�o�[�摜�\��
//	DrawGraph(0, 0, g_GameOverImage, FALSE);
//
//	//�E�N���b�N�Ń��j���[�ɖ߂�
//	if (g_KeyFlg & MOUSE_INPUT_RIGHT)g_GameState = GAME_TITLE;
//
//	SetFontSize(16);
//	DrawString(150, 450, "---- �E�N���b�N�������ă^�C�g���֖߂�@----", 0xffffff, 0);
//
//}
//
///*************************/
///*�摜�ǂݍ���*/
///************************/
//int LoadImages() {
//
//	//�^�C�g��
//	if ((g_TitleImage = LoadGraph("images/Chapter7/Title.png")) == -1)return -1;
//
//	//�X�e�[�W�摜�̓ǂݍ���
//	if ((g_StageImage = LoadGraph("images/Chapter7/stage.png")) == -1)return -1;
//	//�Q�[���N���A�摜�ǂݍ���
//	if ((g_GameClearImage = LoadGraph("images/Chapter7/gameclear.png")) == -1)return -1;
//	//�Q�[���I�[�o�[�摜�ǂݍ���
//	if ((g_GameOverImage = LoadGraph("images/Chapter7/gameover.png")) == -1)return -1;
//	//�u���b�N�摜�ǂݍ��݁i�����ǂݍ��݁j
//	if (LoadDivGraph("images/Chapter7/block.png", 5, 5, 1, 24, 24, g_BlockImage) == -1)return -1;
//
//	return 0;
//
//}
//
///*************************/
///*�T�E���h�ǂݍ���*/
///************************/
//int LoadSounds() {
//
//	//�^�C�g��BGM
//	if ((g_TitleBGM = LoadSoundMem("sounds/muci_action_r01.mp3")) == -1)return -1;
//	//�Q�[���N���A
//	if ((g_GameClearSE = LoadSoundMem("sounds/muci_fan_06.mp3")) == -1)return -1;
//	//�Q�[���I�[�o�[
//	if ((g_GameOverSE = LoadSoundMem("sounds/muci_bara_07.mp3")) == -1)return -1;
//	
//	//�}�E�X�N���b�N���ʉ�
//	if ((g_ClickSE = LoadSoundMem("sounds/ta_ta_warekie02.mp3")) == -1)return -1;
//	//�u���b�N�������ʉ�
//	if ((g_FadeOutSE = LoadSoundMem("sounds/ani_ta_biyon02.mp3")) == -1)return -1;
//
//	//�u���b�N�ړ����ʉ�
//	if ((g_MoveBlockSE = LoadSoundMem("sounds/ta_ta_doron01.mp3")) == -1)return -1;
//	
//
//	return 0;
//
//}
//
//
///*************************/
///*�X�e�[�W�̃u���b�N��`��*/
///*************************/
//void DrawStage(void) {
//
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			if (g_Block[i][j].flg != 0 && g_Block[i][j].image != 0) {
//				DrawGraph(g_Block[i][j].x, g_Block[i][j].y, g_BlockImage[g_Block[i][j].image], TRUE);
//			}
//		}
//	}
//	SetFontSize(64);
//	DrawFormatString(40, 100, 0xffffff, "%3d", g_Count);
//	//�f�o�b�N�p
//	DrawFormatString(40, 400, 0xffffff, "%3d", g_Rensa);
//
//	//�v�����Ԃ��߂�����Q�[���I�[�o�[
//	int Time = TIMELIMIT * g_Color - (GetNowCount() - g_StartTime);
//	if (Time <= 0) {
//		g_GameState = GAME_OVER;
//	}
//	DrawFormatString(40, 270, 0xffffff, "%3d", Time / 1000);
//}
//
//
///*************************/
///*�u���b�N������*/
///*************************/
//void EraseBlock(void) {
//
//	//�N���b�N�Ńu���b�N������
//	if(g_KeyFlg & MOUSE_INPUT_LEFT){
//		PlaySoundMem(g_ClickSE, DX_PLAYTYPE_BACK);
//		int i = g_MouseY / BLOCKSIZE + 1;
//		int j = (g_MouseX - MARGIN) / BLOCKSIZE + 1;
//
//
//		if (g_Block[i][j].image != 0) {
//			//�u���b�N�̘A���J�E���g���[���ɂ���
//			/*g_Block[i][j].image = 0;*/
//			g_Rensa = 0;
//			//�u���b�N���o�b�N�A�b�v����
//			SaveBlock();
//			//�u���b�N�̘A���`�F�b�N
//			RensaCheck(i, j, &g_Rensa);
//			if (g_Rensa < 2) {
//				//�u���b�N�̘A����1�ȉ��Ȃ�u���b�N��߂�
//				RestoreBlock();
//			}
//			else {
//				//�N���b�N���ău���b�N����������
//				g_Count++;
//				g_Status = 1; //�u���b�N�����ֈړ�
//			}
//
//
//		}
//	}
//}
//
///***************************************************/
///*�אڂ��Ă��铯�F�̌��𒲂ׂ�(�T����ɏ���)
//* �����F���F���݂̂����W,y:���݂̂����W,*cnt:�A����
//* �߂�l�F�אڂ��Ă��铯�F�̌�
///***************************************************/
//int RensaCheck(int y,int x, int *cnt)
//{
//
//	    //�Ώۃu���b�N���O�g�̏ꍇreturn�ŏ����𔲂���
//	    if (x == 0 || x == WIDTH - 1 || y == HEIGHT - 1 || y == 0)return 0;
//		
//		int c = g_Block[y][x].image; ///�F���擾
//		g_Block[y][x].image = 0;
//		(*cnt)++;
//
//		if (g_Block[y + 1][x].image == c)RensaCheck(y + 1, x, cnt);
//		if (g_Block[y - 1][x].image == c)RensaCheck(y - 1, x, cnt);
//		if (g_Block[y][x+1].image == c)RensaCheck(y, x+1, cnt);
//		if (g_Block[y][x-1].image == c)RensaCheck(y, x-1, cnt);
//	    
//		return 0;
//
//}
//
///***************************************************/
///*�u���b�N���o�b�N�A�b�v����
///***************************************************/
//void SaveBlock(void)
//{
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].backup = g_Block[i][j].image;
//		}
//	}
//}
//
///***************************************************/
///*�o�b�N�A�b�v�u���b�N��\��
///***************************************************/
//void RestoreBlock(void)
//{
//	for (int i = 0; i < HEIGHT; i++) {
//		for (int j = 0; j < WIDTH; j++) {
//			g_Block[i][j].image = g_Block[i][j].backup;
//		}
//	}
//}
//
///***************************************************/
///*�u���b�N��Ԃ̃`�F�b�N
///***************************************************/
//int CheckBlock(void)
//{
//	//�A���`�F�b�N�̌��ʂ��i�[����ϐ�
//	int Result = 0;
//
//	//��������E�ցA�u���b�N������ΘA�����Ă��邩�`�F�b�N����
//	for (int i = HEIGHT - 1;i > 0; i--) {
//		for (int j = 1; j < WIDTH; j++) {
//			if (g_Block[i][j].image != 0) {
//				//�A���`�F�b�N�̌��ʂ��i�[
//				Result = 0;
//				RensaCheck(i, j, &Result);
//				//�A���`�F�b�N�̌��ʂ��A���L��̏ꍇ
//				if (Result > 1) {
//					return 2; //�A�����Ă���u���b�N�L
//				}
//			}
//		}
//	}
//	//�A�����Ă���u���b�N�����A�܂��́A�u���b�N����
//	if (Result == 1) {
//		return 1; //�A�����Ă���u���b�N����
//	}
//	else {
//		return 0; //�u���b�N����
//	}
//}
//
///***************************************************/
///*�u���b�N�ړ�
///***************************************************/
//void MoveBlock(void)
//{
//	PlaySoundMem(g_MoveBlockSE, DX_PLAYTYPE_BACK);
//	//���ֈړ����鏈��
//	for (int i = 0; i < HEIGHT - 1; i++) {
//		for (int j = 0; j < WIDTH - 1; j++) {
//			if (g_Block[i][j].image == 0) {
//				for (int k = i; k > 0; k--) {
//					g_Block[k][j].image = g_Block[k - 1][j].image;
//					g_Block[k - 1][j].image = 0;
//				}
//			}
//		}
//	}
//
//	//���ֈړ����鏈��
//	for (int j = WIDTH - 1; j > 1; j--) {   //��20��1
//		//��ԉ��̃u���b�N����(�[��)���`�F�b�N���Ă���
//		if (g_Block[HEIGHT - 2][j - 1].image == 0) {
//			for (int k = 0; k < HEIGHT; k++) { //�c0��20
//				for (int x = j; x < WIDTH; x++) { //��X��21
//				  //�Y���ӏ�����E���̃u���b�N�����ׂĈړ�
//					g_Block[k][x - 1].image = g_Block[k][x].image;
//					//�ړ������u���b�N��0�ɂ��ău���b�N������
//					g_Block[k][x].image = 0;
//				}
//			}
//		}
//	}
//	g_Status = 0;
//
//	//�u���b�N���o�b�N�A�b�v����
//	SaveBlock();
//	//�����ł���u���b�N�����邩�`�F�b�N����
//	int Result = CheckBlock();
//
//	if (Result == 1) { //�����ł���u���b�N���Ȃ�
//		g_GameState = GAME_OVER;
//	}
//	else if (Result == 0) { //�u���b�N���Ȃ�
//		g_GameState = GAME_CLEAR;
//	}
//
//	//�o�b�N�A�b�v�̃u���b�N�̃u���b�N��߂�
//	RestoreBlock();
//}
//
