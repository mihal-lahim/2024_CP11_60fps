#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"scene.h"
#include"title.h"
#include"inputkey.h"

void InitTitle(void)
{
}

void UninitTitle(void)
{
}

void UpdateTitle(void)
{
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//シーンをゲーム本編へ移動させる
		SetScene(SCENE_GAME);
	}
}

void DrawTitle(void)
{
	gotoxy(35, 10);
	std::cout << "たいとる～";
	gotoxy(35, 14);
	std::cout << "Enter おす";
}
