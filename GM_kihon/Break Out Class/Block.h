#pragma once

class Block {
private:
	int g_BlockX;
	int g_BlockY; //�o�[�̍��W
	int height;//8
	int width;//60
	int g_BlockImage[8]; //�u���b�N�摜�p�ϐ�
	int	g_Score;			// �X�R�A
	int g_RestBall;

public:
	Block();

	void DrawBlock();
	/*void Init();*/
	void DrawScore();

	int getX();
	int getY();
	int getheight();
	int getwidth();


};

extern Block block;
