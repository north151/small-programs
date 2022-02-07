#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#define width 800  //地图大小
#define  high 650
#define  PI 3.1415927
#pragma comment(lib,"Winmm.lib")

// 玩家选择相关变量
char choose_map;  //选择地图
//全局变量  定义区域
struct bulletifm   //声明子弹的相关信息结构体变量
{
	int isused;  //是否使用过
	int x;  //坐标位置
	int y;
	int v_x;   //速度
	int v_y;
	int move;   //与墙体碰撞过的次数
};

int map[width][high]={0};  //定义二维数组储存地图元素
                       // 0为空白，1为墙体，
int map_show_x,map_show_y;  //显示地图的初始位置
int gameStatus=0; //代表游戏状态 0初始 1游戏进行 2游戏暂停 3游戏结束
int playerpichigh=40,playerpicwidth=30;//玩家图片高宽  显示时要用
int p1_high=35,p1_width=26;  //玩家1坦克实际大小 （略小于图片大小） 边界判定时要用
int p1_x,p1_y;    //玩家1坐标位置（与所选地图有关）
int p2_x,p2_y;    //玩家2坐标位置
int  p1_angle;  //玩家1 炮口的角度(8 个角度)
int  p2_angle; //玩家2 炮口的角度
int stopspan1=20,stopspan2=20;  //降低旋转灵敏度
int stopshoot1=15,stopshoot2=15;
int bleed1=3,bleed2=3;  //玩家血量
bulletifm bullet[2][30];  //子弹房间（每个玩家最多三十个）
int mouse_x,mouse_y; //鼠标当前位置
int live[2]={3,3};  //玩家血量
int time1_x, time1_y,time2_x,time2_y;//定义一个临时量储存坦克1,2初始位置
int is_died;


////函数声明区
void startmenu();
void pausemenu();
void ReadRecordFile();
void WriteRecordFile();
void startup_map1();
void startup_map2();
void startup_map3();
void startup_map4();
void startup();
void show_map();
void show_player();
void show_bullet();
void show_object();
void show();
void updatewithinput();
void updatewithoutinput();

//////////////////

void ReadRecordFile() //读取游戏数据文件
{
	FILE *fp;
	fp=fopen("gameRecord.dat","r");
	fscanf(fp,"%c %d %d %d %d %d %d %d %d",&choose_map,&p1_angle,&p1_x,&p1_y,&live[0],&p2_angle,&p2_x,&p2_y,&live[1]);
	fclose(fp);

	if(choose_map == '1')  //载入地图
		startup_map1();
	if(choose_map == '2')
		startup_map2();
	if(choose_map == '3')
		startup_map3();
	
	
}

void WriteRecordFile()  //写入游戏数据文件
{
	FILE *fp;
	fp=fopen("gameRecord.dat","w");
	fprintf(fp,"%c %d %d %d %d %d %d %d %d",choose_map,p1_angle,p1_x,p1_y,live[0],p2_angle,p2_x,p2_y,live[1]);
	fclose(fp);
}

