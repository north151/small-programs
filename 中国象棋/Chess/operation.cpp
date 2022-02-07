#include <graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>

#include"show.h"
#include"means.h"
#include"define.h"


//****************************************************************************//
//***************				   ������� 		    **********************//
//****************************************************************************//


//1.��¼��Ϸ
void Welcome()
{
	FILE* fp = fopen(PLAYER, "w");
	//��ʼ������
	initgraph(GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT, 0);//SHOWCONSOLE  ||  0
	//�ڷ�����
	{
		char ch = 'n', name1[20] = {'N'};
		setbkcolor(WCCOLOR1);
		clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
		settextstyle(6.5 * WORDSIZE, 0, WORDSTYLE);
		outtextxy(3 * UNIT, (MAXHIGH - 6) * UNIT / 2, "�巨����");
		outtextxy(3 * UNIT, (MAXHIGH - 2) * UNIT / 2, "��Ϊ��γ");
		settextstyle(1.5 * WORDSIZE, 0, WORDSTYLE);
		outtextxy(4 * UNIT, (MAXHIGH - 2) * UNIT, "����ڷ�����:");
		for(int i=0;i<19;i++)
		{
			ch = _getch();
			name1[i] = ch;
			clearrectangle(7 * UNIT, (MAXHIGH - 2) * UNIT, GRAPHWIDTH * UNIT, (MAXHIGH - 2) * UNIT);
			outtextxy(7 * UNIT, (MAXHIGH - 2) * UNIT, name1);
			if(ch=='\r')break;
		}
		fprintf(fp,"%s\n",name1);
	}
	//�췽����
	{
		char ch = 'n', name2[20] ={'N'};
		setbkcolor(WCCOLOR2);
		clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
		settextstyle(6.5 * WORDSIZE, 0, WORDSTYLE);
		outtextxy(3 * UNIT, (MAXHIGH - 6) * UNIT / 2, "�巨����");
		outtextxy(3 * UNIT, (MAXHIGH - 2) * UNIT / 2, "��Ϊ��γ");
		settextstyle(1.5 * WORDSIZE, 0, WORDSTYLE);
		outtextxy(4 * UNIT, (MAXHIGH - 2) * UNIT, "����췽����:");
		for (int i = 0; i < 19 ; i++)
		{
			ch = _getch();
			name2[i] = ch;
			clearrectangle(7 * UNIT, (MAXHIGH - 2) * UNIT, GRAPHWIDTH * UNIT, (MAXHIGH - 2) * UNIT);
			outtextxy(7 * UNIT, (MAXHIGH - 2) * UNIT, name2);
			if (ch == '\r')break;
		}
		fprintf(fp, "%s\n", name2);
	}
	fclose(fp);
	return;
}

//2.��ʼ����
void InitBoard(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im)
{
	//��ʼ����
	{
		//��ʼ����
		{
			map[0][0] = b3, map[0][1] = b4, map[0][2] = b5, map[0][3] = b6, map[0][4] = b7, map[0][5] = b6, map[0][6] = b5, map[0][7] = b4, map[0][8] = b3;
			map[1][0] = no, map[1][1] = no, map[1][2] = no, map[1][3] = no, map[1][4] = no, map[1][5] = no, map[1][6] = no, map[1][7] = no, map[1][8] = no;
			map[2][0] = no, map[2][1] = b2, map[2][2] = no, map[2][3] = no, map[2][4] = no, map[2][5] = no, map[2][6] = no, map[2][7] = b2, map[2][8] = no;
			map[3][0] = b1, map[3][1] = no, map[3][2] = b1, map[3][3] = no, map[3][4] = b1, map[3][5] = no, map[3][6] = b1, map[3][7] = no, map[3][8] = b1;
			map[4][0] = no, map[4][1] = no, map[4][2] = no, map[4][3] = no, map[4][4] = no, map[4][5] = no, map[4][6] = no, map[4][7] = no, map[4][8] = no;
			map[5][0] = no, map[5][1] = no, map[5][2] = no, map[5][3] = no, map[5][4] = no, map[5][5] = no, map[5][6] = no, map[5][7] = no, map[5][8] = no;
			map[6][0] = r1, map[6][1] = no, map[6][2] = r1, map[6][3] = no, map[6][4] = r1, map[6][5] = no, map[6][6] = r1, map[6][7] = no, map[6][8] = r1;
			map[7][0] = no, map[7][1] = r2, map[7][2] = no, map[7][3] = no, map[7][4] = no, map[7][5] = no, map[7][6] = no, map[7][7] = r2, map[7][8] = no;
			map[8][0] = no, map[8][1] = no, map[8][2] = no, map[8][3] = no, map[8][4] = no, map[8][5] = no, map[8][6] = no, map[8][7] = no, map[8][8] = no;
			map[9][0] = r3, map[9][1] = r4, map[9][2] = r5, map[9][3] = r6, map[9][4] = r7, map[9][5] = r6, map[9][6] = r5, map[9][7] = r4, map[9][8] = r3;
		}
		//��ʼ����
		{
			scores->flag = RMOVE;
			scores->r1 = 5, scores->r2 = 2, scores->r3 = 2, scores->r4 = 2, scores->r5 = 2, scores->r6 = 2, scores->r7 = 1;
			scores->b1 = 5, scores->b2 = 2, scores->b3 = 2, scores->b4 = 2, scores->b5 = 2, scores->b6 = 2, scores->b7 = 1;
		}
	}
	//��ʼ����
	{
		setbkcolor(GRAPHCOLOR);
		cleardevice();
		clearrectangle(0, 0, (MAXWIDTH + 1) * UNIT, (MAXHIGH + 1) * UNIT);
	}
	//��ʼ����
	{
		InitChess(im);
		BeginBatchDraw();
		ShowGround();
		ShowLayout();
		EndBatchDraw();
	}
}


