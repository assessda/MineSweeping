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


int BlockRow;						//����
int BlockColumn;					//����
int Mine_Num;						//�׵ĸ���
int AllMineNum;						//�׵��ܸ���

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
void StartGmae();			//��ʼ��Ϸ



//achieve.h///////////
void StartUI();						//��ʼ��������
void StartControl();                //��ʼ����Ŀ���
void StartUIGame();					//��ui�������Ϸ
void GameModeInit();					//��Ϸģʽ�ĳ�ʼ��
void Initialization();				//��ʼ��
void BuryMine();					//����
void MineWarn();					//�׸����ľ���
void DrawInit();					//��ͼ�ĳ�ʼ��
void GameControl();					//��Ϸ����
void NoWarnExtend(int, int);		//û�����־�������ݹ麯��		
void OverShowMine();				//��Ϸ����������ʾ�������
void IconLocate();					//ͼ��İڲ�
void FlagInit();					//��ǳ�ʼ��
void PrintWinLost();				//���win OR LostͼƬ
//void test();						//����


bool DecideWin();					//�ж��Ƿ�Win