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
///////////////
//グローバル変数
////////////////
PLAYER g_Player;


///////////////
//マクロ定義
////////////////
#define PLAYER_MOVE_SPEED_X (MOVE_SPEED_X * 1.0)
#define PLAYER_MOVE_SPEED_Y (MOVE_SPEED_Y * 1.0)
#define GRAVITY        (0.04)//重力
#define JUMP_POWER     (0.75)//ジャンプ力
#define RESIST_X       (0.4)//地上のX方向摩擦
#define RESIST_X_AIR   (0.01)//空中のX方向摩擦

//初期化処理
void InitPlayer(void)
{
	memset(&g_Player, 0, sizeof(PLAYER));
	g_Player.PosX = g_Player.OldPosX = 40;//プレイヤーのX位置
	g_Player.PosY = g_Player.OldPosY = 25;//プレイヤーのY位置

	g_Player.Direct = 0.0;//向き
	g_Player.Hit = false;//当たってない
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

#ifdef ACTION
	//アクションゲームでは使用しない
#else//シューティング用
	g_Player.SpeedY = 0;
#endif

	//カーソルキーの入力で上下左右に移動する
	if (GetKeyPress(KEYNAME::KEY_W))
	{
#ifdef ACTION
		if (g_Player.Jump)
		{
			if (!g_Player.SecondJump)
			{
				g_Player.SpeedY = -JUMP_POWER;
				g_Player.SecondJump = true;
			}
		}
#else//シューティング

		g_Player.SpeedY = -PLAYER_MOVE_SPEED_Y;
#endif
		g_Player.Direct = 90; //上向き
	}
	if (GetKeyPress(KEYNAME::KEY_A))
	{
		g_Player.SpeedX = -PLAYER_MOVE_SPEED_X;
		g_Player.Direct = 0; //左向き
	}
	if (GetKeyPress(KEYNAME::KEY_S))
	{
#ifdef ACTION
	//アクションでは使わない
#else
		g_Player.SpeedY = PLAYER_MOVE_SPEED_Y;
		g_Player.Direct = 270; //下向き
#endif
	}
	if (GetKeyPress(KEYNAME::KEY_D))
	{
		g_Player.SpeedX = PLAYER_MOVE_SPEED_X;
		g_Player.Direct = 180; //右向き
	}
	if (GetKeyTrigger(KEYNAME::KEY_SPACE))//シールド
	{
#ifdef ACTION
		if (!g_Player.Jump)
		{
			g_Player.SpeedY = -JUMP_POWER;
			g_Player.Jump = true;
		}
#else //SHOOTING用
		//シールド生成
		CreateShield(g_Player.PosX, g_Player.PosY, 1.0);

#endif
	}

	//座標更新
#ifdef ACTION

	//X座標の制御
	
	if (g_Player.Jump||g_Player.SecondJump)
	{//ジャンプ中
		g_Player.PosX += (-g_Player.SpeedX) * RESIST_X_AIR;//抵抗を加える
	}
	else
	{//地上
		g_Player.PosX += (-g_Player.SpeedX) * RESIST_X;//抵抗を加える
	}
	//ここで最終結果
	g_Player.PosX += g_Player.SpeedX;

	//Y座標の制御
	g_Player.SpeedY += GRAVITY;//重力を加える

	//ここで最終結果
	g_Player.PosY += g_Player.SpeedY;

	//地面に割り込んだ時
	if (g_Player.PosY > SCREEN_BOTTOM)
	{
		g_Player.PosY = SCREEN_BOTTOM;//地面に場所を移動させる
		g_Player.SpeedY = 0.0;//移動値のリセット
		g_Player.Jump = false;
		g_Player.SecondJump = false;
	}
#else//SHOOTING用
	g_Player.PosX += g_Player.SpeedX;
	g_Player.PosY += g_Player.SpeedY;
#endif

	//座標制御 場外に出ないようにする
	if (g_Player.PosX > SCREEN_RIGHT - 2)
	{
		g_Player.PosX = SCREEN_RIGHT - 2;
	}
	if (g_Player.PosX <  SCREEN_LEFT + 2)
	{
		g_Player.PosX = SCREEN_LEFT + 2;
	}
	if (g_Player.PosY > SCREEN_BOTTOM - 1)
	{
		g_Player.PosY = SCREEN_BOTTOM - 1;
	}
	if (g_Player.PosY < SCREEN_TOP + 1)
	{
		g_Player.PosY = SCREEN_TOP + 1;
	}

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
	std::cout << "●";
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
		direct_y += -0.5;
	}
	else if (GetKeyPress(KEYNAME::KEY_DOWN))
	{
		direct_y += 0.5;
	}

	if (GetKeyPress(KEYNAME::KEY_RIGHT))
	{
		direct_x += 1;
	}
	else if (GetKeyPress(KEYNAME::KEY_LEFT))
	{
		direct_x += -1;
	}


	//弾生成
	CreateBullet(g_Player.PosX, g_Player.PosY, direct_x, direct_y);
}