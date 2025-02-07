#pragma once

//マクロ定義
#define ITEM_MAX (10) //アイテムの最大数

enum ITEM_TYPE
{
	ITEM_NONE,	//通常
	ITEM_FIRE,	//ファイア
	ITEM_ICE,	//アイス

	ITEM_NUM,	//アイテムの数あ
};

//アイテム構造体
struct ITEM
{
	float PosX;//現在のX座標
	float PosY;//現在のY座標

	float OldPosX;//過去のX座標
	float OldPosY;//過去のY座標

	int Type;//アイテムの種類
	int Color;//アイテムの色

	bool Use;//使用中かどうか

	bool Hit;//当たったかどうか
};

//////////////////
//プロトタイプ宣言
//////////////////

void InitItem();
void UninitItem();
void UpdateItem();
void DrawItem();

//アイテムの生成
void SetItem(float x, float y, int type);

//アイテムの消去
void DeleteItem(int);

