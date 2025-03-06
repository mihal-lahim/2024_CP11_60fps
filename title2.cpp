#define CONIOEX
#include"conioex.h"
#include"title2.h"
#include"scene.h"
#include"inputkey.h"
#include"score.h"
#include <iostream>
#include"sound.h"

///////
//グローバル変数
///////
PLAYERTITLE g_PlayerTitle;

int Timer = 0;

//初期化
void InitTitle2(void)
{
	g_PlayerTitle.PosX = 40;
	g_PlayerTitle.PosY = 4;
	g_PlayerTitle.OldPosX = 0;
	g_PlayerTitle.OldPosY = 0;
}
//終了
void UnInitTitle2(void)
{
}
//更新
void UpdateTitle2(void)
{
	//タイマー加算
	Timer++;
	if (Timer == 0 || Timer == 300 || Timer == 600 || Timer == 900 || Timer == 1200 || Timer == 1500)
	{
		//SE
		CountDownSE_Start();
	}
	if (Timer == 1500)
	{
		Timer = 0;
	}
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//エンターSE
		SelectSE_Start();
		//シーンをゲーム本編へ移動させる
		SetScene(SCENE_GAME);
		//スコアのリセット
		ClearPoint();
	}
}
//描画
void DrawTitle2(void)
{
	gotoxy(2, 1);
	std::cout << "+-------------+";
	gotoxy(2, 2);
	std::cout << "| 操 作 説 明 |";
	gotoxy(2, 3);
	std::cout << "+-------------+";

	gotoxy(1, 1);
	//位置消去
	if (GetKeyRelease(KEYNAME::KEY_W))
	{
		gotoxy(40, 3);
	}
	else if (GetKeyRelease(KEYNAME::KEY_A))
	{
		gotoxy(38, 4);
	}
	else if (GetKeyRelease(KEYNAME::KEY_S))
	{
		gotoxy(40, 5);
	}
	else if (GetKeyRelease(KEYNAME::KEY_D))
	{
		gotoxy(42, 4);
	}
	else
	{
		gotoxy(40, 4);
	}
	std::cout << "  ";

	//位置
	if (GetKeyPress(KEYNAME::KEY_W))
	{
		gotoxy(40, 3);
	}
	else if (GetKeyPress(KEYNAME::KEY_A))
	{
		gotoxy(38, 4);
	}
	else if (GetKeyPress(KEYNAME::KEY_S))
	{
		gotoxy(40, 5);
	}
	else if (GetKeyPress(KEYNAME::KEY_D))
	{
		gotoxy(42, 4);
	}
	else
	{
		//基本の位置
		gotoxy(40, 4);
	}

	std::cout << "●";

	//Wキー
	gotoxy(15, 11);
	if (GetKeyPress(KEYNAME::KEY_W))
	{
		textcolor(YELLOW);
	}
	std::cout << "[W]";
	textcolor(WHITE);
	//Aキー
	gotoxy(12, 12);
	if (GetKeyPress(KEYNAME::KEY_A))
	{
		textcolor(YELLOW);
	}
	std::cout << "[A]";
	textcolor(WHITE);
	//Sキー
	gotoxy(15, 12);
	if (GetKeyPress(KEYNAME::KEY_S))
	{
		textcolor(YELLOW);
	}
	std::cout << "[S]";
	textcolor(WHITE);
	//Dキー
	gotoxy(18, 12);
	if (GetKeyPress(KEYNAME::KEY_D))
	{
		textcolor(YELLOW);
	}
	std::cout << "[D]";
	textcolor(WHITE);

	//スペースキー
	gotoxy(37, 12);
	if (GetKeyPress(KEYNAME::KEY_SPACE))
	{
		textcolor(YELLOW);
	}
	std::cout << "[SPACE]";
	textcolor(WHITE);

	//矢印キー
	//上
	gotoxy(60, 11);
	if (GetKeyPress(KEYNAME::KEY_UP))
	{
		textcolor(YELLOW);
	}
	std::cout << "[↑]";
	textcolor(WHITE);
	//左
	gotoxy(56, 12);
	if (GetKeyPress(KEYNAME::KEY_LEFT))
	{
		textcolor(YELLOW);
	}
	std::cout << "[←]";
	textcolor(WHITE);
	//下
	gotoxy(60, 12);
	if (GetKeyPress(KEYNAME::KEY_DOWN))
	{
		textcolor(YELLOW);
	}
	std::cout << "[↓]";
	textcolor(WHITE);
	//右
	gotoxy(64, 12);
	if (GetKeyPress(KEYNAME::KEY_RIGHT))
	{
		textcolor(YELLOW);
	}
	std::cout << "[→]";
	textcolor(WHITE);

	//チャットウィンドウ
	gotoxy(2, 15);
	std::cout << "+---------------------------------------------------------------------------+";
	gotoxy(2, 16);
	if (Timer < 300)
	{
		std::cout << "| WASDキーで上下左右に移動できる。                                          |";
	}
	else if (Timer < 600)
	{
		std::cout << "| 矢印キーで指定された方向に射撃ができる。斜め撃ちもかっこいいぞ！          |";
	}
	else if (Timer < 900)
	{
		std::cout << "| 危険な時にはスペースキーのシールドで身を守ろう！ただし使いすぎには注意だ。|";
	}
	else if (Timer < 1200)
	{
		std::cout << "| アイテムを拾うと自身の属性を変えて攻撃できる！敵と違う色だと大ダメージ！  |";
	}
	else if(Timer < 1500)
	{
		std::cout << "| 体力が0になるとゲームオーバー。気を付けてくれ。                           |";
	}
	
	gotoxy(2, 17);
	std::cout << "|                                                                           |";
	gotoxy(2, 18);
	std::cout << "|                                                                           |";
	gotoxy(2, 19);
	std::cout << "|                                                                           |";
	gotoxy(2, 20);
	std::cout << "|                                                                           |";
	gotoxy(2, 21);
	std::cout << "| 準備ができたらENTERキーでスタート！                                       |";
	gotoxy(2, 22);
	std::cout << "+---------------------------------------------------------------------------+";
}