
#define CONIOEX
#include"conioex.h"
#include"ranking.h"
#include"file.h"
#include<iostream>
#include<iomanip>
#include"result.h"
#include"inputkey.h"
#include"scene.h"
//////////////
//グローバル変数
//////////////
RANKING g_ranking[RANKING_MAX];
bool UpdateFlg;
void InitRanking(void)
{
	FileRead(g_ranking);
	UpdateFlg = false;
}
void UnInitRanking(void)
{
}
void UpdateRanking(void)
{
	RANKING* TempRanking = GetTempRanking();
	
	for (int i = 0; i < RANKING_MAX; i++)
	{
		//現在登録されているスコアより大きかったら
		if (TempRanking->Score > g_ranking[i].Score && UpdateFlg == false)
		{
			for (int j = RANKING_MAX - 1; j > i - 1; j--)
			{
				g_ranking[j].Score = g_ranking[j - 1].Score;
				strcpy(g_ranking[j].Name, g_ranking[j - 1].Name);
			}

			//名前打たせる
			//名前
			char Temp[256];
			gotoxy(40, 20);
			std::cout << "名前を入力してください  ";
			setcursortype(SOLIDCURSOR);
			std::cin >> Temp;
			setcursortype(NOCURSOR);
			//更新
			system("cls");
			strcpy(g_ranking[i].Name, Temp);
			g_ranking[i].Score = TempRanking->Score;
			FileWrite(g_ranking);
			UpdateFlg = true;
		}
	}

	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//シーンをタイトルへ移動させる
		SetScene(SCENE_TITLE);
	}
}
void DrawRanking(void)
{
	gotoxy(30, 2);
	std::cout << "RANKING\n\n\n";
	
	//ランキング表示
	for (int i = 0; i < RANKING_MAX; i++)
	{
		
		std::cout << "                        " << i + 1;

		switch (i)
		{
		case 0:
			std::cout << "st";
			break;
		case 1:
			std::cout << "nd";
			break;
		case 2:
			std::cout << "rd";
			break;
		default:
			std::cout << "th";
			break;
		}
		std::cout << "  " << std::setw(16) << std::right << g_ranking[i].Name << "  " << g_ranking[i].Score << "\n\n";
	}
	gotoxy(30, 20);
	std::cout << "ENTER でタイトルに戻る";

}
