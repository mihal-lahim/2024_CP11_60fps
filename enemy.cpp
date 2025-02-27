#define CONIOEX
#include"conioex.h"
#include<iostream>
#include "game.h"
#include "enemy.h"
#include"collision.h"
#include"scene.h"
#include"score.h"
#include"item.h"

//////////////////
//グローバル変数//
//////////////////
ENEMY g_Enemy[ENEMY_MAX];//敵構造体配列
int g_KillCount = 0;//キル数
DWORD StageClearTime;//クリアタイム

DWORD StageBetween;//ステージとステージの間
int countdownValue = 5; // カウントダウンの初期値
DWORD lastCountdownUpdate = 0; // 最後にカウントダウンを更新した時間
bool EndCountDown;
int CountDownHyouji = 4;//表示回数の限界


////////////////////////////////
//敵キャラ初期配置情報　構造体//
////////////////////////////////
struct EnemyData
{
	float X, Y;		//座標情報
	float Mx, My;	//移動量
	int Life;		//敵の体力
	int Type;		//タイプ
};

////////////////////////////
//敵初期配置データテーブル//
////////////////////////////
EnemyData g_EnemyTable[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{17,	14	,  0.1f,	 0.0f,	20,ITEM_FIRE}, //1体目
		{19,	12	,  0.1f,	 0.0f,	20,ITEM_FIRE}, //2体目
		{21,	10	,  0.1f,	 0.0f,	20,ITEM_FIRE}, //3体目
		{23,	8	,  0.1f,	 0.0f,	20,ITEM_FIRE}, //4体目
		{25,	6	,  0.1f,	 0.0f,	20,ITEM_FIRE}, //5体目
										
		{54,	6	,  -0.1f,	 0.0f,	20,ITEM_ICE}, //6体目
		{56,	8	,  -0.1f,	 0.0f,	20,ITEM_ICE}, //7体目
		{58,	10	,  -0.1f,	 0.0f,	20,ITEM_ICE}, //8体目
		{60,	12	,  -0.1f,	 0.0f,	20,ITEM_ICE}, //9体目
		{62,	14	,  -0.1f,	 0.0f,	20,ITEM_ICE}, //10体目
};

EnemyData g_EnemyTable2[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{17,	2	,  0.2f,	 0.15f,20,ITEM_FIRE}, //1体目
		{17,	3	,  0.19f,	 0.16f,20,ITEM_FIRE}, //2体目
		{17,	4	,  0.18f,	 0.17f,20,ITEM_FIRE}, //3体目
		{17,	5	,  0.17f,	 0.18f,20,ITEM_FIRE}, //4体目
		{17,	6	,  0.16f,	 0.19f,20,ITEM_FIRE}, //5体目
									   
		{17,	7	,  0.15f,	 0.20f,20,ITEM_FIRE}, //6体目
		{17,	8	,  0.14f,	 0.21f,20,ITEM_FIRE}, //7体目
		{17,	9	,  0.13f,	 0.22f,20,ITEM_FIRE}, //8体目
		{17,	9	,  0.12f,	 0.23f,20,ITEM_FIRE}, //9体目
		{17,	10	,  0.11f,	 0.24f,20,ITEM_FIRE}, //10体目
};

EnemyData g_EnemyTable3[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{62,	14	,  -0.11f,	 -0.15f,20,ITEM_ICE}, //1体目
		{62,	15	,  -0.12f,	 -0.14f,20,ITEM_ICE}, //2体目
		{62,	16	,  -0.13f,	 -0.13f,20,ITEM_ICE}, //3体目
		{62,	17	,  -0.14f,	 -0.12f,20,ITEM_ICE}, //4体目
		{62,	18	,  -0.15f,	 -0.11f,20,ITEM_ICE}, //5体目
		{62,	19	,  -0.16f,	 -0.10f,20,ITEM_ICE}, //6体目
		{62,	20	,  -0.17f,	 -0.09f,20,ITEM_ICE}, //7体目
		{62,	21	,  -0.18f,	 -0.08f,20,ITEM_ICE}, //8体目
		{62,	22	,  -0.19f,	 -0.07f,20,ITEM_ICE}, //9体目
		{62,	23	,  -0.2f,	 -0.06f,20,ITEM_ICE}, //10体目





};

