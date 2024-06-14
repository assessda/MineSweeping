#pragma once
#include "statement.h"

////////////////////////////////界面部分///////////////////
//开始界面的设计
void StartUI()
{
	initgraph(500, 500 + 100);
	SetWorkingImage(&StartMap);
	setbkcolor(RGB(40, 44, 52));
	cleardevice();
	SetWorkingImage();
	putimage(0, 0, 500, 500 + 100, &StartMap, 0, 0);
	loadimage(&HEAD, "image\\uihead.png", 250, 150);
	loadimage(&EASY, "image\\easy.png", 250, 60);
	loadimage(&NORMAL, "image\\normal.png", 250, 60);
	loadimage(&TROUBLE, "image\\trouble.png", 250, 60);
	loadimage(&CLOSE, "image\\close.png", 50, 50);

	putimage(125, 50, 250, 150, &HEAD, 0, 0);
	putimage(125, 200, 250, 60, &EASY, 0, 0);
	putimage(125, 280, 250, 60, &NORMAL, 0, 0);
	putimage(125, 360, 250, 60, &TROUBLE, 0, 0);
	putimage(225, 460, 50, 50, &CLOSE, 0, 0);
}

//开始界面的控制
void StartControl()
{
	MOUSEMSG m;
	m = GetMouseMsg();
	if (m.uMsg == WM_LBUTTONDOWN)
	{
		if (m.x >= 125 && m.x <= (125 + 250) && m.y >= 200 && m.y <= (200 + 60))
		{
			UIFlag = 0;
			GameDifficult = 1;
		}
		if (m.x >= 125 && m.x <= (125 + 250) && m.y >= 280 && m.y <= (280 + 60))
		{
			UIFlag = 0;
			GameDifficult = 2;
		}
		if (m.x >= 125 && m.x <= (125 + 250) && m.y >= 360 && m.y <= (360 + 60))
		{
			UIFlag = 0;
			GameDifficult = 3;
		}
		if (m.x >= 225 && m.x <= (225 + 50) && m.y >= 460 && m.y <= (460 + 50))
		{
			UIFlag = 0;
			ExitFlag = 1;
		}
	}
}

//从UI界面进入游戏
void StartUIGame()
{
	StartUI();
	while (UIFlag)
	{
		StartControl();
	}

}

//游戏模式的初始化1
void GameModeInit()
{
	//难度一
	if (GameDifficult == 1)
	{
		WIDTH = SWIDTH;
		HEIGHT = SHEIGHT;
		map = smap;
		BlockRow = SBLOCKROW;
		BlockColumn = SBLOCKCOLUMN;
		AllMineNum = SMINENUM;
	}

	//难度二
	if (GameDifficult == 2)
	{
		WIDTH = MWIDTH;
		HEIGHT = MHEIGHT;
		map = mmap;
		BlockRow = MBLOCKROW;
		BlockColumn = MBLOCKCOLUMN;
		AllMineNum = MMINENUM;
	}

	//难度三
	if (GameDifficult == 3)
	{
		WIDTH = LWIDTH;
		HEIGHT = LHEIGHT;
		map = lmap;
		BlockRow = LBLOCKROW;
		BlockColumn = LBLOCKCOLUMN;
		AllMineNum = LMINENUM;
	}
}

////////////////////////////////游戏部分//////////////////
//初始化2
void Initialization()
{
	OverFlag = 0;
	//给每个区块划分界限
	for (int i = 0; i < BlockRow; i++)
	{
		for (int j = 0; j < BlockColumn; j++)
		{
			blocks[i][j].LBoundary = j * BLOCK_WIDTH;
			blocks[i][j].RBoundary = (j + 1) * BLOCK_WIDTH - 1;
			blocks[i][j].TBoundary = i * BLOCK_HEIGHT;
			blocks[i][j].UBoundary = (i + 1) * BLOCK_HEIGHT - 1;
			blocks[i][j].MineAsideNum = 0;
			blocks[i][j].TypeFlag = 0;
			blocks[i][j].ClickFlag = 0;

		}
	}
	Mine_Num = 0;
}

//埋雷
void BuryMine()
{
	srand(GetTickCount());
	for (int i = 0; i < AllMineNum; )
	{
		int a = rand() % BlockRow;
		int b = rand() % BlockColumn;
		if (blocks[a][b].TypeFlag != -1)
		{
			blocks[a][b].TypeFlag = -1;
			Mine_Num++;
			i++;
		}
	}
}

