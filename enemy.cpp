#define CONIOEX
#include"conioex.h"
#include<iostream>
#include "game.h"
#include "enemy.h"
#include"collision.h"
#include"scene.h"
#include"score.h"


///////////////////////////////////////
//グローバル変数
///////////////////////////////////////
ENEMY g_Enemy[ENEMY_MAX];//敵構造体配列
///////////////////////////////////////
//敵キャラ初期配置情報　構造体
///////////////////////////////////////
struct EnemyData
{
	float X, Y;		//座標情報
	float Mx, My;	//移動量
	int Color;		//キャラクターカラー
	int Life;		//敵の体力
};
///////////////////////////////////////
//敵初期配置データテーブル
///////////////////////////////////////
EnemyData g_EnemyTable[] =
{
//	X位置, Y位置, X移動力,Y移動力,敵色,		   体力
	{10.0,	10.0,	 0.20,	-0.20,GREEN,		 1}, //1体目
	{20.0,	04.0,	-0.20,	-0.45,MAGENTA, 		 1}, //2体目
	{30.0,	13.0,	-0.15,	 0.25,BROWN,		 1}, //3体目
	{40.0,	23.0,	 0.10,	-0.30,CYAN,			 1}, //4体目
	{27.0,	17.0,	 0.20,	 0.10,GREEN,		 1}, //5体目
	{78.0,	01.0,	 0.30,	 0.20,LIGHTCYAN,	 1}, //6体目
	{59.0,	06.0,	-0.30,	 0.20,LIGHTMAGENTA,  1}, //7体目
	{12.0,	13.0,	-0.20,	 0.10,YELLOW,		 1}, //8体目
	{64.0,	06.0,	-0.10,	 0.00,LIGHTBLUE,	 1}, //9体目
	{31.0,	02.0,	-0.30,	 0.50,DARKGRAY,	     1}, //10体目
};

//初期化
void InitEnemy()
{
	//構造体の中を0でクリア
	memset(&g_Enemy[0], 0, sizeof(ENEMY) * ENEMY_MAX);

	//最初にテーブルの情報を使って敵を作成しておく
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		CreateEnemy(g_EnemyTable[i].X, g_EnemyTable[i].Y, g_EnemyTable[i].Mx, g_EnemyTable[i].My, g_EnemyTable[i].Color,g_EnemyTable[i].Life);
	}
}

//終了処理
void UnInitEnemy()
{

}

//更新処理
void UpdateEnemy()
{
	int EnemyScore = 0;//敵を倒した数

	SCORE* tScore = GetScore();//スコアの取得
	PLAYER* tPlayer = GetPlayer();//プレイヤーの取得

	//使用中の構造体をすべて更新する
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//構造体が使用中なら更新する
		if (g_Enemy[i].Use == true)
		{
			
			//現在の座標をOldへ保存
			g_Enemy[i].OldPosX = g_Enemy[i].PosX;
			g_Enemy[i].OldPosY = g_Enemy[i].PosY;

			//現在の座標へ移動量を加算
			g_Enemy[i].PosX += g_Enemy[i].SpeedX;
			g_Enemy[i].PosY += g_Enemy[i].SpeedY;

			//壁衝突
			//上
			if (g_Enemy[i].PosY < SCREEN_TOP)
			{
				g_Enemy[i].SpeedY *= -1.0;//移動量の反転
				g_Enemy[i].PosY = SCREEN_TOP;
			}

			//上
			else if (g_Enemy[i].PosY > SCREEN_BOTTOM)
			{
				g_Enemy[i].SpeedY *= -1.0;//移動量の反転
				g_Enemy[i].PosY = SCREEN_BOTTOM;
			}

			//左
			if (g_Enemy[i].PosX < SCREEN_LEFT)
			{
				g_Enemy[i].SpeedX *= -1.0;//移動量の反転
				g_Enemy[i].PosX = SCREEN_LEFT;
			}

			//右
			else if (g_Enemy[i].PosX > SCREEN_RIGHT)
			{
				g_Enemy[i].SpeedX *= -1.0;//移動量の反転
				g_Enemy[i].PosX = SCREEN_RIGHT;
			}
		}

		//弾との当たり判定
		g_Enemy[i].Hit = EnemyCollisionBullet(&g_Enemy[i]);

		//敵に弾が当たると消える
		if (g_Enemy[i].Hit)
		{

			g_Enemy[i].Life--;
			g_Enemy[i].Hit = false;
			if (g_Enemy[i].Life < 1)
			{
				g_Enemy[i].Use = false;
				AddPoint(1);//スコア加算
			}
		}
	}
	
}

//描画処理
void DrawEnemy()
{
	//使用中の構造体をすべて表示する
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//構造体が使用中
		if (g_Enemy[i].Use == true)
		{
			//前回の位置から移動したか？Y座標でも確認が必要
			if (g_Enemy[i].OldPosX != g_Enemy[i].PosX ||
				g_Enemy[i].OldPosY != g_Enemy[i].PosY)
			{
				gotoxy(g_Enemy[i].OldPosX, g_Enemy[i].OldPosY);
				std::cout << "  ";
			}
			gotoxy(g_Enemy[i].PosX, g_Enemy[i].PosY);
			textcolor(g_Enemy[i].Color);//色変え
			std::cout << "◆";
			textcolor(WHITE);//色変え
		}
		if (g_Enemy[i].Life < 1)
		{
			gotoxy(g_Enemy[i].PosX, g_Enemy[i].PosY);
			textcolor(g_Enemy[i].Color);//色変え
			std::cout << "  ";
			textcolor(WHITE);//色変え
		}
	}
}


//生成処理
void CreateEnemy(float X, float Y, float Mx, float My, int Color,int Life)
{
	//未使用の構造体を見つけて、敵のデータをセット
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//構造体が未使用なら
		if (g_Enemy[i].Use == false)
		{
			g_Enemy[i].PosX = g_Enemy[i].OldPosX = X;
			g_Enemy[i].PosY = g_Enemy[i].OldPosY = Y;
			g_Enemy[i].SpeedX = Mx;
			g_Enemy[i].SpeedY = My;
			g_Enemy[i].Color  = Color;
			g_Enemy[i].Life   = Life;

			g_Enemy[i].Use = true;//使用中にする

			break;//敵一つ生成したら終了
		}
	}
}

//構造体情報取得
ENEMY* GetEnemy()
{
	//敵の構造体配列の先頭のポインターを返す
	return &g_Enemy[0];
}