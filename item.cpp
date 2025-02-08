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
		int FirePosX = rand() % 78 + 1;
		int FirePosY = rand() % 23 + 1;

		int IcePosX  = rand() % 78 + 1;
		int IcePosY  = rand() % 23 + 1;

		int ItemType = rand() % 2 + 1;

		//使用中のアイテム
		int UseItem = 0;
		
		if (g_Item[i].Use == false)
		{
			//最後にアイテムを生成した時間から一定時間経過したらアイテムを生成 1000ms = 1秒
			if (timeGetTime() - lastItemSetTime > 1000)
			{
				SetItem(IcePosX, IcePosY, ItemType);

				//最後にアイテムを生成した時間を更新
				lastItemSetTime = timeGetTime();
			}
		}
		else//アイテムが使用中ならば
		{
			UseItem++;
		}

		//すべてのアイテムが使用中ならば
		if (UseItem == ITEM_MAX)
		{
			//ここから0208
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
		else
		{
			gotoxy(g_Item[i].PosX, g_Item[i].PosY);
			std::cout << "  ";
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