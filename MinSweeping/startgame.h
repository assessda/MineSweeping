#pragma once
#include "achieve.h"


void StartGame()
{
	MenuFlag = 1;
	while (MenuFlag == 1)
	{
		FlagInit();
		StartUIGame();
		while (ExitFlag != 1)
		{
			GameModeInit();
			while (AgainFlag == 1)
			{
				Initialization();
				BuryMine();
				MineWarn();
				DrawInit();
				//test();
				IconLocate();
				while (!OverFlag)
				{
					GameControl();
				}
			}
		}
	}
	closegraph();
}
