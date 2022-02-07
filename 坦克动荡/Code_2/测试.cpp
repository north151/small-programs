#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define width 800  //��ͼ��С
#define  high 650
#define  PI 3.1415926

// ���ѡ����ر���
char choose_map;  //ѡ���ͼ

//ȫ�ֱ���  ��������
struct bulletifm   //�����ӵ��������Ϣ�ṹ�����
{
	int isused;  //�Ƿ�ʹ�ù�
	int x;  //����λ��
	int y;
	int v_x;   //�ٶ�
	int v_y;
	int move;   //��ǽ����ײ���Ĵ���
};

int map[width][high]={0};  //�����ά���鴢���ͼԪ��
                       // 0Ϊ�հף�1Ϊǽ�壬
int map_show_x,map_show_y;  //��ʾ��ͼ�ĳ�ʼλ��

int gameStatus=0; //������Ϸ״̬ 0��ʼ 1��Ϸ���� 2��Ϸ��ͣ 3��Ϸ����

int playerpichigh=30,playerpicwidth=50;//���ͼƬ�߿�

int p1_x,p1_y ;    //���1����λ�ã�����ѡ��ͼ�йأ�
float p1_angle;    //���1 �ڿڵĽǶ�

bulletifm bullet[30];  //�ӵ����䣨�����ʮ����



////����������
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

void ReadRecordFile() //��ȡ��Ϸ�����ļ�
{
	FILE *fp;
	fp=fopen("gameRecord.dat","r");
	fscanf(fp,"%c %f %d %d",&choose_map,&p1_angle,&p1_x,&p1_y);
	fclose(fp);

	if(choose_map == '2')  //�����ͼ
		startup_map2();
	if(choose_map == '1')
		startup_map1();
}

void WriteRecordFile()  //д����Ϸ�����ļ�
{
	FILE *fp;
	fp=fopen("gameRecord.dat","w");
	fprintf(fp,"%c %f %d %d",choose_map,p1_angle,p1_x,p1_y);
	fclose(fp);
}

void startmenu()   //��Ϸ��ʼ�˵�����
{
//	putimage(0, 0, &img_bk);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("����"));
	outtextxy(width*0.3, high*0.2, "1 ����Ϸ");
	outtextxy(width*0.3, high*0.3, "2 ��ȡ��Ϸ�浵");
	outtextxy(width*0.3, high*0.4, "3 �˳�");
	
	settextcolor(RED);
	settextstyle(30,0, _T("����"));
	outtextxy(width*0.35, high*0.6, "wasd �����ƶ�");
	outtextxy(width*0.35, high*0.65, "�ո� �����ӵ�");
	outtextxy(width*0.35, high*0.7, "ESC����ͣ��Ϸ");

	FlushBatchDraw();
	
	  
		char input;
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') {   //����Ϸ
			gameStatus = 1;
			cleardevice();

			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(50,0, _T("����"));
			outtextxy(width*0.3, high*0.2, "��ѡ���ͼ1��2");
			
			FlushBatchDraw();
				
			choose_map=getch();  //ѡ���ͼ  
			//��ʼ����ͼ(�������λ�ã�
			if(choose_map == '2')
				startup_map2();
			if(choose_map == '1')
				startup_map1();
		}

		else if (input == '2')
		{
			ReadRecordFile();   //������Ϸ����
			gameStatus = 1;
		}
		else if (input == '3')
		{
			gameStatus = 3;
			exit(0);
		}
	
	cleardevice();

}

