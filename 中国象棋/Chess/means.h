#ifndef MEANS_H
#define MEANS_H

#include"define.h"


//������

//2.��������
void BackChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);
//3.��ƽ����
void DrawChess();

//4.�ع����
void ReviewChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);



//ִ�з�ʽ:

//1.��������
void Draw12L(Pos x0, Pos y0);
//2.��������
void Draw12R(Pos x0, Pos y0);
//3.��������
void InitChess(PImage im);
//4.�Ƿ񰴼�
Status Is_HitKey(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, Map px, Map py, PImage im);
//7.��������
void FreeChess(PChess* chess);
//��������
void ChessChart(PChess* chess);


//****************************************************************************

#endif // !MEANS_H
