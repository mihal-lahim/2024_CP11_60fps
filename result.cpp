#define CONIOEX
#include "conioex.h"
#include"result.h"
#include"inputkey.h"
#include"scene.h"
#include<iostream>
#include"score.h"
#include"Player.h"
#include"file.h"
#include"ranking.h"
#include"sound.h"
//////////////////
//グローバル変数//
//////////////////
RESULT g_Result;
RANKING g_tempRanking;


//初期化処理
void InitResult(void)
{
	//BGM停止
	GameOverSE_End();//ゲームオーバーSE
	BattleBGM_End();//バトルBGM停止
	AllClearSE_Start();//全クリアSE
}

//終了処理
void UninitResult(void)
{
}

//更新処理
void UpdateResult(void)
{
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//シーンをランキングへ移動させる
		SetScene(SCENE_RANKING);
	}
	PLAYER* Player = GetPlayer();
	//スコア計算
	
	//取得アイテム数が０の時、１加算
	if (Player->ItemGetCount == 0)
	{
		g_Result.TotalScore = GetScore()->nPoint * 1;
	}
	else
	{
		g_Result.TotalScore = GetScore()->nPoint * Player->ItemGetCount;
	}
	//ヒット率
	g_Result.TotalScore *= Player->HitPercent;
	//タイムボーナス負の数になるの防止
	if (g_Result.TimeBonus < 0)
	{
		g_Result.TimeBonus = 1;
	}
	g_Result.TotalScore *= g_Result.TimeBonus;

	

	//ランキング用に入れる
	g_tempRanking.Score = g_Result.TotalScore;
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
	std::cout << "HIT LATE   :" << round(Player->HitPercent * 1000) / 10 << " %";
	gotoxy(32, 13);
	std::cout << "GET ITEMS  :" << Player->ItemGetCount;
	gotoxy(32, 15);
	std::cout << "TIME BONUS :" << g_Result.TimeBonus;
	gotoxy(32, 17);
	std::cout << "TOTAL SCORE:" << g_Result.TotalScore;
	gotoxy(30, 21);
	std::cout << "ENTER　で次へ進む";
}

//構造体情報取得
RESULT* GetResult()
{
	//構造体のポインターを返す
	return &g_Result;
}

//構造体情報取得
RANKING* GetTempRanking()
{
	//構造体のポインターを返す
	return &g_tempRanking;
}