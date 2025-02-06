#define CONIOEX
#include "conioex.h"
#include"result.h"
#include"inputkey.h"
#include"scene.h"
#include<iostream>
#include"score.h"


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
	gotoxy(30, 11);
	std::cout << "ゲームクリアおめでとう";
	gotoxy(36, 13);
	std::cout << "SCORE:"<< GetScore()->nPoint;
	gotoxy(30, 15);
	std::cout << "ENTER　でタイトルに戻る";
}