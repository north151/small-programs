#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#define width 800  //��ͼ��С
#define  high 650

//ȫ�ֱ���
int map[width][high]={0};  //�����ά���鴢���ͼԪ��
                       // 0Ϊ�հף�1Ϊǽ�壬
int map_show_x,map_show_y;  //��ʾ��ͼ�ĳ�ʼλ��






//////////////////

void map2() //���ص�ͼ2
{
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

void map1() //���ص�ͼ1
{
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

void startup()//��ʼ������
{

	
	map_show_x=200;
	map_show_y=50;

	//��ʼ����ͼ
	map2();

	//�����Ĵ�С���ȵ�ͼ��һ�㣩
	initgraph(800,650);


	//����������ɫ
	setbkcolor(WHITE);
	cleardevice();

	BeginBatchDraw();  //��ʼ��ͼ
}



void show() //��ʾ
{
	setbkcolor(WHITE);
	cleardevice();

	int i,j;
	//����ÿ������Ԫ��
	for(i=0;i<width;i++){
		for(j=0;j<high;j++){
			  if(map[i][j] == 1){
				setcolor(BLACK);
				setfillcolor(BLACK);
				fillcircle(i+map_show_x,j+map_show_y,2);
				}
		    
		}
	}


	
	FlushBatchDraw();  //������ͼ
}



void main()  //������
{
	startup();
	while(1)
	{
		show();
	}
	
}