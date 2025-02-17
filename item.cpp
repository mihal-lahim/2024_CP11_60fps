#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"item.h"
#include"player.h"
#include"collision.h"
#include"game.h"


//////////////////
//グローバル変数//
//////////////////

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
	//アイテム使用数
	int UseCount = 0;

	//消去アイテム
	int Delete = rand() % ITEM_MAX;

	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (g_Item[i].Use == true)
		{
			//アイテム使用数の加算
			UseCount++;
		}
	}
	//全てのアイテムが生成されていたら全てのアイテムを消去する
	if (UseCount == ITEM_MAX)
	{
		for (int i = 0; i < ITEM_MAX; i++)
		{
			g_Item[i].Use = false;
		}
	}
	else
	{
		//使用中の構造体をすべて更新する
		for (int i = 0; i < ITEM_MAX; i++)
		{
			//アイテムの位置を指定
			int ItemPosX = rand() % SCREEN_RIGHT + SCREEN_LEFT;
			int ItemPosY = rand() % SCREEN_BOTTOM + SCREEN_TOP;

			//アイテムの種類を指定
			int ItemType = rand() % 2 + 1;

			//アイテム使用数
			int Use = 0;

			if (g_Item[i].Use == false)
			{
				//最後にアイテムを生成した時間から一定時間経過したらアイテムを生成 1000ms = 1秒
				if (timeGetTime() - lastItemSetTime > 1500)
				{
					SetItem(ItemPosX, ItemPosY, ItemType);

					//最後にアイテムを生成した時間を更新
					lastItemSetTime = timeGetTime();
				}
			}

			//当たり判定//////////////
			g_Item[i].Hit = ItemCollisionPlayer(&g_Item[i]);

			//プレイヤーが取得したら消える
			if (g_Item[i].Hit)
			{
				g_Item[i].Use = false;
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
			switch (g_Item[i].Type)
			{
			case ITEM_FIRE:
				std::cout << "炎";
				break;
			case ITEM_ICE:
				std::cout << "水";
				break;
			default:
				break;
			}
			
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

//アイテム構造体取得
//構造体情報取得
ITEM* GetItem()
{
	//弾の構造体配列の先頭のポインターを返す
	return &g_Item[0];
}