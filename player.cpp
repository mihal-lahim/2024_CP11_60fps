#define CONIOEX
#include"conioex.h"
#include"game.h"
#include"player.h"
#include<iostream>
#include"scene.h"
#include"bullet.h"
#include"collision.h"
#include"inputkey.h"
#include"shield.h"
#include"item.h"

///////////////
//グローバル変数
///////////////
PLAYER g_Player;

//初期化処理
void InitPlayer(void)
{
	memset(&g_Player, 0, sizeof(PLAYER));
	g_Player.PosX = g_Player.OldPosX = 40;//プレイヤーのX位置
	g_Player.PosY = g_Player.OldPosY = 23;//プレイヤーのY位置

	g_Player.Direct = 0.0;	//向き
	g_Player.Hit = false;	//当たってない
	g_Player.Item = ITEM_NONE;//アイテムなし
}

//終了処理
void UnInitPlayer(void)
{
}

//更新処理
void UpdatePlayer(void)
{
	//現在の位置保存
	g_Player.OldPosX = g_Player.PosX;
	g_Player.OldPosY = g_Player.PosY;

	//移動量のリセット
	g_Player.SpeedX = 0;
	g_Player.SpeedY = 0;

	//カーソルキーの入力で上下左右に移動する
	if (GetKeyPress(KEYNAME::KEY_W) && g_Player.PosY > SCREEN_TOP + 2)
	{
		g_Player.SpeedY = -PLAYER_MOVE_SPEED_Y;
		g_Player.Direct = 90; //上向き
	}
	if (GetKeyPress(KEYNAME::KEY_A) && g_Player.PosX > SCREEN_LEFT + 2)
	{
		g_Player.SpeedX = -PLAYER_MOVE_SPEED_X;
		g_Player.Direct = 0; //左向き
	}
	if (GetKeyPress(KEYNAME::KEY_S) && g_Player.PosY < SCREEN_BOTTOM - 1)
	{
		g_Player.SpeedY = PLAYER_MOVE_SPEED_Y;
		g_Player.Direct = 270; //下向き
	}
	if (GetKeyPress(KEYNAME::KEY_D) && g_Player.PosX < SCREEN_RIGHT - 2)
	{
		g_Player.SpeedX = PLAYER_MOVE_SPEED_X;
		g_Player.Direct = 180; //右向き
	}
	if (GetKeyTrigger(KEYNAME::KEY_SPACE))//シールド
	{
		//シールド生成
		CreateShield(g_Player.PosX, g_Player.PosY, 2.0);
	}

	//座標更新
	g_Player.PosX += g_Player.SpeedX;
	g_Player.PosY += g_Player.SpeedY;

	//弾発射　上下左右
	if (GetKeyPress(KEYNAME::KEY_UP)	|| GetKeyPress(KEYNAME::KEY_DOWN) ||
		GetKeyPress(KEYNAME::KEY_RIGHT) || GetKeyPress(KEYNAME::KEY_LEFT))
	{
		Shot();
	}
	
	//当たり判定///////////////////
	
	//敵キャラクターとの当たり判定
	g_Player.Hit = PlayerCollisionEnemy(&g_Player);

	if (g_Player.Hit)//プレイヤーが死んだらタイトルへ移動　現在当たったらだが、体力制御にする
	{
		//シーンをタイトルへ移動させる
		SetScene(SCENE_TITLE);
	}

	//アイテムとの当たり判定
	g_Player.ItemHit = PlayerCollisionItem(&g_Player);

	if (g_Player.ItemHit)
	{
		//アイテムタイプを入れる	
		g_Player.Item = g_Player.ItemHit;
	}
}

//描画処理
void DrawPlayer(void)
{
	//座標が変化していた場合、過去の座標を消去する
	if ((g_Player.PosX != g_Player.OldPosX) || (g_Player.PosY != g_Player.OldPosY))
	{
		gotoxy(g_Player.OldPosX, g_Player.OldPosY);
		std::cout << "  ";
	}
	//キャラクター
	gotoxy(g_Player.PosX, g_Player.PosY);

	//アイテムにより色変え
	switch (g_Player.Item)
	{
	case ITEM_NONE:
		textcolor(WHITE);
		break;
	case ITEM_FIRE:
		textcolor(RED);
		break;
	case ITEM_ICE:
		textcolor(LIGHTCYAN);
		break;
	default:
		break;
	}
	std::cout << "●";
	textcolor(WHITE);
}

//構造体情報取得
PLAYER* GetPlayer()
{
	//構造体のポインターを返す
	return &g_Player;
}

//玉発射関数
void Shot(void)
{
	//弾の速さ（加える力）の指定に使用する
	float direct_x = 0.0;//横方向
	float direct_y = 0.0;//縦方向

	if (GetKeyPress(KEYNAME::KEY_UP))
	{
		direct_y += -1.0;
	}
	else if (GetKeyPress(KEYNAME::KEY_DOWN))
	{
		direct_y += 1.0;
	}

	if (GetKeyPress(KEYNAME::KEY_RIGHT))
	{
		direct_x += 2.0;
	}
	else if (GetKeyPress(KEYNAME::KEY_LEFT))
	{
		direct_x += -2.0;
	}


	//弾生成
	CreateBullet(g_Player.PosX, g_Player.PosY, direct_x, direct_y);
}