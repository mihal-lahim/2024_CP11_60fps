#define CONIOEX
#include "conioex.h"
#include "field.h"
#include"game.h"
#include<iostream>

//障害物の構造体配列
FIELD g_Field[FIELD_MAX];

//障害物再描画
bool g_UpdateFlg = true;

//初期化
void InitField()
{
	FieldUpdate();

	for (int i = 0; i < FIELD_MAX; i++)
	{
		g_Field[i].PosX		= 0.0;
		g_Field[i].PosY		= 0.0;
		g_Field[i].Width	= 0.0;
		g_Field[i].Height	= 0.0;
		g_Field[i].Use		= false;

		//移動処理用
		g_Field[i].OldPosX	= 0.0;
		g_Field[i].OldPosY	= 0.0;
		g_Field[i].SpeedX	= 0.0;
		g_Field[i].SpeedY	= 0.0;
		g_Field[i].Move		= false;
		g_Field[i].Count	= 0;
	}

	CreateField(10.0, 21.0, 08.0, 4.0, 0.0, 0.00);
	CreateField(22.0, 18.0, 16.0, 4.0, 0.0, 0.00);
	CreateField(48.0, 18.0, 10.0, 7.0, 0.0, 0.00);
	CreateField(36.0, 14.0, 08.0, 6.0, 0.0, 0.00);
	CreateField(18.0, 10.0, 10.0, 4.0, 0.1, 0.00);
	CreateField(64.0, 21.0, 06.0, 4.0, 0.0, 0.00);
	CreateField(46.0, 08.0, 30.0, 3.0, 0.0, 0.03);
}

void UnInitField()
{
}

void UpdateField()
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		if (g_Field[i].Use)
		{
			if (g_Field[i].Move)
			{
				//移動処理
				g_Field[i].OldPosX = g_Field[i].PosX;
				g_Field[i].OldPosY = g_Field[i].PosY;
				g_Field[i].PosX += g_Field[i].SpeedX;
				g_Field[i].PosY += g_Field[i].SpeedY;

				//床移動
				g_Field[i].Count++;
				if (g_Field[i].Count > 80)
				{
					g_Field[i].SpeedX *= -1.0;//反転処理
					g_Field[i].SpeedY *= -1.0;//反転処理
					g_Field[i].Count = 0;//カウンターリセット
				}
			}
		}
	}
}

void DrawField()
{
	//背景再描画フラグ
	if (g_UpdateFlg)
	{
		//フィールド全描画
		UpdateDrawField();
		g_UpdateFlg = false;
	}
	else
	{
		//動く床だけ描画
		textcolor(LIGHTGRAY);//色設定
		//ブロック
		for (int i = 0; i < FIELD_MAX; i++)
		{
			if (g_Field[i].Use)
			{
				//移動処理
				if (g_Field[i].Move)
				{
					//前回から座標が変化したら
					if (g_Field[i].OldPosX != g_Field[i].PosX || g_Field[i].OldPosY != g_Field[i].PosY)
					{
						for (int Height = 0; Height < g_Field[i].Height; Height++)
						{
							gotoxy(g_Field[i].OldPosX, g_Field[i].OldPosY + Height);
							for (int Width = 0; Width < g_Field[i].Width / 2; Width++)
							{
								std::cout << "  ";
							}
						}
					}
				}
				//地面の表示
				for (int Height = 0; Height < g_Field[i].Height; Height++)
				{
					gotoxy(g_Field[i].PosX, g_Field[i].PosY + Height);
					for (int Width = 0; Width < g_Field[i].Width / 2; Width++)
					{
						std::cout << "□";
					}
				}
			}
		}
	}
}

void UpdateDrawField()
{
	//色設定
	textcolor(LIGHTGRAY);

	//外枠の設定
	gotoxy(SCREEN_LEFT, SCREEN_TOP);
	for (int i = SCREEN_LEFT - 1; i < SCREEN_RIGHT / 2; i++)
	{
		std::cout << "□";
	}
	for (int i = SCREEN_TOP + 1; i < SCREEN_BOTTOM; i++)
	{
		gotoxy(SCREEN_LEFT, i);
		std::cout << "□";
		gotoxy(SCREEN_RIGHT - 1, i);
		std::cout << "□";
	}
	gotoxy(SCREEN_LEFT, SCREEN_BOTTOM);
	for (int i = SCREEN_LEFT - 1; i < SCREEN_RIGHT / 2; i++)
	{
		std::cout << "□";
	}

	//ブロックの表示
	for (int i = 0; i < FIELD_MAX; i++)
	{
		if (g_Field[i].Use)
		{
			//移動処理
			if (g_Field[i].Move)
			{
				//前回から座標が変化したら
				if (g_Field[i].OldPosX != g_Field[i].PosX || g_Field[i].OldPosY != g_Field[i].PosY)
				{
					for (int Height = 0; i < g_Field[i].Height; Height++)
					{
						gotoxy(g_Field[i].OldPosX, g_Field[i].OldPosY + Height);
						for (int Width = 0; Width < g_Field[i].Width / 2; Width++)
						{
							std::cout << "  ";
						}
					}
				}
			}
			for (int Height = 0; Height < g_Field[i].Height; Height++)
			{
				//地面の表示
				gotoxy(g_Field[i].PosX, g_Field[i].PosY + Height);
				for (int Width = 0; Width < g_Field[i].Width / 2; Width++)
				{
					std::cout << "□";
				}
			}
		}
	}
}

void CreateField(float X, float Y, float Width, float Height, float Mx, float My)
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		if (g_Field[i].Use == false)
		{
			g_Field[i].PosX = X;
			g_Field[i].PosY = Y;
			g_Field[i].Width = Width;
			g_Field[i].Height = Height;
			g_Field[i].Use = true;

			//移動処理用
			g_Field[i].OldPosX = X;
			g_Field[i].OldPosY = Y;
			g_Field[i].SpeedX = Mx;
			g_Field[i].SpeedY = My;

			if (g_Field[i].SpeedX == 0.0f && g_Field[i].SpeedY == 0.0f)
			{
				//移動しない
				g_Field[i].Move = false;
			}
			else
			{
				//移動する
				g_Field[i].Move = true;
			}
			break;
		}
	}
}

//フィールドの構造体配列のポインタを取得
FIELD* GetField()
{
	return &g_Field[0];
}

void FieldUpdate()
{
	g_UpdateFlg = true;
}