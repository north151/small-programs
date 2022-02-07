#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define width 800  //地图大小
#define  high 650
#define  PI 3.1415926

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

int playerpichigh=30,playerpicwidth=50;//玩家图片高宽

int p1_x,p1_y ;    //玩家1坐标位置（与所选地图有关）
float p1_angle;    //玩家1 炮口的角度

bulletifm bullet[30];  //子弹房间（最多三十个）



////函数声明区
void startmenu();
void pausemenu();
void ReadRecordFile();
void WriteRecordFile();
void startup_map1();
void startup_map2();
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
	fscanf(fp,"%c %f %d %d",&choose_map,&p1_angle,&p1_x,&p1_y);
	fclose(fp);

	if(choose_map == '2')  //载入地图
		startup_map2();
	if(choose_map == '1')
		startup_map1();
}

void WriteRecordFile()  //写入游戏数据文件
{
	FILE *fp;
	fp=fopen("gameRecord.dat","w");
	fprintf(fp,"%c %f %d %d",choose_map,p1_angle,p1_x,p1_y);
	fclose(fp);
}

void startmenu()   //游戏开始菜单界面
{
//	putimage(0, 0, &img_bk);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, "1 新游戏");
	outtextxy(width*0.3, high*0.3, "2 读取游戏存档");
	outtextxy(width*0.3, high*0.4, "3 退出");
	
	settextcolor(RED);
	settextstyle(30,0, _T("黑体"));
	outtextxy(width*0.35, high*0.6, "wasd 控制移动");
	outtextxy(width*0.35, high*0.65, "空格 发射子弹");
	outtextxy(width*0.35, high*0.7, "ESC键暂停游戏");

	FlushBatchDraw();
	
	  
		char input;
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == '1') {   //新游戏
			gameStatus = 1;
			cleardevice();

			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(50,0, _T("黑体"));
			outtextxy(width*0.3, high*0.2, "请选择地图1或2");
			
			FlushBatchDraw();
				
			choose_map=getch();  //选择地图  
			//初始化地图(包含玩家位置）
			if(choose_map == '2')
				startup_map2();
			if(choose_map == '1')
				startup_map1();
		}

		else if (input == '2')
		{
			ReadRecordFile();   //载入游戏进程
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 3;
			exit(0);
		}
	
	cleardevice();

}

void pausemenu()   //游戏暂停菜单界面
{
	cleardevice();
//	putimage(0, 0, &img_bk);	// 显示背景
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("黑体"));
	outtextxy(width*0.3, high*0.2, "1 继续游戏");
	outtextxy(width*0.3, high*0.3, "2 保存档案");
	outtextxy(width*0.3, high*0.4, "3 退出");
	
	settextcolor(BLUE);
	settextstyle(30,0, _T("黑体"));
	outtextxy(width*0.35, high*0.6, "wasd 控制移动");
	outtextxy(width*0.35, high*0.65, "空格 发射子弹");
	outtextxy(width*0.35, high*0.7, "ESC键暂停游戏");

	FlushBatchDraw();
	
	char input;
	if(kbhit())  // 判断是否有输入
	{
		input = getch();  // 根据用户的不同输入来移动，不必输入回车
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			WriteRecordFile();  //保存游戏进度
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 3;
			exit(0);
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
	
	//初始化玩家位置(相对于地图）
	p1_x=rand()%400;
	p1_y=rand()%800;
	p1_angle=50;
	
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

	//初始化玩家位置(相对于地图）
	p1_x=rand()%450;
	p1_y=rand()%450;
	p1_angle=50;

}

void startup()//初始化数据
{
	initgraph(800,650);//画布的大小（比地图大一点）
	setbkcolor(WHITE);//画布背景颜色
	cleardevice();
	
	BeginBatchDraw();  //开始绘图
	
	//初始菜单
	while (gameStatus == 0){  
		startmenu();
	}
		

	//初始地图在整个画布中的显示位置
	map_show_x=200;
	map_show_y=50;
	
	//初始子弹位置 及 子弹速度
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
/*
	//用数组打印地图  （打印速度很慢）
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

		
}

void show_player()  //显示玩家
{
	//显示玩家1
	IMAGE p1_1,p1_2,p1_1_0,p1_2_0;
	loadimage(&p1_1_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\2.jpg");
	loadimage(&p1_2_0,"C:\\Users\\14432\\Desktop\\坦克动荡图片素材\\1.jpg");
	rotateimage(&p1_1,&p1_1_0,p1_angle,WHITE,TURKISH_CHARSET,TURKISH_CHARSET);   //按照角度旋转图片
	rotateimage(&p1_2,&p1_2_0,p1_angle,WHITE,TURKISH_CHARSET,TURKISH_CHARSET);
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


void show()  //显示
{

	//显示地图
	show_map();
	//显示人物
	show_player();
	//显示子弹
	show_bullet();


	FlushBatchDraw();  //批量绘图
}


void updatewithinput()  //与输入有关的更新
{
		

		//判断坦克四周有无墙体


		if( GetAsyncKeyState(0x57) & 0x8000 && map[p1_x][p1_y-playerpichigh/2] != 1)
			p1_y--;
		if( GetAsyncKeyState(0x53) & 0x8000 && map[p1_x][p1_y+playerpichigh/2] != 1)
			p1_y++;
		if( GetAsyncKeyState(0x41) & 0x8000 && map[p1_x-playerpicwidth/2][p1_y] != 1)
			p1_x--;
		if( GetAsyncKeyState(0x44) & 0x8000 && map[p1_x+playerpicwidth/2][p1_y] != 1)
			p1_x++;

		if ( GetAsyncKeyState(0x20) & 0x8000 ){  //按下空格
			int k;
			for(k=0;k<30;k++){  //检索每个子弹
				if(bullet[k].isused == 0){  //找到一个空的子弹房间
					bullet[k].isused = 1;
					//位置
					bullet[k].x = p1_x;
					bullet[k].y = p1_y;
					//速度（取决于炮口方向）
					bullet[k].v_x = 1;
					bullet[k].v_y = 1;

					bullet[k].move = 0;
					break;
				}
			}
			Sleep(20);
		}
		

		if (kbhit()){
			if( getch() == 27 ){  //按下EXC键
				gameStatus=2;  //暂停状态
			}
		}

	

}

void updatewithoutinput()  //与输入无关的更新
{
	while(gameStatus==2){
		pausemenu();  //暂停菜单
	}

	//实现子弹的移动，反弹，自动消失
	int k;
	for(k=0;k<30;k++){
		if(bullet[k].isused == 1){  //当子弹存在
			//子弹移动
			bullet[k].x+=bullet[k].v_x;
			bullet[k].y+=bullet[k].v_y;
			//子弹反弹
	/*		if( map[bullet[k].x,bullet[k].y] == 1){  
				//打到墙体，子弹速度方向改变
				bullet[k].v_x=-bullet[k].v_x;
				bullet[k].v_y=-bullet[k].v_y;
				bullet[k].move++;  //击墙次数加一
			}  */
			//子弹自动消失
			if(bullet[k].move == 5){
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