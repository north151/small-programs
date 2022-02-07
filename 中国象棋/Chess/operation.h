
//��,ͷ�ļ�
#ifndef OPERATION_H
#define OPERATION_H

#include"define.h"

//****************************************************************************


//�������
 
//1.��¼��Ϸ
void Welcome();

//2.��ʼ����
void InitBoard(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im);

//3.��ʼ�Ծ�
Status Begin(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);

//4.ѡ������
Status ChooseChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);

//5.��������
void DropChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im);


//6.չʾȫ��
void Show(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im);


//7.�Ƿ�Ӯ��
Status Is_WinChess(Map map[MAXHIGH][MAXWIDTH], Survival* scores);


//****************************************************************************



#endif // ! OPERATION_H