void startmenu()   //游戏开始菜单界面
{
	cleardevice();
	IMAGE beijing1; //背景图片
	loadimage(&beijing1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background1.jpg",800,650);
	putimage(0,0,&beijing1);

	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(50,0, _T("楷体"));
	outtextxy(width*0.3, high*0.2, "新游戏");
	outtextxy(width*0.3, high*0.3, "读取游戏存档");
	outtextxy(width*0.3, high*0.4, "游戏帮助");
	outtextxy(width*0.3, high*0.5, "退出");
	
	FlushBatchDraw();
	
	//鼠标输入
	MOUSEMSG m;//定义鼠标信息
	if(MouseHit()){
		m = GetMouseMsg();  //获取一条鼠标消息
	if(m.uMsg==WM_LBUTTONDOWN){ //如果左键按下
		
		if (m.x>width*0.3 && m.x<width*0.3+50*3 && m.y>high*0.2 && m.y<high*0.2+50  ){   //新游戏
			cleardevice();
			//地图选择界面
			IMAGE beijing1; //背景图片
			loadimage(&beijing1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background1.jpg",800,650);
			putimage(0,0,&beijing1);

			setbkmode(TRANSPARENT);
			settextcolor(WHITE);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.2, "选择地图");
			outtextxy(width*0.6, high*0.7, "返回");

			setbkmode(TRANSPARENT);
			settextcolor(WHITE);
			settextstyle(50,0, _T("楷体"));
			outtextxy(width*0.2, high*0.5, "1");
			outtextxy(width*0.3, high*0.5, "2");
			outtextxy(width*0.4, high*0.5, "3");
			outtextxy(width*0.5, high*0.5, "4");
			
			FlushBatchDraw();

			//播放一次音效
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\经典街机投币音效_爱给网_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
							
			while(1){
			MOUSEMSG m;//定义鼠标信息
			if(MouseHit()){
				m = GetMouseMsg();  //获取一条鼠标消息	
			if(m.uMsg==WM_LBUTTONDOWN){ //如果左键按下
				//初始化地图
				int i,j;
				for(i=0;i<width;i++)
					for(j=0;j<high;j++)
						map[i][j] =0;
				if(m.x>width*0.2 && m.x<width*0.2+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map1();
					choose_map='1';
					//初始化玩家位置(相对于地图）
					p1_x=75;
					p1_y=50;
					p1_angle=rand()%8-4;
					p2_x=125;
					p2_y=175;
					p2_angle=rand()%8-4;

					time1_x = p1_x;
					time1_y = p1_y;
					time2_x = p2_x;
					time2_y = p2_y;
					live[0] = 3, live[1] = 3;//定义初始生命值
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.3 && m.x<width*0.3+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map2();
					choose_map='2';
					//初始化玩家位置(相对于地图）
					p1_x=175;
					p1_y=175;
					p1_angle=rand()%8-4;
					p2_x=425;
					p2_y=25;
					p2_angle=rand()%8-4;
					
					time1_x = p1_x;
					time1_y = p1_y;
					time2_x = p2_x;
					time2_y = p2_y;
					live[0] = 3, live[1] = 3;//定义初始生命值
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.4 && m.x<width*0.4+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map3();
					choose_map='3';
					//初始化玩家位置(相对于地图）
					p1_x=425;
					p1_y=325;
					p1_angle=rand()%8-4;
					p2_x=100;
					p2_y=525;
					p2_angle=rand()%8-4;
					
					time1_x = p1_x;
					time1_y = p1_y;
					time2_x = p2_x;
					time2_y = p2_y;
					live[0] = 3, live[1] = 3;//定义初始生命值
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.5 && m.x<width*0.5+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map4();
					choose_map='4';
					//初始化玩家位置(相对于地图）
					p1_x=50;
					p1_y=225;
					p1_angle=rand()%8-4;
					p2_x=75;
					p2_y=125;
					p2_angle=rand()%8-4;
					
					time1_x = p1_x;
					time1_y = p1_y;
					time2_x = p2_x;
					time2_y = p2_y;
					live[0] = 3, live[1] = 3;//定义初始生命值
					gameStatus = 1;
					break;
				} 
				else if(m.x>width*0.6 && m.x<width*0.6+30*2 && m.y>high*0.7 && m.y<high*0.7+30){
					startmenu();
					break;
				}

			}
			}
			}
		}
		else if (m.x>width*0.3 && m.x<width*0.3+50*6 && m.y>high*0.3 && m.y<high*0.3+50 ){  //继续游戏		
			ReadRecordFile();   //载入游戏进程
			gameStatus = 1;
		}
		else if( m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.4 && m.y<high*0.4+50 ){  //游戏帮助
			cleardevice();
			IMAGE beijing1; //背景图片
			loadimage(&beijing1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background1.jpg",800,650);
			putimage(0,0,&beijing1);
			
			setbkmode(TRANSPARENT);
			settextcolor(WHITE);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.3, "wasd 控制玩家1移动");
			outtextxy(width*0.35, high*0.38, "上下左右 控制玩家2移动");
			outtextxy(width*0.35, high*0.46, "空格 回车 发射子弹");
			outtextxy(width*0.35, high*0.54, "ESC键暂停游戏");
			outtextxy(width*0.5, high*0.7, "返回");

			FlushBatchDraw();
	
			while(1){
				MOUSEMSG m;//定义鼠标信息
				if(MouseHit()){
					m = GetMouseMsg();  //获取一条鼠标消息	
					if(m.uMsg==WM_LBUTTONDOWN){ //如果左键按下
						if(m.x>width*0.5 && m.x<width*0.5+30*2 && m.y>high*0.7 && m.y<high*0.7+30){
							startmenu();
							break;
						}
					}
				}
			}

		}
		else if (m.x>width*0.3 && m.x<width*0.3+50*2 && m.y>high*0.5 && m.y<high*0.5+50 )  //退出
		{
			gameStatus = 3;
			exit(0);
		}
	}

	
	
	//播放一次音效
	mciSendString("close jpmusic",NULL,0,NULL);
	mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\经典街机投币音效_爱给网_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
	mciSendString("play jpmusic",NULL,0,NULL);
	
	cleardevice();

	}
}

void pausemenu()   //游戏暂停菜单界面
{
	cleardevice();
	IMAGE beijing1; //背景图片
	loadimage(&beijing1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background1.jpg",800,650);
	putimage(0,0,&beijing1);

	setbkmode(TRANSPARENT);
	settextcolor(WHITE);
	settextstyle(50,0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, "继续游戏");
	outtextxy(width*0.3, high*0.3, "返回主菜单");
	outtextxy(width*0.3, high*0.4, "保存档案");
	outtextxy(width*0.3, high*0.5, "游戏帮助");
	outtextxy(width*0.3, high*0.6, "退出");

	FlushBatchDraw();
	

	//鼠标输入
	MOUSEMSG m;//定义鼠标信息
	if(MouseHit()){
		m = GetMouseMsg();  //获取一条鼠标消息
	if(m.uMsg==WM_LBUTTONDOWN){
	
		if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.2 && m.y<high*0.2+50) 
			gameStatus = 1;
		else if(m.x>width*0.3 && m.x<width*0.3+50*5 && m.y>high*0.3 && m.y<high*0.3+50){
			gameStatus = 0;
		}
		else if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.4 && m.y<high*0.4+50)
		{
			WriteRecordFile();  //保存游戏进度
			gameStatus = 1;
		}
		else if(m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.5 && m.y<high*0.5+50){
			cleardevice();
			IMAGE beijing1; //背景图片
			loadimage(&beijing1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background1.jpg",800,650);
			putimage(0,0,&beijing1);

			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.3, "wasd 控制玩家1移动");
			outtextxy(width*0.35, high*0.38, "上下左右 控制玩家2移动");
			outtextxy(width*0.35, high*0.46, "空格 回车 发射子弹");
			outtextxy(width*0.35, high*0.54, "ESC键暂停游戏");
			outtextxy(width*0.5, high*0.7, "返回");
			
			FlushBatchDraw();
			
			while(1){
				MOUSEMSG m;//定义鼠标信息
				if(MouseHit()){
					m = GetMouseMsg();  //获取一条鼠标消息	
					if(m.uMsg==WM_LBUTTONDOWN){ //如果左键按下
						if(m.x>width*0.5 && m.x<width*0.5+30*2 && m.y>high*0.7 && m.y<high*0.7+30){
							startmenu();
							break;
						}
					}
				}
			}
		}
		else if (m.x>width*0.3 && m.x<width*0.3+50*2 && m.y>high*0.6 && m.y<high*0.6+50){
			gameStatus = 3;
			exit(0);
		}
	}
	}
	cleardevice();
	
}




