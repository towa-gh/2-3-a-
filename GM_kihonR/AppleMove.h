#pragma once

class AppleMove {
private:

	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 640;



	/*int g_enemy;*/
	//int g_Mileage;
	//int g_apple;
	/*int g_GameState;*/


public:
	//AppleMove();
	void EnemyControl();
	int CreateEnemy();

	/*int getg_Mileage();
	int getg_apple();*/
	
	/*void GameInit();*/

	/*void BackScrool();*/

	/*int LoadImages();*/
};

extern AppleMove applemove ;