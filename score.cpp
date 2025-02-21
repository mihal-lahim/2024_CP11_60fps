//=============================================================================
//＜使い方＞
//		score.cpp と score.h をプロジェクト内に入れる
//		game.cppとスコアを操作するプログラムに「#include "score.h"」を入れる
//
//		ClearPoint() → 現在の得点を消去する
//		AddPoint(int nPoint) → 得点に加算（減算）する
//		SetPoint(int nPoint) → 指定の得点に設定する
//		SetMaxPoint(int nPoint) → 指定の得点に設定する
//		GetScore() → 現在の得点情報を取得する
//		
//=============================================================================
#define	CONIOEX
#include "conioex.h"
#include "score.h"
#include <iostream>
#include"player.h"
#include"item.h"
#include"UI.h"
SCORE g_tScore;

void InitScore()
{
	memset(&g_tScore, 0, sizeof(SCORE));
}

void UnInitScore()
{
}

void UpdateScore()
{
}

void DrawScore()
{
	int Shift = 0;
	int NowScore = g_tScore.nPoint;
	PLAYER* Player = GetPlayer();
	UI* UI = GetUI();
	//桁数カウント
	do
	{
		NowScore /= 10;
		Shift++;
	} while (NowScore != 0);

	textbackground(UI->Color);
	gotoxy(70, 15);
	std::cout << "SCORE";

	gotoxy(75 - Shift, 17);
	std::cout << g_tScore.nPoint << " ";
	
	textbackground(BLACK);

}

void ClearPoint()
{
	g_tScore.nPoint = 0;
}

void AddPoint(int nPoint)
{
	g_tScore.nPoint += nPoint;
}

void SetPoint(int nPoint)
{
	g_tScore.nPoint = nPoint;
}

void SetMaxPoint(int nPoint)
{
	g_tScore.nPoint = nPoint;
}

SCORE* GetScore()
{
	return	&g_tScore;
}