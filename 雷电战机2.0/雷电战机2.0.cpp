#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include<queue>
#include<string>
#include<time.h>
#include<stack>
using namespace std;
#include "Mmsystem.h"
#pragma comment(lib,"Winmm.lib")
struct Node{
	int x,y;
}; 
queue<Node>fire;
queue<Node>monsters,mon_fires;
bool mp[1000];
char score[5],life[4];
int x,y;
void Print_fire()
{
	IMAGE img;
	int len1=fire.size();
	for(int i=1;i<=len1;i++)
	{
		Node t1=fire.front();
		fire.pop();
		loadimage(&img,_T("pictures//bg.jpg"),50,60);
		putimage(t1.x,t1.y,&img);
		t1.y-=10;
		if(t1.y<=10)continue;
		loadimage(&img,_T("pictures//fire.jpg"),50,60);//
		putimage(t1.x,t1.y,&img);
		fire.push(t1);
	}
}
void Print_monster()
{
	int len2=monsters.size();
	IMAGE img;
	for(int i=1;i<=len2;i++)
	{
		Node t2=monsters.front();
		monsters.pop();
		loadimage(&img,_T("pictures//bg.jpg"),50,60);
		putimage(t2.x,t2.y,&img);
		t2.y+=10;
		if(t2.y>540)continue;
		loadimage(&img,_T("pictures//monsters.jpg"),50,60);
		putimage(t2.x,t2.y,&img);
		monsters.push(t2);
		int sign=rand()%30+1;
		if(sign%8==0)
		{
			Node paodan;
			paodan.x=t2.x;
			paodan.y=t2.y+70;
			mon_fires.push(paodan);
		}
	}
}
int lifes;
void Life()
{
	int len2=monsters.size();
	int len3=mon_fires.size();
	int i;
	IMAGE img;
	for(i=1;i<=len2;i++)
	{
		Node t2=monsters.front();
		monsters.pop();
		if(abs(x-t2.x)<=50&&y-t2.y<=60)
		{
			loadimage(&img,_T("pictures//bg.jpg"),50,60);
			putimage(t2.x,t2.y,&img);
			lifes+=10;
			life[2]+=1;
			int j;
			for(j=2;j>=0;j--)
			{
				if(life[j]>'9')
				{
					life[j]='0';
					life[j-1]++;
				}
			}
			break;
		}
		else monsters.push(t2);
	}
	for(i=1;i<=len3;i++)
	{
		Node t3=mon_fires.front();
		mon_fires.pop();
		if(abs(x-t3.x)<=45&&y-t3.y<=60)
		{
			loadimage(&img,_T("pictures//bg.jpg"),50,60);
			putimage(t3.x,t3.y,&img);
			lifes+=20;
			life[2]+=2;
			int j;
			for(j=2;j>=0;j--)
			{
				if(life[j]>'9')
				{
					life[j]-='9';
					life[j]-=1;
					life[j-1]++;
				}
			}
			break;
		}
		else mon_fires.push(t3);
	}
}
void Plane(int x,int y,int k)
{
	IMAGE img;
	if(k==1)
	{
		loadimage(&img,_T("pictures//bg.jpg"),50,60);//先把图片放在工程项目下，使用L+"绝对路径"
		putimage(x,y,&img);
	}
	else{
		loadimage(&img,_T("pictures//bg1.jpg"),50,60);//先把图片放在工程项目下，使用L+"绝对路径"
		putimage(x,y,&img);
	}
}
void Print_mon_fires()
{
	int len3=mon_fires.size();
	int i;
	IMAGE img;
	for(i=1;i<=len3;i++)
	{
		Node t3=mon_fires.front();
		mon_fires.pop();
		loadimage(&img,_T("pictures//bg.jpg"),50,60);
		putimage(t3.x,t3.y,&img);
		t3.y+=10;
		if(t3.y>540)continue;
		loadimage(&img,_T("pictures//mon_fire.jpg"),50,60);
		putimage(t3.x,t3.y,&img);
		mon_fires.push(t3);
	}
}
void Change()
{
	int len1=fire.size();
	int len2=monsters.size();
	int len3=mon_fires.size();
	IMAGE img;
	int i,j;
	for(i=1;i<=len1;i++)
	{
		Node t1;
		t1=fire.front();
		fire.pop();
		bool check=false;
		len2=monsters.size();
		for(j=1;j<=len2;j++)
		{
			Node t2=monsters.front();
			monsters.pop();
			if(t1.y-t2.y<=60&&abs(t1.x-t2.x)<=45)
			{
				loadimage(&img,_T("pictures//bg.jpg"),50,60);
				putimage(t1.x,t1.y,&img);
				putimage(t2.x,t2.y,&img);
				mp[t2.x]=false;
				score[4]++;
				int k;
				for(k=4;k>=1;k--)
				{
					if(score[k]>='9')
					{
						score[k]='0';
						score[k-1]+=1;
					}
				}
				check=true;
				break;
			}
			else monsters.push(t2);
		}
		if(check==false)
		fire.push(t1);
	}
	len1=fire.size();
	for(i=1;i<=len1;i++)
	{
		Node t1=fire.front();
		fire.pop();
		bool check=false;
		len3=mon_fires.size();
		for(j=1;j<=len3;j++)
		{
			Node t3=mon_fires.front();
			mon_fires.pop();
			if(t1.y-t3.y<=60&&abs(t1.x-t3.x)<=40)
			{
				loadimage(&img,_T("pictures//bg.jpg"),50,60);
				putimage(t1.x,t1.y,&img);
				putimage(t3.x,t3.y,&img);
				check=true;
				break;
			}
			else mon_fires.push(t3);
		}
		if(check==false)
		fire.push(t1); 
	}
}
void Score_Life()
{
	settextstyle(30,0,0);
	setcolor(GREEN);
	outtextxy(820,60,"Q发射炮弹");
	setcolor(BLUE);
	char ch[10]="当前得分";
	outtextxy(820,160,ch);
	outtextxy(840,200,score);
	setcolor(YELLOW);
	char ch1[20]="生命值损耗";
	outtextxy(820,280,ch1);
	outtextxy(840,320,life);
}
void Init()
{
	memset(mp,0,sizeof(mp));
	x=450;
	y=540;
	lifes=0;
	strcpy(score,"00000");
	strcpy(life,"-000");
	while(!fire.empty())
	fire.pop();
	while(!monsters.empty())
	monsters.pop();
	while(!mon_fires.empty())
	mon_fires.pop();
	Plane(x,y,2);
}
int main(int argc, _TCHAR* argv[])
{
	initgraph(1000,600);
	Init();
	char co;
	int tim=0;
	while(true)
	{
		if(monsters.size()<5)
		{
			int check=rand()%20+1;
			if(check%5==0)continue;
			Node t;
			int x0=rand()%800+2;
			if(x0<=0||x0>=750)continue;
			int i;
			bool sign=false;
			for(i=50;i<=750;i++)
				if(mp[i]==true&&abs(x0-i)<50)
				{
					sign=true;
					break;
				}
			if(sign)
				continue;
			mp[x0]=true;
			t.x=x0;
			t.y=1;
			monsters.push(t);
		}
		if(kbhit())
		{
			co=getch();
			if(co=='P')
			{
				Node t;
				t.x=x,t.y=y-60;
				fire.push(t);
			}
			else
			{
				Plane(x,y,1);
				if(co=='W')
				{
					if(y>10)
					y-=10;
				}
				else if(co=='S')
				{
					if(y<540)
					y+=10;
				}
				else if(co=='A')
				{
					if(x>10)
					x-=10;
				}
				else if(co=='D')
				{
					if(x<740)
					x+=10;
				}
				Plane(x,y,2);
			}
		}
		if(tim%2==0)
			Print_fire();
		Change();
		if(tim%20==0)
			Print_monster();
		if(tim%2==0)
		Print_mon_fires();
		Life();
		Score_Life();
		if(lifes>=100)
		{
			char ch[20]="GAME_OVER!!!";
			outtextxy(800,400,ch);
			break;
		}
		tim%=100000;
		Sleep(10);
		tim++;
	}
	getch();
	closegraph();
	return 0;
}
