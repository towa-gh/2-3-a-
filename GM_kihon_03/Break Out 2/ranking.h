#pragma once
#include<stdio.h>

// ランキングデータ（構造体）
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
class Ranking {
private: 
	FILE* fp;
	
	// ランキングデータ変数宣言
	struct	RankingData		g_Ranking[10];


public:
	int  SaveRanking(void);		//ランキングデータの保存
	int ReadRanking(void);
	void SortRanking(void);

	RankingData getRankingData(int i);
	void setName(int i, char name[11]);
	void setScore(int i, int score);

};
extern Ranking ranking;