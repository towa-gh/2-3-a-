#pragma once
#include<stdio.h>

// �����L���O�f�[�^�i�\���́j
struct	RankingData {
	int		no;
	char	name[11];
	long	score;
};
class Ranking {
private: 
	FILE* fp;
	
	// �����L���O�f�[�^�ϐ��錾
	struct	RankingData		g_Ranking[10];


public:
	int  SaveRanking(void);		//�����L���O�f�[�^�̕ۑ�
	int ReadRanking(void);
	void SortRanking(void);

	RankingData getRankingData(int i);
	void setName(int i, char name[11]);
	void setScore(int i, int score);

};
extern Ranking ranking;