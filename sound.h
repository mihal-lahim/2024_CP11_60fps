#pragma once

//////////////
//マクロ定義//
//////////////

#define		SOUND_TITLE	"maou_bgm_8bit13.MP3"
#define		SOUND_BATTLE "maou_bgm_8bit15.MP3"
#define		SOUND_SHOT	"se_shot_004.wav"
#define		SOUND_KILL "se_hit_002.wav"
#define		SOUND_ENTER "se_etc_005.wav"
#define		SOUND_SHIELD "斬撃11.mp3"
#define		SOUND_CLEAR "8bit-ME_Victory02.MP3"
#define		SOUND_ALLCLEAR "8bit-ME_Victory01.MP3"
#define		SOUND_DAMAGE "8bitダメージ5.MP3"
#define		SOUND_GAMEOVER "falled-sound-effect-278635.MP3"



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
void ShieldSE_Start(void);
void ShieldSE_End(void);
void ClearSE_Start(void);
void ClearSE_End(void);
void AllClearSE_Start(void);
void AllClearSE_End(void);
void DamageSE_Start(void);
void DamageSE_End(void);
void GameOverSE_Start(void);
void GameOverSE_End(void);
void SoundEnd(void);
