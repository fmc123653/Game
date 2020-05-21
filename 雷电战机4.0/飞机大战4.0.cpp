#include<graphics.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
#include<iostream>
#include<queue>
#include<string>
#include<time.h>
#include<stack>
#include <fstream> 
#include<math.h>
using namespace std;
#include "Mmsystem.h"
#pragma comment(lib,"Winmm.lib")
struct Node{
	int x,y;
	int cind,dis;
	int key;
	int plane_sign;
}; 
struct Pao{
int x,y,dp;
};
queue<Node>fire;
queue<Node>monsters,mon_fires;
queue<Pao>paohui;
int x,y,life,score,tim;
int shoot_po,music_ans;
int xx,yy,zhiyuan_dp,zhiyuan_sign,help_ans;
int come_time;
bool zhiyuan_come;
void Print_zhiyuan(int co)
{
	if(co==1)
	{
		if(yy>=400)
		yy-=5;
	}
	else if(co==2)
	{
		if(yy>=600)
			return;
		yy+=5;
	}
	IMAGE img1,img2;
	if(zhiyuan_dp<=0)
	{
		if(xx>x)
		zhiyuan_sign=1;
		else zhiyuan_sign=2;
		zhiyuan_dp=200;
	}
	zhiyuan_dp-=2;
	if(zhiyuan_sign==2)
		xx+=2;
	else if(zhiyuan_sign==1)
		xx-=2;
	if(xx>=950)
		xx-=2;
	if(xx<=0)
		xx+=2;
	loadimage(&img1,_T("pictures\\zhiyuan.jpg"),50,60);//
	loadimage(&img2,_T("pictures\\zhiyuana.jpg"),50,60);//
	putimage(xx,yy,&img2, SRCAND);
	putimage(xx,yy,&img1, SRCPAINT);
	if(tim%20==0)
	{
		Node zhiyuan_fire;
		zhiyuan_fire.x=xx;
		zhiyuan_fire.y=yy-70;
		zhiyuan_fire.key=2;
		fire.push(zhiyuan_fire);
	}
}
void Print_fire()
{
	
	int len1=fire.size();
	for(int i=1;i<=len1;i++)
	{
		Node t1=fire.front();
		fire.pop();
		if(tim%2==0)
		t1.y-=10;
		if(t1.y<=10)
		{
			continue;
		}
		IMAGE img1,img2;
		if(t1.key==1)
		{
			
			loadimage(&img1,_T("pictures\\shoot2.jpg"),150,30);//
			loadimage(&img2,_T("pictures\\shoot2a.jpg"),150,30);//
			putimage(t1.x-50,t1.y,&img2, SRCAND);
			putimage(t1.x-50,t1.y,&img1, SRCPAINT);
		}
		else if(t1.key==0)
		{
		
			loadimage(&img1,_T("pictures\\fire1.jpg"),50,60);//
			loadimage(&img2,_T("pictures\\fire2.jpg"),50,60);//WWWW
			putimage(t1.x,t1.y,&img2, SRCAND);
			putimage(t1.x,t1.y,&img1, SRCPAINT);
		}
		else if(t1.key==2)
		{
			loadimage(&img1,_T("pictures\\zhiyuan_fire.jpg"),50,60);//
			loadimage(&img2,_T("pictures\\zhiyuan_firea.jpg"),50,60);//WWWW
			putimage(t1.x,t1.y,&img2, SRCAND);
			putimage(t1.x,t1.y,&img1, SRCPAINT);
		}
		fire.push(t1);
	}
}
int lf,rf,down,cind;
void Print_monster()
{
	int len2=monsters.size();
	IMAGE img1,img2;
	for(int i=1;i<=len2;i++)
	{
		Node t2=monsters.front();
		monsters.pop();

		if(t2.cind==0)
		{
			int find=rand()%100+1;
			if(find%7==0)
			{
				t2.dis=100;
				t2.cind=7;
			}
			else if(find%5==0)
			{
				t2.dis=100;
				t2.cind=5;
			}
			else{
				t2.dis=50;
				t2.cind=2;
			}
		}
		if(t2.cind==2)
		{
			if(t2.dis<=0)
				t2.cind=0;
			else{
				t2.dis--;
				t2.y++;
			}
		}
		else if(t2.cind==7)
		{
			if(t2.dis<=0)
				t2.cind=0;
			else{
				t2.dis--;
				t2.x+=2;
				t2.y++;
			}
		}
		else if(t2.cind==5)
		{
			if(t2.dis<=0)
				t2.cind=0;
			else{
				t2.dis--;
				t2.x-=2;
				t2.y++;
			}
		}
		if(t2.x<=10)continue;
		if(t2.x>=940)continue;
		if(t2.y>540)continue;
		if(t2.plane_sign==1)
		{
			loadimage(&img1,_T("pictures\\monsters1.jpg"),50,60);//
			loadimage(&img2,_T("pictures\\monsters2.jpg"),50,60);//
		}
		else if(t2.plane_sign==2)
		{
			loadimage(&img1,_T("pictures\\monsters3.jpg"),50,60);//
			loadimage(&img2,_T("pictures\\monsters3a.jpg"),50,60);//
		}
		putimage(t2.x,t2.y,&img2, SRCAND);
		putimage(t2.x,t2.y,&img1, SRCPAINT);
		monsters.push(t2);
		if(tim%20==0)
		{
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
		if(abs(x-t2.x)<=50&&abs(y-t2.y)<=60)
		{
			//paohui
			Pao pao;
			pao.x=t2.x-20;
			pao.y=t2.y-10;
			pao.dp=1;
			paohui.push(pao);
			life-=5;

			char list[100];
			sprintf(list,"open musics\\paohui.mp3 alias BackMusic%d",music_ans);
			mciSendString(list, NULL, 0, NULL); // 打开音乐
			sprintf(list,"setaudio BackMusic%d volume to 300",music_ans);
			mciSendString(list,NULL,0,NULL);		//设置音量大小
			sprintf(list,"play BackMusic%d from 0",music_ans);
			mciSendString(list, NULL, 0, NULL);	
			music_ans++;
			music_ans%=1000;

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
			life-=10;
			char list[100];
			sprintf(list,"open musics\\paohui.mp3 alias BackMusic%d",music_ans);
			mciSendString(list, NULL, 0, NULL); // 打开音乐
			sprintf(list,"setaudio BackMusic%d volume to 300",music_ans);
			mciSendString(list,NULL,0,NULL);		//设置音量大小
			sprintf(list,"play BackMusic%d from 0",music_ans);
			mciSendString(list, NULL, 0, NULL);	
			music_ans++;
			music_ans%=1000;
			
			//paohui
			Pao pao;
			pao.x=t3.x-20;
			pao.y=t3.y-10;
			pao.dp=1;
			paohui.push(pao);	
			break;
		}
		else mon_fires.push(t3);
	}
}
int huoyan_ans;
bool up_check,zy_check;
void Plane(int x,int y)
{
	IMAGE img1,img2;
	
	loadimage(&img1,_T("pictures\\plane1.jpg"),50,60);//
	loadimage(&img2,_T("pictures\\plane2.jpg"),50,60);//
	putimage(x,y,&img2, SRCAND);
	putimage(x,y,&img1, SRCPAINT);	
	huoyan_ans++;

	IMAGE img3,img4;
	int width=30;
	if(huoyan_ans<=10)
	{
		if(up_check)
		{
			loadimage(&img3,_T("pictures\\huoyan3.jpg"),30,50);//
			loadimage(&img4,_T("pictures\\huoyan3a.jpg"),30,50);//
		}
		else
		{
			if(zy_check)
				width=40;
			else width=30;
			loadimage(&img3,_T("pictures\\huoyan1.jpg"),30,width);//
			loadimage(&img4,_T("pictures\\huoyan1a.jpg"),30,width);//
		}
		putimage(x+10,y+50,&img4, SRCAND);
		putimage(x+10,y+50,&img3, SRCPAINT);
	}
	else if(huoyan_ans>10&&huoyan_ans<=20)
	{
		if(up_check)
		{
			loadimage(&img3,_T("pictures\\huoyan4.jpg"),30,50);//
			loadimage(&img4,_T("pictures\\huoyan4a.jpg"),30,50);//
		}
		else
		{
			if(zy_check)
				width=40;
			else width=30;
			loadimage(&img3,_T("pictures\\huoyan2.jpg"),30,width);//
			loadimage(&img4,_T("pictures\\huoyan2a.jpg"),30,width);//
		}
		putimage(x+10,y+50,&img4, SRCAND);
		putimage(x+10,y+50,&img3, SRCPAINT);
	}
	huoyan_ans%=21;
}
void Print_mon_fires()
{
	int len3=mon_fires.size();
	int i;
	IMAGE img1,img2;
	for(i=1;i<=len3;i++)
	{
		Node t3=mon_fires.front();
		mon_fires.pop();
		if(tim%2==0)
		t3.y+=10;
		if(t3.y>540)
		{
			continue;
		}
		loadimage(&img1,_T("pictures\\mon_fire1.jpg"),50,60);//
		loadimage(&img2,_T("pictures\\mon_fire2.jpg"),50,60);//
		putimage(t3.x,t3.y,&img2, SRCAND);
		putimage(t3.x,t3.y,&img1, SRCPAINT);

		mon_fires.push(t3);
	}
}
void Change()
{
	int len1,len2,len3;
	int i,j;
	len1=fire.size();
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
			bool shoot_go=false;
			if(t1.key==0)
			{
				if(t1.y-t2.y>=0&&t1.y-t2.y<=60&&abs(t1.x-t2.x)<=45)
					shoot_go=true;
			}
			else if(t1.key==1)
			{
				if(t1.y-t2.y>=0&&t1.y-t2.y<=45&&abs(t1.x-t2.x)<=100)
					shoot_go=true;
			}
			else if(t1.key==2)
			{
				if(t1.y-t2.y>=0&&t1.y-t2.y<=45&&abs(t1.x-t2.x)<=40)
					shoot_go=true;
			}
			if(shoot_go)
			{
				if(zhiyuan_come==false)
					help_ans+=10;
				char list[100];
				sprintf(list,"open musics\\paohui.mp3 alias BackMusic%d",music_ans);
				mciSendString(list, NULL, 0, NULL); // 打开音乐
				sprintf(list,"setaudio BackMusic%d volume to 300",music_ans);
				mciSendString(list,NULL,0,NULL);		//设置音量大小
				sprintf(list,"play BackMusic%d from 0",music_ans);
				mciSendString(list, NULL, 0, NULL);	
				music_ans++;
				music_ans%=1000;
				
				//paohui
				Pao pao;
				pao.x=t2.x-20;
				pao.y=t2.y-10;
				pao.dp=1;
				paohui.push(pao);				
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

			bool shoot_go=false;
			if(t1.key==0)
			{
				if(t1.y-t3.y<=60&&abs(t1.x-t3.x)<=45)
					shoot_go=true;
			}
			else if(t1.key==1)
			{
				if(t1.y-t3.y<=45&&abs(t1.x-t3.x)<=100)
					shoot_go=true;
			}
			if(shoot_go)
			{
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
	char HPtext[50],MPtext[50],HELPtext[50];
	sprintf(HPtext,"HP       %d/%d",life,100);
	sprintf(MPtext,"SCORE    %d",score*100);
	sprintf(HELPtext,"HELP");

	rectangle(7,11,120,31);
	rectangle(7,32,120,52);
	rectangle(800,11,980,31);
	setfillcolor(BLUE);
	solidrectangle(802,12,826+help_ans,30);
	setfillcolor(RED);
	solidrectangle(9,12,18+life,30);
	setfillcolor(BLACK);
	solidrectangle(9,33,119,51);
	outtextxy(9,13,HPtext);
	outtextxy(9,35,MPtext);
	outtextxy(802,13,HELPtext);
}
void Paohui()
{
	int len=paohui.size();
	int x0,y0;
	x0=100,y0=120;
	IMAGE img1,img2;
	for(int i=1;i<=len;i++)
	{
		Pao pao=paohui.front();
		paohui.pop();
		if(pao.dp==1)
		{
				loadimage(&img1,_T("pictures\\hui1.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui1a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==2)
		{
				loadimage(&img1,_T("pictures\\hui2.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui2a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==3)
		{
				loadimage(&img1,_T("pictures\\hui3.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui3a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==4)
		{
				loadimage(&img1,_T("pictures\\hui4.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui4a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==5)
		{
				loadimage(&img1,_T("pictures\\hui5.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui5a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==6)
		{
				loadimage(&img1,_T("pictures\\hui6.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui6a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==7)
		{
				loadimage(&img1,_T("pictures\\hui7.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui7a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp==8)
		{
				loadimage(&img1,_T("pictures\\hui8.jpg"),x0,y0);
				loadimage(&img2,_T("pictures\\hui8a.jpg"),x0,y0);//
				putimage(pao.x,pao.y,&img2, SRCAND);
				putimage(pao.x,pao.y,&img1, SRCPAINT);
		}
		else if(pao.dp>8)continue;



		if(tim%10==0)
		pao.dp++;
		paohui.push(pao);
	}
}
int shoot_ans;
bool zanting;
bool light_check;
void GetCommand()
{
	if(GetAsyncKeyState(VK_ESCAPE) & 0x8000) {exit(0);}	
	if(GetAsyncKeyState('W') & 0x8000)
	{
		y-=3;
		up_check=true;
	}
	else up_check=false;
	if(GetAsyncKeyState('S') & 0x8000) y+=3;
	if(GetAsyncKeyState('A') & 0x8000)
	{
		x-=3;
		zy_check=true;
	}
	if(GetAsyncKeyState('D') & 0x8000)
	{
		x+=3;
		zy_check=true;
	}
	if((GetAsyncKeyState('D') & 0x8000)==false &&(GetAsyncKeyState('A') & 0x8000)==false)
		zy_check=false;

	if(GetAsyncKeyState('Z') & 0x8000)
	{
			zanting=true;
	}
	if(GetAsyncKeyState('X') & 0x8000)
	{
			zanting=false;
	}
	if(GetAsyncKeyState('Q') & 0x8000) 
	{
		shoot_po=0;
	}
	if(GetAsyncKeyState('E') & 0x8000)
	{
		shoot_po=1;
	}
	if(GetAsyncKeyState('P') & 0x8000)
	{
		if(tim%5==0)
		{
			Node t;
			t.x=x,t.y=y-60;
			t.key=shoot_po;
			fire.push(t);
			char list[100];
			sprintf(list,"open musics\\shoot.mp3 alias shoot%d",shoot_ans);
			mciSendString(list, NULL, 0, NULL); // 打开音乐
			sprintf(list,"setaudio shoot%d volume to 300",shoot_ans);
			mciSendString(list,NULL,0,NULL);		//设置音量大小
			sprintf(list,"play shoot%d from 0",shoot_ans);
			mciSendString(list, NULL, 0, NULL);	
			shoot_ans++;
			shoot_ans%=1000;
		}
	}
	if(GetAsyncKeyState('L') & 0x8000)
		light_check=true;
}
int light_dp;
void Init()
{
	x=450;
	y=540;
	while(!fire.empty())
	fire.pop();
	while(!monsters.empty())
	monsters.pop();
	while(!mon_fires.empty())
	mon_fires.pop();
	tim=0;
	score=0;
	life=100;
	cind=0;
	music_ans=0;
	shoot_ans=0;
	shoot_po=0;
	zanting=false;
	huoyan_ans=0;
	up_check=false;
	zy_check=false;
	light_check=false;
	light_dp=0;
	xx=500;
	yy=600;
	zhiyuan_dp=0;
	help_ans=0;
	come_time=0;
	zhiyuan_come=false;
}
bool GameOver()				//游戏结束
{

	char gameovertext[256];
	int highest_score=0;
	ifstream cinfile("scores.txt"); 
    if (!cinfile.is_open()) 
    { 
        cout << "未成功打开文件" << endl; 
        return 0;
    }
	cinfile>>highest_score;
	if(score>highest_score) 
	{
		sprintf(gameovertext,"Game Over!\nScore:%d\nNew High Score!(Yes to Retry,No to Exit)",score);
		highest_score=score;
	}
	else 
	{
		sprintf(gameovertext,"Game Over!\nScore:%d\nHighest Score:%d\n(Yes to Retry,No to Exit)",score,highest_score);		
	}
	cinfile.close();
	ofstream coutfile("scores.txt"); 
	coutfile<<highest_score;
	coutfile.close();
	if(MessageBox(GetHWnd(),gameovertext,"Game Over",MB_YESNO)==IDYES)
		return true;
	else
		return false;
}
int main(int argc, _TCHAR* argv[])
{
	initgraph(1000,600);	
	mciSendString("open musics\\bgm.mp3 alias BackMusic", NULL, 0, NULL); // 打开音乐
	mciSendString("setaudio BackMusic volume to 600",NULL,0,NULL);		//设置音量大小
	mciSendString("play BackMusic repeat", NULL, 0, NULL);	
read:
	Init();
			//循环播放
	IMAGE bg;
	loadimage(&bg,_T("pictures\\bgphoto.jpg"),1000,600);
	while(true)
	{
		GetCommand();
		if(zanting)continue;
		BeginBatchDraw();
		if(monsters.size()<5)
		{
			int check=rand()%20+1;
			if(check%5==0)continue;
			Node t;
			int x0=rand()%800+2;
			if(x0<=0||x0>=950)continue;
			int plane_sign=rand()%10+1;
			if(plane_sign%2==0)
				t.plane_sign=1;
			else if(plane_sign%2==1)
				t.plane_sign=2;
			t.x=x0;
			t.y=1;
			t.cind=0;
			monsters.push(t);
		}
		putimage(0,0,&bg);
		Plane(x,y);
		if(help_ans>=150)
			zhiyuan_come=true;
		if(zhiyuan_come)
		{	
			Print_zhiyuan(1);
			if(tim%5==0)
			help_ans-=1;
		}
		else
		{
			Print_zhiyuan(2);
		}
		if(help_ans<=0)
		{
			help_ans=0;
			zhiyuan_come=false;
		}
		Print_fire();
		Change();
		Print_monster();
		Print_mon_fires();
		Life();
		Paohui();
		Score_Life();
		if(lifes>=100)
		{
			char ch[20]="GAME_OVER!!!";
			outtextxy(800,400,ch);
			break;
		}
		EndBatchDraw(); 
		Sleep(5);
		tim++;
		tim%=10000;
		if(life<=0)
		{
			if(GameOver())
				goto read;
			else return 0;
		}
	}
	closegraph();
	return 0;
}
