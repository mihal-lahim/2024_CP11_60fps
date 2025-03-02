#include"scene.h"
#define CONIOEX//一回だけ
#include"conioex.h"
#include"title.h"
#include"game.h"
#include"result.h"
#include"ranking.h"
#include"title2.h"

//****************************************
//グローバル変数
//****************************************

//起動時に動作させたいシーンをセットしておく
SCENE g_Scene = SCENE_TITLE;//現在動作中のシーン
SCENE g_SceneNext = SCENE_TITLE;//移行先のシーン

//シーンの初期化処理
void InitScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		//タイトル画面の初期化処理
		InitTitle();
		break;
	case SCENE_TITLE2:
		//タイトル画面の初期化処理
		InitTitle2();
		break;
	case SCENE_GAME:
		//ゲーム本編の初期化処理
		InitGame();
		break;
	case SCENE_RESULT:
		//リザルト画面の初期化処理
		InitResult();
	case SCENE_RANKING:
		//ランキング画面の初期化処理
		InitRanking();
		break;
	}
	return;
}

//シーンの終了処理
void UnInitScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		//タイトル画面の終了処理
		UninitTitle();
		break;
	case SCENE_TITLE2:
		//タイトル画面2の終了処理
		UnInitTitle2();
		break;
	case SCENE_GAME:
		//ゲーム本編の終了処理
		UnInitGame();
		break;
	case SCENE_RESULT:
		//リザルト画面の終了処理
		UninitResult();
		break;
	case SCENE_RANKING:
		//ランキング画面の終了処理
		UnInitRanking();
		break;
	}
	return;
}

//シーンの更新処理
void UpdateScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		//タイトル画面の更新処理
		UpdateTitle();
		break;
	case SCENE_TITLE2:
		//タイトル画面2の更新処理
		UpdateTitle2();
		break;
	case SCENE_GAME:
		//ゲーム本編の更新処理
		UpdateGame();
		break;
	case SCENE_RESULT:
		//リザルト画面の更新処理
		UpdateResult();
		break;
	case SCENE_RANKING:
		//リザルト画面の更新処理
		UpdateRanking();
		break;
	}
	return;
}

//シーンの描画処理
void DrawScene(void)
{
	switch (g_Scene)
	{
	case SCENE_TITLE:
		//タイトル画面の描画処理
		DrawTitle();
		break;
	case SCENE_TITLE2:
		//タイトル画面2の描画処理
		DrawTitle2();
		break;
	case SCENE_GAME:
		//ゲーム本編の描画処理
		DrawGame();
		break;
	case SCENE_RESULT:
		//リザルト画面の描画処理
		DrawResult();
		break;
	case SCENE_RANKING:
		//リザルト画面の描画処理
		DrawRanking();
		break;
	}
	return;
}

//移行先シーンのセット
void SetScene(SCENE next)
{
	g_SceneNext = next;
}

//シーン切り替え処理
void CheckScene(void)
{
	//移行先シーンがセットされているかを確認する
	if (g_Scene != g_SceneNext)
	{
		//現在動作中のシーンを終了させる
		UnInitScene();
		//現在動作中のシーンを移行先シーンで更新する　ここで入れ替えてるのが大事
		g_Scene = g_SceneNext;
		//更新したシーンの初期化を行う
		InitScene();
		//画面のクリア
		clrscr();
	}
	return;
}