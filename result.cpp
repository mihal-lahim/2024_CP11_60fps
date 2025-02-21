#define CONIOEX
#include "conioex.h"
#include"result.h"
#include"inputkey.h"
#include"scene.h"
#include<iostream>
#include"score.h"
#include"Player.h"

RESULT g_Result;


void InitResult(void)
{
}

void UninitResult(void)
{
}

void UpdateResult(void)
{
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//シーンをゲームタイトルへ移動させる
		SetScene(SCENE_TITLE);
	}
	PLAYER* Player = GetPlayer();

	//スコア計算
	g_Result.TotalScore = GetScore()->nPoint * Player->ItemGetCount;
	g_Result.TotalScore *= Player->HitPercent;
	
	g_Result.TotalScore *= g_Result.TimeBonus;

}

void DrawResult(void)
{
	PLAYER* Player = GetPlayer();
	gotoxy(30, 5);
	std::cout << "ゲームクリアおめでとう";
	gotoxy(32, 7);
	std::cout << "SCORE      :"<< GetScore()->nPoint;
	gotoxy(32, 9);
	std::cout << "CLEARTIME  :" << Player->ClearTime / 1000 << " sec";
	gotoxy(32, 11);
	std::cout << "HIT LATE   :" << Player->HitPercent * 100 << " %";
	gotoxy(32, 13);
	std::cout << "GET ITEMS  :" << Player->ItemGetCount;
	gotoxy(32, 15);
	std::cout << "TIME BONUS :" << g_Result.TimeBonus;
	gotoxy(32, 17);
	std::cout << "TOTAL SCORE:" << g_Result.TotalScore;

	gotoxy(30, 21);
	std::cout << "ENTER　でタイトルに戻る";
}

//構造体情報取得
RESULT* GetResult()
{
	//構造体のポインターを返す
	return &g_Result;
}