
//#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include	<stdio.h>
#include	"conioex.h"

#include"sound.h"

//=============================================================================
//  メイン関数
//=============================================================================
int	Sound(void)
{
	// サウンドファイルネーム
	char aSoundName1[64] = SOUND_TITLE;
	char aSoundName2[64] = SOUND_BATTLE;
	char aSoundName3[64] = SOUND_SHOT;

	// サウンドハンドルの取得 [conioex.h]
	int hSound1 = opensound(aSoundName1);
	int hSound2 = opensound(aSoundName2);
	int hSound3 = opensound(aSoundName3);

	// サウンドボリューム
	int nPercent = 50;

	//カーソル非表示 [conioex.h]
	setcursortype(NOCURSOR);

	do {
		//**************************************
		// 入力処理
		//**************************************

		// Aキー押下 [conioex.h]
		if (inport(PK_A))
		{
			// 音声再生 [conioex.h]
			playsound(hSound1, 0);
		}

		// Sキー押下 [conioex.h]
		if (inport(PK_S))
		{
			// 音声再生 [conioex.h]
			playsound(hSound2, 0);
		}

		// Dキー押下 [conioex.h]
		if (inport(PK_D))
		{
			// 音声再生 [conioex.h]
			playsound(hSound3, 0);
		}

		// Qキー押下 [conioex.h]
		if (inport(PK_Q))
		{
			// 音声停止 [conioex.h]
			stopsound(hSound1);
			stopsound(hSound2);
			stopsound(hSound3);
		}

		// Wキー押下 [conioex.h]
		if (inport(PK_W))
		{
			// 音量を上げる
			if (nPercent < 100)
			{
				nPercent++;
			}
			// 音量の設定  [conioex.h]
			setvolume(hSound1, nPercent);
			setvolume(hSound2, nPercent);
			setvolume(hSound3, nPercent);
		}

		// Eキー押下 [conioex.h]
		if (inport(PK_E))
		{
			// 音量を下げる
			if (nPercent > 0)
			{
				nPercent--;
			}
			// 音量の設定  [conioex.h]
			setvolume(hSound1, nPercent);
			setvolume(hSound2, nPercent);
			setvolume(hSound3, nPercent);
		}

		//**************************************
		// 表示処理
		//**************************************

		// 色設定 [conioex.h]
		textcolor(YELLOW);

		// 座標の固定 [conioex.h]
		gotoxy(2, 2);

		printf("ボリューム：%03d\n ", nPercent);

		printf("[Q]キーでサウンド停止　[W]キーで音量を上げる　[E]キーで音量を下げる　\n ");

		printf("[A]キーでサウンド１再生　[S]キーでサウンド２再生　[D]キーでサウンド３再生　\n ");

		printf("[ESC]キーで終了　\n ");

		// ESCキー押下 [conioex.h]
	} while (!inport(PK_ESC));

	//カーソル表示 [conioex.h]
	setcursortype(NORMALCURSOR);

	// サウンドハンドルの解放 [conioex.h]
	closesound(hSound1);
	closesound(hSound2);
	closesound(hSound3);

	return 0;
}


//タイトルBGM
void TitleBGM_Start(void)
{
	char aSoundName[256] = SOUND_TITLE;
	int hSound = opensound(aSoundName);
	playsound(hSound, 1);
}

void TitleBGM_End(void)
{
	char aSoundName[256] = SOUND_TITLE;
	int hSound = opensound(aSoundName);
	stopsound(hSound);
	closesound(hSound);
}
//タイトルBGM
void BattleBGM_Start(void)
{
	char aSoundName[64] = SOUND_BATTLE;
	int hSound = opensound(aSoundName);
	playsound(hSound, 1);
}

void BattleBGM_End(void)
{
	char aSoundName[64] = SOUND_BATTLE;
	int hSound = opensound(aSoundName);
	stopsound(hSound);
	closesound(hSound);
}
//ショットSE
void ShotSE_Start(void)
{
	char aSoundName[64] = SOUND_SHOT;
	int hSound = opensound(aSoundName);
	playsound(hSound, 0);
}

void ShotSE_End(void)
{
	char aSoundName[64] = SOUND_SHOT;
	int hSound = opensound(aSoundName);
	stopsound(hSound);
	closesound(hSound);
}
//撃破SE
void KillSE_Start(void)
{
	char aSoundName[64] = SOUND_KILL;
	int hSound = opensound(aSoundName);
	playsound(hSound, 0);
}

void KillSE_End(void)
{
	char aSoundName[64] = SOUND_KILL;
	int hSound = opensound(aSoundName);
	stopsound(hSound);
	closesound(hSound);
}
//ENTER_SE
void SelectSE_Start(void)
{
	char aSoundName[64] = SOUND_ENTER;
	int hSound = opensound(aSoundName);
	playsound(hSound, 0);
}

void SelectSE_End(void)
{
	char aSoundName[64] = SOUND_ENTER;
	int hSound = opensound(aSoundName);
	stopsound(hSound);
	closesound(hSound);
}