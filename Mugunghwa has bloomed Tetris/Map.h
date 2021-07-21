#pragma once
#include<Windows.h>
#include <conio.h>
#include <string.h>
#include <ctime>	
#include "Block.h"
#include "Stage.h"
#include <stdio.h>
#include<stdlib.h>
#include<time.h>




struct Map
{

	Map();

	Stage map_Stage;  

	int check_gostop;
	int total_Block[21][14]; // 

	int is_gameOver; // 

	Block play_Block; // 
	Block next_Block; // 

	COORD start_point; // 
	COORD play_point; // 

	
	int score;
	int s_or_g;

	float coin = 0;


	void gotoxy(int x, int y);
	void setColor(int color);

	void gameStart();
	void showMap();
	void showBlock();
	void eraseBlock();
	void replaceBlock();
	void showGameOver();
	void showClear();
	void checkFullLine();
	int strikeCheck();
	int moveBlock();
	void store();
	void showNext();//다음 블럭 출력
	void showLogo();//인트로
	void inputData();//레벨 정보 입력+도움말
	void showStart();//점수판
	void setCursorView(bool visible);
	void story();
	void story2();
	void stop(char stop_color);
	void go(char go_color);

	void go2(char go_color);

	void Bomb();
	void clearone();
	void TimeExtension(int time);
	void LineMu1(int line);
};