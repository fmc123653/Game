#include<iostream>
#include<conio.h>
#include<windows.h>
#include<queue>
#include<time.h>
using namespace std;
void Pos(int x,int y,char *c)
{
	COORD coord;
	coord.X = x; //第3行
	coord.Y = y; //第3列
	//获取控制台缓冲区句柄，固定写法
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	//设置光标位置，固定写法
	SetConsoleCursorPosition(ConsoleHandle, coord);
	printf("%s",c);
}
struct Node{
	int x,y;
}; 
int score,mp[50][50];
void Planes(int x,int y,int k)
{
	if(k==1)
	{
		Pos(x,y," ");
		Pos(x-1,y+1," ");
		Pos(x+1,y+1," ");		
	}
	else if(k==2)
	{
		Pos(x,y,"@");
		Pos(x-1,y+1,"O");
		Pos(x+1,y+1,"O");		
	}
}
queue<Node>fire;
queue<Node>monsters,mon_fires;
int tim;
bool gam;
int x,y;
void Change()
{
	int len1=fire.size();
	int len2=monsters.size();
	int len3=mon_fires.size();
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
			if(t1.x==t2.x&&t1.y==t2.y||t1.x==t2.x-1&&t1.y==t2.y-1||t1.x==t2.x+1&&t1.y==t2.y-1)
			{
				Pos(t1.x,t1.y," ");
				Pos(t2.x,t2.y," ");
				Pos(t2.x-1,t2.y-1," ");
				Pos(t2.x+1,t2.y-1," ");
				score++;
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
			if(t1.x==t3.x&&t1.y==t3.y)
			{
				Pos(t1.x,t1.y," ");
				Pos(t3.x,t3.y," ");
				check=true;
				break;
			}
			else mon_fires.push(t3);
		}
		if(check==false)
		fire.push(t1); 
	}
}
void Print_fire()
{
	int len1=fire.size();
	for(int i=1;i<=len1;i++)
	{
		Node t1=fire.front();
		fire.pop();
		Pos(t1.x,t1.y," ");
		t1.y--;
		if(t1.y<=1)continue;
		Pos(t1.x,t1.y,"$");
		fire.push(t1);
	}
}
void Print_monster()
{
	int len2=monsters.size();
	for(int i=1;i<=len2;i++)
	{
		Node t2=monsters.front();
		monsters.pop();
		mp[t2.x][t2.y]=0;
		mp[t2.x-1][t2.y-1]=0;
		mp[t2.x+1][t2.y-1]=0;
		Pos(t2.x,t2.y," ");
		Pos(t2.x-1,t2.y-1," ");
		Pos(t2.x+1,t2.y-1," ");
		t2.y+=1;
		if(t2.y>=30)continue;
		mp[t2.x][t2.y]=1;
		mp[t2.x-1][t2.y-1]=1;
		mp[t2.x+1][t2.y-1]=1;
		Pos(t2.x,t2.y,"T");
		Pos(t2.x-1,t2.y-1,"O");
		Pos(t2.x+1,t2.y-1,"O");
		monsters.push(t2);
		int sign=rand()%30+1;
		if(sign%8==0)
		{
			Node paodan;
			paodan.x=t2.x;
			paodan.y=t2.y+1;
			mon_fires.push(paodan);
		}
	}
}
void Print_mon_fires()
{
	int len3=mon_fires.size();
	for(int i=1;i<=len3;i++)
	{
		Node t3=mon_fires.front();
		mon_fires.pop();
		Pos(t3.x,t3.y," ");
		t3.y++;
		if(t3.y>29)continue;
		Pos(t3.x,t3.y,"V");
		mon_fires.push(t3);
	}
}
void Scores()
{
	Pos(60,15,"Q发射炮弹    SCORES=");
	cout<<score;
}
bool Life()
{
	int len2=monsters.size();
	int len3=mon_fires.size();
	int i;
	for(i=1;i<=len2;i++)
	{
		Node t2=monsters.front();
		monsters.pop();
		if(t2.x==x&&t2.y==y||t2.x==x-1&&t2.y==y+1||t2.x==x+1&&t2.y==y+1)
		return false;
		monsters.push(t2);
	}
	for(i=1;i<=len3;i++)
	{
		Node t3=mon_fires.front();
		mon_fires.pop();
		if(t3.x==x&&t3.y==y||t3.x==x-1&&t3.y==y+1||t3.x==x+1&&t3.y==y+1)
		return false;
		mon_fires.push(t3);
	}
	return true;
}
void Init()
{
	memset(mp,0,sizeof(mp));
	srand( (unsigned)time( NULL ) ); //初始化随机数
	score=0;
	gam=true;
	int i;
	for(i=1;i<=50;i++)
	{
		Pos(i,1,"O"),Pos(i,30,"O");	
	}
	for(i=1;i<=30;i++)
	{
		Pos(1,i,"O"),Pos(50,i,"O");	
	}
	score=0;
	while(!fire.empty())
	fire.pop();
	while(!monsters.empty())
	monsters.pop();
	while(!mon_fires.empty())
	mon_fires.pop();
}
int main()
{
read:
	system("cls");
	Init();
	x=25,y=28;
	Planes(25,28,2);
	char co;	
	tim=0;
	while(true)
	{
		if(monsters.size()<5)
		{
			int check=rand()%20+1;
			if(check%5==0)continue;
			Node t;
			int x0=rand()%48+2;
			if(x0<=2||x0>=48)continue;
			if(mp[x0][3]==0&&mp[x0-1][2]==0&&mp[x0+1][2]==0)
			{
				t.x=x0;
				t.y=3;
				mp[x0][3]=1;
				mp[x0-1][2]=1;
				mp[x0+1][2]=1;
				monsters.push(t);
			}
		}
		if(kbhit())
		{
			co=getch();
			if(co=='P')
			{
				Node t;
				t.x=x,t.y=y-1;
				fire.push(t);
			}
			else{
				Planes(x,y,1);
				if(co=='W')
				{
					if(y>2)
					y--;
				}
				else if(co=='S')
				{
					if(y<28)
					y++;
				}
				else if(co=='A')
				{
					if(x>3)
					x--;
				}
				else if(co=='D')
				{
					if(x<48)
					x++;
				}
				Planes(x,y,2);
			}
		}
		
		if(tim%2==0)
		Print_fire();
		
		if(fire.size()>0)
		Change();
		
		if(tim%10==0)
		Print_monster();
		if(tim%2==0)
		Print_mon_fires();
		Scores();
		if(Life()==false)
		break;
		Sleep(50);
		tim%=100000;
		tim++;
	}
	system("cls");
	cout<<"GAME_OVER!!! SCORES="<<score<<endl;
	cout<<"Do you want play the game again?"<<endl;
	cout<<"please input yes or no"<<endl;
	char s[100];
	scanf("%s",s);
	if(strcmp(s,"YES")==0)
	goto read; 
	return 0;
}
