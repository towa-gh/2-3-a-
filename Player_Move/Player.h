#pragma once

class Player {

private:


	int saigo;
	
	int kansei;

	//int playerX;

	//int playerY;


	//���@�̍\����
	struct PLAYER {

		int flg;          //�g�p�t���O
		int x, y;          //���W��.��
		int speed;          //�ړ����x
	};

	//���@
	struct PLAYER g_player;

public:

	//Player();

	void getPlayer();

	void PlayerControl(int L,int R);

	void getsaigo();

};

extern Player player;