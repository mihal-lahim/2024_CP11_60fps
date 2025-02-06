#define CONIOEX
#include"conioex.h"
#include"collision.h"
#include<iostream>

//敵キャラクターとプレイヤー弾の当たり判定
//敵から呼び出す関数
//戻り値　true 当たり　false 外れ
bool EnemyCollisionBullet(ENEMY* ptEnemy)
{
	//弾の配列のポインター取得
	BULLET* tBullet = GetBullet();

	//敵の判定用の四角形を作成
	float EnemyLeft	 = ptEnemy->PosX - ENEMY_COLLISION_SIZEX;
	float EnemyRight = ptEnemy->PosX + ENEMY_COLLISION_SIZEX;
	float EnemyUp	 = ptEnemy->PosY - ENEMY_COLLISION_SIZEY;
	float EnemyDown  = ptEnemy->PosY + ENEMY_COLLISION_SIZEY;

	//全ての弾とのチェック
	for (int i = 0; i < BULLET_MAX; i++)
	{
		//構造体が使用中か？
		if (tBullet[i].Use == true)
		{
			//弾の判定用の四角形を作成
			float BulletLeft  = tBullet->PosX - BULLET_COLLISION_SIZEX;
			float BulletRight = tBullet->PosX + BULLET_COLLISION_SIZEX;
			float BulletUp	  = tBullet->PosY - BULLET_COLLISION_SIZEY;
			float BulletDown  = tBullet->PosY + BULLET_COLLISION_SIZEY;

			//当たり判定
			if (EnemyRight < BulletLeft)
			{
				continue;
			}
			if (EnemyLeft > BulletRight)
			{
				continue;
			}
			if (EnemyUp > BulletDown)
			{
				continue;
			}	
			if (EnemyDown < BulletUp)
			{
				continue;
			}

			//敵と弾が当たった
			return true;
		}
	}
	//どの弾とも当たっていない
	return false;
}

//プレイヤーと敵キャラクターの当たり判定
//プレイヤーから呼び出す関数
//戻り値　true 当たり　false 外れ
bool PlayerCollisionEnemy(PLAYER* ptPlayer)
{
	//プレイヤーの短形を作成
	float PlayerLeft  = ptPlayer->PosX - CHARACTER_COLLISION_SIZEX;
	float PlayerRight = ptPlayer->PosX + CHARACTER_COLLISION_SIZEX;
	float PlayerUp    = ptPlayer->PosY - CHARACTER_COLLISION_SIZEY;
	float PlayerDown  = ptPlayer->PosY + CHARACTER_COLLISION_SIZEY;

	//敵キャラクターの構造体ポインタを取得
	ENEMY* tEnemy = GetEnemy();

	//全ての敵構造体配列とチェック
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//構造体が使用中か？
		if (tEnemy[i].Use == true)
		{
			//敵の短形を作成
			float EnemyLeft  = tEnemy[i].PosX - ENEMY_COLLISION_SIZEX;
			float EnemyRight = tEnemy[i].PosX + ENEMY_COLLISION_SIZEX;
			float EnemyUp    = tEnemy[i].PosY - ENEMY_COLLISION_SIZEY;
			float EnemyDown  = tEnemy[i].PosY + ENEMY_COLLISION_SIZEY;

			//当たり判定
			if (PlayerRight < EnemyLeft)
			{
				continue;
			}
			if (PlayerLeft > EnemyRight)
			{
				continue;
			}
			if (PlayerUp > EnemyDown)
			{
				continue;
			}
			if (PlayerDown < EnemyUp)
			{
				continue;
			}

			//当たり
			return true;
		}
	}
	//すべての敵と当たらなかったとき
	return false;
}

//シールドと敵キャラクターの当たり判定
//シールドから呼び出す関数
//戻り値　true 当たり　false 外れ
bool ShieldCollisionEnemy(SHIELD* ptShield)
{
	//シールドの短形を作成
	float ShieldLeft = ptShield->PosX - SHIELD_COLLISION_SIZEX;
	float ShieldRight = ptShield->PosX + SHIELD_COLLISION_SIZEX;
	float ShieldUp = ptShield->PosY - SHIELD_COLLISION_SIZEY;
	float ShieldDown = ptShield->PosY + SHIELD_COLLISION_SIZEY;

	//敵キャラクターの構造体ポインタを取得
	ENEMY* tEnemy = GetEnemy();

	//全ての敵構造体配列とチェック
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		//構造体が使用中か？
		if (tEnemy[i].Use == true)
		{
			//敵の短形を作成
			float EnemyLeft = tEnemy[i].PosX - ENEMY_COLLISION_SIZEX;
			float EnemyRight = tEnemy[i].PosX + ENEMY_COLLISION_SIZEX;
			float EnemyUp = tEnemy[i].PosY - ENEMY_COLLISION_SIZEY;
			float EnemyDown = tEnemy[i].PosY + ENEMY_COLLISION_SIZEY;

			//当たり判定
			if (ShieldRight < EnemyLeft)
			{
				continue;
			}
			if (ShieldLeft > EnemyRight)
			{
				continue;
			}
			if (ShieldUp > EnemyDown)
			{
				continue;
			}
			if (ShieldDown < EnemyUp)
			{
				continue;
			}

			//当たり
			return true;
		}
	}
	//すべての敵と当たらなかったとき
	return false;
}

//敵とシールドキャラクターの当たり判定
//敵から呼び出す関数
//戻り値　true 当たり　false 外れ
bool EnemyCollisionShield(ENEMY* ptEnemy)
{
	//敵の短形を作成
	float EnemyLeft = ptEnemy->PosX - ENEMY_COLLISION_SIZEX;
	float EnemyRight = ptEnemy->PosX + ENEMY_COLLISION_SIZEX;
	float EnemyUp = ptEnemy->PosY - ENEMY_COLLISION_SIZEY;
	float EnemyDown = ptEnemy->PosY + ENEMY_COLLISION_SIZEY;

	//シールドの構造体ポインタを取得
	SHIELD* tShield = GetShield();

	//全てのシールド構造体配列とチェック
	for (int i = 0; i < SHIELD_MAX; i++)
	{
		//構造体が使用中か？
		if (tShield[i].Use == true)
		{
			//シールドの短形を作成
			float ShieldLeft = tShield[i].PosX - SHIELD_COLLISION_SIZEX;
			float ShieldRight = tShield[i].PosX + SHIELD_COLLISION_SIZEX;
			float ShieldUp = tShield[i].PosY - SHIELD_COLLISION_SIZEY;
			float ShieldDown = tShield[i].PosY + SHIELD_COLLISION_SIZEY;

			//当たり判定
			if (ShieldRight < EnemyLeft)
			{
				continue;
			}
			if (ShieldLeft > EnemyRight)
			{
				continue;
			}
			if (ShieldUp > EnemyDown)
			{
				continue;
			}
			if (ShieldDown < EnemyUp)
			{
				continue;
			}
			//当たり
			return true;
		}
	}
	//すべての敵と当たらなかったとき
	return false;
}
