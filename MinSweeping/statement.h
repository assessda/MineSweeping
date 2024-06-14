#pragma once
#include <iostream>
#include <stdio.h>
#include <graphics.h>
#include <cmath>
#include <ctime>
#include <conio.h>
#include <mmsystem.h>
#pragma comment(lib,"winmm.Lib")

#define SWIDTH 400
#define SHEIGHT 400
#define MWIDTH 640
#define MHEIGHT 640
#define LWIDTH 1400
#define LHEIGHT 640
#define BLOCK_WIDTH 40
#define BLOCK_HEIGHT 40
#define SBLOCKROW 10
#define SBLOCKCOLUMN 10
#define MBLOCKROW 16
#define MBLOCKCOLUMN 16
#define LBLOCKROW 16
#define LBLOCKCOLUMN 35
#define SMINENUM 10
#define MMINENUM 40
#define LMINENUM 99


int BlockRow;						//行数
int BlockColumn;					//列数
int Mine_Num;						//雷的个数
int AllMineNum;						//雷的总个数

struct block
{
	int LBoundary;
	int RBoundary;
	int TBoundary;
	int UBoundary;
	int MineAsideNum;
	int TypeFlag;
	int ClickFlag;
};

struct block blocks[100][100];

IMAGE smap(SWIDTH, SHEIGHT + 100);
IMAGE mmap(MWIDTH, MHEIGHT + 100);
IMAGE lmap(LWIDTH, LHEIGHT + 100);
IMAGE StartMap(500, 500 + 100);
IMAGE map;
IMAGE block;
IMAGE EASY,NORMAL, TROUBLE, HEAD, EXIT, MENU, AGAIN, CLOSE;
IMAGE MINE, SELECTEDMINE, FLAG, BLOCK, ERRORFLAG;
IMAGE NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8;
IMAGE WIN, LOST;

int OverFlag;
int GameDifficult;
int ExitFlag;
int UIFlag;
int AgainFlag;
int MenuFlag;
int NoClickFlag;

int WIDTH;
int HEIGHT;

int ShowMineNum;


//startgame.h//////////
void StartGmae();			//开始游戏



//achieve.h///////////
void StartUI();						//开始界面的设计
void StartControl();                //开始界面的控制
void StartUIGame();					//从ui界面进游戏
void GameModeInit();					//游戏模式的初始化
void Initialization();				//初始化
void BuryMine();					//埋雷
void MineWarn();					//雷附近的警告
void DrawInit();					//绘图的初始化
void GameControl();					//游戏控制
void NoWarnExtend(int, int);		//没有数字警告延伸递归函数		
void OverShowMine();				//游戏机结束后显示其余的雷
void IconLocate();					//图表的摆布
void FlagInit();					//标记初始化
void PrintWinLost();				//输出win OR Lost图片
//void test();						//测试


bool DecideWin();					//判断是否Win