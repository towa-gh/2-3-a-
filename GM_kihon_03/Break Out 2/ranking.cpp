#include"DxLib.h"
#include"ranking.h"

Ranking ranking;

/***********************************************
 * ランキングデータの保存
 ***********************************************/
int  Ranking::SaveRanking(void){

	// ファイルオープン
	if ((fp = fopen("dat/chapter4/rankingdata.txt", "w")) == NULL) {
		/* エラー処理 */
		printf("Ranking Data Error\n");
		return -1;
	}
	// ランキングデータ分配列データを書き込む
	for (int i = 0; i < 10; i++) {
		fprintf(fp, "%2d %10s %10d\n", g_Ranking[i].no, g_Ranking[i].name, g_Ranking[i].score);
	}
	//ファイルクローズ
	fclose(fp);

	return 0;
}

/*************************************
 * ランキングデータ読み込み
 *************************************/
int Ranking::ReadRanking(void)
{
	FILE* fp;
#pragma warning(disable:4996)

	//ファイルオープン
	if ((fp = fopen("dat/rankingdata.txt", "r")) == NULL) {
		//エラー処理
		printf("Ranking Data Error\n");
		return -1;
	}

	//ランキングデータ配分列データを読み込む
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%2d %10s %10d", &g_Ranking[i].no, g_Ranking[i].name,11, &g_Ranking[i].score);
	}

	//ファイルクローズ
	fclose(fp);

	return 0;
}
/***********************************************
 * ランキング並べ替え
 ***********************************************/
void Ranking::SortRanking(void)
{
	int i, j;
	RankingData work;
	// 選択法ソート
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score <= g_Ranking[j].score) {
				work = g_Ranking[i];
				g_Ranking[i] = g_Ranking[j];
				g_Ranking[j] = work;
			}
		}
	}
	// 順位付け
	for (i = 0; i < 10; i++) {
		g_Ranking[i].no = 1;
	}
	// 得点が同じ場合は、同じ順位とする
	// 同順位があった場合の次の順位はデータ個数が加算された順位とする
	for (i = 0; i < 9; i++) {
		for (j = i + 1; j < 10; j++) {
			if (g_Ranking[i].score > g_Ranking[j].score) {
				g_Ranking[j].no++;
			}
		}
	}
}
RankingData Ranking::getRankingData(int i) {
	return g_Ranking[i];
}