#include"DxLib.h"
#include"Bar.h"
#include "common.h"


Bar bar;//�N���X�̃I�u�W�F�N�g

Bar::Bar() {
	g_BarX = 0;
	g_BarY = 0;
	height = 8;
	width = 60;
}
/***********************************************
 * �o�[�̕`�揈��
 ***********************************************/
void Bar::DrawBar() {
	DrawBox(g_BarX, g_BarY, g_BarX + width, g_BarY + height, 0xFFD700, TRUE);
}

/***********************************************
 * �o�[�̈ړ�����
 ***********************************************/
void Bar:: MoveBar(void) {
	int g_MouseX, g_MouseY;//�}�E�X�̍��W

	//�}�E�X������W�ǂݎ��
	GetMousePoint(&g_MouseX, &g_MouseY);

	

	g_BarX = g_MouseX;
	if (g_BarX < 0) {
		g_BarX = 0;
	}
	else if (g_BarX > 640 - width) {
		g_BarX = 580;
	}
}

void Bar::Init() {
	g_BarX = 290;
	g_BarY = 440;

}

int Bar::getX() {
	return g_BarX;
}

int Bar::getY() {
	return g_BarY;
}

int Bar::getheight() {
	return height;
}

int Bar::getwidth() {
	return width;
}