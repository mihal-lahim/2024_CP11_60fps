#ifndef _COLLISION_H_
#define _COLLISION_H_

#include"bullet.h"
#include"enemy.h"
#include"player.h"
#include"shield.h"
#include"item.h"

//キャラクターの当たり判定のサイズ　X:Y =2:1正方形
//キャラクターごとにサイズが異なるのが普通だが
//その場合は初期化で構造体へ格納しておく
#define CHARACTER_COLLISION_SIZEX (0.5)
#define CHARACTER_COLLISION_SIZEY (0.3)

//弾のサイズ
#define BULLET_COLLISION_SIZEX (0.6)
#define BULLET_COLLISION_SIZEY (0.7)

//敵のサイズ
#define ENEMY_COLLISION_SIZEX (0.5)
#define ENEMY_COLLISION_SIZEY (0.3)

//シールドのサイズ
#define SHIELD_COLLISION_SIZEX (0.5)
#define SHIELD_COLLISION_SIZEY (0.3)

//アイテムのサイズ
#define ITEM_COLLISION_SIZEX (0.5)
#define ITEM_COLLISION_SIZEY (0.3)

//敵キャラクターとプレイヤー弾の当たり判定
//敵から呼び出す関数
bool EnemyCollisionBullet(ENEMY* ptEnemy);

//プレイヤーキャラクターと敵キャラクターの当たり判定
//プレイヤーから呼び出す関数
bool PlayerCollisionEnemy(PLAYER* ptPlayer);

//シールドと敵キャラクターの当たり判定
//シールドから呼び出す関数
bool ShieldCollisionEnemy(SHIELD* ptShield);

//敵とシールドキャラクターの当たり判定
//敵から呼び出す関数
bool EnemyCollisionShield(ENEMY* ptEnemy);

//プレイヤーキャラクターとアイテムの当たり判定
//プレイヤーから呼び出す関数
int PlayerCollisionItem(PLAYER* ptPlayer);

//アイテムとプレイヤーキャラクターの当たり判定
//アイテムから呼び出す関数
bool ItemCollisionPlayer(ITEM* ptItem);
#endif
