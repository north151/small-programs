#include <graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>

#include"operation.h"
#include"show.h"
#include"define.h"


//****************************************************************************//
//***************				   ������ 		    **********************//
//****************************************************************************//


//1.��������
void BackChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im)
{
	//����
	if ((*chess) != NULL && (*chess)->next != NULL)//δ�ص�����
	{
		PChess back = (*chess)->next;
		//������
		if ((*chess)->flag == RMOVE)
		{
			switch (back->dead)
			{
			case no:break;
			case r1:scores->r1++; break;
			case r2:scores->r2++; break;
			case r3:scores->r3++; break;
			case r4:scores->r4++; break;
			case r5:scores->r5++; break;
			case r6:scores->r6++; break;
			}
		}
		//������
		else if ((*chess)->flag == BMOVE)
		{
			switch (back->dead)
			{
			case no:break;
			case b1:scores->b1++; break;
			case b2:scores->b2++; break;
			case b3:scores->b3++; break;
			case b4:scores->b4++; break;
			case b5:scores->b5++; break;
			case b6:scores->b6++; break;
			}
		}
		//���ӹ�λ
		{
			(*chess)->flag = back->flag;
			scores->flag = back->flag;
			map[back->y1][back->x1] = map[back->y2][back->x2];
			map[back->y2][back->x2] = back->dead;
			(*chess)->next = back->next;
			free(back);
		}
		//����
		{
			Show(map, scores, im);
			Pos x0 = BASICWIDTH, y0 = MAXHIGH + 0.75;
			clearrectangle(x0 * UNIT, y0 * UNIT, MAXWIDTH * UNIT, GRAPHHIGH * UNIT);
			settextcolor(WORDCOLOR);
			settextstyle(WORDSIZE, 0, WORDSTYLE);
			outtextxy(x0 * UNIT, y0 * UNIT, "��ɱ��, ����ȡʤ");
		}
	}
	return;
}


