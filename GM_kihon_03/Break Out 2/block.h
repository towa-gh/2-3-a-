#pragma once

class Block {
private:
		int x, y;
		int w, h;
		int image;
		int score;
		bool isShow;
		int g_BlockImage[8];
	
	//�u���b�N�f�[�^�̐錾
	//struct ObjectBlock g_Block[HEIGHT][WIDTH];

public:
	void DrawBlock(void);   //�`�揈��
	void ChangeColor(int);     //�F�ύX
	

};
