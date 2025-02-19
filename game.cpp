#define CONIOEX
#include"conioex.h"
#include<iostream>
#include"game.h"
#include"bullet.h"
#include"player.h"
#include"enemy.h"
#include"shield.h"
#include"score.h"
#include"field.h"
#include"item.h"
#include"UI.h"

void InitGame(void)
{
	InitPlayer();	//	プレイヤー
	InitBullet();	//　弾
	InitEnemy();	//　敵
	InitShield();	//　シールド
	InitScore();	//　スコア
	//InitField();	//　フィールド
	InitItem();		//　アイテム
	InitUI();		//UI

}

void UninitGame(void)
{
	UnInitPlayer();
	UnInitBullet();
	UnInitEnemy();
	UnInitShield();
	UninitScore();
	//UnInitField();
	UninitItem();
	UnInitUI();
}

void UpdateGame(void)
{
	UpdatePlayer();
	UpdateBullet();
	UpdateEnemy();
	UpdateShield();
	UpdateScore();
	//UpdateField();
	UpdateItem();
	UpdateUI();
		
}

void DrawGame(void)//書く順番要調整 先に書きたいものを前に
{
	//DrawField();
	DrawEnemy();
	DrawBullet();
	DrawShield();
	DrawPlayer();
	DrawItem();
	//DrawScore();
	DrawUI();
}


