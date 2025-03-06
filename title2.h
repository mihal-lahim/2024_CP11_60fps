#pragma once


/// <summary>
/// 構造体
/// </summary>
struct PLAYERTITLE
{
	float PosX;//現在のX座標
	float PosY;//現在のY座標
	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標
};

////////////////////
//プロトタイプ宣言//
////////////////////
void InitTitle2(void);
void UnInitTitle2(void);
void UpdateTitle2(void);
void DrawTitle2(void);