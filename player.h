#ifndef _PLAYER_H_
#define _PLAYER_H_

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
};
//プロトタイプ宣言
void InitPlayer(void);
void UnInitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);

PLAYER* GetPlayer(void);
void JumpPlayer(void);
void Shot(void);

#endif