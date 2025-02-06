#pragma once

//#define ACTION
#define SHOOTING
//マクロ定義
#define SCREEN_LEFT (1)   //画面の大きさ左
#define SCREEN_TOP  (1)    //画面の大きさ上
#define SCREEN_BOTTOM (24.5)  //画面の大きさ下
#define SCREEN_RIGHT (79) //画面の大きさ右

#define MOVE_SPEED_X (0.5)//X方向の移動力
#define MOVE_SPEED_Y (0.2)//Y方向の移動力

//プロトタイプ宣言
void InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
