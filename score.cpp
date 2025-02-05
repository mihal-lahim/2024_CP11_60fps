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

SCORE g_tScore;

void InitScore()
{
	memset(&g_tScore, 0, sizeof(SCORE));
}

void UninitScore()
{
}

void UpdateScore()
{
}

void DrawScore()
{
	gotoxy(1, 4);
	std::cout << "SCORE:" << g_tScore.nPoint;
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