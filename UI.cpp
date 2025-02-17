#define CONIOEX
#include "conioex.h"
#include"UI.h"
#include"game.h"
#include<iostream>



//‰Šú‰»ˆ—
void InitUI(void)
{
	
}

//I—¹ˆ—
void UnInitUI(void)
{

}

//XVˆ—
void UpdateUI(void)
{

}

//•`‰æˆ—
void DrawUI(void)
{
	//”wŒi•`‰æ
	for (int i = 1; i < 24; i++)
	{
		for (int j = 1; j < 79; j++)
		{
			if (j < SCREEN_LEFT || SCREEN_RIGHT < j)
			{
				textbackground(BLUE);
				gotoxy(j, i);
				std::cout << "  ";
			}
		}
	}
	textbackground(BLACK);

	//î•ñ‚Ì•`‰æ
	
}
