#define CONIOEX
#include"conioex.h"
#include<iostream>
#include "game.h"
#include "enemy.h"
#include"collision.h"
#include"scene.h"
#include"score.h"
#include"item.h"


///////////////////////////////////////
//グローバル変数
///////////////////////////////////////
ENEMY g_Enemy[ENEMY_MAX];//敵構造体配列
int g_KillCount = 0;//キル数
DWORD StageClearTime;//クリアタイム
DWORD StageBetween;//ステージとステージの間

///////////////////////////////////////
//敵キャラ初期配置情報　構造体
///////////////////////////////////////
struct EnemyData
{
	float X, Y;		//座標情報
	float Mx, My;	//移動量
	int Color;		//キャラクターカラー
	int Life;		//敵の体力
	int Type;		//タイプ
};
///////////////////////////////////////
//敵初期配置データテーブル
///////////////////////////////////////
EnemyData g_EnemyTable[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{18,	8	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //1体目
		{20,	4	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //2体目
		{30,	6	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //3体目
		{40,	8	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //4体目
		{40,	10	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //5体目
		{30,	4	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //6体目
		{30,	10	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //7体目
		{40,	6	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //8体目
		{50,	3	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //9体目
		{40,	6	,  0.2f,	 0.1f,	WHITE,2,ITEM_ICE}, //10体目
};


//EnemyData g_EnemyTable[] =
//{
//	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
//		{18,	8	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //1体目
//		{20,	4	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //2体目
//		{30,	6	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //3体目
//		{40,	8	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //4体目
//		{40,	10	,  0.2f,	 0.1f,	RED,2,ITEM_FIRE}, //5体目
//		{30,	4	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //6体目
//		{30,	10	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //7体目
//		{40,	6	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //8体目
//		{50,	3	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //9体目
//		{40,	6	,  0.2f,	 0.1f,	LIGHTCYAN,2,ITEM_ICE}, //10体目
//};

EnemyData g_EnemyTable2[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{19,	20	,  0.6f,	 0.15f,	RED,1,ITEM_FIRE}, //1体目
		{16,	20	,  0.25f,	 0.15f,	RED,1,ITEM_FIRE}, //2体目
		{24,	20	,  0.2f,	 0.15f,	RED,1,ITEM_FIRE}, //3体目
		{32,	20	,  0.3f,	 0.15f,	RED,1,ITEM_FIRE}, //4体目
		{40,	20	,  0.25f,	 0.15f,	RED,1,ITEM_FIRE}, //5体目
		{48,	20	,  0.2f,	 0.15f,	RED,1,ITEM_FIRE}, //6体目
		{56,	20	,  0.15f,	 0.15f,	RED,1,ITEM_FIRE}, //7体目
		{29,	20	,  0.1f,	 0.15f,	RED,1,ITEM_FIRE}, //8体目
		{57,	20	,  0.05f,	 0.15f,	RED,1,ITEM_FIRE}, //9体目
		{24,	20	,  0.0f,	 0.15f,	RED,1,ITEM_FIRE}, //10体目
};

EnemyData g_EnemyTable3[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{19,	20	,  0.6f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //1体目
		{16,	20	,  0.25f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //2体目
		{24,	20	,  0.2f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //3体目
		{32,	20	,  0.3f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //4体目
		{40,	20	,  0.25f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //5体目
		{48,	20	,  0.2f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //6体目
		{56,	20	,  0.15f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //7体目
		{29,	20	,  0.1f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //8体目
		{57,	20	,  0.05f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //9体目
		{24,	20	,  0.0f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //10体目
};

EnemyData g_EnemyTable4[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{19,	20	,  0.6f,	 0.15f,	RED,1,ITEM_FIRE}, //1体目
		{16,	20	,  0.25f,	 0.15f,	RED,1,ITEM_FIRE}, //2体目
		{24,	20	,  0.2f,	 0.15f,	RED,1,ITEM_FIRE}, //3体目
		{32,	20	,  0.3f,	 0.15f,	RED,1,ITEM_FIRE}, //4体目
		{40,	20	,  0.25f,	 0.15f,	RED,1,ITEM_FIRE}, //5体目
		{48,	20	,  0.2f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //6体目
		{56,	20	,  0.15f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //7体目
		{29,	20	,  0.1f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //8体目
		{57,	20	,  0.05f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //9体目
		{24,	20	,  0.0f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //10体目
};

EnemyData g_EnemyTable5[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{19,	20	,  0.6f,	 0.15f,	RED,1,ITEM_FIRE}, //1体目
		{16,	20	,  0.25f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //2体目
		{24,	20	,  0.2f,	 0.15f,	RED,1,ITEM_FIRE}, //3体目
		{32,	20	,  0.3f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //4体目
		{40,	20	,  0.25f,	 0.15f,	RED,1,ITEM_FIRE}, //5体目
		{48,	20	,  0.2f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //6体目
		{56,	20	,  0.15f,	 0.15f,	RED,1,ITEM_FIRE}, //7体目
		{29,	20	,  0.1f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //8体目
		{57,	20	,  0.05f,	 0.15f,	RED,1,ITEM_FIRE}, //9体目
		{24,	20	,  0.0f,	 0.15f,	LIGHTCYAN,1,ITEM_ICE}, //10体目
};



//初期化
void InitEnemy()
{
	//構造体の中を0でクリア
	memset(&g_Enemy[0], 0, sizeof(ENEMY) * ENEMY_MAX);

	//最初にテーブルの情報を使って敵を作成しておく
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		CreateEnemy(g_EnemyTable[i].X, g_EnemyTable[i].Y, g_EnemyTable[i].Mx, g_EnemyTable[i].My, g_EnemyTable[i].Color,g_EnemyTable[i].Life, g_EnemyTable[i].Type);
	}

	//クリアタイム/ステージ間の初期化
	StageClearTime = timeGetTime();

	//間の初期化
	StageBetween = 0;
}

//終了処理
void UnInitEnemy()
{

}

//更新処理
void UpdateEnemy()
{
	//スコア取得
	int Score = GetScore()->nPoint;
	//敵を倒した数
	int KillCount = 0;
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

			//下
			else if (g_Enemy[i].PosY > SCREEN_BOTTOM)
			{
				g_Enemy[i].SpeedY *= -1.0;//移動量の反転
				g_Enemy[i].PosY = SCREEN_BOTTOM;
			}

			//左
			if (g_Enemy[i].PosX < SCREEN_LEFT + 1)
			{
				g_Enemy[i].SpeedX *= -1.0;//移動量の反転
				g_Enemy[i].PosX = SCREEN_LEFT + 1;
			}

			//右
			else if (g_Enemy[i].PosX > SCREEN_RIGHT - 1)
			{
				g_Enemy[i].SpeedX *= -1.0;//移動量の反転
				g_Enemy[i].PosX = SCREEN_RIGHT - 1;
			}

			/////当たり判定/////////////////

			//弾との当たり判定
			g_Enemy[i].Hit = EnemyCollisionBullet(&g_Enemy[i]);

			//シールドとの当たり判定
			g_Enemy[i].ShieldHit = EnemyCollisionShield(&g_Enemy[i]);

			//プレイヤーとの当たり判定
			g_Enemy[i].PlayerHit = EnemyCollisionPlayer(&g_Enemy[i]);

			//敵に弾が当たると体力が減り、消える
			if (g_Enemy[i].Hit)
			{
				BULLET* bullet = GetBullet();

				//敵のタイプと弾のタイプを比較して与えられるダメージを決定する
				switch (bullet->Type)
				{
				case ITEM_NONE:
					g_Enemy[i].Life -= 2;
					break;
				case ITEM_FIRE:
					//同タイプなら与えるダメージが減る
					if (bullet->Type == g_Enemy[i].Type)
					{
						g_Enemy[i].Life--;
					}
					//違うタイプなら与えるダメージが増える
					else
					{
						g_Enemy[i].Life -= 5;
					}
					break;
				case ITEM_ICE:
					//同タイプなら与えるダメージが減る
					if (bullet->Type == g_Enemy[i].Type)
					{
						g_Enemy[i].Life--;
					}
					//違うタイプなら与えるダメージが増える
					else
					{
						g_Enemy[i].Life -= 5;
					}
					break;
				default:
					break;
				}

				g_Enemy[i].Hit = false;

				if (g_Enemy[i].Life < 1)
				{
					g_Enemy[i].Use = false;
					AddPoint(10);//スコア加算
				}
			}

			//シールドに当たると跳ね返る
			if (g_Enemy[i].ShieldHit || g_Enemy[i].PlayerHit)
			{
				//移動量の反転
				g_Enemy[i].SpeedX *= -1;
				g_Enemy[i].SpeedY *= -1;
			}
		}
		else//てきがいないとき
		{
			KillCount++;

			//全員死んだら次の敵出す
			if (KillCount == ENEMY_MAX)
			{
				if (StageBetween == 0)
				{
					StageBetween = timeGetTime();
				}
				else if (timeGetTime() - StageBetween > 5000)
				{
					//クリア
					PLAYER* Player = GetPlayer();
					Player->Stage++;

					//クリアタイムの加算
					Player->ClearTime += timeGetTime() - StageClearTime;
					StageClearTime = timeGetTime();

					//クリアした層により出す敵変える
					switch (Player->Stage)
					{
					case 2:
						//５秒ディレイ
						if (timeGetTime() - StageBetween > 5000)
						{
							//ステージ３
							for (int j = 0; j < ENEMY_MAX; j++)
							{
								CreateEnemy(g_EnemyTable2[j].X, g_EnemyTable2[j].Y, g_EnemyTable2[j].Mx, g_EnemyTable2[j].My, g_EnemyTable2[j].Color, g_EnemyTable2[j].Life, g_EnemyTable2[j].Type);
							}
							StageBetween = 0;
						}
						break;
					case 3:
						//５秒ディレイ
						if (timeGetTime() - StageBetween > 5000)
						{
							//ステージ３
							for (int j = 0; j < ENEMY_MAX; j++)
							{
								CreateEnemy(g_EnemyTable3[j].X, g_EnemyTable3[j].Y, g_EnemyTable3[j].Mx, g_EnemyTable3[j].My, g_EnemyTable3[j].Color, g_EnemyTable3[j].Life, g_EnemyTable3[j].Type);
							}
							StageBetween = 0;
						}
						break;
					case 4:
						//５秒ディレイ
						if (timeGetTime() - StageBetween > 5000)
						{
							//ステージ４
							for (int j = 0; j < ENEMY_MAX; j++)
							{
								CreateEnemy(g_EnemyTable4[j].X, g_EnemyTable4[j].Y, g_EnemyTable4[j].Mx, g_EnemyTable4[j].My, g_EnemyTable4[j].Color, g_EnemyTable4[j].Life, g_EnemyTable4[j].Type);
							}
							StageBetween = 0;
						}
						break;
					case 5:
						//５秒ディレイ
						if (timeGetTime() - StageBetween > 5000)
						{
							//ステージ４
							for (int j = 0; j < ENEMY_MAX; j++)
							{
								CreateEnemy(g_EnemyTable5[j].X, g_EnemyTable5[j].Y, g_EnemyTable5[j].Mx, g_EnemyTable5[j].My, g_EnemyTable5[j].Color, g_EnemyTable5[j].Life, g_EnemyTable5[j].Type);
							}
							StageBetween = 5000;
						}
						break;
					default:
						break;
					}
				}
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
				std::cout << "　";

				gotoxy(g_Enemy[i].PosX, g_Enemy[i].PosY);

				textcolor(g_Enemy[i].Color);//色変え
				std::cout << "><";
				textcolor(WHITE);//色変え
			}
			
			
#ifdef _DEBUG
			/*gotoxy(2, 5 + i);
			std::cout << g_Enemy[i].PosX << "  "<<g_Enemy[i].PosY << "  ";*/
#endif _DEBUG

			//体力がなくなったら
			if (g_Enemy[i].Life < 1)
			{
				g_Enemy[i].Life = 0;
				gotoxy(g_Enemy[i].PosX, g_Enemy[i].PosY);
				std::cout << "　";
			}
		}
	}
}


//生成処理
void CreateEnemy(float X, float Y, float Mx, float My, int Color,int Life,int Type)
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
			g_Enemy[i].Type = Type;

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