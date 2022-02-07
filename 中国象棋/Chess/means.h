#ifndef MEANS_H
#define MEANS_H

#include"define.h"


//程序功能

//2.悔下棋子
void BackChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);
//3.和平退棋
void DrawChess();

//4.回顾棋局
void ReviewChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);



//执行方式:

//1.左炮卒线
void Draw12L(Pos x0, Pos y0);
//2.右炮卒线
void Draw12R(Pos x0, Pos y0);
//3.加载棋子
void InitChess(PImage im);
//4.是否按键
Status Is_HitKey(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, Map px, Map py, PImage im);
//7.销毁棋谱
void FreeChess(PChess* chess);
//生成棋谱
void ChessChart(PChess* chess);


//****************************************************************************

#endif // !MEANS_H
