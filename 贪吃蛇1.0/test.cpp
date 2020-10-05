#include<iostream>
#include<windows.h>
#include<vector>
#include<conio.h>
#include<time.h>
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)
//在指定位置显示内容 
void gotoxy(int x,int y,char c)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo; //variablendklaration
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut,&csbiInfo);
	csbiInfo.dwCursorPosition.X = x; //cursorposition X koordinate festlegen
	csbiInfo.dwCursorPosition.Y = y; //cursorposition Y koordinate festlegen
	SetConsoleCursorPosition(hConsoleOut,csbiInfo.dwCursorPosition); //den cursor an die festgelegte koordinate setzen
	printf("%c",c);//输出你指定的字符 
}  
int X1=1,Y1=1;//活动范围的左上角坐标
int X2=60,Y2=30;//活动范围的右下角坐标
struct Snake
{
	int x,y;
};
vector<Snake>snake;
void init()//初始化函数 
{ 
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	for(int i=X1;i<=X2;i++)
	{
		gotoxy(i,Y1,'#');
		gotoxy(i,Y2,'#');
	}
	for(int j=Y1;j<=Y2;j++)
	{
		gotoxy(X1,j,'#');
		gotoxy(X2,j,'#');
	}
	snake.clear();//初始化清空	
	Snake t;
	t.x=(X1+X2)/2;
	t.y=(Y1+Y2)/2;
	snake.push_back(t);
} 
//更新的位置，上下左右 
int XX[4]={0,0,-1,1};
int YY[4]={-1,1,0,0};
int food_x,food_y; 
bool search(int L,int R)
{
	if(L>R)return false;
	int MID=random(L,R);
	int d=X2-X1-1;//不能包括围墙，需要把围墙的宽度减去 
	int y=(MID+d)/d+X1;
	int t=MID%d;
	int x=Y1;
	if(t==0)
	x+=d;
	else x+=t; 
	bool flag=false;
	for(int i=0;i<snake.size();i++)
	{
		if(snake[i].x==x&&snake[i].y==y)
		{
			flag=true;
			break;
		}
	}
	if(flag)
	{
		bool res=search(L,MID-1);
		if(res)return true;
		res=search(MID+1,R);
		if(res)return true;
		return false;
	}
	else 
	{
		food_x=x;
		food_y=y;
		return true;
	}
}
void Print(int direction)//显示蛇的内容
{
	int n=snake.size()-1;
	gotoxy(snake[n].x,snake[n].y,' ');//先清除蛇尾留下的痕迹 
	for(int i=n;i>=1;i--)
	snake[i]=snake[i-1];//进行节点更新
	snake[0].x+=XX[direction];
	snake[0].y+=YY[direction]; 
	for(int i=1;i<=n;i++)
	gotoxy(snake[i].x,snake[i].y,'*');
	gotoxy(snake[0].x,snake[0].y,'@');//蛇头用@表示 
	gotoxy(food_x,food_y,'O');
} 
bool game_over()
{
	for(int i=1;i<snake.size();i++)
	{
		if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y)return false;
	}
	if(snake[0].x>=X2||snake[0].x<=X1)return false;
	if(snake[0].y>=Y2||snake[0].y<=Y1)return false;
	return true;
}
int main()
{
	init();
	int direction=1;
	bool is_food=false;
	while(true)
	{

		if(is_food==false)
		{
			search((X1+2)*(Y1+2),(X2-2)*(Y2-2));
			is_food=true;
		}
		if(snake[0].x==food_x&&snake[0].y==food_y)
		{
			Snake t;
			t.x=food_x,t.y=food_y;
			is_food=false;
			snake.insert(snake.begin(),t);
		}
		Print(direction);		
		if(game_over()==false)
		{
			gotoxy(X1,Y2+1,' ');
			cout<<"游戏结束！！！\n";
			return 0;
		}
		if(kbhit())//判断有键盘指令输入 
		{
			char c=getch();
			if(c=='W')//往上 
			direction=0;
			else if(c=='S')//往下 
			direction=1;
			else if(c=='A')//往左 
			direction=2;
			else if(c=='D')//往右 
			direction=3;
		}
		gotoxy((X1+X2)/2,Y2+2,' ');//为了不在游戏界面中显示白色光标影响界面效果
		cout<<"当前得分："<<snake.size()*10<<endl;
		Sleep(150);//延迟150ms，控制程序显示时间	
	} 
	return 0;
} 
