#ifndef DEFINE_H
#define DEFINE_H

#include<graphics.h>



//��λ
#define UNIT        65				
//�������
#define GRAPHWIDTH  14		//������
#define GRAPHHIGH   11.5	//������
//��������
#define GRAPHCOLOR  RGB(238,180,34)
//��¼����
#define WCCOLOR1    BLACK
#define WCCOLOR2	RED
//������ɫ
#define LINECOLOR   BLACK
//������ɫ
#define WORDCOLOR   BLACK
//���ִ�С
#define WORDSIZE    20
//����
#define WORDSTYLE   "����"




//���̹��
#define BASICWIDTH  1	//���̳���
#define BASICHIGH   1	//���̳���
#define MAXWIDTH    9	//���������
#define MAXHIGH     10	//���������
//��������
#define _wh         6	//������߲�
//������ɫ
#define BCCOLOR     BLACK 
//������ɫ
#define RCCOLOR     RED
//���Ӵ�С
#define CHESSSIZE   65
//ѡ����ɫ
#define RCSECOLOR   RED
//������ɫ
#define BCSECOLOR   BLUE
//������ɫ
#define KEYCOLOR    BLUE




//��¼�ļ�
#define PLAYER   ".\\FILE\\palyer.txt"		    //λ��
//����ж�
#define TRUE    1	//��
#define FALSE   0	//��
#define OK      1 
#define NO      0
#define OT      2
#define RMOVE   1	//�����ƶ�
#define BMOVE   0	//�����ƶ�
//��¼��
enum CHESS_VAL		//r :���� b :����
{
	no = 0,			//no:�ո�										//7: ˧��					
	r1 = 1, r2 = 2, r3 = 3, r4 = 4, r5 = 5, r6 = 6, r7 = 7,			//1: ����	2: ��		3: ܇	 
	b1 = -1, b2 = -2, b3 = -3, b4 = -4, b5 = -5, b6 = -6, b7 = -7	//4: �R	    5: ����		6: ʿ��
};




//��������
typedef int Bool;
typedef int Move;
//����״̬
typedef int Status;
//��������
typedef double Pos;
//��¼����
typedef int Map;




//��������
typedef struct CHESS
{
	Move flag;               //��ǰ�ƶ�
	Map  dead;	             //��¼����
	Map x1, y1,x2,y2;        //��
	struct CHESS* next;      //��һ����
}Chess,*PChess;
//��ͼ����
typedef struct PICTURE
{
	IMAGE mask;
	IMAGE r1, r2, r3, r4, r5, r6, r7;
	IMAGE b1, b2, b3, b4, b5, b6, b7;
}Image,*PImage;
//�������
typedef struct SURVIVAL		//���Ӵ����,��ǰִ�巽
{
	int flag;
	int r1, r2, r3, r4, r5, r6, r7;
	int b1, b2, b3, b4, b5, b6, b7;
}Survival,*PSurvival;


#endif // !DEFINE_H
