#define CONIOEX
#include"conioex.h"
#include"hitpoint.h"
#include<iostream>
#include"player.h"

/////////////////
//グローバル変数
/////////////////



//初期化処理
void InitHitPoint(void)
{

}

//終了処理
void UnInitHitPoint(void)
{
}

//更新処理
void UpdateHitPoint(void)
{
	//プレイヤー構造体取得
	PLAYER* Player = GetPlayer();
	int NowHP = 0;

	//現在のHPを代入
	 NowHP = Player->Life;
}

//描画処理
void DrawHitPoint(void)
{
	//プレイヤー構造体取得
	PLAYER* Player = GetPlayer();

	gotoxy(4, 22);
	std::cout << "HP";
	//textbackground(GREEN);
	textcolor(GREEN);
	for (int i = 0; i < Player->Life; i++)
	{
		gotoxy(i + 6, 22);
		std::cout << "〇";
	}
	textbackground(BLACK);
	textcolor(WHITE);

	//ここから失った分だけ消すプログラム書く
	for (int i = Player->MaxLife; i > Player->Life + 1; i--)
	{
		gotoxy(i + 6, 22);
		std::cout << " ";
	}

}