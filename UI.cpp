#define CONIOEX
#include "conioex.h"
#include"UI.h"
#include"game.h"
#include<iostream>
#include"player.h"

/////////////////////
//グローバル変数
/////////////////////

UI g_UI;

//初期化処理
void InitUI(void)
{
	UIUpdate();
}

//終了処理
void UnInitUI(void)
{

}

//更新処理
void UpdateUI(void)
{

}

//描画処理
void DrawUI(void)
{
	if (g_UI.UpdateFlg)
	{
		//背景描画
		for (int i = 1; i < 24; i++)
		{
			for (int j = 1; j < 79; j++)
			{
				if (j < SCREEN_LEFT-2 || SCREEN_RIGHT + 2 < j)
				{
					textbackground(BLUE);
					gotoxy(j, i);
					std::cout << "  ";
				}
			}
		}
		g_UI.UpdateFlg = false;
	}

	//情報の描画
	//プレイヤー情報取得
	PLAYER* Player = GetPlayer();

	//現在のステージ
	gotoxy(69, 3);
	std::cout << "STAGE";
	gotoxy(71, 4);
	std::cout << Player->Stage;

	//HP表示
	gotoxy(6, 22);
	std::cout << "HP: " << Player->Life;

	textbackground(BLACK);
	textcolor(WHITE);
}

void UIUpdate()
{
	g_UI.UpdateFlg = true;
}
