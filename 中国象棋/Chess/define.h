#ifndef DEFINE_H
#define DEFINE_H

#include<graphics.h>



//单位
#define UNIT        65				
//画布规格
#define GRAPHWIDTH  14		//画布宽
#define GRAPHHIGH   11.5	//画布高
//画布背景
#define GRAPHCOLOR  RGB(238,180,34)
//登录界面
#define WCCOLOR1    BLACK
#define WCCOLOR2	RED
//线条颜色
#define LINECOLOR   BLACK
//文字颜色
#define WORDCOLOR   BLACK
//文字大小
#define WORDSIZE    20
//字体
#define WORDSTYLE   "楷体"




//棋盘规格
#define BASICWIDTH  1	//棋盘初行
#define BASICHIGH   1	//棋盘初列
#define MAXWIDTH    9	//棋盘最大行
#define MAXHIGH     10	//棋盘最大列
//线条差量
#define _wh         6	//内外格线差
//黑棋颜色
#define BCCOLOR     BLACK 
//红棋颜色
#define RCCOLOR     RED
//棋子大小
#define CHESSSIZE   65
//选中颜色
#define RCSECOLOR   RED
//落子颜色
#define BCSECOLOR   BLUE
//按键颜色
#define KEYCOLOR    BLUE




//记录文件
#define PLAYER   ".\\FILE\\palyer.txt"		    //位置
//真假判定
#define TRUE    1	//真
#define FALSE   0	//假
#define OK      1 
#define NO      0
#define OT      2
#define RMOVE   1	//红棋移动
#define BMOVE   0	//黑棋移动
//记录表
enum CHESS_VAL		//r :红棋 b :黑棋
{
	no = 0,			//no:空格										//7: 帅将					
	r1 = 1, r2 = 2, r3 = 3, r4 = 4, r5 = 5, r6 = 6, r7 = 7,			//1: 兵卒	2: 炮		3: 車	 
	b1 = -1, b2 = -2, b3 = -3, b4 = -4, b5 = -5, b6 = -6, b7 = -7	//4: 馬	    5: 相象		6: 士仕
};




//布尔类型
typedef int Bool;
typedef int Move;
//返回状态
typedef int Status;
//坐标类型
typedef double Pos;
//记录类型
typedef int Map;




//棋子类型
typedef struct CHESS
{
	Move flag;               //当前移动
	Map  dead;	             //记录死棋
	Map x1, y1,x2,y2;        //棋
	struct CHESS* next;      //下一步棋
}Chess,*PChess;
//棋图类型
typedef struct PICTURE
{
	IMAGE mask;
	IMAGE r1, r2, r3, r4, r5, r6, r7;
	IMAGE b1, b2, b3, b4, b5, b6, b7;
}Image,*PImage;
//存活类型
typedef struct SURVIVAL		//棋子存活数,当前执棋方
{
	int flag;
	int r1, r2, r3, r4, r5, r6, r7;
	int b1, b2, b3, b4, b5, b6, b7;
}Survival,*PSurvival;


#endif // !DEFINE_H