//3.��ʼ�Ծ�
Status Begin(Map map[MAXHIGH][MAXWIDTH], PChess* chess, Survival* scores, PImage im)
{
	HWND hwnd = GetHWnd();
	POINT point;
	MOUSEMSG m;
	while (TRUE)
	{
		//�õ������Ϣ
		{
			m = GetMouseMsg();
			GetCursorPos(&point);
			ScreenToClient(hwnd, &point);
		}
		//������������ѡ�в���
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			Pos x1 = (MAXWIDTH + 0.7) * UNIT, x2 = x1 + 2 * UNIT;
			Pos y1 = (MAXHIGH - 4) * UNIT, y2 = y1 + 0.7 * UNIT;
			Pos x3 = (GRAPHWIDTH - 1.5) * UNIT, x4 = (GRAPHWIDTH - 0.5) * UNIT;
			Pos y3 = (GRAPHHIGH - 0.6) * UNIT, y4 = (GRAPHHIGH - 0.1) * UNIT;
			Pos x5 = x1, x6 = x2, y5 = (MAXHIGH - 1) * UNIT, y6 = y5 + 0.7 * UNIT;
			//��ʼ�Ծ�
			if((point.x >= x1 && point.x <= x2)&&(point.y >= y1 && point.y <= y2))
			{
				FreeChess(chess);
				ShowChess(map, im);
				ShowScore(scores);
				return OK;
			}
			//�ع�����
			else if ((point.x >= x5 && point.x <= x6) && (point.y >= y5 && point.y <= y6))
			{
				ReviewChess(map, chess, scores, im);
				return NO;
			}
			//�˳�����
			else if ((point.x >= x3 && point.x <= x4) && (point.y >= y3 && point.y <= y4))
			{
				ShowGoodbye();
				return OT;
			}
		}
	}
}


//4.ѡ������
Status ChooseChess(Map map[MAXHIGH][MAXWIDTH], PChess *chess, Survival* scores, PImage im)
{
	HWND hwnd = GetHWnd();
	POINT point;
	MOUSEMSG m;
	Map x = BASICHIGH, y = BASICHIGH;
	while (TRUE)
	{
		CHOOSEERROR://ѡ����Ч
		//�õ������Ϣ
		{
			m = GetMouseMsg();
			GetCursorPos(&point);
			ScreenToClient(hwnd, &point);
		}
		//������������ѡ�в���
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			Status mode = Is_HitKey(map, chess, scores, point.x, point.y, im);
			if (mode == OK)return NO;
			else if (mode == OT)return OT;
			else if (mode == NO)
			{
				for (y = BASICHIGH - 1; y < MAXHIGH; y++)
				{
					for (x = BASICWIDTH - 1; x < MAXWIDTH; x++)
					{
						//�ǿ�����
						if (map[y][x] != no)
						{
							//ȷ������(/8Ϊ������Сѡ�з�Χ�Լ�����)
							if ((point.x - (x + 1.05) * UNIT) * (point.x - (x + 1.05) * UNIT) * (point.y - (y + 1.1) * UNIT) * (point.y - (y + 1.1) * UNIT) < (CHESSSIZE * CHESSSIZE) / 8)
							{
								if ((*chess)->flag == BMOVE && map[y][x] < 0)
								{
									(*chess)->y1 = y;
									(*chess)->x1 = x;
								}
								//ѡ�к���
								else if ((*chess)->flag == RMOVE && map[y][x] > 0)
								{
									(*chess)->y1 = y;
									(*chess)->x1 = x;
								}
								//ѡ����Ч
								else
								{
									goto CHOOSEERROR;
								}
								ShowChooseChess(map, x, y, *chess);
								//����ѡ��
								return OK;
							}

						}
					}
				}
			}
		}
	}
}


