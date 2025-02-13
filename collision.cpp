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
			float BulletLeft  = tBullet->PosX - BULLET_COLLISION_SIZEX + 0.8;
			float BulletRight = tBullet->PosX + BULLET_COLLISION_SIZEX - 0.5;
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

//プレイヤーとアイテムの当たり判定
//プレイヤーから呼び出す関数
//戻り値　アイテムコード
int PlayerCollisionItem(PLAYER* ptPlayer)
{
	//プレイヤーの短形を作成
	float PlayerLeft = ptPlayer->PosX - CHARACTER_COLLISION_SIZEX;
	float PlayerRight = ptPlayer->PosX + CHARACTER_COLLISION_SIZEX;
	float PlayerUp = ptPlayer->PosY - CHARACTER_COLLISION_SIZEY;
	float PlayerDown = ptPlayer->PosY + CHARACTER_COLLISION_SIZEY;

	//アイテムの構造体ポインタを取得
	ITEM* tItem = GetItem();

	//全てのアイテム構造体配列とチェック
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//構造体が使用中か？
		if (tItem[i].Use == true)
		{
			//アイテムの短形を作成
			float ItemLeft = tItem[i].PosX - ITEM_COLLISION_SIZEX;
			float ItemRight = tItem[i].PosX + ITEM_COLLISION_SIZEX;
			float ItemUp = tItem[i].PosY - ITEM_COLLISION_SIZEY;
			float ItemDown = tItem[i].PosY + ITEM_COLLISION_SIZEY;

			//当たり判定
			if (PlayerRight < ItemLeft)
			{
				continue;
			}
			if (PlayerLeft > ItemRight)
			{
				continue;
			}
			if (PlayerUp > ItemDown)
			{
				continue;
			}
			if (PlayerDown < ItemUp)
			{
				continue;
			}

			//当たり アイテム分け
			ptPlayer->Item = tItem[i].Type;

			switch (ptPlayer->Item)
			{
			case ITEM_FIRE:
				return ITEM_FIRE;
				break;
			case ITEM_ICE:
				return ITEM_ICE;
				break;
			default:
				break;
			}
		}
	}
	//アイテムと当たらなかったとき
	return ITEM_NONE;
}

//アイテムとプレイヤーの当たり判定
//アイテムから呼び出す関数
//戻り値　true 当たり　false 外れ
bool ItemCollisionPlayer(ITEM* ptItem)
{
	//アイテムの短形を作成
	float ItemLeft = ptItem->PosX - ITEM_COLLISION_SIZEX;
	float ItemRight = ptItem->PosX + ITEM_COLLISION_SIZEX;
	float ItemUp = ptItem->PosY - ITEM_COLLISION_SIZEY;
	float ItemDown = ptItem->PosY + ITEM_COLLISION_SIZEY;

	//プレイヤーの構造体ポインタを取得
	PLAYER* tPlayer = GetPlayer();

	//プレイヤーの短形を作成
	float PlayerLeft = tPlayer->PosX - CHARACTER_COLLISION_SIZEX;
	float PlayerRight = tPlayer->PosX + CHARACTER_COLLISION_SIZEX;
	float PlayerUp = tPlayer->PosY - CHARACTER_COLLISION_SIZEY;
	float PlayerDown = tPlayer->PosY + CHARACTER_COLLISION_SIZEY;

	//当たり判定
	if (PlayerRight < ItemLeft || PlayerLeft > ItemRight|| 
		PlayerUp    > ItemDown || ItemUp   > PlayerDown)
	{
		return false;
	}
	return true;
}

//敵とプレイヤーの当たり判定
//敵から呼び出す関数
//戻り値　true 当たり　false 外れ
bool EnemyCollisionPlayer(ENEMY* ptEnemy)
{
	//敵の短形を作成
	float EnemyLeft = ptEnemy->PosX - ENEMY_COLLISION_SIZEX;
	float EnemyRight = ptEnemy->PosX + ENEMY_COLLISION_SIZEX;
	float EnemyUp = ptEnemy->PosY - ENEMY_COLLISION_SIZEY;
	float EnemyDown = ptEnemy->PosY + ENEMY_COLLISION_SIZEY;

	//プレイヤーの構造体ポインタを取得
	PLAYER* tPlayer = GetPlayer();

	//プレイヤーの短形を作成
	float PlayerLeft = tPlayer->PosX - CHARACTER_COLLISION_SIZEX;
	float PlayerRight = tPlayer->PosX + CHARACTER_COLLISION_SIZEX - 0.5;
	float PlayerUp = tPlayer->PosY - CHARACTER_COLLISION_SIZEY;
	float PlayerDown = tPlayer->PosY + CHARACTER_COLLISION_SIZEY - 0.4;

	//当たり判定
	if (PlayerRight < EnemyLeft || PlayerLeft > EnemyRight ||
		PlayerUp > EnemyDown || EnemyUp > PlayerDown)
	{
		return false;
	}
	return true;
}

//プレイヤーと敵キャラクターの当たり判定
//プレイヤーから呼び出す関数
//戻り値　true 当たり　false 外れ
bool PlayerCollisionEnemy(PLAYER* ptPlayer)
{
	//プレイヤーの短形を作成
	float PlayerLeft = ptPlayer->PosX - CHARACTER_COLLISION_SIZEX;
	float PlayerRight = ptPlayer->PosX + CHARACTER_COLLISION_SIZEX - 0.5;
	float PlayerUp = ptPlayer->PosY - CHARACTER_COLLISION_SIZEY;
	float PlayerDown = ptPlayer->PosY + CHARACTER_COLLISION_SIZEY - 0.4;

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

