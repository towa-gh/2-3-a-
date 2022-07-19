#include"BaseAP.h"
BaseAP::BaseAP() {
	p_flg = 1;
	p_x = 320;
	p_y = 380;
	p_w = 63;
	p_h = 120;
	p_angle = 0;
	p_count = 0;
	p_speed = 5;

	g_Apple->flg = 0;
	g_Apple->h = 0;
	g_Apple->img = 0;
	g_Apple->point = 0;
	g_Apple->speed = 0;
	g_Apple->type = 0;
	g_Apple->w = 0;
	g_Apple->x = 0;
	g_Apple->y = 0;
}
void BaseAP::PlayerInit(){
	p_flg = TRUE;
	p_x = PLAYER_POS_X;
	p_y = PLAYER_POS_Y;
	p_w = PLAYER_WIDTH;
	p_h = PLAYER_HEIGHT;
	p_angle = 0.0;
	p_count = 0;
	p_speed = PLAYER_SPEED;
}
void BaseAP::AppleInit() {
	for (int i = 0; i < APPLE_MAX; i++) {
		g_Apple[i].flg = FALSE;
	}
}