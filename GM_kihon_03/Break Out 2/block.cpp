#include"DxLib.h"
#include"block.h"
#include "common.h"

#define HEIGHT 10
#define WIDTH 16

Block block[HEIGHT][WIDTH];

/***********************************************
 * ÉuÉçÉbÉNï`âÊèàóù
 ***********************************************/
void Block::DrawBlock(void) {
	if (isShow) {
				DrawGraph(x,y,g_BlockImage[image], TRUE);
	}
}
void Block::ChangeColor(int color) {
	if (0 <= color && color < 8) {
		image = color;
	}
}

void Block::Init(int x1,int y1,int image) {

}
