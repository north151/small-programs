

/***************************
 *
 * 名称    : Chess
 * 作者    : north151
 * 功能    : 棋盘,棋谱记录
 * 版本    : 2.0
 * 
 ************************** */



#include <graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<string.h>
#include<conio.h>

#include"operation.h"
#include"show.h"
#include"means.h"
#include"define.h"


//程序入口
int main()
{
	//1.登录游戏
	Welcome();
	Image im;
	PChess chess=NULL;
	Survival scores;
	Map map[MAXHIGH][MAXWIDTH];
	Status mode = OK;
RENEW:
	//2.初始棋盘
	InitBoard(map,&scores, &im);
	//3.开始对局
	while (TRUE)
	{
		mode = Begin(map, &chess, &scores, &im);
		if (mode == OT) {
			return FALSE;
		}
		else if (mode == NO) 
			continue;
		else if (mode == OK)
			break;
	}
	while (TRUE)
	{	
		mode=ChooseChess(map, &chess, &scores, &im);//4.选中棋子(包含按键)
		if (mode == OK)//选中棋子
		{
			DropChess(map, &chess, &scores, &im);	//5.落下棋子(不包含按键)
			Show(map, &scores, &im);				//6.展示全局
			if (Is_WinChess(map, &scores))break;	//7.是否赢棋
		}
		else if (mode == NO)//按下悔棋
		{
			continue;
		}
		else if (mode == OT)//按下和棋
		{
			break;
		}	
	}
	ChessChart(&chess);
	goto RENEW;
	return 0;
}

