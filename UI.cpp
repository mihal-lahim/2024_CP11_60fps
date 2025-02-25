#define CONIOEX
#include "conioex.h"
#include"UI.h"
#include"game.h"
#include<iostream>
#include"player.h"
#include"item.h"
#include"score.h"

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
	//プレイヤー情報取得
	PLAYER* Player = GetPlayer();
	//プレイヤーのアイテム情報が更新されていればカラーも更新
	switch (Player->Item)
	{
	case ITEM_NONE:
		g_UI.Color = WHITE;
		break;
	case ITEM_FIRE:
		g_UI.Color = RED;
		break;
	case ITEM_ICE:
		g_UI.Color = LIGHTCYAN;
		break;
	default:
		break;
	}
	//UIに色変更がかかるとき、更新
	if (g_UI.Color != g_UI.OldColor)
	{
		UIUpdate();
	}
	//カラー情報更新
	g_UI.OldColor = g_UI.Color;
}

//描画処理
void DrawUI(void)
{
	//プレイヤー情報取得
	PLAYER* Player = GetPlayer();
	if (g_UI.UpdateFlg)
	{
		//背景描画
		for (int i = 1; i < 24; i++)
		{
			for (int j = 1; j < 79; j++)
			{
				if (j < SCREEN_LEFT || SCREEN_RIGHT + 1 < j)
				{
					gotoxy(j, i);
					textbackground(g_UI.Color);
					std::cout << " ";
				}
			}
		}
		g_UI.UpdateFlg = false;
	}
	//色変更
	switch (Player->Item)
	{
	case ITEM_NONE:
		textbackground(WHITE);
		break;
	case ITEM_FIRE:
		textbackground(RED);
		break;
	case ITEM_ICE:
		textbackground(LIGHTCYAN);
		break;
	default:
		break;
	}
	//情報の描画
	//現在のステージ
	gotoxy(70, 3);
	std::cout << "STAGE";
	gotoxy(72, 4);
	std::cout << Player->Stage;
	//HP表示
	gotoxy(69, 6);
	std::cout << "HP: " << Player->Life;
	//残りのシールド表示
	gotoxy(69, 8);
	std::cout << "Shield:" << Player->ShieldCharge;
	//プレイヤーのタイプ表示
	gotoxy(69, 10);
	std::cout << "You Type";
	gotoxy(71, 11);
	switch (Player->Item)
	{
	case ITEM_NONE:
		
		std::cout << "NONE";
		break;
	case ITEM_FIRE:
		textbackground(BLACK);
		textcolor(RED);
		std::cout << "FIRE";
		break;
	case ITEM_ICE:
		textbackground(LIGHTBLUE);
		textcolor(LIGHTCYAN);
		std::cout << "AQUA";
		break;
	default:
		break;
	}
	//色変え
	textcolor(WHITE);
	//スコア表示
	DrawScore();
	//色変えリセット
	textbackground(BLACK);
	textcolor(WHITE);
}

//更新するよ
void UIUpdate()
{
	g_UI.UpdateFlg = true;
}

//構造体取得関数
UI* GetUI()
{
	return	&g_UI;
}