//雷附近的警告
void MineWarn()
{
	for (int i = 1; i < BlockRow - 1; i++)
	{
		for (int j = 1; j < BlockColumn - 1; j++)
		{
			if (blocks[i + 1][j].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i + 1][j + 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i + 1][j - 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i - 1][j].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i - 1][j + 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i - 1][j - 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i][j + 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
			if (blocks[i][j - 1].TypeFlag == -1)
				blocks[i][j].MineAsideNum++;
		}
	}
	//四个角
	//0列,0行
	if (blocks[0][0 + 1].TypeFlag == -1)
		blocks[0][0].MineAsideNum++;
	if (blocks[0 + 1][0].TypeFlag == -1)
		blocks[0][0].MineAsideNum++;
	if (blocks[0 + 1][0 + 1].TypeFlag == -1)
		blocks[0][0].MineAsideNum++;
	//最后一列,0行
	if (blocks[0][BlockColumn - 2].TypeFlag == -1)
		blocks[0][BlockColumn - 1].MineAsideNum++;
	if (blocks[0 + 1][BlockColumn - 1].TypeFlag == -1)
		blocks[0][BlockColumn - 1].MineAsideNum++;
	if (blocks[0 + 1][BlockColumn - 2].TypeFlag == -1)
		blocks[0][BlockColumn - 1].MineAsideNum++;
	//0列,最后一行
	if (blocks[BlockRow - 1][0 + 1].TypeFlag == -1)
		blocks[BlockRow - 1][0].MineAsideNum++;
	if (blocks[BlockRow - 2][0].TypeFlag == -1)
		blocks[BlockRow - 1][0].MineAsideNum++;
	if (blocks[BlockRow - 2][0 + 1].TypeFlag == -1)
		blocks[BlockRow - 1][0].MineAsideNum++;
	//9列,9行
	if (blocks[BlockRow - 1][BlockColumn - 2].TypeFlag == -1)
		blocks[BlockRow - 1][BlockColumn - 1].MineAsideNum++;
	if (blocks[BlockRow - 2][BlockColumn - 1].TypeFlag == -1)
		blocks[BlockRow - 1][BlockColumn - 1].MineAsideNum++;
	if (blocks[BlockRow - 2][BlockColumn - 2].TypeFlag == -1)
		blocks[BlockRow - 1][BlockColumn - 1].MineAsideNum++;
	//第0行
	for (int i = 1; i < BlockColumn - 1; i++)
	{
		if (blocks[0][i - 1].TypeFlag == -1)
			blocks[0][i].MineAsideNum++;
		if (blocks[0][i + 1].TypeFlag == -1)
			blocks[0][i].MineAsideNum++;
		if (blocks[0 + 1][i].TypeFlag == -1)
			blocks[0][i].MineAsideNum++;
		if (blocks[0 + 1][i - 1].TypeFlag == -1)
			blocks[0][i].MineAsideNum++;
		if (blocks[0 + 1][i + 1].TypeFlag == -1)
			blocks[0][i].MineAsideNum++;
	}
	//最后一行
	for (int i = 1; i < BlockColumn - 1; i++)
	{
		if (blocks[BlockRow - 1][i - 1].TypeFlag == -1)
			blocks[BlockRow - 1][i].MineAsideNum++;
		if (blocks[BlockRow - 1][i + 1].TypeFlag == -1)
			blocks[BlockRow - 1][i].MineAsideNum++;
		if (blocks[BlockRow - 2][i].TypeFlag == -1)
			blocks[BlockRow - 1][i].MineAsideNum++;
		if (blocks[BlockRow - 2][i - 1].TypeFlag == -1)
			blocks[BlockRow - 1][i].MineAsideNum++;
		if (blocks[BlockRow - 2][i + 1].TypeFlag == -1)
			blocks[BlockRow - 1][i].MineAsideNum++;
	}
	//第0列
	for (int i = 1; i < BlockRow - 1; i++)
	{
		if (blocks[i + 1][0].TypeFlag == -1)
			blocks[i][0].MineAsideNum++;
		if (blocks[i - 1][0].TypeFlag == -1)
			blocks[i][0].MineAsideNum++;
		if (blocks[i][0 + 1].TypeFlag == -1)
			blocks[i][0].MineAsideNum++;
		if (blocks[i + 1][0 + 1].TypeFlag == -1)
			blocks[i][0].MineAsideNum++;
		if (blocks[i - 1][0 + 1].TypeFlag == -1)
			blocks[i][0].MineAsideNum++;
	}
	//最后一列
	for (int i = 1; i < BlockRow - 1; i++)
	{
		if (blocks[i + 1][BlockColumn - 1].TypeFlag == -1)
			blocks[i][BlockColumn - 1].MineAsideNum++;
		if (blocks[i - 1][BlockColumn - 1].TypeFlag == -1)
			blocks[i][BlockColumn - 1].MineAsideNum++;
		if (blocks[i][BlockColumn - 2].TypeFlag == -1)
			blocks[i][BlockColumn - 1].MineAsideNum++;
		if (blocks[i + 1][BlockColumn - 2].TypeFlag == -1)
			blocks[i][BlockColumn - 1].MineAsideNum++;
		if (blocks[i - 1][BlockColumn - 2].TypeFlag == -1)
			blocks[i][BlockColumn - 1].MineAsideNum++;
	}
}

