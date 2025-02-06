#ifndef _PLAYER_H_
#define _PLAYER_H_

//////////////
//マクロ定義
//////////////
#define PLAYER_MOVE_SPEED_X (MOVE_SPEED_X * 1.0)
#define PLAYER_MOVE_SPEED_Y (MOVE_SPEED_Y * 1.0)
#define GRAVITY        (0.04)//重力
#define JUMP_POWER     (0.75)//ジャンプ力
#define RESIST_X       (0.4)//地上のX方向摩擦
#define RESIST_X_AIR   (0.01)//空中のX方向摩擦

enum ITEM
{
	ITEM_NONE,
	ITEM_GUN,
	ITEM_BOMB,
	ITEM_MAX
};

//プレイヤーデータ構造体
struct PLAYER
{
	float PosX;//現在のX座標
	float PosY;//現在のY座標

	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標

	float SpeedX;//X座標の移動量
	float SpeedY;//Y座標の移動量

	bool  Jump;  //ジャンプ中かどうか
	bool  SecondJump;  //ジャンプ中かどうか
	
	float Direct; //向き

	bool Hit; //ヒットフラグ

	int Kill; //敵を倒した数

	int Item; //取得したアイテムコード
};

//プロトタイプ宣言
void InitPlayer(void);
void UnInitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer(void);
void Shot(void);

#endif