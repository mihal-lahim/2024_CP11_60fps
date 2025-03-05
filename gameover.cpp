
#define CONIOEX
#include"conioex.h"
#include"scene.h"
#include "inputkey.h"
#include "gameover.h"
#include "sound.h"
#include<iostream>

//初期化処理
void InitGameOver(void)
{
	//ゲームオーバーSE再生
	GameOverSE_Start();
}

//終了処理
void UnInitGameOver(void)
{
	//ゲームオーバーSE停止
	GameOverSE_End();
}

//更新処理
void UpdateGameOver(void)
{
	//エンターキーが押されたら
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//SE
		SelectSE_Start();

		//タイトルへ移動
		SetScene(SCENE_TITLE);
	}
}

//描画処理
void DrawGameOver(void)
{
	//ゲームオーバー表示
	gotoxy(35, 10);
	std::cout << "Game Over";
	gotoxy(30, 15);
	std::cout << "Press Enter Key to Title";
}