#pragma once

#define RANKING_MAX (5)

struct RANKING
{
	char Name[256];//名前
	int Score;//スコア

};

////////////
//プロトタイプ
///////////////

void FileWrite(RANKING* ranking);
void FileRead(RANKING* ranking);