//5.��������
void DropChess(Map map[MAXHIGH][MAXWIDTH], PChess *chess, Survival* scores, PImage im)
{
	HWND hwnd = GetHWnd();
	POINT point;
	MOUSEMSG m;
	Map x = BASICHIGH, y = BASICHIGH;
	while (TRUE)
	{
		//�õ������Ϣ
		{
			m = GetMouseMsg();
			GetCursorPos(&point);
			ScreenToClient(hwnd, &point);
		}
		//���������������Ӳ���
		if (m.uMsg == WM_LBUTTONDOWN)
		{
			for (y = BASICHIGH - 1; y < MAXHIGH; y++)
			{
				for (x = BASICWIDTH - 1; x < MAXWIDTH; x++)
				{
					//ȷ������λ��(/8Ϊ������Сѡ�з�Χ�Լ�����)
					if ((point.x - (x + 1.05) * UNIT) * (point.x - (x + 1.05) * UNIT) * (point.y - (y + 1.1) * UNIT) * (point.y - (y + 1.1) * UNIT) < (CHESSSIZE * CHESSSIZE) / 8)
					{
						//��ֹ�Ե�����
						//�����ƶ�
						if ((*chess)->flag == RMOVE && map[y][x]<=0 )
						{
							//��¼������
							{
								switch (map[y][x])
								{
								case no:break;
								case b1:scores->b1--; break;
								case b2:scores->b2--; break;
								case b3:scores->b3--; break;
								case b4:scores->b4--; break;
								case b5:scores->b5--; break;
								case b6:scores->b6--; break;
								case b7:scores->b7--; break;
								}
								scores->flag = BMOVE;
								(*chess)->dead = map[y][x]; //��¼����,�Ա�����
								(*chess)->y2 = y, (*chess)->x2 = x;
							}
							//�ƶ�����
							{
								map[y][x] = map[(*chess)->y1][(*chess)->x1];
								map[(*chess)->y1][(*chess)->x1] = no;
								//ShowDropChess(x, y, *chess);
							}
							//��һ����
							{
								PChess temp = (PChess)malloc(sizeof(Chess));
								temp->flag = BMOVE;
								temp->dead = no;
								temp->next = (*chess);
								(*chess) = temp;
							}
						}
						//�����ƶ�
						else if ((*chess)->flag == BMOVE && map[y][x] >= 0)
						{
							//��¼������
							{
								switch (map[y][x])
								{
								case no:break;
								case r1:scores->r1--; break;
								case r2:scores->r2--; break;
								case r3:scores->r3--; break;
								case r4:scores->r4--; break;
								case r5:scores->r5--; break;
								case r6:scores->r6--; break;
								case r7:scores->r7--; break;
								}
								scores->flag = RMOVE;
								(*chess)->dead = map[y][x]; //��¼����,�Ա�����
								(*chess)->y2 = y, (*chess)->x2 = x;
							}
							//�ƶ�����
							{
								map[y][x] = map[(*chess)->y1][(*chess)->x1];
								map[(*chess)->y1][(*chess)->x1] = no;
								//ShowDropChess(x, y, *chess);
							}
							//��һ����
							{
								PChess temp = (PChess)malloc(sizeof(Chess));
								temp->flag = RMOVE;
								temp->dead = no;
								temp->next = (*chess);
								(*chess) = temp;
							}
						}
						//��������(������ѡ����)
						return;
					}

				}
			}
		}
	}
}


//6.չʾȫ��
void Show(Map map[MAXHIGH][MAXWIDTH], Survival* scores, PImage im)
{
	clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);//��ձ���
	BeginBatchDraw();				//��ʼ������,��ֹ��˸
	ShowGround();					//չʾ�̶�����
	ShowChess(map, im);			    //չʾ����
	ShowScore(scores);		        //չʾ����
	EndBatchDraw();					//����������
	return;
}


//7.�Ƿ�Ӯ��
Status Is_WinChess(Map map[MAXHIGH][MAXWIDTH], Survival* scores)
{
	//��˧����
	if (scores->r7 == 0 || scores->b7 == 0)
	{
		ShowWinChess(scores);
		return OK;
	}
	//��˧���
	else
	{
		Map x0 = 0, y0 = 0;
		Map x = 0, y = 0;
		for (y0 = BASICHIGH - 1; y < BASICHIGH + 2; y++)
		{
			for (x0 = BASICWIDTH + 3; x < BASICWIDTH + 5; x++)
			{
				if (map[y0][x0] == b7)goto FOUNDB7;
			}
		}
	FOUNDB7:
		for (y = y0 + 1; y < MAXHIGH; y++)
		{
			if (map[y][x0] == r7)
			{
				ShowWinChess(scores);
				return OK;
			}
			else if (map[y][x0] != no) return NO;
		}
	}
	return NO;
}










