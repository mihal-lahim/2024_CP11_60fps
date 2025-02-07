#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"item.h"
#include"player.h"


/////////////
// グローバル変数
/////////////

ITEM g_Item[ITEM_MAX];//アイテム構造体配列
DWORD lastItemSetTime;//最後にアイテムを生成した時間

//初期化処理
void InitItem()
{
	//構造体の中を0でクリア
	memset(&g_Item[0], 0, sizeof(ITEM) * ITEM_MAX);
	//ランダム値を取得
	srand((unsigned int)time(NULL));
	// 最後にアイテムを生成した時間を初期化
	lastItemSetTime = timeGetTime();
}

//終了処理
void UninitItem()
{
}

//更新処理
void UpdateItem()
{
	//使用中の構造体をすべて更新する
	for (int i = 0; i < ITEM_MAX; i++)
	{
		int PosX = rand() % 80;
		int PosY = rand() % 25;
		if (g_Item[i].Use == false)
		{
			//最後にアイテムを生成した時間から一定時間経過したらアイテムを生成
			if (timeGetTime() - lastItemSetTime > 1000)
			{
				SetItem(PosX, PosY, ITEM_FIRE);
				lastItemSetTime = timeGetTime();
			}
		}
	}
}

//描画処理
void DrawItem()
{
	//使用中の構造体をすべて表示する
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//構造体が使用中
		if (g_Item[i].Use == true)
		{
			//前回の位置から移動したか？Y座標でも確認が必要
			if (g_Item[i].OldPosX != g_Item[i].PosX ||
				g_Item[i].OldPosY != g_Item[i].PosY)
			{
				gotoxy(g_Item[i].OldPosX, g_Item[i].OldPosY);
				std::cout << "  ";
			}
			gotoxy(g_Item[i].PosX, g_Item[i].PosY);
			textcolor(g_Item[i].Color);//色変え
			std::cout << "★";
			textcolor(WHITE);//色変え
		}
	}
}

//アイテムの生成
void SetItem(float x, float y, int type)
{
	//未使用の構造体を検索
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].Use == false)
		{
			g_Item[i].Use = true;
			g_Item[i].PosX = x;
			g_Item[i].PosY = y;
			g_Item[i].OldPosX = x;
			g_Item[i].OldPosY = y;
			g_Item[i].Type = type;

			//アイテムタイプにより色を変える
			switch (type)
			{
			case ITEM_FIRE:
			{
				g_Item[i].Color = RED;
				break;
			}
			case ITEM_ICE:
			{
				g_Item[i].Color = LIGHTCYAN;
				break;
			}
			default:
				break;
			}
			break;
		}
	}
}

//アイテムの消去
void DeleteItem(int Delete)
{
	g_Item[Delete].Use = false;
}