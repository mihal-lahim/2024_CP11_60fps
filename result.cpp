#define CONIOEX
#include "conioex.h"
#include"result.h"
#include"inputkey.h"
#include"scene.h"
#include<iostream>
#include"score.h"
#include"Player.h"


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
}

void DrawResult(void)
{
	PLAYER* Player = GetPlayer();
	gotoxy(30, 11);
	std::cout << "ゲームクリアおめでとう";
	gotoxy(36, 13);
	std::cout << "SCORE:"<< GetScore()->nPoint;
	gotoxy(32, 15);
	std::cout << "CLEARTIME:" << Player->ClearTime / 1000 << "sec";
	gotoxy(30, 17);
	std::cout << "ENTER　でタイトルに戻る";
}