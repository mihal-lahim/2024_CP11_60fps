#pragma once

//////////////
//マクロ定義//
//////////////

#define		SOUND_TITLE	"maou_bgm_8bit13"
#define		SOUND_BATTLE "maou_bgm_8bit15"
#define		SOUND_SHOT	"se_shot_004"
#define		SOUND_KILL "se_hit_002"
#define		SOUND_ENTER "se_etc_005"


//プロトタイプ宣言
void TitleBGM_Start(void);
void TitleBGM_End(void);
void BattleBGM_Start(void);
void BattleBGM_End(void);
void ShotSE_Start(void);
void ShotSE_End(void);
void KillSE_Start(void);
void KillSE_End(void);
void SelectSE_Start(void);
void SelectSE_End(void);