void startup_map1() //加载地图1
{
	//此地图大小 200*400
	int i,j;
	for(i=0,j=0;i<200;i++)     map[i][j] = 1;
	for(i=199,j=0;j<400;j++)   map[i][j] = 1;
	for(i=0,j=0;j<400;j++)     map[i][j] = 1;
	for(i=0,j=399;i<200;i++)   map[i][j] = 1;
	for(i=50,j=0;j<50;j++)     map[i][j] = 1;
	for(i=0,j=50;i<50;i++)     map[i][j] = 1;
	for(i=0,j=100;i<50;i++)    map[i][j] = 1;
	for(i=100,j=0;j<100;j++)   map[i][j] = 1;
	for(i=100,j=100;i<150;i++) map[i][j] = 1;
	for(i=150,j=50;j<200;j++)  map[i][j] = 1;
	for(i=0,j=150;i<100;i++)   map[i][j] = 1;
	for(i=50,j=150;j<200;j++)  map[i][j] = 1;
	for(i=100,j=150;j<250;j++) map[i][j] = 1;
	for(i=0,j=300;i<50;i++)    map[i][j] = 1;
	for(i=50,j=250;j<350;j++)  map[i][j] = 1;
	for(i=100,j=300;j<400;j++) map[i][j] = 1;
	for(i=150,j=250;j<300;j++) map[i][j] = 1;
	for(i=150,j=250;i<200;i++) map[i][j] = 1;
	for(i=150,j=350;i<200;i++) map[i][j] = 1;
	
	
}

void startup_map2() //加载地图2
{

	//此地图大小 450*450
	int i,j;
	for(i=0,j=0;i<450;i++)    map[i][j] = 1 ;
	for(i=449,j=0;j<450;j++)  map[i][j] = 1 ;
	for(i=0,j=0;j<450;j++)    map[i][j] = 1 ;
	for(i=0,j=449;i<450;i++)  map[i][j] = 1 ;
	for(i=0,j=50;i<50;i++)    map[i][j] = 1 ;
	for(i=50,j=50;j<100;j++)  map[i][j] = 1 ;
	for(i=50,j=100;i<100;i++) map[i][j] = 1 ;
	for(i=100,j=0;j<50;j++)   map[i][j] = 1 ;
	for(i=100,j=50;i<200;i++) map[i][j] = 1 ;
	for(i=250,j=0;j<100;j++)  map[i][j] = 1 ;
	for(i=300,j=50;i<400;i++) map[i][j] = 1 ;
	for(i=350,j=50;j<150;j++) map[i][j] = 1 ;
	for(i=400,j=50;j<100;j++) map[i][j] = 1 ;
	for(i=350,j=150;i<450;i++)map[i][j] = 1 ;
	for(i=0,j=150;i<50;i++)   map[i][j] = 1 ;
	for(i=50,j=150;j<250;j++) map[i][j] = 1 ;
	for(i=100,j=150;i<150;i++)map[i][j] = 1 ;
	for(i=150,j=150;j<250;j++)map[i][j] = 1 ;
	for(i=150,j=100;i<200;i++)map[i][j] = 1 ;
	for(i=200,j=100;j<200;j++)map[i][j] = 1 ;
	for(i=250,j=150;j<250;j++)map[i][j] = 1 ;
	for(i=250,j=150;i<300;i++)map[i][j] = 1 ;
	for(i=300,j=100;j<300;j++)map[i][j] = 1 ;
	for(i=100,j=200;j<300;j++)map[i][j] = 1 ;
	for(i=100,j=300;i<200;i++)map[i][j] = 1 ;
	for(i=50,j=300;j<350;j++) map[i][j] = 1 ;
	for(i=0,j=350;i<100;i++)  map[i][j] = 1 ;
	for(i=0,j=400;i<200;i++)  map[i][j] = 1 ;
	for(i=200,j=350;j<400;j++)map[i][j] = 1 ;
	for(i=350,j=200;j<350;j++)map[i][j] = 1 ;
	for(i=400,j=200;j<300;j++)map[i][j] = 1 ;
	for(i=300,j=350;i<400;i++)map[i][j] = 1 ;
	for(i=300,j=350;j<400;j++)map[i][j] = 1 ;
	for(i=250,j=400;i<350;i++)map[i][j] = 1 ;
	for(i=400,j=400;i<450;i++)map[i][j] = 1 ;
	for(i=400,j=400;j<450;j++)map[i][j] = 1 ;

}

