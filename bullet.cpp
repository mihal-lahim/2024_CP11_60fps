#define CONIOEX
#include"conioex.h"
#include<iostream>
#include "bullet.h"
#include "game.h"
#include"player.h"
#include"item.h"

////////////////
//グローバル変数
////////////////

BULLET g_Bullet[BULLET_MAX];//弾構造体配列

//初期化処理
void InitBullet(void)
{
	//構造体の中を０でクリア
	memset(&g_Bullet[0], 0, sizeof(BULLET) * BULLET_MAX);
}

//終了処理
void UnInitBullet(void)
{
	
}

//更新処理
void UpdateBullet(void)
{
	//使用中の構造体をすべて更新する
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//構造体が使用中なら更新する
		if (g_Bullet[i].Use == true)
		{
			//現在の座標をOldに保存
			g_Bullet[i].OldPosX = g_Bullet[i].PosX;
			g_Bullet[i].OldPosY = g_Bullet[i].PosY;

			//現在の座標へ移動量を加算
			g_Bullet[i].PosX += g_Bullet[i].SpeedX;
			g_Bullet[i].PosY += g_Bullet[i].SpeedY;
		}

		//現在の座標が画面外なら使用中フラグをfalseにする
		if ((g_Bullet[i].PosX < SCREEN_LEFT) || (g_Bullet[i].PosX > SCREEN_RIGHT) || 
			(g_Bullet[i].PosY < SCREEN_TOP)  || (g_Bullet[i].PosY > SCREEN_BOTTOM))
		{
			g_Bullet[i].Use = false;//構造体を未使用にする
		}

		//取得しているアイテムによって弾の属性を変える
		PLAYER* Player = GetPlayer();
		
		//アイテムタイプを入れる
		g_Bullet[i].Type = Player->Item;
	}
}

//描画処理
void DrawBullet(void)
{
	//使用中の構造体をすべて表示する
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//前回の位置から移動したか？本当はY座標でも確認が必要
		if (g_Bullet[i].PosX != g_Bullet[i].OldPosX ||
			g_Bullet[i].PosY != g_Bullet[i].OldPosY)
		{
			gotoxy(g_Bullet[i].OldPosX, g_Bullet[i].OldPosY);//前回の場所の消去
			std::cout << "  ";
		}
		//構造体が使用中なら
		if (g_Bullet[i].Use == true)
		{
			gotoxy(g_Bullet[i].PosX, g_Bullet[i].PosY);//今回の場所への移動
			PLAYER* Player = GetPlayer();
			//アイテムにより色変え
			switch (Player->Item)
			{
			case ITEM_NONE:
				textcolor(WHITE);
				break;
			case ITEM_FIRE:
				textcolor(RED);
				break;
			case ITEM_ICE:
				textcolor(LIGHTCYAN);
				break;
			default:
				break;
			}
			std::cout << "・";
			textcolor(WHITE);//色変え
		}
	}
}

//生成処理
void CreateBullet(float X,float Y,float Mx,float My)
{
	//未使用の構造体を見つけて、弾のデータをセット
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//構造体が未使用なら
		if (!g_Bullet[i].Use)
		{
			g_Bullet[i].PosX = g_Bullet[i].OldPosX = X;
			g_Bullet[i].PosY = g_Bullet[i].OldPosY = Y;
			g_Bullet[i].SpeedX = Mx;
			g_Bullet[i].SpeedY = My;
			g_Bullet[i].Use = true;

			break;//弾を一つ作成したら終了
		}
	}
}

//構造体情報取得
BULLET* GetBullet()
{
	//弾の構造体配列の先頭のポインターを返す
	return &g_Bullet[0];
}

