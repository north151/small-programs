#ifndef  SHOW_H
#define  SHOW_H

#include"define.h"


//不变因素
//****************************************************************************//


//1.展示按键
void ShowLayout();

//2.展示棋盘
void ShowGround();

//3.赢得棋局
void ShowWinChess(Survival* scores);


//变化因素
//****************************************************************************//
 

//1.展示棋子
void ShowChess(Map map[MAXHIGH][MAXWIDTH], PImage im);

//2.展示棋况
void ShowScore(Survival* scores);

//3.展示选棋
void ShowChooseChess(Map map[MAXHIGH][MAXWIDTH], Map x, Map y, Chess *chess);

//4.展示落棋
void ShowDropChess(Map x, Map y, Chess* chess);


//按键内容展示
//****************************************************************************//

//1.展示悔棋
void ShowBackChess();

//2.展示和棋
void ShowDrawChess();

//3.展示棋谱
void ShowReviewChess();

//4.展示排行
void ShowRank();

//5.退出程序
void ShowGoodbye();



#endif // ! SHOW_H



