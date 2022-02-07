#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<math.h>
#define width 800  //��ͼ��С
#define  high 650
#define  PI 3.1415927
#pragma comment(lib,"Winmm.lib")

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
int playerpichigh=40,playerpicwidth=30;//���ͼƬ�߿�  ��ʾʱҪ��
int p1_high=35,p1_width=26;  //���1̹��ʵ�ʴ�С ����С��ͼƬ��С�� �߽��ж�ʱҪ��
int p1_x,p1_y;    //���1����λ�ã�����ѡ��ͼ�йأ�
int p2_x,p2_y;    //���2����λ��
int  p1_angle;  //���1 �ڿڵĽǶ�(8 ���Ƕ�)
int  p2_angle; //���2 �ڿڵĽǶ�
int stopspan1=20,stopspan2=20;  //������ת������
int bleed1=3,bleed2=3;  //���Ѫ��
bulletifm bullet[2][30];  //�ӵ����䣨ÿ����������ʮ����
int mouse_x,mouse_y; //��굱ǰλ��


////����������
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

void ReadRecordFile() //��ȡ��Ϸ�����ļ�
{
	FILE *fp;
	fp=fopen("gameRecord.dat","r");
	fscanf(fp,"%c %d %d %d %d %d %d",&choose_map,&p1_angle,&p1_x,&p1_y,&p2_angle,&p2_x,&p2_y);
	fclose(fp);

	if(choose_map == '1')  //�����ͼ
		startup_map1();
	if(choose_map == '2')
		startup_map2();
	if(choose_map == '3')
		startup_map3();
	
	
}

void WriteRecordFile()  //д����Ϸ�����ļ�
{
	FILE *fp;
	fp=fopen("gameRecord.dat","w");
	fprintf(fp,"%c %d %d %d %d %d %d",choose_map,p1_angle,p1_x,p1_y,p2_angle,p2_x,p2_y);
	fclose(fp);
}