//绘图的初始化
void DrawInit()
{
	initgraph(WIDTH, HEIGHT + 100);
	SetWorkingImage(&map);
	setbkcolor(WHITE);
	cleardevice();
	SetWorkingImage();
	putimage(0, 0, WIDTH, HEIGHT + 100, &map, 0, 0);
	loadimage(&block, "image\\block.png", 40, 40);
	for (int i = 0; i < BlockRow; i++)
	{
		for(int j = 0; j < BlockColumn; j++)
		{
			putimage(j * 40, i * 40, &block);
		}
	}
	
}

//点击控制
void GameControl()
{
	//游戏界面
	MOUSEMSG m;
	m = GetMouseMsg();
	if(NoClickFlag != 1)
	{ 
		for (int i = 0; i < BlockRow; i++)
		{
			for (int j = 0; j < BlockColumn; j++)
			{
				if (m.x > blocks[i][j].LBoundary && m.x < blocks[i][j].RBoundary \
					&& m.y > blocks[i][j].TBoundary && m.y < blocks[i][j].UBoundary \
					&& m.uMsg == WM_LBUTTONDOWN && blocks[i][j].ClickFlag == 0)
				{
				
					if (blocks[i][j].TypeFlag == -1)
					{
						NoClickFlag = 1;
						blocks[i][j].ClickFlag = 1;
						PlaySound(TEXT("music\\Click.wav"), NULL, NULL);
					
						//踩雷了，结束游戏
						loadimage(&SELECTEDMINE, "image\\selectedmine.png", 40, 40);
						putimage(j * 40, i * 40, 40, 40, &SELECTEDMINE, 0, 0);
						OverShowMine();
						PrintWinLost();
						PlaySound(TEXT("music\\explosion.wav"), NULL, SND_ASYNC);
					}
					else 
					{ 
						if (blocks[i][j].MineAsideNum != 0)
						{
							blocks[i][j].ClickFlag = 1;
							PlaySound(TEXT("music\\Click.wav"), NULL, NULL);
							switch (blocks[i][j].MineAsideNum)		//显示附近的雷数
							{
								case 1:
									loadimage(&NUM1, "image\\1.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM1, 0, 0);
									break;
								case 2:
									loadimage(&NUM2, "image\\2.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM2, 0, 0);
									break;
								case 3:
									loadimage(&NUM3, "image\\3.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM3, 0, 0);
									break;
								case 4:
									loadimage(&NUM4, "image\\4.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM4, 0, 0);
									break;
								case 5:
									loadimage(&NUM5, "image\\5.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM5, 0, 0);
									break;
								case 6:
									loadimage(&NUM6, "image\\6.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM6, 0, 0);
									break;
								case 7:
									loadimage(&NUM7, "image\\7.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM7, 0, 0);
									break;
								case 8:
									loadimage(&NUM8, "image\\8.png", 40, 40);
									putimage(j * 40, i * 40, 40, 40, &NUM8, 0, 0);
									break;

							}
						
						
						}
						////////////点击后空白，延伸递归
						if (blocks[i][j].MineAsideNum == 0)
						{
							blocks[i][j].ClickFlag = 1;
							PlaySound(TEXT("music\\Click.wav"), NULL, NULL);
							loadimage(&NUM0, "image\\0.png", 40, 40);
							putimage(j * 40, i * 40, 40, 40, &NUM0, 0, 0);
							NoWarnExtend(i , j);
						}
					}
				}
				if (m.x > blocks[i][j].LBoundary && m.x < blocks[i][j].RBoundary \
					&& m.y > blocks[i][j].TBoundary && m.y < blocks[i][j].UBoundary \
					&& m.uMsg == WM_RBUTTONUP && blocks[i][j].ClickFlag != 1)
				{
				
					if (blocks[i][j].ClickFlag == 0)			//竖红旗
					{
						blocks[i][j].ClickFlag = 2;
						loadimage(&FLAG, "image\\flag.png", 40, 40);
						putimage(j * 40, i * 40, 40, 40, &FLAG, 0, 0);
					
					}
					else if (blocks[i][j].ClickFlag == 2)		//取消红旗
					{
						blocks[i][j].ClickFlag = 0;
						loadimage(&BLOCK, "image\\block.png", 40, 40);
						putimage(j * 40, i * 40, 40, 40, &BLOCK, 0, 0);
					
					
					}
				}
			}
		}
		if (DecideWin())
		{
			NoClickFlag = 1;
			PrintWinLost();
		}
	}
	//菜单界面//////////////////////////////////
	if (GameDifficult == 1)
	{
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//主菜单
			if (m.x >= 0 && m.x <= 80 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 1;
			}
			//重玩
			if (m.x >= 100 && m.x <= 180 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				NoClickFlag = 0;
			}
			//退出游戏
			if (m.x >= 200 && m.x <= 280 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 0;
			}
		}
	}
	if (GameDifficult == 2)
	{
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//主菜单
			if (m.x >= 60 && m.x <= 140 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 1;
			}
			//重玩
			if (m.x >= 210 && m.x <= 290 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				NoClickFlag = 0;
			}
			//退出游戏
			if (m.x >= 360 && m.x <= 440 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 0;
			}
		}
	}
	if (GameDifficult == 3)
	{
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			//主菜单
			if (m.x >= WIDTH / 2 - 250 && m.x <= WIDTH / 2 - 250 + 80 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 1;
			}
			//重玩
			if (m.x >= WIDTH / 2 - 50 && m.x <= WIDTH / 2 - 50 + 80 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				NoClickFlag = 0;
			}
			//退出游戏
			if (m.x >= WIDTH / 2 + 150 && m.x <= WIDTH / 2 + 230 && m.y >= HEIGHT && m.y <= HEIGHT + 80)
			{
				OverFlag = 1;
				AgainFlag = 0;
				ExitFlag = 1;
				MenuFlag = 0;
			}
		}
	}
}

////没有数字警告延伸递归函数
void NoWarnExtend(int a, int b)
{
	if (blocks[a][b + 1].ClickFlag == 0 && blocks[a][b + 1].TypeFlag != -1 && (b + 1) <= (BlockColumn - 1))
	{
		blocks[a][b + 1].ClickFlag = 1;
		if (blocks[a][b + 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b + 1) * 40, a * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a, b + 1);
		}
		else
		{
			switch (blocks[a][b + 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b + 1) * 40, a * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a][b - 1].ClickFlag == 0 && blocks[a][b - 1].TypeFlag != -1 && (b - 1) >= 0)
	{
		blocks[a][b - 1].ClickFlag = 1;
		if (blocks[a][b - 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b - 1) * 40, a * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a, b - 1);
		}
		else
		{
			switch (blocks[a][b - 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b - 1) * 40, a * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a + 1][b].ClickFlag == 0 && blocks[a + 1][b].TypeFlag != -1 && (a + 1) <= (BlockRow - 1))
	{
		blocks[a + 1][b].ClickFlag = 1;
		if (blocks[a + 1][b].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage(b * 40, (a + 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a + 1, b);
		}
		else
		{
			switch (blocks[a + 1][b].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage(b * 40, (a +1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage(b * 40, (a + 1)* 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage(b * 40, (a + 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a - 1][b].ClickFlag == 0 && blocks[a - 1][b].TypeFlag != -1 && (a - 1) >= 0)
	{
		blocks[a - 1][b].ClickFlag = 1;
		if (blocks[a - 1][b].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage(b * 40, (a - 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a - 1, b);
		}
		else
		{
			switch (blocks[a - 1][b].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage(b * 40, (a - 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a + 1][b + 1].ClickFlag == 0 && blocks[a + 1][b + 1].TypeFlag != -1 && (a + 1) <= (BlockRow - 1) && (b + 1) <= (BlockColumn - 1))
	{
		blocks[a + 1][b + 1].ClickFlag = 1;
		if (blocks[a + 1][b + 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a + 1, b + 1);
		}
		else
		{
			switch (blocks[a + 1][b + 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b + 1) * 40, (a + 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a + 1][b - 1].ClickFlag == 0 && blocks[a + 1][b - 1].TypeFlag != -1 && (a + 1) <= (BlockRow - 1) && (b - 1) >= 0)
	{
		blocks[a + 1][b - 1].ClickFlag = 1;
		if (blocks[a + 1][b - 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a + 1, b - 1);
		}
		else
		{
			switch (blocks[a + 1][b - 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b - 1) * 40, (a + 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a - 1][b - 1].ClickFlag == 0 && blocks[a - 1][b - 1].TypeFlag != -1 && (a - 1) >= 0 && (b - 1) >= 0)
	{
		blocks[a - 1][b - 1].ClickFlag = 1;
		if (blocks[a - 1][b - 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a - 1, b - 1);
		}
		else
		{
			switch (blocks[a - 1][b - 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b - 1) * 40, (a - 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}
	if (blocks[a - 1][b + 1].ClickFlag == 0 && blocks[a - 1][b + 1].TypeFlag != -1 && (a - 1) >= 0 && (b + 1) <= (BlockColumn - 1))
	{
		blocks[a - 1][b + 1].ClickFlag = 1;
		if (blocks[a - 1][b + 1].MineAsideNum == 0)
		{
			loadimage(&NUM0, "image\\0.png", 40, 40);
			putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM0, 0, 0);
			NoWarnExtend(a - 1, b + 1);
		}
		else
		{
			switch (blocks[a - 1][b + 1].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage((b + 1) * 40, (a - 1) * 40, 40, 40, &NUM8, 0, 0);
				break;
			}
		}
	}



}

//游戏机结束后显示其余的雷
void OverShowMine()
{
	for (int i = 0; i < BlockRow; i++)
	{
		for (int j = 0; j < BlockColumn; j++)
		{
			if (blocks[i][j].ClickFlag == 0 && blocks[i][j].TypeFlag == -1)
			{
				blocks[i][j].ClickFlag = 1;
				loadimage(&MINE, "image\\mine.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &MINE, 0, 0);
			}
			if (blocks[i][j].ClickFlag == 2 && blocks[i][j].TypeFlag != -1)
			{
				blocks[i][j].ClickFlag = 3;
				loadimage(&ERRORFLAG, "image\\errorflag.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &ERRORFLAG, 0, 0);
			}
		}
	}
}

//标记初始化
void FlagInit()
{
	MenuFlag = 0;
	ExitFlag = 0;
	AgainFlag = 1;
	OverFlag = 0;
	UIFlag = 1;
	NoClickFlag = 0;
}

//图表的摆布
void IconLocate()
{
	if(GameDifficult == 1)
	{ 
		loadimage(&EXIT, "image\\exit.png", 80, 80);
		loadimage(&AGAIN, "image\\again.png", 80, 80);
		loadimage(&MENU, "image\\menu.png", 80, 80);

		putimage(100, HEIGHT, 80, 80, &AGAIN, 0, 0);
		putimage(200, HEIGHT, 80, 80, &EXIT, 0, 0);
		putimage(0, HEIGHT, 80, 80, &MENU, 0, 0);


		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(25, 0, "微软雅黑");
		outtextxy(300, HEIGHT + 20, "总雷数:");
		outtextxy(300, HEIGHT + 50, "10");
	}
	if (GameDifficult == 2)
	{
		loadimage(&EXIT, "image\\exit.png", 80, 80);
		loadimage(&AGAIN, "image\\again.png", 80, 80);
		loadimage(&MENU, "image\\menu.png", 80, 80);

		putimage(210, HEIGHT, 80, 80, &AGAIN, 0, 0);
		putimage(360, HEIGHT, 80, 80, &EXIT, 0, 0);
		putimage(60, HEIGHT, 80, 80, &MENU, 0, 0);

		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(25, 0, "微软雅黑");
		outtextxy(500, HEIGHT + 20, "总雷数:");
		outtextxy(500, HEIGHT + 50, "40");
	}
	if (GameDifficult == 3)
	{
		loadimage(&EXIT, "image\\exit.png", 80, 80);
		loadimage(&AGAIN, "image\\again.png", 80, 80);
		loadimage(&MENU, "image\\menu.png", 80, 80);

		putimage(WIDTH / 2 - 50, HEIGHT, 80, 80, &AGAIN, 0, 0);
		putimage(WIDTH / 2 + 150, HEIGHT, 80, 80, &EXIT, 0, 0);
		putimage(WIDTH / 2 - 250, HEIGHT, 80, 80, &MENU, 0, 0);

		setbkmode(TRANSPARENT);
		settextcolor(RED);
		settextstyle(25, 0, "微软雅黑");
		outtextxy(WIDTH / 2 + 400, HEIGHT + 20, "总雷数:");
		outtextxy(WIDTH / 2 + 400, HEIGHT + 50, "100");
	}
}

//判断并显示GameOver,或者YouWIn
void PrintWinLost()
{
	if (DecideWin())
	{
		
		for (int i = 0; i < BlockRow; i++)
		{
			for (int j = 0; j < BlockColumn; j++)
			{
				if (blocks[i][j].TypeFlag == -1)
				{
					putimage(j * 40, i * 40, 40, 40, &FLAG, 0, 0);
				}
			}
		}
		 loadimage(&WIN, "image\\youwin.png", WIDTH / 3, HEIGHT / 5);
		putimage(WIDTH / 2 - WIDTH / 6, HEIGHT / 4, WIDTH / 3, HEIGHT / 5, &WIN, 0, 0);
	}
	else if (NoClickFlag == 1)
	{
		loadimage(&LOST, "image\\gameover.png", WIDTH / 3, HEIGHT / 5);
		putimage(WIDTH / 2 - WIDTH / 6, HEIGHT / 4, WIDTH / 3, HEIGHT / 5, &LOST, 0, 0);
	}
}

//判断是否Win
bool DecideWin()
{
	for (int i = 0; i < BlockRow; i++)
	{
		for (int j = 0; j < BlockColumn; j++)
		{
			if (blocks[i][j].TypeFlag == -1)
			{
				if (blocks[i][j].ClickFlag == 1)
					return false;
			}
			if (blocks[i][j].TypeFlag != -1)
			{
				if (blocks[i][j].ClickFlag != 1)
					return false;
			}
		}
	}
	return true;
}
//测试
/*void test()
{
	for (int i = 0; i < BlockRow; i++)
	{
		for (int j = 0; j < BlockColumn; j++)
		{
			if (blocks[i][j].TypeFlag == -1)
			{
				loadimage(&MINE, "image\\mine.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &MINE, 0, 0);
			}
			else {
			switch (blocks[i][j].MineAsideNum)		//显示附近的雷数
			{
			case 1:
				loadimage(&NUM1, "image\\1.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM1, 0, 0);
				break;
			case 2:
				loadimage(&NUM2, "image\\2.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM2, 0, 0);
				break;
			case 3:
				loadimage(&NUM3, "image\\3.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM3, 0, 0);
				break;
			case 4:
				loadimage(&NUM4, "image\\4.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM4, 0, 0);
				break;
			case 5:
				loadimage(&NUM5, "image\\5.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM5, 0, 0);
				break;
			case 6:
				loadimage(&NUM6, "image\\6.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM6, 0, 0);
				break;
			case 7:
				loadimage(&NUM7, "image\\7.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM7, 0, 0);
				break;
			case 8:
				loadimage(&NUM8, "image\\8.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM8, 0, 0);
				break;
			case 0:
				loadimage(&NUM0, "image\\0.png", 40, 40);
				putimage(j * 40, i * 40, 40, 40, &NUM0, 0, 0);
				break;
			}
			}
		}

	}



}*/