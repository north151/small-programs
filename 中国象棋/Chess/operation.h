
//宏,头文件
#ifndef OPERATION_H
#define OPERATION_H

#include"define.h"

//****************************************************************************


//下棋操作
 
//1.登录游戏
void Welcome();

//2.初始棋盘
void InitBoard(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im);

//3.开始对局
Status Begin(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);

//4.选中棋子
Status ChooseChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);

//5.落下棋子
void DropChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);


//6.展示全局
void Show(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im);


//7.是否赢棋
Status Is_WinChess(Map map[MAXHIGH][MAXWIDTH], Survival* scores);


//****************************************************************************



#endif // ! OPERATION_H