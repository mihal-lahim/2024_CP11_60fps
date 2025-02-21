#pragma once

struct RESULT
{
	int TotalScore;//総合スコア
	int TimeBonus;//タイムボーナス
};


//プロトタイプ宣言
void InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);

RESULT* GetResult();