void startmenu()   //��Ϸ��ʼ�˵�����
{
	cleardevice();
//	putimage(0, 0, &img_bk);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("����"));
	outtextxy(width*0.3, high*0.2, "����Ϸ");
	outtextxy(width*0.3, high*0.3, "��ȡ��Ϸ�浵");
	outtextxy(width*0.3, high*0.4, "��Ϸ����");
	outtextxy(width*0.3, high*0.5, "�˳�");
	
	FlushBatchDraw();
	
	//�������
	MOUSEMSG m;//���������Ϣ
	if(MouseHit()){
		m = GetMouseMsg();  //��ȡһ�������Ϣ
	if(m.uMsg==WM_LBUTTONDOWN){ //����������
		
		if (m.x>width*0.3 && m.x<width*0.3+50*3 && m.y>high*0.2 && m.y<high*0.2+50  ){   //����Ϸ
			cleardevice();
			//��ͼѡ�����
			setbkmode(TRANSPARENT);
			settextcolor(BLUE);
			settextstyle(30,0, _T("����"));
			outtextxy(width*0.35, high*0.2, "ѡ���ͼ");
			outtextxy(width*0.6, high*0.7, "����");

			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(50,0, _T("����"));
			outtextxy(width*0.2, high*0.5, "1");
			outtextxy(width*0.3, high*0.5, "2");
			outtextxy(width*0.4, high*0.5, "3");
			outtextxy(width*0.5, high*0.5, "4");
			
			FlushBatchDraw();

			//����һ����Ч
			mciSendString("close jpmusic",NULL,0,NULL);
			mciSendString("open C:\\Users\\14432\\Desktop\\̹�˶�����Ч�ز�\\����ֻ�Ͷ����Ч_������_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
			mciSendString("play jpmusic",NULL,0,NULL);
							
			while(1){
			MOUSEMSG m;//���������Ϣ
			if(MouseHit()){
				m = GetMouseMsg();  //��ȡһ�������Ϣ	
			if(m.uMsg==WM_LBUTTONDOWN){ //����������
				//��ʼ����ͼ
				if(m.x>width*0.2 && m.x<width*0.2+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map1();
					choose_map='1';
					//��ʼ�����λ��(����ڵ�ͼ��
					p1_x=75;
					p1_y=50;
					p1_angle=rand()%8-4;
					p2_x=125;
					p2_y=175;
					p2_angle=rand()%8-4;
					
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.3 && m.x<width*0.3+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map2();
					choose_map='2';
					//��ʼ�����λ��(����ڵ�ͼ��
					p1_x=175;
					p1_y=175;
					p1_angle=rand()%8-4;
					p2_x=425;
					p2_y=25;
					p2_angle=rand()%8-4;
					
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.4 && m.x<width*0.4+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map3();
					choose_map='3';
					//��ʼ�����λ��(����ڵ�ͼ��
					p1_x=425;
					p1_y=325;
					p1_angle=rand()%8-4;
					p2_x=100;
					p2_y=525;
					p2_angle=rand()%8-4;
					
					gameStatus = 1;
					break;
				}
				else if(m.x>width*0.5 && m.x<width*0.5+50 && m.y>high*0.5 && m.y<high*0.5+50){
					startup_map4();
					choose_map='4';
					//��ʼ�����λ��(����ڵ�ͼ��
					p1_x=50;
					p1_y=225;
					p1_angle=rand()%8-4;
					p2_x=75;
					p2_y=125;
					p2_angle=rand()%8-4;
					
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
		else if (m.x>width*0.3 && m.x<width*0.3+50*6 && m.y>high*0.3 && m.y<high*0.3+50 ){  //������Ϸ		
			ReadRecordFile();   //������Ϸ����
			gameStatus = 1;
		}
		else if( m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.4 && m.y<high*0.4+50 ){  //��Ϸ����
			cleardevice();
			
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(30,0, _T("����"));
			outtextxy(width*0.35, high*0.3, "wasd �����ƶ�");
			outtextxy(width*0.35, high*0.45, "�ո� �����ӵ�");
			outtextxy(width*0.35, high*0.6, "ESC����ͣ��Ϸ");
			outtextxy(width*0.5, high*0.7, "����");

			FlushBatchDraw();
	
			while(1){
				MOUSEMSG m;//���������Ϣ
				if(MouseHit()){
					m = GetMouseMsg();  //��ȡһ�������Ϣ	
					if(m.uMsg==WM_LBUTTONDOWN){ //����������
						if(m.x>width*0.5 && m.x<width*0.5+30*2 && m.y>high*0.7 && m.y<high*0.7+30){
							startmenu();
							break;
						}
					}
				}
			}

		}
		else if (m.x>width*0.3 && m.x<width*0.3+50*2 && m.y>high*0.5 && m.y<high*0.5+50 )  //�˳�
		{
			gameStatus = 3;
			exit(0);
		}
	}

	
	
	//����һ����Ч
	mciSendString("close jpmusic",NULL,0,NULL);
	mciSendString("open C:\\Users\\14432\\Desktop\\̹�˶�����Ч�ز�\\����ֻ�Ͷ����Ч_������_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
	mciSendString("play jpmusic",NULL,0,NULL);
	
	cleardevice();

	}
}

void pausemenu()   //��Ϸ��ͣ�˵�����
{
	cleardevice();
//	putimage(0, 0, &img_bk);	// ��ʾ����
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(50,0, _T("����"));
	outtextxy(width*0.3, high*0.2, "������Ϸ");
	outtextxy(width*0.3, high*0.3, "���浵��");
	outtextxy(width*0.3, high*0.4, "��Ϸ����");
	outtextxy(width*0.3, high*0.5, "�˳�");

	FlushBatchDraw();
	

	//�������
	MOUSEMSG m;//���������Ϣ
	if(MouseHit()){
		m = GetMouseMsg();  //��ȡһ�������Ϣ
	if(m.uMsg==WM_LBUTTONDOWN){
	
		if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.2 && m.y<high*0.2+50) 
			gameStatus = 1;
		else if (m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.3 && m.y<high*0.3+50)
		{
			WriteRecordFile();  //������Ϸ����
			gameStatus = 1;
		}
		else if(m.x>width*0.3 && m.x<width*0.3+50*4 && m.y>high*0.4 && m.y<high*0.4+50){
			
			cleardevice();
			
			setbkmode(TRANSPARENT);
			settextcolor(RED);
			settextstyle(30,0, _T("����"));
			outtextxy(width*0.35, high*0.3, "wasd �����ƶ�");
			outtextxy(width*0.35, high*0.45, "�ո� �����ӵ�");
			outtextxy(width*0.35, high*0.6, "ESC����ͣ��Ϸ");
			outtextxy(width*0.5, high*0.7, "����");
			
			FlushBatchDraw();
			
			while(1){
				MOUSEMSG m;//���������Ϣ
				if(MouseHit()){
					m = GetMouseMsg();  //��ȡһ�������Ϣ	
					if(m.uMsg==WM_LBUTTONDOWN){ //����������
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

}

void startup_map3()  //���ص�ͼ3
{
	//�˵�ͼ��С 600*550
	int i, j;
	for (i = 0; i < 550; i++)
	{
		map[0][i] = 1;
		map[600 - 1][i] = 1;//�Ա߿�ֵ
	}
	for (j = 0; j < 600; j++)
	{
		map[j][0] = 1;
		map[j][550 - 1] = 1;
	}
	for (i = 0; i < 100; i++)//���ϰ��︳ֵ
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
	//�õ�ͼΪ250*250
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

void startup()//��ʼ������
{
	initgraph(800,650);//�����Ĵ�С���ȵ�ͼ��һ�㣩
	setbkcolor(WHITE);//����������ɫ
	cleardevice();
	
	BeginBatchDraw();  //��ʼ��ͼ

	//��ʼ���ű�������
	mciSendString("open C:\\Users\\14432\\Desktop\\̹�˶�����Ч�ز�\\��ͷ��������_������_aigei_com.mp3 alias bkmusic",NULL,0,NULL);
	mciSendString("play bkmusic repeat",NULL,0,NULL);

	
	//��ʼ�˵�
	while (gameStatus == 0){  
		startmenu();
	}
		

	//��ʼ ��ͼ�����������е���ʾλ��
	map_show_x=200;
	map_show_y=50;
	
	//��ʼ �ӵ�λ�� �� �ӵ��ٶ�
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<30;j++){
			bullet[i][j].isused=0;  //��ʾ����ӵ�����δʹ��
			bullet[i][j].x=0;
			bullet[i][j].y=0;
			bullet[i][j].v_x=0;
			bullet[i][j].v_y=0;
			bullet[i][j].move=0;
		}

}



void show_map() //��ʾ��ͼ
{

/*	//�������ӡ��ͼ  ����ӡ�ٶȺ�����
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
	if(choose_map == '3'){
		IMAGE ditu3;
		loadimage(&ditu3,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\��ͼ3.JPG");
		putimage(map_show_x,map_show_y,&ditu3);
	}
	if(choose_map == '4'){
		IMAGE ditu4;
		loadimage(&ditu4,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\��ͼ4.JPG");
		putimage(map_show_x,map_show_y,&ditu4);
	}

		
}

void show_player()  //��ʾ���
{
	//��ʾ���1
	IMAGE p1_1,p1_2,p1_1_0,p1_2_0;
	loadimage(&p1_1_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\2.jpg",playerpicwidth,playerpichigh);//����ͼ
	loadimage(&p1_2_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\1.jpg",playerpicwidth,playerpichigh);//ԭͼ
	rotateimage(&p1_1,&p1_1_0,PI*p1_angle*1.0/4,SRCINVERT);   //���սǶ���תͼƬ
	rotateimage(&p1_2,&p1_2_0,PI*p1_angle*1.0/4,WHITE);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_1,NOTSRCERASE);
	putimage(p1_x+map_show_x-playerpicwidth/2,p1_y+map_show_y-playerpichigh/2,&p1_2,SRCINVERT);
	//��ʾ���2
	IMAGE p2_1,p2_2,p2_1_0,p2_2_0;
	loadimage(&p2_1_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\4.jpg",playerpicwidth,playerpichigh);//����ͼ
	loadimage(&p2_2_0,"C:\\Users\\14432\\Desktop\\̹�˶���ͼƬ�ز�\\3.jpg",playerpicwidth,playerpichigh);//ԭͼ
	rotateimage(&p2_1,&p2_1_0,PI*p2_angle*1.0/4,SRCINVERT);   //���սǶ���תͼƬ
	rotateimage(&p2_2,&p2_2_0,PI*p2_angle*1.0/4,WHITE);
	putimage(p2_x+map_show_x-playerpicwidth/2,p2_y+map_show_y-playerpichigh/2,&p2_1,NOTSRCERASE);
	putimage(p2_x+map_show_x-playerpicwidth/2,p2_y+map_show_y-playerpichigh/2,&p2_2,SRCINVERT);

}

void show_bullet()  //��ʾ�ӵ�
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

void show_object() //��ʾ����
{

}

void show()  //��ʾ
{

	IMAGE beijing; //����ͼƬ
	loadimage(&beijing,"D:\\����\\�ɻ���ս\\�ɻ���սͼƬ�����ز�\\background2.jpg",800,650);
	putimage(0,0,&beijing);


	//��ʾ��ͼ
	show_map();
	//��ʾ����
	show_player();
	//��ʾ�ӵ�
	show_bullet();
	//��ʾ����
	show_object();

	FlushBatchDraw();  //������ͼ
}

int can_move1(int x,int y,int a,int tankv_x,int tankv_y)  //�ж�̹���ܷ�ǰ��
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

int can_move2(int x,int y,int a,int tankv_x,int tankv_y)  //�ж�̹���ܷ����
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

void updatewithinput()  //��(��Ϸ��)�����йصĸ���
{
  //���1
		int tankv_x = 2*sin(PI*p1_angle/4);  //������ˮƽƽ����(1 �� 2��
		int tankv_y = 2*cos(PI*p1_angle/4);
		int temp_direction1=0;  //��ʱ��¼��ֹ��ǰ������� ����ת������֮�йأ�
	
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

		//���1 ������ת(��̹���ƶ������й�)
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

		if ( GetAsyncKeyState(0x20) & 0x8000 ){  //���¿ո� ���1�����ӵ�	
			int j;
			//����ÿ���ӵ�
			for(j=0;j<30;j++){ 
				if(bullet[0][j].isused == 0){  //�ҵ�һ���յ��ӵ�����
					//����һ����Ч
					mciSendString("close jpmusic",NULL,0,NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\̹�˶�����Ч�ز�\\ײ��������1_������_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString("play jpmusic",NULL,0,NULL);
					bullet[0][j].isused = 1;
					//λ��
					//ע�����ڿ�λ�÷���
					bullet[0][j].x = p1_x-10*tankv_x;
					bullet[0][j].y = p1_y-10*tankv_y;
					//�ٶȣ�ȡ�����ڿڷ���
					bullet[0][j].v_x = -2*sin(PI*p1_angle/4);
					bullet[0][j].v_y = -2*cos(PI*p1_angle/4);
					//�޶��ӵ��ٶȴ�СС��2�����ڱ߽��ж���
					if(bullet[0][j].v_x == 2 ) bullet[0][j].v_x =1;
					if(bullet[0][j].v_x ==-2 ) bullet[0][j].v_x =-1;
					if(bullet[0][j].v_y == 2 ) bullet[0][j].v_y =1;
					if(bullet[0][j].v_y ==-2 ) bullet[0][j].v_y =-1;
					//��ǽ����
					bullet[0][j].move = 0;
					break;
				}
			}
		}

   /////���2
		tankv_x = 2*sin(PI*p2_angle/4);  //������ˮƽƽ����(1 �� 2��
		tankv_y = 2*cos(PI*p2_angle/4);
		int temp_direction2=0;  //��ʱ��¼��ֹ��ǰ������� ����ת������֮�йأ�
		
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

		//���2 ������ת(��̹���ƶ������й�)
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


		if ( GetAsyncKeyState(0x0d) & 0x8000 ){  //���»س� ���2�����ӵ�		
			int j;
			//����ÿ���ӵ�
			for(j=0;j<30;j++){ 
				if(bullet[1][j].isused == 0){  //�ҵ�һ���յ��ӵ�����
					//����һ����Ч
					mciSendString("close jpmusic",NULL,0,NULL);
					mciSendString("open C:\\Users\\14432\\Desktop\\̹�˶�����Ч�ز�\\ײ��������1_������_aigei_com.mp3 alias jpmusic",NULL,0,NULL);
					mciSendString("play jpmusic",NULL,0,NULL);
					bullet[1][j].isused = 1;
					//λ��
					//ע�����ڿ�λ�÷���
					bullet[1][j].x = p2_x-10*tankv_x;
					bullet[1][j].y = p2_y-10*tankv_y;
					//�ٶȣ�ȡ�����ڿڷ���
					bullet[1][j].v_x = -2*sin(PI*p2_angle/4);
					bullet[1][j].v_y = -2*cos(PI*p2_angle/4);
					//�޶��ӵ��ٶȴ�СС��2�����ڱ߽��ж���
					if(bullet[1][j].v_x == 2 ) bullet[1][j].v_x =1;
					if(bullet[1][j].v_x ==-2 ) bullet[1][j].v_x =-1;
					if(bullet[1][j].v_y == 2 ) bullet[1][j].v_y =1;
					if(bullet[1][j].v_y ==-2 ) bullet[1][j].v_y =-1;
					//��ǽ����
					bullet[1][j].move = 0;
					break;
				}
			}
		}

		if(kbhit()){
			char input ;
			input = getch();
			if( input == 27 ){  //����EXC��
				gameStatus=2;  //��ͣ״̬
			}
		}
		
}

void updatewithoutinput()  //�������޹صĸ���
{
	while(gameStatus==2){
		pausemenu();  //��ͣ�˵�
	}
	

	//ʵ���ӵ����ƶ�������������̹�ˣ��Զ���ʧ
	int i,j;
	for(i=0;i<2;i++)
		for(j=0;j<30;j++){
			if(bullet[i][j].isused == 1){  //���ӵ�����
				//�ӵ��ƶ�
				bullet[i][j].x+=bullet[i][j].v_x;
				bullet[i][j].y+=bullet[i][j].v_y;
				//�ӵ�����
				if(bullet[i][j].v_x>0){
					if( map[ bullet[i][j].x+1][ bullet[i][j].y] == 1 ){  
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //��ǽ������һ
					}  
				}
				else if(bullet[i][j].v_x<0){
					if( map[ bullet[i][j].x-1][ bullet[i][j].y] == 1 ){
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //��ǽ������һ
					}
				}
				else if(bullet[i][j].v_x==0){
					if( map[ bullet[i][j].x][ bullet[i][j].y] == 1 ){
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //��ǽ������һ
					}
				}
				if(bullet[i][j].v_y>0){
					if( map[ bullet[i][j].x][ bullet[i][j].y+1] == 1 ){  
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //��ǽ������һ
					} 
				}
				else if(bullet[i][j].v_y<0){
					if( map[ bullet[i][j].x ][ bullet[i][j].y-1] == 1 ){  
						bullet[i][j].v_y=-bullet[i][j].v_y;		
						bullet[i][j].move++;  //��ǽ������һ
					} 
				}
				else if(bullet[i][j].v_y==0){
					if( map[ bullet[i][j].x ][ bullet[i][j].y ] == 1 ){
						bullet[i][j].v_x=-bullet[i][j].v_x;		
						bullet[i][j].move++;  //��ǽ������һ
					}
				}
				//�ӵ��Զ���ʧ
				if(bullet[i][j].move == 10){
					bullet[i][j].isused=0;
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