void startup_map3()  //加载地图3
{
	//此地图大小 600*550
	int i, j;
	for (i = 0; i < 550; i++)
	{
		map[0][i] = 1;
		map[600 - 1][i] = 1;//对边框赋值
	}
	for (j = 0; j < 600; j++)
	{
		map[j][0] = 1;
		map[j][550 - 1] = 1;
	}
	for (i = 0; i < 100; i++)//对障碍物赋值
		map[i][50] = 1;
	for (i = 500; i < 600; i++)
		map[i][50] = 1;
	for (i = 350; i < 400; i++)
		map[i][50] = 1;
	for (i = 500; i < 600; i++)
		map[i][100] = 1;
	for (i = 350; i < 400; i++)
		map[i][100] = 1;
	for (i = 0; i < 50; i++)
		map[i][150] = 1;
	for (i = 200; i < 350; i++)
		map[i][150] = 1;
	for (i = 400; i < 600; i++)
		map[i][150] = 1;
	for (i = 0; i < 50; i++)
		map[i][200]= 1;
	for (i = 100; i < 150; i++)
		map[i][200]= 1;
	for (i = 200; i < 300; i++)
		map[i][200] = 1;
	for (i = 350; i < 500; i++)
		map[i][200] = 1;
	for (i = 50; i < 100; i++)
		map[i][250] = 1;
	for (i = 50; i < 100; i++)
		map[i][250] = 1;
	for (i = 100; i < 300; i++)
		map[i][250] = 1;
	for (i = 350; i < 550; i++)
		map[i][250] = 1;
	for (i = 50; i < 100; i++)
		map[i][300] = 1;
	for (i = 150; i < 250; i++)
		map[i][300] = 1;
	for (i = 300; i < 350; i++)
		map[i][300] = 1;
	for (i = 400; i < 450; i++)
		map[i][300] = 1;
	for (i = 500; i < 550; i++)
		map[i][300] = 1;
	for (i = 50; i < 150; i++)
		map[i][350] = 1;
	for (i = 300; i < 450; i++)
		map[i][350] = 1;
	for (i = 500; i < 600; i++)
		map[i][350] = 1;
	for (i = 100; i < 150; i++)
		map[i][400] = 1;
	for (i = 300; i < 350; i++)
		map[i][400] = 1;
	for (i = 450; i < 550; i++)
		map[i][400] = 1;
	for (i = 0; i < 50; i++)
		map[i][450] = 1;
	for (i = 250; i < 300; i++)
		map[i][450] = 1;
	for (i = 350; i < 400; i++)
		map[i][450] = 1;
	for (i = 50; i < 100; i++)
		map[i][500] = 1;
	for (i = 150; i < 200; i++)
		map[i][500] = 1;
	for (i = 250; i < 400; i++)
		map[i][500] = 1;
	for (i = 450; i < 500; i++)
		map[i][500] = 1;
	for (i = 550; i < 600; i++)
		map[i][500] = 1;
	for (j = 400; j < 500; j++)
		map[50][j] = 1;
	for (j = 250; j < 300; j++)
		map[50][j] = 1;
	for (j = 100; j < 200; j++)
		map[100][j] = 1;
	for (j = 300; j < 350; j++)
		map[100][j] = 1;
	for (j = 400; j < 450; j++)
		map[100][j] = 1;
	for (j = 0; j < 50; j++)
		map[150][j] = 1;
	for (j = 100; j < 150; j++)
		map[150][j] = 1;
	for (j = 200; j < 250; j++)
		map[150][j] = 1;
	for (j = 350; j < 450; j++)
		map[150][j] = 1;
	for (j = 50; j < 100; j++)
		map[200][j] = 1;
	for (j = 150; j < 200; j++)
		map[200][j] = 1;
	for (j = 300; j < 400; j++)
		map[200][j] = 1;
	for (j = 500; j < 550; j++)
		map[200][j] = 1;
	for (j = 0; j < 50; j++)
		map[250][j] = 1;
	for (j = 100; j < 150; j++)
		map[250][j] = 1;
	for (j = 200; j < 300; j++)
		map[250][j] = 1;
	for (j = 400; j < 450; j++)
		map[250][j] = 1;
	for (j = 50; j < 100; j++)
		map[300][j] = 1;
	for (j = 50; j < 100; j++)
		map[350][j] = 1;
	for (j = 150; j < 250; j++)
		map[350][j] = 1;
	for (j = 300; j < 400; j++)
		map[350][j] = 1;
	for (j = 500; j < 550; j++)
		map[350][j] = 1;
	for (j = 250; j < 300; j++)
		map[400][j] = 1;
	for (j = 350; j < 400; j++)
		map[400][j] = 1;
	for (j = 450; j < 500; j++)
		map[400][j] = 1;
	for (j = 50; j < 100; j++)
		map[450][j] = 1;
	for (j = 400; j < 500; j++)
		map[500][j] = 1;
	for (j = 200; j < 300; j++)
		map[550][j] = 1;
	for (j = 450; j < 500; j++)
		map[550][j] = 1;
}

void startup_map4()
{
	//该地图为250*250
	int i, j;
	for (i = 0; i < 250; i++)
	{
		map[i][249] = 1;
		map[i][0] = 1;
	}
	for (j = 0; j < 250; j++)
	{
		map[0][j] = 1;
		map[249][j] = 1;
	}
	for (i = 0; i < 50; i++)
		map[i][50] = 1;
	for (i = 150; i < 250; i++)
		map[i][50] = 1;
	for (i = 0; i < 100; i++)
		map[i][150] = 1;
	for (i = 150; i < 250; i++)
		map[i][150] = 1;
	for (i = 0; i < 50; i++)
		map[i][200] = 1;
	for (i = 150; i < 200; i++)
		map[i][200] = 1;
	for (j = 100; j < 150; j++)
		map[50][j] = 1;
	for (j = 0; j < 50; j++)
		map[100][j] = 1;
	for (j = 200; j < 250; j++)
		map[100][j] = 1;
	for (j = 150; j < 200; j++)
		map[150][j] = 1;
	for (j = 0; j < 100; j++)
		map[200][j] = 1;
}

