#define CONIOEX
#include "conioex.h"
#include "field.h"
#include<iostream>

//áŠQ•¨‚Ì\‘¢‘Ì”z—ñ
FIELD g_Field[FIELD_MAX];

//áŠQ•¨Ä•`‰æ
bool g_UpdateFlg = true;

//‰Šú‰»
void InitField()
{
	for (int i = 0; i < FIELD_MAX; i++)
	{
		g_Field[i].PosX		= 0.0;
		g_Field[i].PosY		= 0.0;
		g_Field[i].Width	= 0.0;
		g_Field[i].Height	= 0.0;
		g_Field[i].Use		= false;

		//ˆÚ“®ˆ——p
		g_Field[i].OldPosX	= 0.0;
		g_Field[i].OldPosY	= 0.0;
		g_Field[i].SpeedX	= 0.0;
		g_Field[i].SpeedY	= 0.0;
		g_Field[i].Move		= false;
		g_Field[i].Count	= 0;
	}

	CreateField(10.0, 21.0, 08.0, 4.0, 0.0, 0.00);
	CreateField(22.0, 18.0, 16.0, 4.0, 0.0, 0.00);
	CreateField(48.0, 18.0, 10.0, 7.0, 0.0, 0.00);
	CreateField(36.0, 14.0, 08.0, 6.0, 0.0, 0.00);
	CreateField(18.0, 10.0, 10.0, 4.0, 0.1, 0.00);
	CreateField(64.0, 21.0, 06.0, 4.0, 0.0, 0.00);
	CreateField(46.0, 08.0, 30.0, 3.0, 0.0, 0.03);
}

