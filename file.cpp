#define CONIOEX
#include"conioex.h"
#include<fstream> //ファイル入出力
#include"file.h"
#include<iostream>
//=============================================================================
// セーブデータ書き込み関数
// 引数：プレイヤー情報、セーブデータ番号
// 戻り値：なし
// 概要：できたデータの書き込み
//=============================================================================
void FileWrite(RANKING* ranking)
{
	//書き込み
	std::ofstream File;

	File.open("Ranking.dat", std::ios::binary);
	
	//ファイル書き込み
	for (int i = 0; i < RANKING_MAX; i++,ranking++)
	{
		File.write((char*)ranking, sizeof(RANKING));
	}

	File.close();

	return;
}
//=============================================================================
// セーブデータ読み込み関数
// 引数：キャラクター情報
// 戻り値：なし
// 概要：できているデータの読み込み
//=============================================================================
void FileRead(RANKING* ranking)
{
	//書き込み
	std::ifstream File;
	//読み込み
	File.open("ranking.dat", std::ios::binary);
	
	//ファイル読み込み
	if (File)
	{
		for (int i = 0; i < RANKING_MAX; i++, ranking++)
		{
			File.read((char*)ranking, sizeof(RANKING));

		}
		File.close();
	}
	else
	{
		std::cout << "ファイル読み込みエラー\n";
	}
	return;
}