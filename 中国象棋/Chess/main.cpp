

/***************************
 *
 * ����    : Chess
 * ����    : north151
 * ����    : ����,���׼�¼
 * �汾    : 2.0
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


//�������
int main()
{
	//1.��¼��Ϸ
	Welcome();
	Image im;
	PChess chess=NULL;
	Survival scores;
	Map map[MAXHIGH][MAXWIDTH];
	Status mode = OK;
RENEW:
	//2.��ʼ����
	InitBoard(map,&scores, &im);
	//3.��ʼ�Ծ�
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
		mode=ChooseChess(map, &chess, &scores, &im);//4.ѡ������(��������)
		if (mode == OK)//ѡ������
		{
			DropChess(map, &chess, &scores, &im);	//5.��������(����������)
			Show(map, &scores, &im);				//6.չʾȫ��
			if (Is_WinChess(map, &scores))break;	//7.�Ƿ�Ӯ��
		}
		else if (mode == NO)//���»���
		{
			continue;
		}
		else if (mode == OT)//���º���
		{
			break;
		}	
	}
	ChessChart(&chess);
	goto RENEW;
	return 0;
}

