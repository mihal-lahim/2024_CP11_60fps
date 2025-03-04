
//#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include	<stdio.h>
#include	"conioex.h"
#include"sound.h"


//////////////////
//グローバル変数//
//////////////////
char SoundTitle[64] = SOUND_TITLE;//タイトルBGM
int nSoundTitle = opensound(SoundTitle);


char SoundBattle[64] = SOUND_BATTLE;//バトルBGM
int nSoundBattle = opensound(SoundBattle);

char SoundShot[64] = SOUND_SHOT;//ショットSE
int nSoundShot = opensound(SoundShot);

char SoundKill[64] = SOUND_KILL;//キルSE
int nSoundKill = opensound(SoundKill);

char SoundEnter[64] = SOUND_ENTER;//エンターSE
int nSoundEnter = opensound(SoundEnter);

char SoundShield[64] = SOUND_SHIELD;//シールドSE
int nSoundShield = opensound(SoundShield);

char SoundClear[64] = SOUND_CLEAR;//クリアSE
int nSoundClear = opensound(SoundClear);

char SoundAllClear[64] = SOUND_ALLCLEAR;//オールクリアSE
int nSoundAllClear = opensound(SoundAllClear);

char SoundDamage[64] = SOUND_DAMAGE;//ダメージSE
int nSoundDamage = opensound(SoundDamage);

char SoundGameOver[64] = SOUND_GAMEOVER;//ゲームオーバーSE
int nSoundGameOver = opensound(SoundGameOver);


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
	/*closesound(hSound1);
	closesound(hSound2);
	closesound(hSound3);*/

	return 0;
}

//タイトルBGM
void TitleBGM_Start(void)
{
	playsound(nSoundTitle, 1);
}
void TitleBGM_End(void)
{
	stopsound(nSoundTitle);
}

//バトルBGM
void BattleBGM_Start(void)
{
	playsound(nSoundBattle, 1);
}
void BattleBGM_End(void)
{
	stopsound(nSoundBattle);
	
}

//ショットSE
void ShotSE_Start(void)
{
	playsound(nSoundShot, 0);
}
void ShotSE_End(void)
{
	stopsound(nSoundShot);

}

//撃破SE
void KillSE_Start(void)
{
	playsound(nSoundKill, 0);
}
void KillSE_End(void)
{
	stopsound(nSoundKill);
	
}

//ENTER_SE
void SelectSE_Start(void)
{
	playsound(nSoundEnter, 0);
}
void SelectSE_End(void)
{
	stopsound(nSoundEnter);
	
}


//シールドSE
void ShieldSE_Start(void)
{
	playsound(nSoundShield, 0);
}
void ShieldSE_End(void)
{
	stopsound(nSoundShield);

}

//クリアSE
void ClearSE_Start(void)
{
	playsound(nSoundClear, 0);
}
void ClearSE_End(void)
{
	stopsound(nSoundClear);
}

//オールクリアSE
void AllClearSE_Start(void)
{
	playsound(nSoundAllClear, 0);
}
void AllClearSE_End(void)
{
	stopsound(nSoundAllClear);
}

//ダメージSE
void DamageSE_Start(void)
{
	playsound(nSoundDamage, 0);
}
void DamageSE_End(void)
{
	stopsound(nSoundDamage);
}

//ゲームオーバーSE
void GameOverSE_Start(void)
{
	playsound(nSoundGameOver, 0);
}
void GameOverSE_End(void)
{
	stopsound(nSoundGameOver);
}

//サウンドファイル閉じ
void SoundEnd(void)
{
	closesound(nSoundTitle);
	closesound(nSoundBattle);
	closesound(nSoundShot);
	closesound(nSoundKill);
	closesound(nSoundEnter);
	closesound(nSoundShield);
	closesound(nSoundClear);
	closesound(nSoundAllClear);
	closesound(nSoundDamage);
	closesound(nSoundGameOver);
}