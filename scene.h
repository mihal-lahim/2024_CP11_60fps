#pragma once


//列挙体でシーンの種類を定義する
enum SCENE
{
	SCENE_TITLE,//タイトル画面
	SCENE_TITLE2,//タイトル画面2
	SCENE_GAME,//ゲーム本編
	SCENE_RESULT,//ゲーム結果表示画面
	SCENE_RANKING,//ランキング表示画面

	SCENE_NUM,//終端コード
};

//プロトタイプ宣言
void InitScene(void);//初期化      )
void UnInitScene(void);//終了処理  )
void UpdateScene(void);//更新      )ここ四点セット
void DrawScene(void);//描画        )

void SetScene(SCENE next);
void CheckScene(void);