EnemyData g_EnemyTable4[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{18,	2	,   0.15f,	 0.15f,50,ITEM_FIRE}, //1体目
		{20,	2	,   0.16f,	 0.14f,50,ITEM_FIRE}, //2体目
		{22,	2	,   0.17f,	 0.13f,50,ITEM_FIRE}, //3体目
		{24,	2	,   0.18f,	 0.12f,50,ITEM_FIRE}, //4体目
		{26,	2	,   0.19f,	 0.11f,50,ITEM_FIRE}, //5体目
									   
		{52,	2	,  -0.15f,	-0.15f,50,ITEM_ICE}, //6体目
		{54,	2	,  -0.16f,	-0.14f,50,ITEM_ICE}, //7体目
		{58,	2	,  -0.17f,	-0.13f,50,ITEM_ICE}, //8体目
		{60,	2	,  -0.18f,	-0.12f,50,ITEM_ICE}, //9体目
		{62,	2	,  -0.19f,	-0.11f,50,ITEM_ICE}, //10体目
};

EnemyData g_EnemyTable5[] =
{
	//	X位置,Y位置,X移動力,Y移動力,敵色,	  体力,タイプ
		{17,	12	,  0.2f,	 0.10f,	70,ITEM_FIRE}, //1体目
		{23,	6	,  0.1f,	 0.1f,	70,ITEM_ICE}, //2体目
		{39,	2	,  0.0f,	 0.10f,	70,ITEM_FIRE}, //3体目
		{55,	6	, -0.1f,	 0.1f,	70,ITEM_ICE}, //4体目
		{63,	12	, -0.2f,	 0.10f,	70,ITEM_FIRE}, //5体目

		{17,	14	,  0.2f,	 -0.10f,70,ITEM_ICE}, //6体目
		{23,	17	,  0.1f,	 -0.1f,	70,ITEM_FIRE}, //7体目
		{39,	23	,  0.0f,	 -0.10f,70,ITEM_ICE}, //8体目
		{55,	17	, -0.1f,	 -0.1f,	70,ITEM_FIRE}, //9体目
		{63,	14	, -0.2f,	 -0.10f,70,ITEM_ICE}, //10体目
};

