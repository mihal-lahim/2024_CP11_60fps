#pragma once

////////////
//UI構造体//
////////////
struct UI
{
	int UpdateFlg;
	int OldColor;
	int Color;
};

//プロトタイプ宣言
void InitUI(void);
void UnInitUI(void);
void UpdateUI(void);
void DrawUI(void);

void UIUpdate(void);

UI* GetUI();
