#ifndef _BULLET_H_
#define _BULLET_H_

////////////////////////
//マクロ定義
////////////////////////
#define BULLET_MAX (100)//同時に発射できる弾数
////////////////
//弾　構造体
////////////////
struct BULLET
{
	bool Use;//使用中フラグ

	float PosX;//現在のX座標
	float PosY;//現在のY座標

	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標

	float SpeedX;//X座標の移動量
	float SpeedY;//Y座標の移動量

	int Type;//弾の属性
};

///////////////////////////
//プロトタイプ宣言
///////////////////////////
void InitBullet(void);
void UnInitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);

void CreateBullet(float X, float Y, float Mx, float My);
BULLET* GetBullet();

#endif//_BULLET_H_