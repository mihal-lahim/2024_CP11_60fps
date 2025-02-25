#ifndef _ENEMY_H_
#define _ENEMY_H_

/////////////////
//マクロ定義
////////////////
#define ENEMY_MAX (10)//同時に出現する敵の数
//#define KILL_MAX (20)//倒す敵の数

/////////////////////
//敵キャラ構造体
////////////////////
struct ENEMY
{
	float PosX;		//現在のX座標
	float PosY;		//現在のY座標

	float OldPosX;	//過去のX座標
	float OldPosY;	//過去のY座標

	float SpeedX;	//X座標の移動量
	float SpeedY;	//Y座標の移動量

	bool Use;		//使用判定
	int  Color;		//色

	bool Hit;		//ヒットフラグ
	bool ShieldHit;	//シールドヒットフラグ
	bool PlayerHit;	//プレイヤーヒットフラグ

	int	 Life;		//体力
	int  Type;		//敵のタイプ
};


////////////////////
//プロトタイプ宣言
////////////////////
void InitEnemy();
void UnInitEnemy();
void UpdateEnemy();
void DrawEnemy();

void CreateEnemy(float X, float Y, float Mx, float My,int Life,int Type);
ENEMY* GetEnemy();
#endif
