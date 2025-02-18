#ifndef _PLAYER_H_
#define _PLAYER_H_

//////////////
//マクロ定義
//////////////
#define PLAYER_MOVE_SPEED_X (MOVE_SPEED_X * 0.5)
#define PLAYER_MOVE_SPEED_Y (MOVE_SPEED_Y * 0.5)
#define GRAVITY        (0.04)//重力
#define JUMP_POWER     (0.75)//ジャンプ力
#define RESIST_X       (0.4)//地上のX方向摩擦
#define RESIST_X_AIR   (0.01)//空中のX方向摩擦
#define STAGE_MAX       (5)

//プレイヤーデータ構造体
struct PLAYER
{
	float PosX;//現在のX座標
	float PosY;//現在のY座標

	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標

	float SpeedX;//X座標の移動量
	float SpeedY;//Y座標の移動量

	int Life;//体力
	int MaxLife;//体力の最大値
	
	float Direct; //向き

	bool Hit; //ヒットフラグ
	int ItemHit;//アイテムヒットフラグ

	int Kill; //敵を倒した数

	int Item; //取得したアイテムコード

	int Stage;//現在のステージ
	float ClearTime;//クリアタイム
};

//プロトタイプ宣言
void InitPlayer(void);
void UnInitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer(void);
void Shot(void);

#endif