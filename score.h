#pragma once
#ifndef _SCORE_H_
#define _SCORE_H_

//*************************************
// スコア 構造体
//*************************************
struct SCORE	//スコア
{
	int nPoint;				// 得点
	int nMaxPoint;		// 最高得点

	bool bUse;				// 使用中フラグ

};

void InitScore();
void UnInitScore();
void UpdateScore();
void DrawScore();

void ClearPoint();
void AddPoint(int nPoint);
void SetMaxPoint(int nPoint);
SCORE* GetScore();

#endif //_SCORE_H_