void pausemenu()   //��Ϸ��ͣ�˵�����
{
	cleardevice();
//	putimage(0, 0, &img_bk);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("����"));
	outtextxy(width*0.3, high*0.2, "1 ������Ϸ");
	outtextxy(width*0.3, high*0.3, "2 ���浵��");
	outtextxy(width*0.3, high*0.4, "3 �˳�");
	
	settextcolor(BLUE);
	settextstyle(30,0, _T("����"));
	outtextxy(width*0.35, high*0.6, "wasd �����ƶ�");
	outtextxy(width*0.35, high*0.65, "�ո� �����ӵ�");
	outtextxy(width*0.35, high*0.7, "ESC����ͣ��Ϸ");

	FlushBatchDraw();
	
	char input;
	if(kbhit())  // �ж��Ƿ�������
	{
		input = getch();  // �����û��Ĳ�ͬ�������ƶ�����������س�
		if (input == '1') 
			gameStatus = 1;
		else if (input == '2')
		{
			WriteRecordFile();  //������Ϸ����
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


void startup_map1() //���ص�ͼ1
{
	//�˵�ͼ��С 200*400
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
	
	//��ʼ�����λ��(����ڵ�ͼ��
	p1_x=rand()%400;
	p1_y=rand()%800;
	p1_angle=50;
	
}

void startup_map2() //���ص�ͼ2
{

	//�˵�ͼ��С 450*450
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

	//��ʼ�����λ��(����ڵ�ͼ��
	p1_x=rand()%450;
	p1_y=rand()%450;
	p1_angle=50;

}

void startup()//��ʼ������
{
	initgraph(800,650);//�����Ĵ�С���ȵ�ͼ��һ�㣩
	setbkcolor(WHITE);//����������ɫ
	cleardevice();
	
	BeginBatchDraw();  //��ʼ��ͼ
	
	//��ʼ�˵�
	while (gameStatus == 0){  
		startmenu();
	}
		

	//��ʼ��ͼ�����������е���ʾλ��
	map_show_x=200;
	map_show_y=50;
	
	//��ʼ�ӵ�λ�� �� �ӵ��ٶ�
	int k;
	for(k=0;k<30;k++){
		bullet[k].isused=0;  //��ʾ����ӵ�����δʹ��
		bullet[k].x=0;
		bullet[k].y=0;
		bullet[k].v_x=0;
		bullet[k].v_y=0;
		bullet[k].move=0;
	}

}



void show_map() //��ʾ��ͼ
{
/*
	//�������ӡ��ͼ  ����ӡ�ٶȺ�����
	int i,j;
	//����ÿ������Ԫ��
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
	//��ͼƬ��ʾ��ͼ
	if(choose_map == '2'){
		IMAGE ditu2;
		loadimage(&ditu2,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\��ͼ2.JPG");
		putimage(map_show_x,map_show_y,&ditu2);
	}
	if(choose_map == '1'){
		IMAGE ditu1;
		loadimage(&ditu1,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\��ͼ1.JPG");
		putimage(map_show_x,map_show_y,&ditu1);
	}

		
}

void show_player()  //��ʾ���
{
	//��ʾ���1
	IMAGE p1_1,p1_2,p1_1_0,p1_2_0;
	loadimage(&p1_1_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\2.jpg");
	loadimage(&p1_2_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\1.jpg");
	rotateimage(&p1_1,&p1_1_0,p1_angle,WHITE,TURKISH_CHARSET,TURKISH_CHARSET);   //���սǶ���תͼƬ
	rotateimage(&p1_2,&p1_2_0,p1_angle,WHITE,TURKISH_CHARSET,TURKISH_CHARSET);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_1,NOTSRCERASE);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_2,SRCINVERT);
	
}

void show_bullet()  //��ʾ�ӵ�
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


void show()  //��ʾ
{

	//��ʾ��ͼ
	show_map();
	//��ʾ����
	show_player();
	//��ʾ�ӵ�
	show_bullet();


	FlushBatchDraw();  //������ͼ
}


void updatewithinput()  //�������йصĸ���
{
		

		//�ж�̹����������ǽ��


		if( GetAsyncKeyState(0x57) & 0x8000 && map[p1_x][p1_y-playerpichigh/2] != 1)
			p1_y--;
		if( GetAsyncKeyState(0x53) & 0x8000 && map[p1_x][p1_y+playerpichigh/2] != 1)
			p1_y++;
		if( GetAsyncKeyState(0x41) & 0x8000 && map[p1_x-playerpicwidth/2][p1_y] != 1)
			p1_x--;
		if( GetAsyncKeyState(0x44) & 0x8000 && map[p1_x+playerpicwidth/2][p1_y] != 1)
			p1_x++;

		if ( GetAsyncKeyState(0x20) & 0x8000 ){  //���¿ո�
			int k;
			for(k=0;k<30;k++){  //����ÿ���ӵ�
				if(bullet[k].isused == 0){  //�ҵ�һ���յ��ӵ�����
					bullet[k].isused = 1;
					//λ��
					bullet[k].x = p1_x;
					bullet[k].y = p1_y;
					//�ٶȣ�ȡ�����ڿڷ���
					bullet[k].v_x = 1;
					bullet[k].v_y = 1;

					bullet[k].move = 0;
					break;
				}
			}
			Sleep(20);
		}
		

		if (kbhit()){
			if( getch() == 27 ){  //����EXC��
				gameStatus=2;  //��ͣ״̬
			}
		}

	

}

void updatewithoutinput()  //�������޹صĸ���
{
	while(gameStatus==2){
		pausemenu();  //��ͣ�˵�
	}

	//ʵ���ӵ����ƶ����������Զ���ʧ
	int k;
	for(k=0;k<30;k++){
		if(bullet[k].isused == 1){  //���ӵ�����
			//�ӵ��ƶ�
			bullet[k].x+=bullet[k].v_x;
			bullet[k].y+=bullet[k].v_y;
			//�ӵ�����
	/*		if( map[bullet[k].x,bullet[k].y] == 1){  
				//��ǽ�壬�ӵ��ٶȷ���ı�
				bullet[k].v_x=-bullet[k].v_x;
				bullet[k].v_y=-bullet[k].v_y;
				bullet[k].move++;  //��ǽ������һ
			}  */
			//�ӵ��Զ���ʧ
			if(bullet[k].move == 5){
				bullet[k].isused=0;
			}

		}
	}

	//ʵ��������ߵ���ع��� �� ���֣�ʰȡ,ʹ�ã�Ч����
	

}

void gameover() //��Ϸ���� ��������
{
	EndBatchDraw();
	getch();
	closegraph();
}


int main()  //������
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