#pragma once

class Player {

private:


	int saigo;
	
	int kansei;


	//���@�̍\����
	struct PLAYER {

		int flg;          //�g�p�t���O
		int x, y;          //���W��.��
		int speed;          //�ړ����x
	};

	//���@
	struct PLAYER g_player;

public:

	void getPlayer();

	void PlayerControl();

	//void GameInit(void);

	//int LoadImages();

	//void GameMain(void);
};

extern Player player;