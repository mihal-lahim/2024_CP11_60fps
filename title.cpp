#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"scene.h"
#include"title.h"
#include"inputkey.h"
#include"score.h"

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
		SetScene(SCENE_GAME);
		//スコアのリセット
		ClearPoint();
	}

	//タイマーをそれぞれ減算していく
	ColorTimer_F--;
	ColorTimer_i--;
	ColorTimer_c--;
	gotoxy(1, 5);
	std::cout << ColorTimer_F;
	gotoxy(1, 6);
	std::cout << ColorTimer_i;
	gotoxy(1, 7);
	std::cout << ColorTimer_c;
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
	for (int x = 10;x < 16;x++)
	{
		gotoxy(x, 10);
		std::cout << " ";
	}
	for (int y = 11;y < 30;y++)
	{
		gotoxy(10, y);
		std::cout << " ";
	}
	for (int x = 11;x < 13;x++)
	{
		gotoxy(x, 20);
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
	for (int y = 10;y < 12;y++)
	{
		for (int x = 18;x < 20;x++)
		{
			gotoxy(x, y);
			std::cout << " ";
		}
	}
	//棒の部分
	for (int y = 16;y < 30;y++)
	{
		for (int x = 18;x < 20;x++)
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
	for (int x = 25;x < 28;x++)
	{
		gotoxy(x, 15);
		std::cout << " ";
	}
	for (int y = 16;y < 20;y++)
	{
		gotoxy(24, y);
		std::cout << " ";
	}
	gotoxy(29, 16);
	std::cout << " ";
	gotoxy(29, 19);
	std::cout << " ";
	for (int x = 25; x < 28;x++)
	{
		gotoxy(x, 21);
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