void startup()//初始化数据
{
	initgraph(800,650);//画布的大小（比地图大一点）
	setbkcolor(WHITE);//画布背景颜色
	cleardevice();
	
	BeginBatchDraw();  //开始绘图

	//开始播放背景音乐
	mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\街头音乐下载_爱给网_aigei_com.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);

	
	//初始菜单
	while (gameStatus == 0){  
		startmenu();
	}
		

	//初始 地图在整个画布中的显示位置
	map_show_x=200;
	map_show_y=50;
	if(choose_map == '3')  {
		map_show_x=100;
	}
	
	//初始 子弹位置 及 子弹速度
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<30;j++){
			bullet[i][j].isused=0;  //表示这个子弹房间未使用
			bullet[i][j].x=0;
			bullet[i][j].y=0;
			bullet[i][j].v_x=0;
			bullet[i][j].v_y=0;
			bullet[i][j].move=0;
		}

}



void show_map() //显示地图
{

/*	//用数组打印地图  （打印速度很慢）
	int i,j;
	//检索每个数组元素
	for(i=0;i<width;i++){
		for(j=0;j<high;j++){
		
			if(map[i][j] == 1){
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillrectangle(i+map_show_x,j+map_show_y,i+map_show_x+4,j+map_show_y+4);
			}
		    
		}
	}
*/
	//用图片显示地图
	if(choose_map == '2'){
		map_show_x = 175;//定义初始位置试地图位于中心
		map_show_y = 75;
		IMAGE ditu2;
		loadimage(&ditu2,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图2.JPG");
		putimage(map_show_x,map_show_y,&ditu2);
	}
	if(choose_map == '1'){
		map_show_x = 300;//定义初始位置试地图位于中心
		map_show_y = 100;
		IMAGE ditu1;
		loadimage(&ditu1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图1.JPG");
		putimage(map_show_x,map_show_y,&ditu1);
	}
	if(choose_map == '3'){
		map_show_x = 100;//定义初始位置试地图位于中心
		map_show_y = 50;
		IMAGE ditu3;
		loadimage(&ditu3,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图3.JPG");
		putimage(map_show_x,map_show_y,&ditu3);
	}
	if(choose_map == '4'){
		map_show_x = 225;//定义初始位置试地图位于中心
		map_show_y = 175;
		IMAGE ditu4;
		loadimage(&ditu4,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图4.JPG");
		putimage(map_show_x,map_show_y,&ditu4);
	}

		
}

void show_player()  //显示玩家
{
	//显示玩家1
	IMAGE p1_1,p1_2,p1_1_0,p1_2_0;
	loadimage(&p1_1_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\2.jpg",playerpicwidth,playerpichigh);//遮罩图
	loadimage(&p1_2_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\1.jpg",playerpicwidth,playerpichigh);//原图
	rotateimage(&p1_1,&p1_1_0,PI*p1_angle*1.0/4,SRCINVERT);   //按照角度旋转图片
	rotateimage(&p1_2,&p1_2_0,PI*p1_angle*1.0/4,WHITE);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_1,NOTSRCERASE);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_2,SRCINVERT);
	//显示玩家2
	IMAGE p2_1,p2_2,p2_1_0,p2_2_0;
	loadimage(&p2_1_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\4.jpg",playerpicwidth,playerpichigh);//遮罩图
	loadimage(&p2_2_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\3.jpg",playerpicwidth,playerpichigh);//原图
	rotateimage(&p2_1,&p2_1_0,PI*p2_angle*1.0/4,SRCINVERT);   //按照角度旋转图片
	rotateimage(&p2_2,&p2_2_0,PI*p2_angle*1.0/4,WHITE);
	putimage(p2_x+map_show_x-playerpicwidth/2,p2_y+map_show_y-playerpichigh/2,&p2_1,NOTSRCERASE);
	putimage(p2_x+map_show_x-playerpicwidth/2,p2_y+map_show_y-playerpichigh/2,&p2_2,SRCINVERT);

}

void show_bullet()  //显示子弹
{
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<30;j++){
			if(bullet[i][j].isused == 1){
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(bullet[i][j].x+map_show_x,bullet[i][j].y+map_show_y,2);
			}
		}

}

void show_object() //显示道具
{

}

void show()  //显示
{

	IMAGE beijing2; //背景图片
	loadimage(&beijing2,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\background2.jpg",800,650);
	putimage(0,0,&beijing2);


	//显示地图
	show_map();
	//显示人物
	show_player();
	//显示子弹
	show_bullet();
	//显示道具
	show_object();

	if (live[1] == 3) {//解决生命值显示的频闪问题
		outtextxy(720, 350, _T("生命：3"));
	}
	else if (live[1] == 2) {
		outtextxy(720, 350, _T("生命：2"));
	}
	else if (live[1] == 1) {
		outtextxy(720, 350, _T("生命：1"));
	}
	if (live[0] == 3) {
		outtextxy(20, 350, _T("生命：3"));
	}
	else if (live[0] == 2) {
		outtextxy(20, 350, _T("生命：2"));
	}
	else if (live[0] == 1) {
		outtextxy(20, 350, _T("生命：1"));
	}
	FlushBatchDraw();  //批量绘图
}

int can_move1(int x,int y,int a,int tankv_x,int tankv_y)  //判断坦克能否前进
{
	
	int i,j;
	for(i=x-p1_width/2,j=y-p1_high/2;i<x+p1_width/2;i++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}
	for(i=x-p1_width/2,j=y+p1_high/2;i<x+p1_width/2;i++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}
	for(i=x-p1_width/2,j=y-p1_high/2;j<y+p1_high/2;j++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;	
	}
	for(i=x+p1_width/2,j=y-p1_high/2;j<y+p1_high/2;j++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}
//	if(sqrt(pow(p1_x-p2_x,2)+pow(p1_y-p2_y,2))<=20)
//		return 0;

	return 1;
}

int can_move2(int x,int y,int a,int tankv_x,int tankv_y)  //判断坦克能否后退
{
	
	int i,j;
	for(i=x-p1_width/2,j=y-p1_high/2;i<x+p1_width/2;i++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
	for(i=x-p1_width/2,j=y+p1_high/2;i<x+p1_width/2;i++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
	for(i=x-p1_width/2,j=y-p1_high/2;j<y+p1_high/2;j++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;	
	}
	for(i=x+p1_width/2,j=y-p1_high/2;j<y+p1_high/2;j++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
//	if(sqrt(pow(p1_x-p2_x,2)+pow(p1_y-p2_y,2))<=35)
//		return 0;
	
	return 1;
}

void updatewithinput()  //与(游戏中)输入有关的更新
{
  //玩家1
		int tankv_x = 2*sin(PI*p1_angle/4);  //两方向水平平移量(1 或 2）
		int tankv_y = 2*cos(PI*p1_angle/4);
		int temp_direction1=0;  //暂时记录静止，前进或后退 （旋转方向与之有关）
	
		if(GetAsyncKeyState(0x57) & 0x8000){  //w
			temp_direction1 = 1;
			if( can_move1(p1_x,p1_y,p1_angle,tankv_x,tankv_y)){
				p1_x -=  tankv_x;
				p1_y -=	 tankv_y;
			}
		}
		if(GetAsyncKeyState(0x53) & 0x8000){  //s
			temp_direction1 = 2;
			if( can_move2(p1_x,p1_y,p1_angle,tankv_x,tankv_y)){
				p1_x +=  tankv_x;
				p1_y +=  tankv_y;			
			}
		}

		//玩家1 左右旋转(与坦克移动方向有关)
		if(stopspan1 > 0) stopspan1--;
		if( GetAsyncKeyState(0x44) & 0x8000 && stopspan1 ==0  ){  //d
			if( temp_direction1 == 0 || temp_direction1 == 1)
				p1_angle --;
			if( temp_direction1 == 2)
				p1_angle ++;
			stopspan1=10;
		}
		if( GetAsyncKeyState(0x41) & 0x8000 && stopspan1 ==0  ){  //a
			if( temp_direction1 == 0 || temp_direction1 == 1)	
				p1_angle ++;
			if( temp_direction1 == 2)
				p1_angle --;	
			stopspan1=10;
		}

		if (stopshoot1 > 0) stopshoot1--;
		if (GetAsyncKeyState(0x20) & 0x8000 && stopshoot1==0) {  //按下空格 玩家1发射子弹	
			int j;
			//检索每个子弹
			for (j = 0; j < 30; j++) {
				if (bullet[0][j].isused == 0) {  //找到一个空的子弹房间
					//播放一次音效
					mciSendString("close jpmusic", NULL, 0, NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\撞击－击中1_爱给网_aigei_com.mp3 alias jpmusic", NULL, 0, NULL);
					mciSendString("play jpmusic", NULL, 0, NULL);
					bullet[0][j].isused = 1;
					//位置
					//注意在炮口位置发出
					bullet[0][j].x = p1_x - 10 * tankv_x;
					bullet[0][j].y = p1_y - 10 * tankv_y;
					//速度（取决于炮口方向）
					bullet[0][j].v_x = -2 * sin(PI*p1_angle / 4);
					bullet[0][j].v_y = -2 * cos(PI*p1_angle / 4);
					//限定子弹速度大小小于2（便于边界判定）
					if (bullet[0][j].v_x == 2) bullet[0][j].v_x = 1;
					if (bullet[0][j].v_x == -2) bullet[0][j].v_x = -1;
					if (bullet[0][j].v_y == 2) bullet[0][j].v_y = 1;
					if (bullet[0][j].v_y == -2) bullet[0][j].v_y = -1;
					//击墙次数
					bullet[0][j].move = 0;
					break;
			}
		}
		stopshoot1 = 15;
	}

   /////玩家2
		tankv_x = 2*sin(PI*p2_angle/4);  //两方向水平平移量(1 或 2）
		tankv_y = 2*cos(PI*p2_angle/4);
		int temp_direction2=0;  //暂时记录静止，前进或后退 （旋转方向与之有关）
		
		if(GetAsyncKeyState(0x26) & 0x8000){
			temp_direction2 = 1;
			if( can_move1(p2_x,p2_y,p2_angle,tankv_x,tankv_y)){
				p2_x -=  tankv_x;
				p2_y -=	 tankv_y;
			}
		}
		if(GetAsyncKeyState(0x28) & 0x8000){
			temp_direction2 = 2;
			if( can_move2(p2_x,p2_y,p2_angle,tankv_x,tankv_y)){
				p2_x +=  tankv_x;
				p2_y +=  tankv_y;			
			}
		}

		//玩家2 左右旋转(与坦克移动方向有关)
		if(stopspan2 > 0)  stopspan2--;
		if( GetAsyncKeyState(VK_RIGHT) & 0x8000 && stopspan2 == 0 ){
			if( temp_direction2 == 0 || temp_direction2 == 1)
				p2_angle --;
			if( temp_direction2 == 2)
				p2_angle ++;
			stopspan2=10;
		}
		if( GetAsyncKeyState(VK_LEFT) & 0x8000 && stopspan2 == 0 ){
			if( temp_direction2 == 0 || temp_direction2 == 1)	
				p2_angle ++;
			if( temp_direction2 == 2)
				p2_angle --;
			stopspan2=10;
		}


		if (stopshoot2 > 0) stopshoot2--;
		if (GetAsyncKeyState(0x0d) & 0x8000 && stopshoot2==0) {  //按下回车 玩家2发射子弹		
			int j;
			//检索每个子弹
			for (j = 0; j < 30; j++) {
				if (bullet[1][j].isused == 0) {  //找到一个空的子弹房间
					//播放一次音效
					mciSendString("close jpmusic", NULL, 0, NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\撞击－击中1_爱给网_aigei_com.mp3 alias jpmusic", NULL, 0, NULL);
					mciSendString("play jpmusic", NULL, 0, NULL);
					bullet[1][j].isused = 1;
					//位置
					//注意在炮口位置发出
					bullet[1][j].x = p2_x - 10 * tankv_x;
					bullet[1][j].y = p2_y - 10 * tankv_y;
					//速度（取决于炮口方向）
					bullet[1][j].v_x = -2 * sin(PI*p2_angle / 4);
					bullet[1][j].v_y = -2 * cos(PI*p2_angle / 4);
					//限定子弹速度大小小于2（便于边界判定）
					if (bullet[1][j].v_x == 2) bullet[1][j].v_x = 1;
					if (bullet[1][j].v_x == -2) bullet[1][j].v_x = -1;
					if (bullet[1][j].v_y == 2) bullet[1][j].v_y = 1;
					if (bullet[1][j].v_y == -2) bullet[1][j].v_y = -1;
					//击墙次数
					bullet[1][j].move = 0;
					break;
				}
			}
			stopshoot2 = 15;
	}

		if(kbhit()){
			char input ;
			input = getch();
			if( input == 27 ){  //按下EXC键
				gameStatus=2;  //暂停状态
			}
		}
		
}


void died_1()
{
	int i,j;
	if (is_died == 1)//若坦克死亡则暂停一段时间
	{
		//Sleep(1000);
		is_died = 0;
	}
	for (i = 0; i < 30; i++)
	{
		if(bullet[0][i].isused==1)
			if (((p1_x - bullet[0][i].x)*(p1_x - bullet[0][i].x) + (p1_y - bullet[0][i].y)*(p1_y - bullet[0][i].y) <= 100))//计算子弹与坦克1的距离，小于某个距离坦克1爆炸
			{
				mciSendString("close jpmusic", NULL, 0, NULL);
				mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\爆炸.mp3 alias jpmusic", NULL, 0, NULL);
				mciSendString("play jpmusic", NULL, 0, NULL);
				IMAGE bank1;
				loadimage(&bank1, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\爆炸.png"), playerpicwidth, playerpichigh);
				putimage(p1_x + map_show_x - playerpicwidth / 2, p1_y + map_show_y - playerpichigh / 2, &bank1);
				FlushBatchDraw();
				p1_x = time1_x;
				p1_y = time1_y;
				live[0]--;
				for (j = 0; j < 30; j++)//子弹命中后使所有子弹消失
				{
					bullet[0][j].isused = 0;
					bullet[1][j].isused = 0;
				}
				is_died = 1;//坦克死亡
				Sleep(1000);
			}
			if(bullet[1][i].isused==1)
				if (((p1_x - bullet[1][i].x)*(p1_x - bullet[1][i].x) + (p1_y - bullet[1][i].y)*(p1_y - bullet[1][i].y) <= 100))
				{
					mciSendString("close jpmusic", NULL, 0, NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\爆炸.mp3 alias jpmusic", NULL, 0, NULL);
					mciSendString("play jpmusic", NULL, 0, NULL);
					IMAGE bank1;
					loadimage(&bank1, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\爆炸.png"), playerpicwidth, playerpichigh);
					putimage(p1_x + map_show_x - playerpicwidth / 2, p1_y + map_show_y - playerpichigh / 2, &bank1);
					FlushBatchDraw();
					p1_x = time1_x;
					p1_y = time1_y;
					live[0]--;
					for (j = 0; j < 30; j++)//子弹命中后使所有子弹消失
					{
						bullet[0][j].isused = 0;
						bullet[1][j].isused = 0;
					}
					is_died = 1;//坦克死亡
					Sleep(1000);
				}
	}
	
}

void died_2()
{
	int i,j;
	for (i = 0; i < 30; i++)
	{
		if(bullet[0][i].isused==1)
			if (((p2_x - bullet[0][i].x)*(p2_x - bullet[0][i].x) + (p2_y - bullet[0][i].y)*(p2_y - bullet[0][i].y) <= 100))//计算子弹与坦克2的距离，小于某个距离坦克1爆炸
			{	
				mciSendString("close jpmusic", NULL, 0, NULL);
				mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\爆炸.mp3 alias jpmusic", NULL, 0, NULL);
				mciSendString("play jpmusic", NULL, 0, NULL);
				IMAGE bank1;
				loadimage(&bank1, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\爆炸.png"), playerpicwidth, playerpichigh);
				putimage(p2_x + map_show_x - playerpicwidth / 2, p2_y + map_show_y - playerpichigh / 2, &bank1);
				FlushBatchDraw();
				p2_x = time2_x;
				p2_y = time2_y;
				live[1]--;
				for (j = 0; j < 30; j++)//子弹命中后使所有子弹消失
				{
					bullet[0][j].isused = 0;
					bullet[1][j].isused = 0;
				}
				is_died = 1;//坦克死亡
				Sleep(1000);
			}		
			if (bullet[1][i].isused==1)
				if (((p2_x - bullet[1][i].x)*(p2_x - bullet[1][i].x) + (p2_y - bullet[1][i].y)*(p2_y - bullet[1][i].y) <= 100))
				{
					mciSendString("close jpmusic", NULL, 0, NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\爆炸.mp3 alias jpmusic", NULL, 0, NULL);
					mciSendString("play jpmusic", NULL, 0, NULL);
					IMAGE bank1;
					loadimage(&bank1, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\爆炸.png"), playerpicwidth, playerpichigh);
					putimage(p2_x + map_show_x - playerpicwidth / 2, p2_y + map_show_y - playerpichigh / 2, &bank1);
					FlushBatchDraw();
					p2_x = time2_x;
					p2_y = time2_y;
					live[1]--;
					for (j = 0; j < 30; j++)//子弹命中后使所有子弹消失
					{
						bullet[0][j].isused = 0;
						bullet[1][j].isused = 0;
					}
					is_died = 1;//坦克死亡
					Sleep(1000);
				}
				
	}
	
}


void updatewithoutinput()  //与输入无关的更新
{
	while (gameStatus == 0){  
		startmenu();  //主菜单
	} 
	while(gameStatus == 2){
		pausemenu();  //暂停菜单
	}
	

	//实现子弹的移动，反弹，击中坦克，自动消失
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<30;j++){
			if(bullet[i][j].isused == 1){  //当子弹存在
				//子弹移动
				bullet[i][j].x+=bullet[i][j].v_x;
				bullet[i][j].y+=bullet[i][j].v_y;
				//子弹反弹
				if(bullet[i][j].v_x>0){
					if( map[ bullet[i][j].x+1][ bullet[i][j].y] == 1 ){  
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //击墙次数加一
					}  
				}
				else if(bullet[i][j].v_x<0){
					if( map[ bullet[i][j].x-1][ bullet[i][j].y] == 1 ){
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //击墙次数加一
					}
				}
				else if(bullet[i][j].v_x==0){
					if( map[ bullet[i][j].x][ bullet[i][j].y] == 1 ){
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //击墙次数加一
					}
				}
				if(bullet[i][j].v_y>0){
					if( map[ bullet[i][j].x][ bullet[i][j].y+1] == 1 ){  
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //击墙次数加一
					} 
				}
				else if(bullet[i][j].v_y<0){
					if( map[ bullet[i][j].x ][ bullet[i][j].y-1] == 1 ){  
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //击墙次数加一
					} 
				}
				else if(bullet[i][j].v_y==0){
					if( map[ bullet[i][j].x ][ bullet[i][j].y ] == 1 ){
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //击墙次数加一
					}
				}
				//子弹自动消失
				if(bullet[i][j].move == 10){
					bullet[i][j].isused=0;
				}

			}
		}

	//实现坦克中弹掉血
	died_1();
	died_2();


	//判断游戏进程
	IMAGE tank1_win;
	IMAGE tank2_win;
	settextcolor(BLACK);
	settextstyle(20, 0, _T("楷体"));
	if (live[0] == 3) { 
		outtextxy(20, 350, _T("生命：3"));
		FlushBatchDraw();
	}
	else if (live[0] == 2) { 
		outtextxy(20, 350, _T("生命：2")); 
		FlushBatchDraw();
	}
	else if (live[0] == 1) {
		outtextxy(20, 350, _T("生命：1")); 
		FlushBatchDraw();
	}
	else if (live[0] == 0)
	{
		mciSendString("close jpmusic", NULL, 0, NULL);
		mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\游戏胜利音效.mp3 alias jpmusic", NULL, 0, NULL);
		mciSendString("play jpmusic", NULL, 0, NULL);
		IMAGE tank1_win;
		loadimage(&tank1_win, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\坦克2win.jpg"),800,650);
		putimage(0,0, &tank1_win);
		FlushBatchDraw();
		Sleep(5000);
		gameStatus = 0;
	}
	if (live[1] == 3) {
		outtextxy(720, 350, _T("生命：3"));
		FlushBatchDraw();
	}
	else if (live[1] == 2) {
		outtextxy(720, 350, _T("生命：2"));
		FlushBatchDraw();
	}
	else if (live[1] == 1) {
		outtextxy(720, 350, _T("生命：1"));
		FlushBatchDraw();
	}
	else if (live[1] == 0)
	{
		mciSendString("close jpmusic", NULL, 0, NULL);
		mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\游戏胜利音效.mp3 alias jpmusic", NULL, 0, NULL);
		mciSendString("play jpmusic", NULL, 0, NULL);
		IMAGE tank2_win;
		loadimage(&tank2_win, _T("C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\坦克1win.jpg"),800,650);
		putimage(0, 0, &tank2_win);
		FlushBatchDraw();
		Sleep(5000);
		gameStatus = 0;
	}

}

void gameover() //游戏结束 后续处理
{
	EndBatchDraw();
	getch();
	closegraph();
}


int main()  //主函数
{
	startup();
	while(1)
	{
		show();
		updatewithinput();
		updatewithoutinput();
	}
	gameover();
	return 0;
}