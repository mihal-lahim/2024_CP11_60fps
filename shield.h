#ifndef _SHIELD_H_
#define _SHIELD_H_

////////////////////////	
//マクロ定義
////////////////////////
#define SHIELD_MAX (8)//同時に生成するシールドの数 自分の周りに１マスずつ

////////////////////////
//シールド構造体
////////////////////////
struct SHIELD
{
	bool Use;//使用中フラグ

	float PosX;//現在のX座標
	float PosY;//現在のY座標

	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標

	float SpeedX;//X座標の移動量
	float SpeedY;//Y座標の移動量

	float UnBreaking;//耐久力
};

///////////////////////////
//プロトタイプ宣言
///////////////////////////
void InitShield(void);
void UnInitShield(void);
void UpdateShield(void);
void DrawShield(void);

void CreateShield(float PlayerPosX, float PlayerPosY, float UnBraking);
SHIELD* GetShield();

#endif

