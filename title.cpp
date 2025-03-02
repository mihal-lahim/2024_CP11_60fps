#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"scene.h"
#include"title.h"
#include"inputkey.h"

//////////////////
//グローバル変数//
//////////////////
TITLE g_Title;

int ColorTimer_F;//色変化のための時間F
int ColorTimer_i;//色変化のための時間i
int ColorTimer_c;//色変化のための時間c

//初期化処理
void InitTitle(void)
{
	ColorTimer_F = RED_POINT;//初期値
	ColorTimer_i = BLUE_POINT;//初期値
	ColorTimer_c = WHITE_POINT;//初期値
	TitleUpdate();
}

//終了処理
void UninitTitle(void)
{
}

//更新処理
void UpdateTitle(void)
{
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//シーンをゲーム本編へ移動させる
		SetScene(SCENE_TITLE2);
	}

	//タイマーをそれぞれ減算していく
	ColorTimer_F--;
	ColorTimer_i--;
	ColorTimer_c--;

#ifdef _DEBUG
	gotoxy(1, 5);
	std::cout << ColorTimer_F;
	gotoxy(1, 6);
	std::cout << ColorTimer_i;
	gotoxy(1, 7);
	std::cout << ColorTimer_c;
#endif _DEBUG

	//Fの色登録
	if (ColorTimer_F > BLUE_POINT)
	{
		g_Title.F_Color = RED;
	}
	else if (ColorTimer_F > WHITE_POINT)
	{
		g_Title.F_Color = LIGHTCYAN;
	}
	else
	{
		g_Title.F_Color = WHITE;

		//タイマーが切れたら元に戻す
		if (ColorTimer_F < 0)
		{
			ColorTimer_F = RED_POINT;
		}
	}
	//iの色登録
	if (ColorTimer_i > BLUE_POINT)
	{
		g_Title.i_Color = RED;
	}
	else if (ColorTimer_i > WHITE_POINT)
	{
		g_Title.i_Color = LIGHTCYAN;
	}
	else
	{
		g_Title.i_Color = WHITE;

		//タイマーが切れたら元に戻す
		if (ColorTimer_i < 0)
		{
			ColorTimer_i = RED_POINT;
		}
	}
	//cの色登録
	if (ColorTimer_c > BLUE_POINT)
	{
		g_Title.c_Color = RED;
	}
	else if (ColorTimer_c > WHITE_POINT)
	{
		g_Title.c_Color = LIGHTCYAN;
	}
	else
	{
		g_Title.c_Color = WHITE;

		//タイマーが切れたら元に戻す
		if (ColorTimer_c < 0)
		{
			ColorTimer_c = RED_POINT;
		}
	}
	//色変更あるとき更新
	if (g_Title.F_OldColor != g_Title.F_Color)
	{
		TitleUpdate();
	}

	//カラー更新
	g_Title.F_OldColor = g_Title.F_Color;
	g_Title.i_OldColor = g_Title.i_Color;
	g_Title.c_OldColor = g_Title.c_Color;
}

//描画処理
void DrawTitle(void)
{
	//色変更あったら更新
	if (g_Title.UpdateFlg)
	{
		Draw_F();
		Draw_i();
		Draw_c();
	}
}

//F
void Draw_F(void)
{
	//色情報入れる
	textbackground(g_Title.F_Color);
	//横
	for (int x = 10;x < 30;x++)
	{
		gotoxy(x, 3);
		std::cout << " ";
	}
	//タテ
	for (int y = 4;y < 20;y++)
	{
		for (int x = 10;x < 13;x++)
		{
			gotoxy(x, y);
			std::cout << " ";
		}
		
	}
	//横２
	for (int x = 11;x < 25;x++)
	{
		gotoxy(x, 11);
		std::cout << " ";
	}
	//色リセット
	textbackground(BLACK);
}

//i
void Draw_i(void)
{
	//色情報入れる
	textbackground(g_Title.i_Color);
	//点の部分
	for (int y = 5;y < 7;y++)
	{
		for (int x = 39;x < 42;x++)
		{
			gotoxy(x, y);
			std::cout << " ";
		}
	}
	//棒の部分
	for (int y = 10;y < 20;y++)
	{
		for (int x = 39;x < 42;x++)
		{
			gotoxy(x, y);
			std::cout << " ";
		}
	}
	//色リセット
	textbackground(BLACK);
}

//c
void Draw_c(void)
{
	//色情報入れる
	textbackground(g_Title.c_Color);
	//  ■■■
	//□　　　□
	//□
	//□　　　□
	//　□□□
	for (int x = 57;x < 68;x++)
	{
		gotoxy(x, 11);
		std::cout << " ";
	}
	//  □□□
	//■　　　□
	//■
	//■　　　□
	//　□□□
	for (int y = 12;y < 19;y++)
	{
		for (int x = 56;x < 59;x++)
		{
			if (x == 58)
			{
				if (y == 12 || y == 18)
				{
					gotoxy(x, y);
					std::cout << " ";
				}
				else
				{
					//描かない
				}
			}
			else
			{
				gotoxy(x, y);
				std::cout << " ";
			}
		}
		
	}
	//  □□□
	//□　　　■
	//□
	//□　　　□
	//　□□□
	for (int y = 12;y < 14;y++)
	{
		for (int x = 66;x < 69;x++)
		{
			if (x == 66 && y == 13)
			{
				//描かない
			}
			else
			{
				gotoxy(x, y);
				std::cout << " ";
			}
		}
	}
	//  □□□
	//□　　  □　
	//□
	//□　　　■
	//　□□□
	for (int y = 17;y < 19;y++)
	{
		for (int x = 66;x < 69;x++)
		{
			if (y == 17 && x == 66)
			{
				//描かない
			}
			else
			{
				gotoxy(x, y);
				std::cout << " ";
			}
		}
	}
	//  □□□
	//□　　　□
	//□
	//□　　　□
	//　■■■
	for (int x = 57; x < 68;x++)
	{
		gotoxy(x, 19);
		std::cout << " ";
	}

	//ピリオド用の色
	textbackground(YELLOW);

	//ピリオド
	for (int x = 73;x < 75;x++)
	{
		gotoxy(x, 19);
		std::cout << " ";
	}
	
	//色リセット
	textbackground(BLACK);
}

//更新するよ
void TitleUpdate(void)
{
	g_Title.UpdateFlg = true;
}