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
#include"score.h"
#include"result.h"

///////////////
//グローバル変数
///////////////
PLAYER g_Player;
DWORD LastHitTime;//最後に当たった時間
int CountShield;//シールドの数

//初期化処理
void InitPlayer(void)
{
	memset(&g_Player, 0, sizeof(PLAYER));
	g_Player.PosX =  40;//プレイヤーのX位置
	g_Player.PosY =  22;//プレイヤーのY位置
	g_Player.OldPosX = 0;
	g_Player.OldPosY = 0;
	g_Player.Direct = 0.0;		//向き
	g_Player.Hit = false;		//当たってない
	g_Player.Item = ITEM_NONE;	//アイテムなし
	g_Player.ItemGetCount = 0;	//アイテム取得数
	g_Player.Life = 1;			//体力１
	g_Player.Stage = 1;			//現在のステージ
	g_Player.ClearTime = 0;		//クリアタイム
	g_Player.ShieldCharge = 2;	//シールド利用可能数
	g_Player.Heat = 36.0;		//温度
	g_Player.HeatSpeed = 1;		//速度乗算値
	g_Player.DamageCollTime = 1000;//ダメージクールタイム
	RESULT* Result = GetResult();
	Result->TimeBonus = 25000;	//タイムボーナス

	LastHitTime = timeGetTime() + 2000;//最後に当たった時間を初期化
}

//終了処理
void UnInitPlayer(void)
{
}

