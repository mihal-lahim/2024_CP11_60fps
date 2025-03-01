#pragma once

//////////////
//マクロ定義//
//////////////
#define CH4NGE_SPEED (80)
#define RED_POINT (CH4NGE_SPEED * 3)
#define BLUE_POINT (CH4NGE_SPEED * 2)
#define WHITE_POINT (CH4NGE_SPEED * 1)


struct TITLE
{
	int F_Color;//Fの色
	int i_Color;//iの色
	int c_Color;//cの色
	int F_OldColor;//過去のFの色
	int i_OldColor;//過去のiの色
	int c_OldColor;//過去のcの色
	bool UpdateFlg;//更新する？
};

//プロトタイプ宣言
void InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void Draw_F(void);
void Draw_i(void);
void Draw_c(void);
void TitleUpdate(void);