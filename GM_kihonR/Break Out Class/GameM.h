#pragma once

class GameM {
private:
	
	int g_PosY;					// �X�N���[�����̂x���W
	int g_OldKey;				// �O��̓��̓L�[
	int g_NowKey;				// ����̓��̓L�[
	int g_GameState;
	int g_MenuNumber;		// ���j���[�J�[�\���ʒu
	int g_MenuY;				// ���j���[�J�[�\���̂x���W
	int g_Stage;
	

public:

	GameM();

	

	void GameMain();

};

extern GameM gameM;
