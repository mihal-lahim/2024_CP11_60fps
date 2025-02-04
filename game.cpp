#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"game.h"
#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"shield.h"

void InitGame(void)
{
	InitPlayer();//	プレイヤー
	InitBullet();//　弾
	InitEnemy();//　敵
	InitShield();//　シールド
		
}

void UninitGame(void)
{
	UnInitPlayer();
	UnInitBullet();
	UnInitEnemy();
	UnInitShield();
		
}

void UpdateGame(void)
{
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateShield();
		
}

void DrawGame(void)//書く順番注意 先に書きたいものを前に
{
	DrawEnemy();
	DrawShield();
	DrawBullet();
	DrawPlayer();
}


