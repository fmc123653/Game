#include<graphics.h>
#include<iostream>
#include<time.h>
#include<conio.h>
#include<vector>
using namespace std;
#define random(a,b) (rand()%(b-a+1)+a)
struct Snake
{
	int x,y;
};
vector<Snake>snake;
//全局变量，蛇头蛇身
IMAGE head_1,head_2,body_1,body_2,food_1,food_2;
int food_x,food_y;
void Move()
{
	//打印食物
	putimage(food_x,food_y,&food_2, SRCAND);
	putimage(food_x,food_y,&food_1, SRCPAINT);
	//打印蛇的图像
	putimage(snake[0].x,snake[0].y,&head_2, SRCAND);
	putimage(snake[0].x,snake[0].y,&head_1, SRCPAINT);
	int i;
	for(i=1;i<snake.size();i++)
	{
		putimage(snake[i].x,snake[i].y,&body_2, SRCAND);
		putimage(snake[i].x,snake[i].y,&body_1, SRCPAINT);
	}

}
//更新的位置，上下左右 
int XX[4]={0,0,-50,50};
int YY[4]={-50,50,0,0};
int direction;
void Update_Move()//改变蛇的运动
{
	int i;
	for(i=snake.size()-1;i>0;i--)
		snake[i]=snake[i-1];
	snake[0].x+=XX[direction];
	snake[0].y+=YY[direction];
}
bool is_food;
int X1=0,Y1=0;//活动范围的左上角坐标
int X2=20,Y2=12;//活动范围的右下角坐标
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
		if(snake[i].x==50*x&&snake[i].y==50*y)
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
		food_x=50*x;
		food_y=50*y;
		return true;
	}
}
void init()//初始化
{
	srand((int)time(0));  // 产生随机种子  把0换成NULL也行
	//初始化
	Snake t;
	t.x=50,t.y=300;
	snake.push_back(t);
	t.x=0,t.y=300;
	snake.push_back(t);
	direction=1;//初始化一个方向
	is_food=false;//表示当前是否有食物
}
bool game_over()
{
	if(snake[0].x<0||snake[0].x>1000-50)return true;
	if(snake[0].y<0||snake[0].y>600-50)return true;
	int i;
	for(i=1;i<snake.size();i++)
	{
		if(snake[0].x==snake[i].x&&snake[0].y==snake[i].y)return true;
	}
	return false;
}
int main()
{
	initgraph(1000,600);
	IMAGE bg;
	//加载对应的图片
	loadimage(&bg,_T("pictures\\bg.jpg"),1000,600);	
	loadimage(&head_1,_T("pictures\\head_1.jpg"),50,50);
	loadimage(&head_2,_T("pictures\\head_2.jpg"),50,50);//
	loadimage(&body_1,_T("pictures\\body_1.jpg"),50,50);
	loadimage(&body_2,_T("pictures\\body_2.jpg"),50,50);//
	loadimage(&food_1,_T("pictures\\food_1.jpg"),50,50);
	loadimage(&food_2,_T("pictures\\food_2.jpg"),50,50);//
	init();
	while(true)
	{
		BeginBatchDraw();//开始批量绘图，这样可以让图片显示比较流畅
		putimage(0,0,&bg);
		if(is_food==false)
		{
			search((X1+2)*(Y1+2),(X2-2)*(Y2-2));
			is_food=true;
		}
		Update_Move();
		Move();	
		if(game_over())
		{
			break;
		}
		if(snake[0].x==food_x&&snake[0].y==food_y)
		{
			Snake t;
			t.x=food_x,t.y=food_y;
			is_food=false;
			snake.insert(snake.begin(),t);
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
		
		////////////////////
		EndBatchDraw(); 
		Sleep(200);
	}
	closegraph();//关闭画布
	cout<<"GAME OVER!!!\n";
	getch();
	getch();
	return 0;
}