#pragma once

class Bar {
private :
	int g_BarX;
	int g_BarY;

	int height;//8
	int width;//60

public:
	Bar();//�R���X�g���N�g
	void DrawBar(void);//�o�[�̕`��
	void MoveBar(void);//�o�[�̈ړ�����
	void Init();
	
	int getX();
	int getY();
	int getheight();
	int getwidth();
};
extern Bar bar;