//2.��ƽ����
void DrawChess()
{
	settextstyle(6.5 * WORDSIZE, 0, WORDSTYLE);
	setbkcolor(BCCOLOR);
	clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
	setcolor(WHITE);
	outtextxy(2.7 * UNIT, (MAXHIGH - 7) * UNIT, "���");
	outtextxy(2.7 * UNIT, (MAXHIGH - 5) * UNIT, "����");
	setbkcolor(RCCOLOR);
	clearrectangle(GRAPHWIDTH * UNIT / 2, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
	setcolor(WHITE);
	outtextxy(7.2 * UNIT, (MAXHIGH - 7) * UNIT, "����");
	outtextxy(7.2 * UNIT, (MAXHIGH - 5) * UNIT, "˧��");
	Sleep(3000); return;
}


//4.�ع����
void ReviewChess(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im)
{
	if ((*chess) == NULL)return;
	PChess rechess = (*chess);
	Map x1, y1, x2, y2;
	Map dead;
	Pos x0 = BASICWIDTH, y0 = MAXHIGH + 0.75;
	//��ʾ
	{
		Show(map, scores, im);
		clearrectangle(x0 * UNIT, y0 * UNIT, MAXWIDTH * UNIT, GRAPHHIGH * UNIT);
		settextcolor(WORDCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		outtextxy(x0 * UNIT, y0 * UNIT, "���س�����һ��");
	}
	while (rechess->next)
	{
		dead = rechess->dead;
		x1 = rechess->x1, y1 = rechess->y1;
		x2 = rechess->x2, y2 = rechess->y2;
		getchar();
		ShowChooseChess(map, x1, y1, rechess);
		getchar();
		//���Ӵ����
		{
			switch (dead)
			{
			case no:break;
			case b1:scores->b1--; break;
			case b2:scores->b2--; break;
			case b3:scores->b3--; break;
			case b4:scores->b4--; break;
			case b5:scores->b5--; break;
			case b6:scores->b6--; break;
			case b7:scores->b7--; break;
			case r1:scores->r1--; break;
			case r2:scores->r2--; break;
			case r3:scores->r3--; break;
			case r4:scores->r4--; break;
			case r5:scores->r5--; break;
			case r6:scores->r6--; break;
			case r7:scores->r7--; break;
			}
			scores->flag = scores->flag == RMOVE ? BMOVE : RMOVE;
		}
		//�ƶ�����
		{
			map[y2][x2] = map[y1][x1];
			map[y1][x1] = no;
			//��ʾ
			{
				Show(map, scores, im);
				settextcolor(WORDCOLOR);
				settextstyle(WORDSIZE, 0, WORDSTYLE);
				clearrectangle(x0 * UNIT, y0 * UNIT, MAXWIDTH * UNIT, GRAPHHIGH * UNIT);
				outtextxy(x0 * UNIT, y0 * UNIT, "���س�����һ��");
			}
		}
		rechess = rechess->next;
	}
	//�ع˽���
	{
		setbkcolor(GRAPHCOLOR);
		clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
		settextcolor(WORDCOLOR);
		settextstyle(6.5 * WORDSIZE, 0, WORDSTYLE);
		outtextxy(2.7 * UNIT, (MAXHIGH - 5) * UNIT,"�ع˽���");
		Sleep(1000);
		InitBoard(map, scores, im);
	}
	return;
}



//****************************************************************************//
//***************				   ִ�з�ʽ  		    **********************//
//****************************************************************************//

//�̶�

//1.��������
void Draw12L(Pos x0, Pos y0)
{
	line(x0 * UNIT - 2, y0 * UNIT + 2, x0 * UNIT - 2, y0 * UNIT + 10);
	line(x0 * UNIT - 2, y0 * UNIT + 2, x0 * UNIT - 10, y0 * UNIT + 2);
	line(x0 * UNIT - 2, y0 * UNIT - 2, x0 * UNIT - 2, y0 * UNIT - 10);
	line(x0 * UNIT - 2, y0 * UNIT - 2, x0 * UNIT - 10, y0 * UNIT - 2);
}


//2.��������
void Draw12R(Pos x0, Pos y0)
{
	line(x0 * UNIT + 2, y0 * UNIT + 2, x0 * UNIT + 2, y0 * UNIT + 10);
	line(x0 * UNIT + 2, y0 * UNIT + 2, x0 * UNIT + 10, y0 * UNIT + 2);
	line(x0 * UNIT + 2, y0 * UNIT - 2, x0 * UNIT + 2, y0 * UNIT - 10);
	line(x0 * UNIT + 2, y0 * UNIT - 2, x0 * UNIT + 10, y0 * UNIT - 2);
}


//3.��������
void InitChess(PImage im)
{
	//loadimage(&im->mask_map, "mask_map.jpg");
	//����
	{
		loadimage(&im->r1, ".\\IMAGE\\r1.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r2, ".\\IMAGE\\r2.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r3, ".\\IMAGE\\r3.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r4, ".\\IMAGE\\r4.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r5, ".\\IMAGE\\r5.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r6, ".\\IMAGE\\r6.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->r7, ".\\IMAGE\\r7.png", CHESSSIZE, CHESSSIZE, FALSE);
	}
	//����
	{
		loadimage(&im->b1, ".\\IMAGE\\b1.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b2, ".\\IMAGE\\b2.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b3, ".\\IMAGE\\b3.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b4, ".\\IMAGE\\b4.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b5, ".\\IMAGE\\b5.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b6, ".\\IMAGE\\b6.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->b7, ".\\IMAGE\\b7.png", CHESSSIZE, CHESSSIZE, FALSE);
		loadimage(&im->mask, ".\\IMAGE\\mask.png", CHESSSIZE, CHESSSIZE, FALSE);
	}
}


//4.�Ƿ񰴼�
Status Is_HitKey(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, Map px, Map py, PImage im)
{
	Pos x1 = (MAXWIDTH + 0.7) * UNIT, x2 = x1 + 2 * UNIT;
	if (px >= x1 && px <= x2)
	{
		Pos y1 = 0, y2 = 0;
		for (int cnt = 2; cnt <= 3; cnt++)
		{
			y1 = (MAXHIGH - cnt) * UNIT, y2 = y1 + 0.7 * UNIT;
			if (py >= y1 && py <= y2)
			{
				//����н��ɻ���,����
				switch (cnt)
				{
				case 2:DrawChess();return OT;
				case 3:BackChess(map,chess,scores,im);return OK;
				}
			}
		}
	}
	return NO;
}


//2.��������
void FreeChess(PChess *chess)
{
	PChess temp;
	while ((*chess)!=NULL)
	{
		temp = (*chess)->next;
		free(*chess);
		(*chess)=temp;
	}
	//��һ������
	{
		(*chess) = (PChess)malloc(sizeof(Chess));
		(*chess)->flag = RMOVE;
		(*chess)->next = NULL; //������Ҫ
	}
}


//6.��ȡ����
void ChessChart(PChess* chess)
{
	PChess last = NULL, next = NULL;
	while (*chess)
	{
		next = (*chess)->next;
		(*chess)->next = last;
		last = (*chess);
		(*chess) = next;
	}
	(*chess) = last;
	return;
}

