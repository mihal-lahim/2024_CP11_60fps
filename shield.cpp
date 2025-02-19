#define CONIOEX
#include"conioex.h"
#include<iostream>
#include "collision.h"
#include"player.h"
#include"enemy.h"
#include"shield.h"
#include"game.h"

////////////////
//グローバル変数
////////////////
SHIELD g_Shield[SHIELD_MAX];//シールド構造体

//初期化処理
void InitShield(void)
{
	//構造体の中を０でクリア
	memset(&g_Shield[0], 0, sizeof(SHIELD) * SHIELD_MAX);
}

//終了処理
void UnInitShield(void)
{
}

//更新処理
void UpdateShield(void)
{
	//プレイヤーの情報を取得
	PLAYER* tPlayer = GetPlayer();

	//使用中の構造体をすべて更新する
	for (int i = 0; i < SHIELD_MAX; i++)
	{
		//構造体が使用中なら更新する
		if (g_Shield[i].Use == true)
		{
			//現在の座標をOldに保存
			g_Shield[i].OldPosX = g_Shield[i].PosX;
			g_Shield[i].OldPosY = g_Shield[i].PosY;
			//現在の座標へ移動量を加算
			g_Shield[i].PosX += tPlayer->SpeedX;
			g_Shield[i].PosY += tPlayer->SpeedY;

			// ウィンドウの境界を超えないように制御
			if (g_Shield[i].PosX < SCREEN_LEFT)
			{
				g_Shield[i].PosX = SCREEN_LEFT;
			}
			else if (g_Shield[i].PosX > SCREEN_RIGHT)
			{
				g_Shield[i].PosX = SCREEN_RIGHT;
			}

			if (g_Shield[i].PosY < SCREEN_TOP)
			{
				g_Shield[i].PosY = SCREEN_TOP;
			}
			else if (g_Shield[i].PosY > SCREEN_BOTTOM)
			{
				g_Shield[i].PosY = SCREEN_BOTTOM;
			}

			//敵との当たり判定
			g_Shield[i].Hit = ShieldCollisionEnemy(&g_Shield[i]);
			if(g_Shield[i].Hit)
			{
				g_Shield[i].UnBreaking --;
				g_Shield[i].Hit = false;
				//耐久力がなくなったら使用中フラグをfalseにする
				if (g_Shield[i].UnBreaking < 1)
				{
					g_Shield[i].Use = false;
					gotoxy(g_Shield[i].PosX, g_Shield[i].PosY);
					std::cout << " ";
				}
			}
		}
	}
}

//描画処理
void DrawShield(void)
{
	//使用中の構造体をすべて表示する
	for (int i = 0; i < SHIELD_MAX; i++)
	{
		if (g_Shield[i].Use == true)
		{
			//前回の位置から移動したか？本当はY座標でも確認が必要
			if (g_Shield[i].PosX != g_Shield[i].OldPosX ||
				g_Shield[i].PosY != g_Shield[i].OldPosY)
			{
				//前回の座標を消去
				gotoxy((int)g_Shield[i].OldPosX, (int)g_Shield[i].OldPosY);
				std::cout << "  ";
			}
			//現在の座標に描画
			if (g_Shield[i].UnBreaking < 2)
			{
				textcolor(RED);
			}
			gotoxy(g_Shield[i].PosX, g_Shield[i].PosY);
			std::cout << "[]";
			textcolor(WHITE);
		}
	}
}

//シールド生成
void CreateShield(float PlayerPosX, float PlayerPosY, float UnBraking)
{
	//未使用の構造体を検索
	for (int i = 0; i < SHIELD_MAX; i++)
	{
		if (g_Shield[i].Use == false)
		{
			//使用中フラグを立てる
			g_Shield[i].Use = true;

			//座標をセット　８方向に生成したいからswitch文で作成するが、もっと言いわけかたあるかも
			switch (i)
			{
			case 0://左上
				g_Shield[i].PosX = PlayerPosX - 2;
				g_Shield[i].PosY = PlayerPosY - 1;
				break;
			case 1://上
				g_Shield[i].PosX = PlayerPosX;
				g_Shield[i].PosY = PlayerPosY - 1;
				break;
			case 2://右上
				g_Shield[i].PosX = PlayerPosX + 2;
				g_Shield[i].PosY = PlayerPosY - 1;
				break;
			case 3://左
				g_Shield[i].PosX = PlayerPosX - 2;
				g_Shield[i].PosY = PlayerPosY;
				break;
			case 4://右
				g_Shield[i].PosX = PlayerPosX + 2;
				g_Shield[i].PosY = PlayerPosY;
				break;
			case 5://左下
				g_Shield[i].PosX = PlayerPosX - 2;
				g_Shield[i].PosY = PlayerPosY + 1;
				break;
			case 6://下
				g_Shield[i].PosX = PlayerPosX;
				g_Shield[i].PosY = PlayerPosY + 1;
				break;
			case 7://右下
				g_Shield[i].PosX = PlayerPosX + 2;
				g_Shield[i].PosY = PlayerPosY + 1;
				break;
			default:
				break;
			}
			
			//移動量をセット
			g_Shield[i].SpeedX = 0;
			g_Shield[i].SpeedY = 0;

			//耐久力をセット
			g_Shield[i].UnBreaking = UnBraking;
		}
	}
}

//構造体情報取得
SHIELD* GetShield(void)
{
	//構造体のポインターを返す
	return &g_Shield[0];
}