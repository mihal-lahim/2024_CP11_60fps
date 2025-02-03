#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"game.h"
#include"bullet.h"
#include"player.h"
#include"enemy.h"

void InitGame(void)
{
	InitPlayer();//	プレイヤー
	InitBullet();//　弾
	InitEnemy();//　敵
}

void UninitGame(void)
{
	UnInitPlayer();
	UnInitBullet();
	UnInitEnemy();
}

void UpdateGame(void)
{
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
}

void DrawGame(void)//書く順番注意 先に書きたいものを前に
{
	DrawEnemy();
	DrawBullet();
	DrawPlayer();
}


