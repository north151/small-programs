#include<conio.h>
#include<math.h>
#include<stdio.h>
#include<graphics.h>
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
int p1_x,p1_y ;    //玩家1坐标位置（与所选地图有关）
int  p1_angle;  //玩家1 炮口的角度(8 个角度)
bulletifm bullet[30];  //子弹房间（最多三十个）
int mouse_x,mouse_y; //鼠标当前位置


////函数声明区
void startmenu();
void pausemenu();
void ReadRecordFile();
void WriteRecordFile();
void startup_map1();
void startup_map2();
void startup_map3();
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
	fscanf(fp,"%c %d %d %d",&choose_map,&p1_angle,&p1_x,&p1_y);
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
	fprintf(fp,"%c %d %d %d",choose_map,p1_angle,p1_x,p1_y);
	fclose(fp);
}

void startmenu()   //游戏开始菜单界面
{
	cleardevice();
//	putimage(0, 0, &img_bk);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
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
			setbkmode(TRANSPARENT);
			settextcolor(BLUE);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.2, "选择地图");
			outtextxy(width*0.6, high*0.7, "返回");

			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
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
				if(m.x>width*0.2 && m.x<width*0.2+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map1();
					choose_map='1';
					//初始化玩家位置(相对于地图）
					p1_x=rand()%400;
					p1_y=rand()%800;
					p1_angle=0.00;
					
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.3 && m.x<width*0.3+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map2();
					choose_map='2';
					//初始化玩家位置(相对于地图）
					p1_x=rand()%450;
					p1_y=rand()%450;
					p1_angle=0.00;
					
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.4 && m.x<width*0.4+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map3();
					choose_map='3';
					//初始化玩家位置(相对于地图）
					p1_x=rand()%550;
					p1_y=rand()%600;
					p1_angle=0.00;
					
					gameStatus = 1;
					break;
				}
			/*	else if(m.x>width*0.5 && m.x<width*0.5+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map4();
					choose_map='4';
					//初始化玩家位置(相对于地图）
					p1_x=rand()%400;
					p1_y=rand()%800;
					p1_angle=0.00;
					
					gameStatus = 1;
					break;
				} */
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
			
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.3, "wasd 控制移动");
			outtextxy(width*0.35, high*0.45, "空格 发射子弹");
			outtextxy(width*0.35, high*0.6, "ESC键暂停游戏");
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
//	putimage(0, 0, &img_bk);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, "继续游戏");
	outtextxy(width*0.3, high*0.3, "保存档案");
	outtextxy(width*0.3, high*0.4, "游戏帮助");
	outtextxy(width*0.3, high*0.5, "退出");

	FlushBatchDraw();
	

	//鼠标输入
	MOUSEMSG m;//定义鼠标信息
	if(MouseHit()){
		m = GetMouseMsg();  //获取一条鼠标消息
	if(m.uMsg==WM_LBUTTONDOWN){
	
		if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.2 && m.y<high*0.2+50) 
			gameStatus = 1;
		else if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.3 && m.y<high*0.3+50)
		{
			WriteRecordFile();  //保存游戏进度
			gameStatus = 1;
		}
		else if(m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.4 && m.y<high*0.4+50){
			
			cleardevice();
			
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(30,0, _T("楷体"));
			outtextxy(width*0.35, high*0.3, "wasd 控制移动");
			outtextxy(width*0.35, high*0.45, "空格 发射子弹");
			outtextxy(width*0.35, high*0.6, "ESC键暂停游戏");
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
		else if (m.x>width*0.3 && m.x<width*0.3+50*2 && m.y>high*0.5 && m.y<high*0.5+50){
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
	//此地图大小 550*600
	int i, j;

	//对边框赋值
	for (i = 0; i < 550; i++){
		map[i][0] = 1;
		map[i][599] = 1;
	}
	for (j = 0; j < 600; j++){
		map[0][j] = 1;
		map[549][j] = 1;
	}
	//对障碍物赋值
	for (i = 0; i < 100; i++)	map[50][i] = 1;
	for (i = 500; i < 600; i++)	map[50][i] = 1;
	for (i = 350; i <400; i++)	map[50][i] = 1;
	for (i = 500; i <600 ; i++)	map[100][i] = 1;
	for (i = 350; i <400 ; i++)	map[100][i] = 1;
	for (i = 0; i <50 ; i++)	map[150][i] = 1;
	for (i = 200; i <350 ; i++)	map[150][i] = 1;
	for (i = 400; i <600 ; i++)	map[150][i] = 1;
	for (i = 0; i < 50; i++)	map[200][i] = 1;
	for (i = 100; i <150 ; i++)	map[200][i] = 1;
	for (i = 200; i < 300; i++)	map[200][i] = 1;
	for (i = 350; i < 500; i++)	map[200][i] = 1;
	for (i = 50; i < 100; i++)	map[200][i] = 1;
	for (i = 50; i < 500; i++)	map[200][i] = 1;
	for (i = 150; i < 300; i++)	map[200][i] = 1;
	for (i = 350; i < 550; i++)	map[200][i] = 1;
	for (i = 50; i <100 ; i++)	map[300][i] = 1;
	for (i = 150; i <250 ; i++)	map[300][i] = 1;
	for (i = 300; i <350 ; i++)	map[300][i] = 1;
	for (i = 400; i < 450; i++)	map[300][i] = 1;
	for (i = 500; i <550 ; i++)	map[300][i] = 1;
	for (i = 50; i < 150; i++)	map[350][i] = 1;
	for (i = 300; i < 450; i++)	map[350][i] = 1;
	for (i = 500; i < 600; i++)	map[350][i] = 1;
	for (i = 100; i < 150; i++)	map[400][i] = 1;
	for (i = 300; i < 350; i++)	map[400][i] = 1;
	for (i = 450; i < 550; i++)	map[400][i] = 1;
	for (i = 0; i < 50; i++)	map[450][i] = 1;
	for (i = 150; i < 300; i++)	map[450][i] = 1;
	for (i =350 ; i < 400; i++)	map[450][i] = 1;
	for (i = 50; i < 100; i++)	map[500][i] = 1;
	for (i = 150; i < 200; i++)	map[500][i] = 1;
	for (i = 250; i < 400; i++)	map[500][i] = 1;
	for (i = 450; i < 500; i++)	map[500][i] = 1;
	for (i = 550; i < 600; i++)	map[500][i]= 1;
	for (j = 400; j < 500; j++)	map[j][50] = 1;
	for (j = 250; j < 300; j++)	map[j][50] = 1;
	for(j = 100; j < 200; j++)	map[j][100] = 1;
	for (j = 300; j < 350; j++)	map[j][100] = 1;
	for (j = 400; j < 450; j++)	map[j][100] = 1;
	for (j = 0; j <50 ; j++)	map[j][150] = 1;
	for (j = 100; j <150 ; j++)	map[j][150] = 1;
	for (j = 200; j < 250; j++)	map[j][150] = 1;
	for (j = 350; j < 450; j++)	map[j][150] = 1;
	for (j = 50; j < 100; j++)	map[j][200] = 1;
	for (j = 150; j < 200; j++)	map[j][200] = 1;
	for (j = 300; j < 400; j++)	map[j][200] = 1;
	for (j = 500; j < 550; j++)	map[j][200] = 1;
	for (j = 0; j < 50; j++)	map[j][200] = 1;
	for (j = 100; j < 150; j++)	map[j][100] = 1;
	for (j = 200; j < 300; j++)	map[j][100] = 1;
	for (j = 400; j < 450; j++)	map[j][100] = 1;
	for (j = 50; j < 100; j++)	map[j][300] = 1;
	for (j = 50; j < 100; j++)	map[j][350] = 1;
	for (j = 150; j < 200; j++)	map[j][350] = 1;
	for (j = 300; j < 400; j++)	map[j][350] = 1;
	for (j = 500; j < 550; j++)	map[j][350] = 1;
	for (j = 250; j < 300; j++)	map[j][400] = 1;
	for (j = 350; j < 400; j++)	map[j][400] = 1;
	for (j = 450; j < 500; j++)	map[j][400] = 1;
	for (j = 50; j < 100; j++)	map[j][450] = 1;
	for (j = 400; j < 500; j++)	map[j][500] = 1;
	for (j = 200; j < 300; j++)	map[j][550] = 1;
	for (j = 450; j < 500; j++)	map[j][550] = 1;
}

void start_map4()
{

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
	
	//初始 子弹位置 及 子弹速度
	int k;
	for(k=0;k<30;k++){
		bullet[k].isused=0;  //表示这个子弹房间未使用
		bullet[k].x=0;
		bullet[k].y=0;
		bullet[k].v_x=0;
		bullet[k].v_y=0;
		bullet[k].move=0;
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
		IMAGE ditu2;
		loadimage(&ditu2,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图2.JPG");
		putimage(map_show_x,map_show_y,&ditu2);
	}
	if(choose_map == '1'){
		IMAGE ditu1;
		loadimage(&ditu1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图1.JPG");
		putimage(map_show_x,map_show_y,&ditu1);
	}
	if(choose_map == '3'){
		IMAGE ditu1;
		loadimage(&ditu1,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\地图3.JPG");
		putimage(map_show_x,map_show_y,&ditu1);
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

}

void show_bullet()  //显示子弹
{
	int k;
	for(k=0;k<30;k++){
		if(bullet[k].isused == 1){
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillcircle(bullet[k].x+map_show_x,bullet[k].y+map_show_y,2);
		}
	}

}

void show_object() //显示道具
{

}

void show()  //显示
{

	IMAGE beijing; //背景图片
	loadimage(&beijing,"D:\\程序\\飞机大战\\飞机大战图片音乐素材\\background2.jpg",800,650);
	putimage(0,0,&beijing);


	//显示地图
	show_map();
	//显示人物
	show_player();
	//显示子弹
	show_bullet();
	//显示道具
	show_object();

	FlushBatchDraw();  //批量绘图
}

int can_move1(int tankv_x,int tankv_y)  //判断坦克是否撞墙(1)
{
	
	int i,j;
	for(i=p1_x-p1_width/2,j=p1_y-p1_high/2;i<p1_x+p1_width/2;i++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}
	for(i=p1_x-p1_width/2,j=p1_y+p1_high/2;i<p1_x+p1_width/2;i++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}
	for(i=p1_x-p1_width/2,j=p1_y-p1_high/2;j<p1_y+p1_high/2;j++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;	
	}
	for(i=p1_x+p1_width/2,j=p1_y-p1_high/2;j<p1_y+p1_high/2;j++){
		if(map[i-tankv_x][j-tankv_y] == 1)  return 0;
	}

	return 1;
}

int can_move2(int tankv_x,int tankv_y)  //判断坦克是否撞墙(2)
{
	
	int i,j;
	for(i=p1_x-p1_width/2,j=p1_y-p1_high/2;i<p1_x+p1_width/2;i++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
	for(i=p1_x-p1_width/2,j=p1_y+p1_high/2;i<p1_x+p1_width/2;i++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
	for(i=p1_x-p1_width/2,j=p1_y-p1_high/2;j<p1_y+p1_high/2;j++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;	
	}
	for(i=p1_x+p1_width/2,j=p1_y-p1_high/2;j<p1_y+p1_high/2;j++){
		if(map[i+tankv_x][j+tankv_y] == 1)  return 0;
	}
	
	return 1;
}

void updatewithinput()  //与(游戏中)输入有关的更新
{

		//坦克前后移动  //坦克移动时要判断坦克四周有无墙体
		int tankv_x = 2*sin(PI*p1_angle/4);  //两方向水平平移量(1 或 2）
		int tankv_y = 2*cos(PI*p1_angle/4);
		int temp_direction=0;  //暂时记录静止，前进或后退 （旋转方向与之有关）
	
		if(GetAsyncKeyState(0x57) & 0x8000)
			if( can_move1(tankv_x,tankv_y)){
				p1_x -=  tankv_x;
				p1_y -=	 tankv_y;
				temp_direction = 1;
			}
		if(GetAsyncKeyState(0x53) & 0x8000)
			if( can_move2(tankv_x,tankv_y)){
				p1_x +=  tankv_x;
				p1_y +=  tankv_y;
				temp_direction = 2;
			}

		//坦克左右旋转
	/*	if( GetAsyncKeyState(0x41) & 0x8000 )
			p1_angle = p1_angle + 1;
		if( GetAsyncKeyState(0x44) & 0x8000 )
			p1_angle = p1_angle - 1;  */
		
		if ( GetAsyncKeyState(0x20) & 0x8000 ){  //按下空格 发射子弹
			
			int k;
			for(k=0;k<30;k++){  //检索每个子弹
				if(bullet[k].isused == 0){  //找到一个空的子弹房间
					//播放一次音效
					mciSendString("close jpmusic",NULL,0,NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\坦克动荡音效素材\\撞击－击中1_爱给网_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString("play jpmusic",NULL,0,NULL);
					bullet[k].isused = 1;
					//位置
					bullet[k].x = p1_x;
					bullet[k].y = p1_y;
					//速度（取决于炮口方向）
					bullet[k].v_x = -2*sin(PI*p1_angle/4);
					bullet[k].v_y = -2*cos(PI*p1_angle/4);
					   //限定子弹速度大小小于2（便于边界判定）
					if(bullet[k].v_x == 2 ) bullet[k].v_x =1;
					if(bullet[k].v_x ==-2 ) bullet[k].v_x =-1;
					if(bullet[k].v_y == 2 ) bullet[k].v_y =1;
					if(bullet[k].v_y ==-2 ) bullet[k].v_y =-1;
					//击墙次数
					bullet[k].move = 0;
					break;
				}
			}
		}

		if(kbhit()){
			char input ;
			input = getch();
			if( input == 27 ){  //按下EXC键
				gameStatus=2;  //暂停状态
			}

			//坦克左右旋转(与坦克移动方向有关)
			if( input == 'd' ){
				if( temp_direction == 0 || temp_direction == 1)
					p1_angle --;
				if( temp_direction == 2)
					p1_angle ++;
			}
			if( input == 'a' ){
				if( temp_direction == 0 || temp_direction == 1)	
					p1_angle ++;
				if( temp_direction == 2)
					p1_angle --;
			}
		}
			
}

void updatewithoutinput()  //与输入无关的更新
{
	while(gameStatus==2){
		pausemenu();  //暂停菜单
	}
	

	//实现子弹的移动，反弹，击中坦克，自动消失
	int k;
	for(k=0;k<30;k++){
		if(bullet[k].isused == 1){  //当子弹存在
			//子弹移动
			bullet[k].x+=bullet[k].v_x;
			bullet[k].y+=bullet[k].v_y;
			//子弹反弹
			if(bullet[k].v_x>0){
				if( map[ bullet[k].x+1][ bullet[k].y] == 1 ){  
					bullet[k].v_x=-bullet[k].v_x;		
					bullet[k].move++;  //击墙次数加一
				}  
			}
			else if(bullet[k].v_x<0){
				if( map[ bullet[k].x-1][ bullet[k].y] == 1 ){
					bullet[k].v_x=-bullet[k].v_x;		
					bullet[k].move++;  //击墙次数加一
				}
			}
			else if(bullet[k].v_x==0){
				if( map[ bullet[k].x][ bullet[k].y] == 1 ){
					bullet[k].v_y=-bullet[k].v_y;		
					bullet[k].move++;  //击墙次数加一
				}
			}
			if(bullet[k].v_y>0){
				if( map[ bullet[k].x][ bullet[k].y+1] == 1 ){  
					bullet[k].v_y=-bullet[k].v_y;		
					bullet[k].move++;  //击墙次数加一
				} 
			}
			else if(bullet[k].v_y<0){
				if( map[ bullet[k].x ][ bullet[k].y-1] == 1 ){  
					bullet[k].v_y=-bullet[k].v_y;		
					bullet[k].move++;  //击墙次数加一
				} 
			}
			else if(bullet[k].v_y==0){
				if( map[ bullet[k].x ][ bullet[k].y ] == 1 ){
					bullet[k].v_x=-bullet[k].v_x;		
					bullet[k].move++;  //击墙次数加一
				}
			}
			//子弹自动消失
			if(bullet[k].move == 15){
				bullet[k].isused=0;
			}

		}
	}

	//实现特殊道具的相关功能 （ 出现，拾取,使用，效果）
	

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