#pragma once

class Ranking {
private:

	int	g_RankingImage;			// 画像用変数
	int g_GameState;
	int	g_KeyFlg;				// 入力キー情報
	int	g_WaitTime;			// 待ち時間
	int g_Score;
	

	
public:
	Ranking();

	void DrawRanking();		//ランキング描画
	void InputRanking();	//ランキング入力
	void SortRanking();		//ランキング並べ替え

	int SaveRanking();		//ランキングデータの保存
	int ReadRanking();		//ランキングデータ読み込み

};

extern Ranking ranking;
