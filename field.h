#pragma once


/////////////////
//マクロ定義
/////////////////
#define FIELD_MAX (40)//障害物の最大数

/////////////////
//障害物構造体
/////////////////

struct FIELD
{
	float PosX;		//X座標
	float PosY;		//Y座標
	float Width;	//幅
	float Height;	//高さ
	bool  Use;		//使用フラグ

	float OldPosX;	//過去のX座標（コンソール表示用）
	float OldPosY;	//過去のY座標（コンソール表示用）
	float SpeedX;	//X座標の移動量
	float SpeedY;	//Y座標の移動量
	int Count;		//カウンタ
	bool Move;		//地面が移動しているかどうか
};

//////////////////
//プロトタイプ宣言
//////////////////
void InitField();
void UnInitField();
void UpdateField();
void DrawField();
FIELD* GetField();

void UpdateDrawField();
void CreateField(float X,float Y,float Width,float Height,float Mx,float My);
void FieldUpdate();