//初期化処理
void InitEnemy() {
	// 構造体の中を0でクリア
	memset(&g_Enemy[0], 0, sizeof(ENEMY) * ENEMY_MAX);

	// 最初に敵を作成しておく
	for (int i = 0; i < ENEMY_MAX; i++) {

		CreateEnemy(g_EnemyTable[i].X, g_EnemyTable[i].Y, g_EnemyTable[i].Mx, g_EnemyTable[i].My, g_EnemyTable[i].Life, g_EnemyTable[i].Type);
	}
	// クリアタイム/ステージ間の初期化
	StageClearTime = timeGetTime();
	StageBetween = 0;
	
	//カウントダウン終わってないよ
	EndCountDown = false;

	//表示回数の限界
	CountDownHyouji = 4;
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
			//敵に弾が当たると体力が減り、体力が０になると消える
			if (g_Enemy[i].Hit)
			{
				//使用中のみ当たり判定あり
				if (g_Enemy[i].Use)
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
					//ヒットフラグをfalseにする
					g_Enemy[i].Hit = false;
					if (g_Enemy[i].Life < 1)
					{
						g_Enemy[i].Use = false;
						gotoxy(g_Enemy[i].PosX - 2, g_Enemy[i].PosY);
						std::cout << "     ";
						AddPoint(100);//スコア加算
					}
					//プレイヤー情報取得
					PLAYER* Player = GetPlayer();
					//当たった情報を飛ばす
					Player->HitCount++;
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
				//現在時間
				if (StageBetween == 0)
				{
					StageBetween = timeGetTime();
					lastCountdownUpdate = StageBetween;
					countdownValue = 5; // カウントダウンの初期値
				}
				//カウントダウンの更新
				DWORD currentTime = timeGetTime();
				if (currentTime - lastCountdownUpdate >= 1000)
				{
					countdownValue--;
					lastCountdownUpdate = currentTime;
				}
				//５秒ディレイ
				if (timeGetTime() - StageBetween > 5000)
				{
					//クリア
					PLAYER* Player = GetPlayer();
					Player->Stage++;
					//２個に復活させる
					Player->ShieldCharge = 2;
					//クリアタイムの加算
					Player->ClearTime += timeGetTime() - StageClearTime;
					StageClearTime = currentTime;
					//カウントダウン終わったよ
					EndCountDown = true;
					//クリアした層により出す敵変える
					switch (Player->Stage)
					{
					case 2:
						//ステージ３
						for (int j = 0; j < ENEMY_MAX; j++)
						{
							CreateEnemy(g_EnemyTable2[j].X, g_EnemyTable2[j].Y, g_EnemyTable2[j].Mx, g_EnemyTable2[j].My, g_EnemyTable2[j].Life, g_EnemyTable2[j].Type);
						}
						StageBetween = 0;
						break;
					case 3:
						//ステージ３
						for (int j = 0; j < ENEMY_MAX; j++)
						{
							CreateEnemy(g_EnemyTable3[j].X, g_EnemyTable3[j].Y, g_EnemyTable3[j].Mx, g_EnemyTable3[j].My, g_EnemyTable3[j].Life, g_EnemyTable3[j].Type);
						}
						StageBetween = 0;
						break;
					case 4:
						//ステージ４
						for (int j = 0; j < ENEMY_MAX; j++)
						{
							CreateEnemy(g_EnemyTable4[j].X, g_EnemyTable4[j].Y, g_EnemyTable4[j].Mx, g_EnemyTable4[j].My, g_EnemyTable4[j].Life, g_EnemyTable4[j].Type);
						}
						StageBetween = 0;
						break;
					case 5:
						//ステージ５
						for (int j = 0; j < ENEMY_MAX; j++)
						{
							CreateEnemy(g_EnemyTable5[j].X, g_EnemyTable5[j].Y, g_EnemyTable5[j].Mx, g_EnemyTable5[j].My, g_EnemyTable5[j].Life, g_EnemyTable5[j].Type);
						}
						StageBetween = 5000;
						
						break;
					default:
						break;
					}
					//カウントダウン終わったよ
					EndCountDown = true;
					//残り表示回数減らす
					CountDownHyouji--;
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
				std::cout << "  ";
				gotoxy(g_Enemy[i].PosX, g_Enemy[i].PosY);
				textcolor(g_Enemy[i].Color);//色変え
				std::cout << "><";
				textcolor(WHITE);//色変え
			}
			//体力がなくなったら
			if (g_Enemy[i].Life < 1)
			{
				g_Enemy[i].Life = 0;
				gotoxy(g_Enemy[i].PosX - 2, g_Enemy[i].PosY);
				std::cout << "    ";
			}
		}
	}
	// カウントダウンの値を描画
	if (StageBetween != 0 && CountDownHyouji > 0)
	{
		PLAYER* Player = GetPlayer();
		// 画面中央に表示
		if (countdownValue == 5 || countdownValue == 4)
		{
			gotoxy(33, 11);
			std::cout << "STAGE " << Player->Stage << " CLEAR!!";
		}
		else
		{
			gotoxy(28, 11);
			std::cout << "Next stage in: " << countdownValue << " seconds";
		}
		
	}
	if (EndCountDown == true)
	{
		gotoxy(28, 11); // 画面中央に表示
		std::cout << "                         ";
		EndCountDown = false;
	}
}

//生成処理
void CreateEnemy(float X, float Y, float Mx, float My, int Life, int Type)
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
			g_Enemy[i].Type = Type;
			//タイプによりカラー指定
			switch (g_Enemy[i].Type)
			{
			case ITEM_FIRE:
				g_Enemy[i].Color = RED;
				break;
			case ITEM_ICE:
				g_Enemy[i].Color = LIGHTCYAN;
				break;
			default:
				break;
			}
			g_Enemy[i].Life = Life;
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