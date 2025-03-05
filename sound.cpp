
//#define _CRT_SECURE_NO_WARNINGS
#define CONIOEX
#include <stdio.h>
#include "conioex.h"
#include "sound.h"


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

char SoundCountDown[64] = SOUND_COUNTDOWN;//カウントダウンSE
int nSoundCountDown = opensound(SoundCountDown);

char SoundPowerUp[64] = SOUND_POWERUP;//パワーアップSE
int nSoundPowerUp = opensound(SoundPowerUp);

char SoundHeal[64] = SOUND_HEAL;//回復SE
int nSoundHeal = opensound(SoundHeal);


//=============================================================================
//  メイン関数
//=============================================================================
int	Sound(void)
{	
	setvolume(nSoundTitle, 30);
	setvolume(nSoundBattle, 30);
	setvolume(nSoundShot, 30);
	setvolume(nSoundKill, 30);
	setvolume(nSoundEnter, 30);
	setvolume(nSoundShield, 30);
	setvolume(nSoundClear, 30);
	setvolume(nSoundAllClear, 30);
	setvolume(nSoundDamage, 30);
	setvolume(nSoundGameOver, 30);
	setvolume(nSoundCountDown, 30);
	setvolume(nSoundPowerUp, 30);
	setvolume(nSoundHeal, 30);
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

//カウントダウンSE
void CountDownSE_Start(void)
{
	playsound(nSoundCountDown, 0);
}
void CountDownSE_End(void)
{
	stopsound(nSoundCountDown);
}

//パワーアップSE
void PowerUpSE_Start(void)
{
	playsound(nSoundPowerUp, 0);
}
void PowerUpSE_End(void)
{
	stopsound(nSoundPowerUp);
}

//回復SE
void HealSE_Start(void)
{
	playsound(nSoundHeal, 0);
}
void HealSE_End(void)
{
	stopsound(nSoundHeal);
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
	closesound(nSoundCountDown);
	closesound(nSoundPowerUp);
	closesound(nSoundHeal);
}