#pragma once

class Ranking {
private:

	int	g_RankingImage;			// �摜�p�ϐ�
	int g_GameState;
	int	g_KeyFlg;				// ���̓L�[���
	int	g_WaitTime;			// �҂�����
	int g_Score;
	

	
public:
	Ranking();

	void DrawRanking();		//�����L���O�`��
	void InputRanking();	//�����L���O����
	void SortRanking();		//�����L���O���בւ�

	int SaveRanking();		//�����L���O�f�[�^�̕ۑ�
	int ReadRanking();		//�����L���O�f�[�^�ǂݍ���

};

extern Ranking ranking;
