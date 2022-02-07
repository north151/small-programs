#ifndef  SHOW_H
#define  SHOW_H

#include"define.h"


//��������
//****************************************************************************//


//1.չʾ����
void ShowLayout();

//2.չʾ����
void ShowGround();

//3.Ӯ�����
void ShowWinChess(Survival* scores);


//�仯����
//****************************************************************************//
 

//1.չʾ����
void ShowChess(Map map[MAXHIGH][MAXWIDTH], PImage im);

//2.չʾ���
void ShowScore(Survival* scores);

//3.չʾѡ��
void ShowChooseChess(Map map[MAXHIGH][MAXWIDTH], Map x, Map y, Chess *chess);

//4.չʾ����
void ShowDropChess(Map x, Map y, Chess* chess);


//��������չʾ
//****************************************************************************//

//1.չʾ����
void ShowBackChess();

//2.չʾ����
void ShowDrawChess();

//3.չʾ����
void ShowReviewChess();

//4.չʾ����
void ShowRank();

//5.�˳�����
void ShowGoodbye();



#endif // ! SHOW_H



