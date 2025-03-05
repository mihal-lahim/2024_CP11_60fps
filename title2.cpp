#define CONIOEX
#include"conioex.h"
#include"title2.h"
#include"scene.h"
#include"inputkey.h"
#include"score.h"
#include <iostream>
#include"sound.h"

//初期化
void InitTitle2(void)
{
}
//終了
void UnInitTitle2(void)
{
}
//更新
void UpdateTitle2(void)
{
	if (GetKeyTrigger(KEYNAME::KEY_ENTER))
	{
		//エンターSE
		SelectSE_Start();
		//シーンをゲーム本編へ移動させる
		SetScene(SCENE_GAME);
		//スコアのリセット
		ClearPoint();
	}
}
//描画
void DrawTitle2(void)
{
	gotoxy(5, 5);
	std::cout << "ENTERでスタート";
}