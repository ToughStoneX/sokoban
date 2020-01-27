#pragma once

#ifndef SOKOBAN
#define SOKOBAN

#include <iostream>

#define VERSION 1.0

typedef struct
{
	int x, y;
} Point;

class Sokoban
{
public:
	Sokoban();
	~Sokoban();

	void Run();
	void GameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch);
	// void EasyGameOperate(int Map[][20], int* n, int* m, int* js, int* sum, int* data, int* sl, int* guanshu, char* ch);
	void EasyMap(int Map[20][20], int* n, int* m, char* ch);
	void MiddleMap(int Map[20][20], int* n, int* m, char* ch);
	void HardMap(int Map[][20], int* n, int* m, char* ch);
	void SelectMap(int Map[][20], int* n, int* m, char* ch, int chapter);
	void MenuTwo(char* ch);
	void MenuOne(char* ch);
	void Menu(char* ch);
	void PlayGame(int Map[20][20], int* n, int* m, char* ch);
	void EasyGame(char* ch);
	void MiddleGame(char* ch);
	void HardGame(char* ch);
	void Operation(char* ch);
	void Introduction(char* ch);
	void GameSummary(char* ch);
	void Select(char* ch);
	int SelectGame(char* ch, int chapter);
	void Gotoxy(int x, int y);
	void Hide();
	void CountDown();
	int BoxData(int Map[][20], int* n, int* m);
	int GroundData(int Map[][20], int* n, int* m);
	int DrawMap(int Map[20][20], int* n, int* m, int chapter);
	int LevelGameReady();
	int SelectGameReady(char* ch, int chapter);

private:
	int step = 0; // 步数
	int space = 0; // 空格
	int disp = 0; // 显示
	int delay = 0; // 延迟
};

#endif