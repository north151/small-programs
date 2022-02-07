#include <graphics.h>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>


#include"operation.h"
#include"means.h"
#include"define.h"




//****************************************************************************//
//***************				   不变因素 		    **********************//
//****************************************************************************//

//1.展示布局
void ShowLayout()
{
	Pos x0 = 0, y0 = 0, x = 0, y = 0;
	//黑棋字
	{
		settextcolor(BCCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		outtextxy((MAXWIDTH + 0.5) * UNIT, (BASICHIGH + 1) * UNIT, "黑棋:");
		settextstyle(0.75 * (WORDSIZE), 0, WORDSTYLE);
		outtextxy((MAXWIDTH + 0.7) * UNIT, (BASICHIGH + 1.5) * UNIT, "卒:");
		outtextxy((MAXWIDTH + 1.7) * UNIT, (BASICHIGH + 1.5) * UNIT, "炮:");
		outtextxy((MAXWIDTH + 2.7) * UNIT, (BASICHIGH + 1.5) * UNIT, "車:");
		outtextxy((MAXWIDTH + 0.7) * UNIT, (BASICHIGH + 2.0) * UNIT, "馬:");
		outtextxy((MAXWIDTH + 1.7) * UNIT, (BASICHIGH + 2.0) * UNIT, "象:");
		outtextxy((MAXWIDTH + 2.7) * UNIT, (BASICHIGH + 2.0) * UNIT, "仕:");
	}
	//红棋字
	{
		settextcolor(RCCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		outtextxy((MAXWIDTH + 0.5) * UNIT, (BASICHIGH + 2.7) * UNIT, "红棋:");
		settextstyle(0.75 * (WORDSIZE), 0, WORDSTYLE);
		outtextxy((MAXWIDTH + 0.7) * UNIT, (BASICHIGH + 3.2) * UNIT, "兵:");
		outtextxy((MAXWIDTH + 1.7) * UNIT, (BASICHIGH + 3.2) * UNIT, "炮:");
		outtextxy((MAXWIDTH + 2.7) * UNIT, (BASICHIGH + 3.2) * UNIT, "車:");
		outtextxy((MAXWIDTH + 0.7) * UNIT, (BASICHIGH + 3.7) * UNIT, "馬:");
		outtextxy((MAXWIDTH + 1.7) * UNIT, (BASICHIGH + 3.7) * UNIT, "相:");
		outtextxy((MAXWIDTH + 2.7) * UNIT, (BASICHIGH + 3.7) * UNIT, "士:");
	}
	//展示按键
	{
		setlinecolor(LINECOLOR);
		settextcolor(WORDCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		char keyword[6][20] = { " 回顾棋局","  和棋","  悔棋"," 开始对局","注意事项","退出" };
		for (int cnt = 1; cnt <= 4; cnt++)
		{
			x0 = MAXWIDTH + 0.7, y0 = MAXHIGH - cnt;
			x = x0 + 2.0, y = y0 + 0.7;
			outtextxy((x0 + 0.2) * UNIT, (y0 + 0.2) * UNIT, keyword[cnt - 1]);
			line(x0 * UNIT, y0 * UNIT, x * UNIT, y0 * UNIT);
			line(x0 * UNIT, y0 * UNIT, x0 * UNIT, y * UNIT);
			line(x * UNIT, y * UNIT, x * UNIT, y0 * UNIT);
			line(x * UNIT, y * UNIT, x0 * UNIT, y * UNIT);
		}
		x0 = GRAPHWIDTH - 1.5, x = GRAPHWIDTH-0.5;
		y0 = GRAPHHIGH - 0.6, y = GRAPHHIGH - 0.1;
		line(x0 * UNIT, y0 * UNIT, x * UNIT, y0 * UNIT);
		line(x0 * UNIT, y0 * UNIT, x0 * UNIT, y * UNIT);
		line(x * UNIT, y * UNIT, x * UNIT, y0 * UNIT);
		line(x * UNIT, y * UNIT, x0 * UNIT, y * UNIT);
		settextstyle(0.9*WORDSIZE, 0, WORDSTYLE);
		outtextxy((x0+0.2) * UNIT, (y0+0.1) * UNIT, keyword[5]);

	}
	//展示对手
	{
		FILE* fp = fopen(PLAYER, "r");
		char ruser[20], buser[20];
		fscanf(fp, "%s", buser, 20 * (sizeof(char)));
		fscanf(fp, "%s", ruser, 20 * (sizeof(char)));
		x0 = BASICWIDTH, y0 = BASICHIGH - 0.75;
		x = MAXWIDTH - 2, y = BASICHIGH - 0.75;
		settextcolor(WORDCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		outtextxy(x0 * UNIT, y0 * UNIT, "黑棋:");
		outtextxy(x0 * UNIT+UNIT, y0 * UNIT, buser);
		outtextxy(x * UNIT, y * UNIT, "红棋:");
		outtextxy(x * UNIT+UNIT, y * UNIT, ruser);
		fclose(fp);
	}
	//展示赠言
	{
		x0 = BASICWIDTH, y0 = MAXHIGH + 0.75;
		settextcolor(WORDCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		outtextxy(x0 * UNIT, y0 * UNIT, "象棋似布阵, 落子如暗兵");
	}
}


//2.展示棋盘
void ShowGround()
{
	Pos x0 = BASICWIDTH, y0 = BASICHIGH, x = BASICWIDTH, y = BASICHIGH;
	//格线
	{
		//内格线
		{
			setlinestyle(PS_SOLID, 1);
			setcolor(LINECOLOR);
			for (x = BASICWIDTH; x <= MAXWIDTH; x++)
			{
				line(x * UNIT, y0 * UNIT, x * UNIT, MAXHIGH * UNIT);
			}
			setcolor(LINECOLOR);
			for (y = BASICHIGH; y <= MAXHIGH; y++)
			{
				line(x0 * UNIT, y * UNIT, MAXWIDTH * UNIT, y * UNIT);
			}
		}
		//外格线
		{
			setcolor(LINECOLOR);
			setlinestyle(PS_SOLID, 2);
			line(BASICWIDTH * UNIT - _wh, BASICHIGH * UNIT - _wh, MAXWIDTH * UNIT + _wh, BASICHIGH * UNIT - _wh);
			line(BASICWIDTH * UNIT - _wh, BASICHIGH * UNIT - _wh, BASICWIDTH * UNIT - _wh, MAXHIGH * UNIT + _wh);
			line(MAXWIDTH * UNIT + _wh, MAXHIGH * UNIT + _wh, BASICWIDTH * UNIT - _wh, MAXHIGH * UNIT + _wh);
			line(MAXWIDTH * UNIT + _wh, MAXHIGH * UNIT + _wh, MAXWIDTH * UNIT + _wh, BASICHIGH * UNIT - _wh);				
		}
	}
	//楚汉界
	{
		for (x = BASICWIDTH + 1, y0 = BASICHIGH + 4, y = BASICHIGH + 5; x < MAXWIDTH; x++)
		{
			setcolor(GRAPHCOLOR);
			line(x * UNIT, y0 * UNIT+1, x * UNIT, y * UNIT-1);
		}
		settextstyle(2*(WORDSIZE), 0, WORDSTYLE);
		settextcolor(WORDCOLOR);
		outtextxy(2.2 * UNIT, 5.2 * UNIT, "楚 河");
		outtextxy(6.2 * UNIT, 5.2 * UNIT, "汉 界");
	}
	//仕士线
	{
		setlinecolor(LINECOLOR);
		setlinestyle(PS_SOLID);
		x0 = BASICWIDTH + 3, x = BASICWIDTH + 5;

		y0 = BASICHIGH, y = BASICHIGH + 2;
		line(x0 * UNIT, y0 * UNIT, x * UNIT, y * UNIT);

		y0 = BASICHIGH + 2, y = BASICHIGH;
		line(x0 * UNIT, y0 * UNIT, x * UNIT, y * UNIT);

		y0 = MAXHIGH, y = MAXHIGH - 2;
		line(x0 * UNIT, y0 * UNIT, x * UNIT, y * UNIT);

		y0 = MAXHIGH - 2, y = MAXHIGH;
		line(x0 * UNIT, y0 * UNIT, x * UNIT, y * UNIT);
	}
	//炮线
	{
		setlinecolor(LINECOLOR);
		setlinestyle(PS_SOLID, 1);
		x0 = BASICWIDTH + 1, y0 = BASICHIGH + 2;
		Draw12L(x0, y0); Draw12R(x0, y0);
		x0 = MAXWIDTH - 1, y0 = BASICHIGH + 2;
		Draw12L(x0, y0); Draw12R(x0, y0);
		x0 = BASICWIDTH + 1, y0 = MAXHIGH - 2;
		Draw12L(x0, y0); Draw12R(x0, y0);
		x0 = MAXWIDTH - 1, y0 = MAXHIGH - 2;
		Draw12L(x0, y0); Draw12R(x0, y0);
	}
	//兵卒线
	{
		setlinecolor(LINECOLOR);
		setlinestyle(PS_SOLID, 1);
		x0 = BASICWIDTH + 2, y0 = BASICHIGH + 3;
		while (x0 < MAXWIDTH)
		{
			Draw12L(x0, y0); Draw12R(x0, y0);
			x0 += 2;
		}
		x0 = BASICWIDTH + 2, y0 = MAXHIGH - 3;
		while (x0 < MAXWIDTH)
		{
			Draw12L(x0, y0); Draw12R(x0, y0);
			x0 += 2;
		}
		x0 = BASICWIDTH, y0 = BASICHIGH + 3;
		Draw12R(x0, y0);
		x0 = BASICWIDTH, y0 = MAXHIGH - 3;
		Draw12R(x0, y0);
		x0 = MAXWIDTH, y0 = BASICHIGH + 3;
		Draw12L(x0, y0);
		x0 = MAXWIDTH, y0 = MAXHIGH - 3;
		Draw12L(x0, y0);
	}
	//展示布局
	{
		ShowLayout();
	}
}


//3.赢得棋局
void ShowWinChess(Survival* scores)
{
	Sleep(1000);//暂缓结束时间
	settextstyle(6.5 * WORDSIZE, 0, WORDSTYLE);
	clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
	if ((scores->r7 == 1&&scores->b7==0) ||(scores->flag == RMOVE&&scores->r7 == 1&&scores->b7 == 1))//对线,当下执棋者胜
	{
		setbkcolor(RCCOLOR);
		clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
		setcolor(WHITE);
		outtextxy(2.7 * UNIT, (MAXHIGH - 6) * UNIT / 2, "红棋获胜");
	}
	else if ((scores->r7 == 0 && scores->b7 == 1) || (scores->flag == BMOVE && scores->r7 == 1 && scores->b7 == 1))
	{
		setbkcolor(BCCOLOR);
		clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
		setcolor(WHITE);
		outtextxy(2.7 * UNIT, (MAXHIGH - 6) * UNIT / 2, "黑棋获胜");
	}
	outtextxy(2.7 * UNIT, (MAXHIGH - 5) * UNIT, "运筹帷幄");
	outtextxy(2.7 * UNIT, (MAXHIGH - 3) * UNIT, "决胜棋盘");
	Sleep(2000);
}


//****************************************************************************//
//***************				   变化因素 		    **********************//
//****************************************************************************//

//1.展示棋子
void ShowChess(Map map[MAXHIGH][MAXWIDTH], PImage im)
{
	IMAGE picture = NULL;
	Bool flag = FALSE;
	Map x = BASICWIDTH, y = BASICHIGH;

	int count = 0;  char s[5];

	for (y = BASICHIGH-1; y < MAXHIGH; y++)
	{
		for (x = BASICWIDTH-1; x < MAXWIDTH; x++)
		{
			flag = TRUE;
			switch (map[y][x])
			{
			case no:flag = FALSE;	   break;
			case r1:picture = im->r1; break;
			case b1:picture = im->b1; break;
			case r2:picture = im->r2; break;
			case b2:picture = im->b2; break;
			case r3:picture = im->r3; break;
			case b3:picture = im->b3; break;
			case r4:picture = im->r4; break;
			case b4:picture = im->b4; break;
			case r5:picture = im->r5; break;
			case b5:picture = im->b5; break;
			case r6:picture = im->r6; break;
			case b6:picture = im->b6; break;
			case r7:picture = im->r7; break;
			case b7:picture = im->b7; break;
			}
			if (flag)
			{
				putimage((x + 0.55) * UNIT, (y + 0.6) * UNIT, &im->mask,SRCAND);//SRCAND
				putimage((x + 0.55) * UNIT, (y + 0.6) * UNIT, &picture, SRCPAINT);// SRCPAINT
				count++;
			}
		}
	}
}


//2.展示棋况
void ShowScore(Survival *scores)
{
	//执棋
	{
		settextstyle(2 * (WORDSIZE), 0, WORDSTYLE);
		if (scores->flag == BMOVE)
		{
			settextcolor(BCCOLOR);
			clearrectangle((MAXWIDTH + 0.6) * UNIT, (BASICHIGH)*UNIT, GRAPHWIDTH * UNIT, (BASICHIGH + 1) * UNIT);
			outtextxy((MAXWIDTH + 0.6) * UNIT, (BASICHIGH)*UNIT, "黑方执棋");
		}
		else if (scores->flag == RMOVE)
		{
			settextcolor(RCCOLOR);
			clearrectangle((MAXWIDTH + 0.6) * UNIT, (BASICHIGH)*UNIT, GRAPHWIDTH * UNIT, (BASICHIGH + 1) * UNIT);
			outtextxy((MAXWIDTH + 0.6) * UNIT, (BASICHIGH)*UNIT, "红方执棋");
		}
	}
	//黑棋
	{
		char bval[5];
		settextcolor(BCCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		settextstyle(15, 0, WORDSTYLE);
		sprintf_s(bval, "%d", scores->b1);
		outtextxy((MAXWIDTH + 1.2) * UNIT, (BASICHIGH + 1.5) * UNIT, bval);
		sprintf_s(bval, "%d", scores->b2);
		outtextxy((MAXWIDTH + 2.2) * UNIT, (BASICHIGH + 1.5) * UNIT, bval);
		sprintf_s(bval, "%d", scores->b3);
		outtextxy((MAXWIDTH + 3.2) * UNIT, (BASICHIGH + 1.5) * UNIT, bval);
		sprintf_s(bval, "%d", scores->b4);
		outtextxy((MAXWIDTH + 1.2) * UNIT, (BASICHIGH + 2.0) * UNIT, bval);
		sprintf_s(bval, "%d", scores->b5);
		outtextxy((MAXWIDTH + 2.2) * UNIT, (BASICHIGH + 2.0) * UNIT, bval);
		sprintf_s(bval, "%d", scores->b6);
		outtextxy((MAXWIDTH + 3.2) * UNIT, (BASICHIGH + 2.0) * UNIT, bval);
	}
	//红棋
	{
		char rval[5];
		settextcolor(RCCOLOR);
		settextstyle(WORDSIZE, 0, WORDSTYLE);
		settextstyle(15, 0, WORDSTYLE);
		sprintf_s(rval, "%d", scores->r1);
		outtextxy((MAXWIDTH + 1.2) * UNIT, (BASICHIGH + 3.2) * UNIT, rval);
		sprintf_s(rval, "%d", scores->r2);
		outtextxy((MAXWIDTH + 2.2) * UNIT, (BASICHIGH + 3.2) * UNIT, rval);
		sprintf_s(rval, "%d", scores->r3);
		outtextxy((MAXWIDTH + 3.2) * UNIT, (BASICHIGH + 3.2) * UNIT, rval);
		sprintf_s(rval, "%d", scores->r4);
		outtextxy((MAXWIDTH + 1.2) * UNIT, (BASICHIGH + 3.7) * UNIT, rval);
		sprintf_s(rval, "%d", scores->r5);
		outtextxy((MAXWIDTH + 2.2) * UNIT, (BASICHIGH + 3.7) * UNIT, rval);
		sprintf_s(rval, "%d", scores->r6);
		outtextxy((MAXWIDTH + 3.2) * UNIT, (BASICHIGH + 3.7) * UNIT, rval);
	}

}


//3.展示选棋
void ShowChooseChess(Map map[MAXHIGH][MAXWIDTH], Map x, Map y,Chess *chess)
{
	//展示赠言
	{
		int mon = 0;
		const char motto[8][100] =
		{
			"棋者落落布子，声东击西",
			"以小卒之力, 渡老帅之命",
			"东风快递, 使命必达",
			"車贵神速, 抢先入局",
			"一马当先, 全军举绩",
			"借神农以日月星辰为象",
			"司九宫安全, 不离将帅",
			"问君能有几多愁, 恰似老将上三楼"
		};
		switch (map[y][x])
		{
		case no:mon = no; break;
		case b1:
		case r1:mon = r1; break;
		case b2:
		case r2:mon = r2; break;
		case b3:
		case r3:mon = r3; break;
		case b4:
		case r4:mon = r4; break;
		case b5:
		case r5:mon = r5; break;
		case b6:
		case r6:mon = r6; break;
		case b7:
		case r7:mon = r7; break;
		}
		{
			Pos x0 = BASICWIDTH, y0 = MAXHIGH + 0.75;
			clearrectangle(x0 * UNIT, y0 * UNIT, MAXWIDTH*UNIT, GRAPHHIGH*UNIT);
			settextcolor(WORDCOLOR);
			settextstyle(WORDSIZE, 0, WORDSTYLE);
			outtextxy(x0 * UNIT, y0 * UNIT, motto[mon]);
		}
	}
	//展示红框
	{
		if(chess->flag==RMOVE) setlinecolor(RCSECOLOR);
		else if(chess->flag == BMOVE) setlinecolor(BCSECOLOR);
		setlinestyle(PS_SOLID, 2);
		BeginBatchDraw();
		line((x + 0.55) * UNIT, (y + 0.6) * UNIT, (x + 0.55) * UNIT + CHESSSIZE, (y + 0.6) * UNIT);
		line((x + 0.55) * UNIT, (y + 0.6) * UNIT, (x + 0.55) * UNIT , (y + 0.6) * UNIT + CHESSSIZE);
		line((x + 0.55) * UNIT + CHESSSIZE, (y + 0.6) * UNIT + CHESSSIZE, (x + 0.55) * UNIT, (y + 0.6) * UNIT + CHESSSIZE);
		line((x + 0.55) * UNIT + CHESSSIZE, (y + 0.6) * UNIT + CHESSSIZE, (x + 0.55) * UNIT + CHESSSIZE, (y + 0.6) * UNIT);
		EndBatchDraw();
	}
	//测试用
	/*if(chess->flag==RMOVE) printf("红棋选中坐标( %d , %d )\n", x, y);
	else if(chess->flag==BMOVE) printf("黑棋选中坐标( %d , %d )\n", x, y);*/
}


//4.展示落棋
void ShowDropChess(Map x, Map y, Chess* chess)
{
	//控制台收集数据测试用(已不显示控制台)
	/*if(chess->flag==RMOVE) printf("黑棋落下坐标( %d , %d )\n", x, y);
	else if (chess->flag == BMOVE) printf("红棋落下坐标( %d , %d )\n", x, y);*/
	return;
}


//****************************************************************************//
//***************				   按键展示 		    **********************//
//****************************************************************************//

//5.退出程序
void ShowGoodbye()
{
	setbkcolor(GRAPHCOLOR);
	clearrectangle(0, 0, GRAPHWIDTH * UNIT, GRAPHHIGH * UNIT);
	settextcolor(WORDCOLOR);
	settextstyle(7 * WORDSIZE, 0, WORDSTYLE);
	outtextxy( 0.5*UNIT, (MAXHIGH - 7) * UNIT, "酒不以劝为饮");
	outtextxy(0.5 * UNIT, (MAXHIGH - 4) * UNIT, "棋不以争为胜");
	Sleep(3000);
	return;
}




























//按键
//展示悔棋
void ShowBackChess()
{

}
//展示棋局
void ShowReviewChess()
{

}
//展示排行
void ShowRank()
{

}