//更新処理
void UpdatePlayer(void)
{
	//移動量のリセット
	g_Player.SpeedX = 0;
	g_Player.SpeedY = 0;
	//速度値のリセット
	g_Player.HeatSpeed = 1;
	//カーソルキーの入力で上下左右に移動する
	if (GetKeyPress(KEYNAME::KEY_W) && g_Player.PosY > SCREEN_TOP + 2)
	{
		g_Player.SpeedY = -PLAYER_MOVE_SPEED_Y;
		//g_Player.Direct = 90; //上向き
		//熱量を移動力に変換
		g_Player.HeatSpeed += (g_Player.Heat - 36) / 2;
		g_Player.SpeedY *= g_Player.HeatSpeed;
		//速度上限値
		if (g_Player.SpeedY < -0.3)
		{
			g_Player.SpeedY = -0.3;
		}
		if (g_Player.SpeedY > -0.12)//W(↑)押して正の値になってしまったら負の限りなく小さい数に
		{
			g_Player.SpeedY = -0.12;
		}
	}
	if (GetKeyPress(KEYNAME::KEY_S) && g_Player.PosY < SCREEN_BOTTOM - 2)
	{
		g_Player.SpeedY = PLAYER_MOVE_SPEED_Y;
		//g_Player.Direct = 270; //下向き
		//熱量を移動力に変換
		g_Player.HeatSpeed += (g_Player.Heat - 36) / 2;
		g_Player.SpeedY *= g_Player.HeatSpeed;
		//速度上限値
		if (g_Player.SpeedY > 0.3)
		{
			g_Player.SpeedY = 0.3;
		}
		if (g_Player.SpeedY < 0.12)//S(↓)押して負の値になってしまったら正の限りなく小さい数に
		{
			g_Player.SpeedY = 0.12;
		}
	}

	if (GetKeyPress(KEYNAME::KEY_A) && g_Player.PosX > SCREEN_LEFT + 2)
	{
		g_Player.SpeedX = -PLAYER_MOVE_SPEED_X;
		//g_Player.Direct = 0; //左向き
		//熱量を移動力に変換
		g_Player.HeatSpeed += (g_Player.Heat - 36) / 2;
		g_Player.SpeedX *= g_Player.HeatSpeed;
		//速度上限値
		if (g_Player.SpeedX < -0.55)
		{
			g_Player.SpeedX = -0.55;
		}
		if (g_Player.SpeedX > -0.3)//A(←)押して正の値になってしまったら負の限りなく小さい数に
		{
			g_Player.SpeedX = -0.3;
		}

	}
	
	if (GetKeyPress(KEYNAME::KEY_D) && g_Player.PosX < SCREEN_RIGHT - 2)
	{
		g_Player.SpeedX = PLAYER_MOVE_SPEED_X;
		//g_Player.Direct = 180; //右向き
		//熱量を移動力に変換
		g_Player.HeatSpeed += (g_Player.Heat - 36) / 2;
		g_Player.SpeedX *= g_Player.HeatSpeed;
		//速度上限値
		if (g_Player.SpeedX > 0.55)
		{
			g_Player.SpeedX = 0.55;
		}
		if (g_Player.SpeedX < 0.3)//D(→)押して負の値になってしまったら正の限りなく小さい数に
		{
			g_Player.SpeedX = 0.3;
		}
	}
	//シールド
	if (GetKeyTrigger(KEYNAME::KEY_SPACE))
	{
		CountShield = 0;
		//シールド構造体取得
		SHIELD* shield = GetShield();
		for (int i = 0; i < SHIELD_MAX; i++)
		{
			//使ってるシールドを数える
			if (shield[i].Use)
			{
				CountShield++;
			}
		}
		//シールドがプレイヤーについていない、かつシールドの残量があればシールドを張れる
		if (CountShield == 0 && g_Player.ShieldCharge > 0)
		{
			g_Player.ShieldCharge--;
			//シールド生成
			CreateShield(g_Player.PosX, g_Player.PosY, 2.0);
		}
	}
	
	//現在の位置保存
	g_Player.OldPosX = g_Player.PosX;
	g_Player.OldPosY = g_Player.PosY;
	//座標更新
	g_Player.PosX += g_Player.SpeedX;
	g_Player.PosY += g_Player.SpeedY;
	//弾発射　上下左右
	if (GetKeyPress(KEYNAME::KEY_UP)	|| GetKeyPress(KEYNAME::KEY_DOWN) ||
		GetKeyPress(KEYNAME::KEY_RIGHT) || GetKeyPress(KEYNAME::KEY_LEFT))
	{
		Shot();
	}
	
	//当たり判定//////////////////
	
	//敵キャラクターとの当たり判定
	g_Player.Hit = PlayerCollisionEnemy(&g_Player);
	
	if (g_Player.Hit)//プレイヤーが死んだらタイトルへ移動　現在当たったらだが、体力制御にする
	{
		//最初に当たってから1.5秒間は無敵時間
		if (timeGetTime() - LastHitTime < 1500)
		{
			//当たり判定無効化
			g_Player.Hit = false;
		}
		else
		{
			g_Player.Life--;
			g_Player.Item = ITEM_NONE;
			//最後に当たった時間を更新
			LastHitTime = timeGetTime();
			if (g_Player.Life == 0)
			{
				//シーンをタイトルへ移動させる
				SetScene(SCENE_TITLE);
			}
		}
	}

	

	//アイテムとの当たり判定
	g_Player.ItemHit = PlayerCollisionItem(&g_Player);
	//当たったアイテムにより処理を変える
	switch (g_Player.ItemHit)
	{
	case ITEM_FIRE:
	case ITEM_ICE:
		//アイテムタイプを入れる
		g_Player.Item = g_Player.ItemHit;
		AddPoint(10);
		break;
	case ITEM_LIFE:
		g_Player.Life += 3;
		AddPoint(1);
		break;
	default:
		break;
	}
	//ヒット率計算
	g_Player.HitPercent = g_Player.HitCount / g_Player.ShotCount;
	//タイムボーナス減算
	RESULT* Result = GetResult();
	if (g_Player.Stage < STAGE_MAX)
	{
		Result->TimeBonus--;
	}
	//現在温度計算
	switch (g_Player.Item)
	{
	case ITEM_FIRE:
		g_Player.Heat += 0.002;
		break;
	case ITEM_ICE:
		g_Player.Heat -= 0.002;
		break;
	default:
		break;
	}
	//ゲームクリア
	if (g_Player.Stage > STAGE_MAX)
	{
		SetScene(SCENE_RESULT);
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
	//キャラクター
	gotoxy(g_Player.PosX, g_Player.PosY);
	std::cout << "●";
	textcolor(WHITE);
#ifdef _DEBUG
	gotoxy(10, 6);
	std::cout << g_Player.ShotCount;
	gotoxy(10, 7);
	std::cout << g_Player.HitCount;
	gotoxy(5, 8);
	std::cout << g_Player.HitPercent;
	gotoxy(10, 9);
	std::cout << g_Player.ItemGetCount;
	gotoxy(10, 11);
	std::cout << g_Player.Heat << "℃";
#endif  _DEBUG
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
		direct_y += -1;
	}
	else if (GetKeyPress(KEYNAME::KEY_DOWN))
	{
		direct_y += 1;
	}

	if (GetKeyPress(KEYNAME::KEY_RIGHT))
	{
		direct_x += 2;
	}
	else if (GetKeyPress(KEYNAME::KEY_LEFT))
	{
		direct_x += -2;
	}
	//弾生成
	CreateBullet(g_Player.PosX, g_Player.PosY, direct_x, direct_y);
}