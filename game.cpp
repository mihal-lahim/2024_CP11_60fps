#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"game.h"
#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"shield.h"
#include"score.h"

void InitGame(void)
{
	InitPlayer();//	プレイヤー
	InitBullet();//　弾
	InitEnemy();//　敵
	InitShield();//　シールド
	InitScore();//　スコア

}

void UninitGame(void)
{
	UnInitPlayer();
	UnInitBullet();
	UnInitEnemy();
	UnInitShield();
	UninitScore();
		
}

void UpdateGame(void)
{
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateShield();
	UpdateScore();
		
}

void DrawGame(void)//書く順番注意 先に書きたいものを前に
{
	DrawEnemy();
	DrawShield();
	DrawBullet();
	DrawPlayer();
	DrawScore();
}


