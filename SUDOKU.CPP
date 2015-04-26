#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h>
#include<dos.h>

union REGS i,o;
int area;

void logo();
void menugraphics();
void menu(int level);
int sudokuprobleminitial(int b[][9],int p,int q);
int sudokuproblemfinal(int b[][9]);
int cancelarray(int na[][9],int p,int q,int levelnum);
void sudokubar(int x,int y,int n);
int options(int x,int y);
int check(int n,int ca[][9],int r,int c);
void caution(int x,int y,int n);
void buildans(int x,int y,int n);
//void sudokuanss();
int click(/*int a1[][9],*/int b1[][9],int c1[][9]);
int checkfinish(int fa[][9]);
void getmousepos(int *button,int *x,int *y);
int checkans(int arr[][9]);
void incorrectsolution();
void problemset(int brr[][9],int arr[][9]);
void finishgame(int mv,int min,int sec);
void escape(int brr[][9],int arr[][9]);
//void *bitmap;


int initmouse(){
i.x.ax=0;
int86(0x33,&i,&o);
return (o.x.ax);
}

void showmouspointer(){
i.x.ax=1;
int86(0x33,&i,&o);
}

void getmousepos(int *button,int *x,int *y){
i.x.ax=3;
int86(0x33,&i,&o);
*button=o.x.bx;
*x=o.x.cx;
*y=o.x.dx;
}

int main(){
	clrscr();
	int gd=DETECT,gm;
	//,button,x,y,a[9][9],b[9][9],c[9][9];
	initgraph(&gd,&gm,"C:\\TurboC3\\BGI");
	initmouse();
	showmouspointer();
	logo();
	//menugraphics();
	//menu();
	/*sudokuprobleminitial(a,9,9);
	sudokuproblemfinal(a);
	for(int i=0;i<9;i++)
		for(int j=0;j<9;j++){
			b[i][j]=a[i][j];
		}
	cancelarray(b,9,9);
	for(i=0;i<9;i++)
		for(j=0;j<9;j++){
			c[i][j]=b[i][j];
		}
	click(b,c);*/
	//getch();
	return 0;
}

void logo(){
//settextjustify(CENTER_TEXT,CENTER_TEXT);
settextstyle(1,0,10);
setbkcolor(9);
setcolor(1);
//outtextxy("SUDOKU");

outtextxy(10,90,"S");
delay(150);
outtextxy(70,90,"U");
delay(150);
outtextxy(130,90,"D");
delay(150);
outtextxy(190,90,"O");
delay(150);
outtextxy(250,90,"K");
delay(150);
outtextxy(310,90,"U");
delay(150);
int array[]={420,240,630,240,600,450,390,450,420,240};
setcolor(BLACK);
fillpoly(5,array);
line(490,240,460,450);
line(560,240,530,450);
line(410,310,620,310);
line(400,380,610,380);
setfillstyle(SOLID_FILL,BLUE);
floodfill(500,250,BLACK);
floodfill(430,250,BLACK);
floodfill(410,320,BLACK);
floodfill(590,440,BLACK);

setcolor(BLUE);
settextstyle(0,0,1);
outtextxy(10,450,"Press any key to start the game.");
//outtextxy(44,105,"SUDOKU");
getch();
//delay(2000);
menugraphics();
}

void menugraphics(){
//char ch[]={'S','U','D','O','K','U'},c;
int j,button,x,y;
char ch;
/*for(j=25;j<520;j=j+95){
	for(int i=0;i<101;i=i+10){
		c=ch[k];
		outtextxy(j,i,c);
		clearviewport();
		printf("%c",c);
	}
	k++;
}*/

cleardevice();
setfillstyle(SOLID_FILL,BLUE);
setcolor(14);
settextstyle(7,0,0);
bar3d(220,100,420,140,3,1);
bar3d(265,160,375,200,3,1);
bar3d(265,220,375,260,3,1);
bar3d(265,280,375,320,3,1);
setcolor(RED);
outtextxy(225,100,"PLAY GAME");
outtextxy(275,160,"HELP");
outtextxy(270,220,"ABOUT");
outtextxy(275,280,"EXIT");

//outtextxy(85,286,"GAME DEVELOPMENT BY SADMAN");


//bar3d(220,300,400,350,3,1);
//outtextxy(44,105,"SUDOKU");
/*getmousepos(&button,&x,&y);
int tempx,tempy;
tempx=x;
tempy=y;*/
/*The objective of the game is to fill all the blank squares in a game with the correct numbers. There are three very simple constraints to follow. In a 9 by 9 square Sudoku game:
Every row of 9 numbers must include all digits 1 through 9 in any order
Every column of 9 numbers must include all digits 1 through 9 in any order
Every 3 by 3 subsection of the 9 by 9 square must include all digits 1 through 9*/
while(!kbhit()){
	setcolor(BLACK);
	getmousepos(&button,&x,&y);
	if(button==1&&x>220&&x<420&&y>100&&y<140){
		button=-1;
		cleardevice();
		settextstyle(0,0,2);
		setfillstyle(SOLID_FILL,BLUE);
		setcolor(14);
		bar3d(280,100,360,140,3,1);
		bar3d(260,160,380,200,3,1);
		bar3d(280,220,360,260,3,1);
		bar3d(280,280,360,320,3,1);
		outtextxy(290,110,"EASY");
		outtextxy(270,170,"MEDIUM");
		outtextxy(290,230,"HARD");
		outtextxy(290,290,"BACK");
		delay(150);
		while(!kbhit()){
			getmousepos(&button,&x,&y);
			if(button==1&&x>280&&x<360&&y>100&&y<140){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(3);
			}
			else if(button==1&&x>260&&x<380&&y>160&&y<200){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(4);
			}
			else if(button==1&&x>280&&x<360&&y>220&&y<260){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(5);
			}
			else if(button==1&&x>280&&x<360&&y>280&&y<320){
				button=-1;
				delay(100);
				menugraphics();
			}
		/*setbkcolor(8);
		setfillstyle(SOLID_FILL,7);
		bar(93,0,545,452);
		menu();*/
		}
	}
	else if(button==1&&x>265&&x<375&&y>160&&y<200){
		cleardevice();
		settextstyle(0,0,1);
		setcolor(BLUE);
		outtextxy(10,50,"The objective of the game is to fill all the blank squares in a game with the");
		outtextxy(10,60,"correct numbers. There are three very simple constraints to follow.");
		outtextxy(10,70,"In a 9 by 9 square Sudoku game:");
		outtextxy(30,80,"* Every row of 9 numbers must include all digits 1 through 9 in any order");
		outtextxy(30,90,"* Every column of 9 numbers must include all digits 1 through 9 in any order");
		outtextxy(30,100,"* Every 3 by 3 subsection of the 9 by 9 square must include all digits 1 ");
		outtextxy(10,110,"through 9.");
		outtextxy(200,455,"Press ESC to go to the main menu.");
		delay(100);
		while((ch=getch())==27){
			cleardevice();
			menugraphics();
		}
	}
	else if(button==1&&x>265&&x<375&&y>220&&y<260){
		cleardevice();
		settextstyle(0,0,1);
		setcolor(BLUE);
		outtextxy(220,100,"VERSION : SUDOKU IN C");
		outtextxy(220,110,"COPYRIGHT © 2011 BY SADMAN ILHAM");
		outtextxy(220,120,"sadman.ilham@yahoo.com");
		outtextxy(200,455,"Press ESC to go to the main menu.");
		delay(100);
		while((ch=getch())==27){
			cleardevice();
			menugraphics();
		}
	}
	else if(button==1&&x>265&&x<375&&y>280&&y<320){
		button=-1;
		delay(100);
		exit(0);
	}
}

//getch();
}


void menu(int level){
int a[9][9],b[9][9],c[9][9];
sudokuprobleminitial(a,9,9);
sudokuproblemfinal(a);
for(int i=0;i<9;i++)
	for(int j=0;j<9;j++){
		b[i][j]=a[i][j];
	}
cancelarray(b,9,9,level);
for(i=0;i<9;i++)
	for(j=0;j<9;j++){
		c[i][j]=b[i][j];
	}
settextstyle(0,0,1);
outtextxy(103,458,"Press ESC to go to the menu.");
click(b,c);
}


int sudokuprobleminitial(int b[][9],int p,int q){

	int i,j,k,l,m=0,n;

	for(k=0;k<3;k++){
		if(k==0)
			l=0;
		else if(k==1)
		  l=3;
		else if(k==2)
		  l=6;
		for(j=k;j<9;j=j+3){
			for(i=0;i<3;i++){
				if(l==9)
					l=0;
				if(m==9)
					m=0;
				b[l][j]=++m;
				l++;
			}
		}
	}

	m=1;
	for(k=1;k<4;k++){
		if(k==1){
			n=1;
			l=0;
		}
		else if(k==2){
			n=2;
			l=3;
		}
		else if(k==3){
			n=0;
			l=6;
		}
		for(j=n;j<9;j=j+3){
			for(i=0;i<3;i++){
				if(i==0){
					if(m==7)
						m=m-6;
					else
						m=m+3;
					}
				else if(i==2)
						m=m-3;
				if(l==9)
					l=0;
				if(m==9)
					m=0;
				b[l][j]=++m;
				l++;
			}
		}
	}

	for(k=0;k<3;k++){
		if(k==0){
			n=2;
			l=0;
			m=8;
		}
		else if(k==1){
			n=0;
			l=3;
			m=8;
		}
		else if(k==2){
			n=1;
			l=6;
			m=8;
		}
		for(j=n;j<9;j=j+3){
			for(i=0;i<3;i++){
				if(i==1)
					m=m-3;
				if(l==9)
					l=0;
				if(m==8&&j!=n)
					m=m-6;
				if(m==2&&j==n+6)
					m=m+3;
				b[l][j]=++m;
				l++;
			}
		}
	}

	return b[p][q];

}




int sudokuproblemfinal(int b[][9]){

	int i,j;
	int r1,r2,c[9],a;
	srand(time(NULL));

	for(a=0;a<3;a++){
	L:if(a==0){
	r1=rand()%3;
	r2=rand()%3;
	if(r1==r2)
		goto L;
	}
	else if(a==1){
	r1=rand()%6;
	r2=rand()%6;
	if(r1==r2)
		goto L;
	if(r1>5||r1<3)
		goto L;
	if(r2>5||r2<3)
		goto L;
	}
	else if(a==2){
	r1=rand()%9;
	r2=rand()%9;
	if(r1==r2)
		goto L;
	if(r1<6||r2<6)
		goto L;
	}
	for(i=0;i<9;i++){
		c[i]=b[i][r1];
		b[i][r1]=b[i][r2];
		b[i][r2]=c[i];
	}
	}

	for(a=0;a<3;a++){
	M:if(a==0){
	r1=rand()%3;
	r2=rand()%3;
	if(r1==r2)
		goto M;
	}
	else if(a==1){
	r1=rand()%6;
	r2=rand()%6;
	if(r1==r2)
		goto M;
	if(r1>5||r1<3)
		goto M;
	if(r2>5||r2<3)
		goto M;
	}
	else if(a==2){
	r1=rand()%9;
	r2=rand()%9;
	if(r1==r2)
		goto M;
	if(r1<6||r2<6)
		goto M;
	}
	for(i=0;i<9;i++){
		c[i]=b[r1][i];
		b[r1][i]=b[r2][i];
		b[r2][i]=c[i];
	}
	}
return 0;
}

int cancelarray(int na[][9],int p,int q,int levelnum){

	if(levelnum==3){
	int r3,r4,r5,x1=103,y1=10;

	for(int i=0;i<p;i++){
	K:
	r3=rand()%9;
	r4=rand()%9;
	r5=rand()%9;
	if(r3==r4||r3==r5||r4==r5)
		goto K;

	for(int j=0;j<q;j++){
		if(j==r3||j==r4||j==r5){
		//printf("_\t");
		na[i][j]=0;
		sudokubar(x1,y1,0);
		x1=x1+48;
		continue;
		}
	//printf("%d\t",b[i][j]);
	sudokubar(x1,y1,na[i][j]);
	x1=x1+48;
	}
	y1=y1+48;
	x1=103;
	}
	}
	else if(levelnum==4){
		int r3,r4,r5,r6,x1=103,y1=10;

		for(int i=0;i<p;i++){
		L:
		r3=rand()%9;
		r4=rand()%9;
		r5=rand()%9;
		r6=rand()%9;
		if(r3==r4||r3==r5||r4==r5||r5==r6||r3==r6||r4==r6)
			goto L;

		for(int j=0;j<q;j++){
			if(j==r3||j==r4||j==r5||j==r6){
			//printf("_\t");
			na[i][j]=0;
			sudokubar(x1,y1,0);
			x1=x1+48;
			continue;
			}
		//printf("%d\t",b[i][j]);
		sudokubar(x1,y1,na[i][j]);
		x1=x1+48;
		}
		y1=y1+48;
		x1=103;
		}
	}
	else if(levelnum==5){
		int r3,r4,r5,r6,r7,x1=103,y1=10;

	for(int i=0;i<p;i++){
	M:
	r3=rand()%9;
	r4=rand()%9;
	r5=rand()%9;
	r6=rand()%9;
	r7=rand()%9;
	if(r3==r4||r3==r5||r4==r5||r5==r6||r3==r6||r3==r7||r4==r6||r4==r7||r5==r7||r6==r7)
		goto M;

	for(int j=0;j<q;j++){
		if(j==r3||j==r4||j==r5||j==r6||j==r7){
		//printf("_\t");
		na[i][j]=0;
		sudokubar(x1,y1,0);
		x1=x1+48;
		continue;
		}
	//printf("%d\t",b[i][j]);
	sudokubar(x1,y1,na[i][j]);
	x1=x1+48;
	}
	y1=y1+48;
	x1=103;
	}
	}
	/*int r3,r4,r5,r6,x1=103,y1=10;

	for(int i=0;i<p;i++){
	K:
	r3=rand()%9;
	r4=rand()%9;
	r5=rand()%9;
	r6=rand()%9;
	if(r3==r4||r3==r5||r4==r5||r5==r6||r3==r6||r4==r6)
		goto K;

	for(int j=0;j<q;j++){
		if(j==r3||j==r4||j==r5||j==r6){
		//printf("_\t");
		na[i][j]=0;
		sudokubar(x1,y1,0);
		x1=x1+48;
		continue;
		}
	//printf("%d\t",b[i][j]);
	sudokubar(x1,y1,na[i][j]);
	x1=x1+48;
	}
	y1=y1+48;
	x1=103;
	}*/
	//sudokuanss();
	setcolor(RED);
	line(144+103,0,144+103,452);
	line(288+103,0,288+103,452);
	line(93,154,432+113,154);
	line(93,298,432+113,298);

return 0;
}

//making the 9X9 box
void sudokubar(int x,int y,int n){

	//int x1;
	char c[1];
	//x1=x+50;
	settextstyle(0,0,2);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x,y,x+48,y+48);
	setcolor(BLACK);
	rectangle(x,y,x+48,y+48);
	if(n!=0){
	itoa(n,c,10);
	setcolor(BLACK);
	outtextxy(x+24,y+24,c);}
	else{
	setfillstyle(SOLID_FILL,GREEN);
	bar(x,y,x+48,y+48);
	setcolor(BLACK);
	rectangle(x,y,x+48,y+48);
	outtextxy(x+24,y+24,"");
	}

	//return 0;
	}


int options(int x,int y){
int ix,iy;
ix=x;
iy=y;
char c[1];
int n=1;
for(int i=0;i<3;i++){
for(int j=x;j<=x+32;j=j+16){

setfillstyle(SOLID_FILL,BLUE);
bar(j,y,j+16,y+16);
setcolor(WHITE);
rectangle(j,y,j+16,y+16);

itoa(n,c,10);
outtextxy(j+7,y+7,c);
n++;
}
y=y+16;
}
/*area=imagesize(ix,iy,ix+48,iy+48);
bitmap=malloc(area);
getimage(ix,iy,ix+48,iy+48,bitmap);*/
return 0;
}

int check(int n,int ca[][9],int r,int c){

	for(int i=0;i<9;i++){

			if(c==i)
				continue;
			else{
				if(n==ca[r][i]){
					caution((i*48)+103,r*48+10,n);
					return -1;
				}
			}
	}
	for(int j=0;j<9;j++){

			if(r==j)
				continue;
			else{
				if(n==ca[j][c]){
					caution((c*48)+103,j*48+10,n);
					return -1;
				}
			}
	}
	ca[r][c]=n;
	return n;
}

void caution(int x,int y,int n){
	char c[1];
	setfillstyle(SOLID_FILL,RED);
	bar(x,y,x+48,y+48);
	setcolor(BLACK);
	rectangle(x,y,x+48,y+48);
	itoa(n,c,10);
	outtextxy(x+24,y+24,c);
	delay(500);
	setfillstyle(SOLID_FILL,WHITE);
	bar(x,y,x+48,y+48);
	setcolor(BLACK);
	rectangle(x,y,x+48,y+48);
	itoa(n,c,10);
	outtextxy(x+24,y+24,c);
}



void buildans(int x,int y,int n){
	char c[1];
	setfillstyle(SOLID_FILL,YELLOW);
	bar(x,y,x+48,y+48);
	setcolor(BLACK);
	rectangle(x,y,x+48,y+48);
	if(n!=0){
		itoa(n,c,10);
		outtextxy(x+24,y+24,c);
	}
	else{
		setfillstyle(SOLID_FILL,GREEN);
		bar(x,y,x+48,y+48);
		setcolor(BLACK);
		rectangle(x,y,x+48,y+48);
		outtextxy(x+24,y+24,"");
	}
	/*area=imagesize(x,y,x+48,y+48);
	bitmap=malloc(area);
	getimage(x,y,x+48,y+48,bitmap);*/
}


/*int click(int a1[][9],int b1[][9],int c1[][9]){
	int a,b,c,d=0,button,x,y,n,m=0,i=0,p=450,q=0;
	char e[1],f[1],g[1];
	//getmousepos(&button,&x,&y);

	while(!kbhit()){

		getmousepos(&button,&x,&y);
		if(button==1){
			p=10;
		}

		if(button==1&&x<432&&y<432&&d!=-1){

			button=-1;
			a=y/48;
			b=x/48;
			if(b1[a][b]==0){
				d=options(b*48,a*48);
				}
		}


/*	else if(button==1&&x<433&&y<433&&x%48!=0&&y%48!=0&&d==-1){
			buildans(b*48,a*48,0);
			button=-1;
			d=0;
			a=y/48;
			b=x/48;
			if(b1[a][b]==0){
				d=options(b*48,a*48);
		       //	}
	      // }

		else if(button==1 && (x>((b*48)+48) || x<(b*48)) && (y>((a*48)+48) || y<(a*48)) && d==-1){

			buildans(b*48,a*48,0);
			button=-1;
			d=0;

			a=y/48;
			b=x/48;
			if(b1[a][b]==0)
				d=options(b*48,a*48);

		}

		else if(button==1 && x<((b*48)+16) && x>b*48 && y<((a*48)+16) && y>a*48 && x%48!=0 && y%48!=0 && d==-1){

			button=-1;
			d=0;
			c=check(1,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==-1)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+32)&&x>((b*48)+16)&&y<((a*48)+16)&&y>a*48&&x%48!=0&&y%48!=0&&d==-1){

			button=-1;
			d=0;
			c=check(2,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==-1)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+48)&&x>((b*48)+32)&&y<((a*48)+16)&&y>a*48&&x%48!=0&&y%48!=0&&d==-1){

			button=-1;
			d=0;
			c=check(3,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+16)&&x>b*48&&y<((a*48)+32)&&y>((a*48)+16)&&x%48!=0&&y%48!=0&&d==-1){

			button=-1;
			d=0;
			c=check(4,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+32)&&x>((b*48)+16)&&y<((a*48)+32)&&y>((a*48)+16)&&x%48!=0&&y%48!=0&&d==-1){

			button=-1;
			d=0;
			c=check(5,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+48)&&x>((b*48)+32)&&y<((a*48)+32)&&y>((a*48)+16)&&x%48!=0&&y%48!=0&&d==-1){
			//if(x>x1&&x<x1+20&&y>y1&&y<y1+60){
			button=-1;
			d=0;
			c=check(6,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+16)&&x>b*48&&y<((a*48)+48)&&y>((a*48)+32)&&x%48!=0&&y%48!=0&&d==-1){
			//if(x>x1&&x<x1+20&&y>y1&&y<y1+60){
			button=-1;
			d=0;
			c=check(7,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+32)&&x>((b*48)+16)&&y<((a*48)+48)&&y>((a*48)+32)&&x%48!=0&&y%48!=0&&d==-1){
			//if(x>x1&&x<x1+20&&y>y1&&y<y1+60){
			button=-1;
			d=0;
			c=check(8,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

		else if(button==1&&x<((b*48)+48)&&x>((b*48)+32)&&y<((a*48)+48)&&y>((a*48)+32)&&x%48!=0&&y%48!=0&&d==-1){
			//if(x>x1&&x<x1+20&&y>y1&&y<y1+60){
			button=-1;
			d=0;
			c=check(9,c1,a,b);
			if(c!=-1){
				buildans(b*48,a*48,c);
				n=checkfinish(c1);
				if(n==0)
					return 0;
			}
			else{
				buildans(b*48,a*48,0);
			}
		}

	}
}*/

     /*	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(c1[i][j]==0){
				n=-1;
				break;
			}
		}
	}
	if(n!=-1)
		return 0;*/




int checkfinish(int fa[][9]){
	int n;
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			if(fa[i][j]==0){
				n=-1;
				break;
			}
		}
		if(n==-1)
			break;
	}
	if(n!=-1)
		//checkans(ba,fa,mv,m,s);
		return 0;
	else
		return -1;
}






int click(/*int a1[][9],*/int b1[][9],int c1[][9]){
	int a,b,c,button,x,y,m,n,p=10,q=10,i=0,j=0,ans,move=0,tempx,tempy,tempa,tempb,op=-1,brk=1,minute,second;
	char ch;
	char num[1],r[1];
	int min,sec;
	struct time t;
	gettime(&t);
	min=t.ti_min;
	sec=t.ti_sec;
	//char e[1],f[1],g[1];
	getmousepos(&button,&x,&y);
	tempx=x;
	tempy=y;
	tempa=(y-10)/48;
	tempb=(x-103)/48;
	/*area=imagesize((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58);
	bitmap=malloc(area);
	getimage((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58,bitmap);*/

	while(!kbhit()||(ch=getch())!=27){

		getmousepos(&button,&x,&y);
		/*if(x!=tempx||y!=tempy){
		if(brk==1){
			brk=-1;
			putimage((tempb*48)+103,(tempa*48)+10,bitmap,0);
		}
		}
		/*if(x!=tempx||y!=tempy){
		if(brk==1){
			brk=-1;
			tempa=(tempy-10)/48;
			tempb=(tempx-103)/48;
			if(c1[tempa][tempb]==0&&op==-1){
				setfillstyle(SOLID_FILL,WHITE);
				bar((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58);
				setcolor(BLACK);
				rectangle((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58);
				//outtextxy((tempb*48)+127,(tempa*48)+34,"");
			}
			if(c1[tempa][tempb]==0&&op==1){
			{
				settextstyle(0,0,0);
				options((tempb*48)+103,(tempa*48)+10);
			}
			if(c1[tempa][tempb]!=0){
				n=c1[tempa][tempb];
				settextstyle(0,0,2);
				setfillstyle(SOLID_FILL,WHITE);
				bar((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58);
				setcolor(BLACK);
				rectangle((tempb*48)+103,(tempa*48)+10,(tempb*48)+151,(tempa*48)+58);
				itoa(n,r,10);
				setcolor(BLACK);
				outtextxy((tempb*48)+103+24,(tempa*48)+10+24,r);}
			}
		}
		}*/

		if(button==1){
			button=-1;
			if(x>103&&x<541&&y<442){
				a=(y-10)/48;
				b=(x-103)/48;
				tempa=a;
				tempb=b;
				//brk=1;
				/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
				bitmap=malloc(area);
				getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/
				if(b1[a][b]==0){
					brk=1;
					if(a!=p||b!=q){
						//op=1;
						move++;
						if(c1[p][q]==0){
							if(p!=9&&q!=9){
								settextstyle(0,0,2);
								buildans((q*48)+103,(p*48)+10,0);
								/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
								bitmap=malloc(area);
								getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/
							}
						}
						settextstyle(0,0,0);
						options((b*48)+103,(a*48)+10);
						c1[a][b]=0;
						/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
						bitmap=malloc(area);
						getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/
					}
					else{
						//op=-1;
						if(c1[a][b]==0){
							if(x%16!=0&&y%16!=0){
								settextstyle(0,0,2);
								/*if(x/((b*48)+103+16)==0&&y/((a*48)+16)==0){
									c=check(1,c1,a,b);
									if(c!=-1){
										c1[a][b]=c;
										buildans((b*48)+103,a*48,c);
										n=checkfinish(c1);
											if(n==0)
												return 0;
									}
								}
								else if(x/((b*48)+103+16)==1&&y/((a*48)+16)==0){
									if(x<((b*48)+103+32)){
										c=check(2,c1,a,b);
										if(c!=-1){
											c1[a][b]=c;
											buildans((b*48)+103,a*48,c);
											n=checkfinish(c1);
												if(n==0)
													return 0;
										}
									}

									else{
										c=check(3,c1,a,b);
										if(c!=-1){
											c1[a][b]=c;
											buildans((b*48)+103,a*48,c);
											n=checkfinish(c1);
												if(n==0)
													return 0;
										}
									}
								}
								else if(x/((b*48)+103+16)==0&&y/((a*48)+16)==1){
									if(y<(a*48)+32){
										c=check(4,c1,a,b);
										if(c!=-1){
											c1[a][b]=c;
											buildans((b*48)+103,a*48,c);
											n=checkfinish(c1);
												if(n==0)
													return 0;
										}
									}
									else{
										c=check(7,c1,a,b);
											if(c!=-1){
												c1[a][b]=c;
												buildans((b*48)+103,a*48,c);
												n=checkfinish(c1);
													if(n==0)
														return 0;
										}
									}
								}
								else if(x/((b*48)+103+16)==1&&y/((a*48)+16)==1){
									if(x<((b*48)+103+32)){
										if(y<(a*48)+32){
											c=check(5,c1,a,b);
											if(c!=-1){
												c1[a][b]=c;
												buildans((b*48)+103,a*48,c);
												n=checkfinish(c1);
													if(n==0)
														return 0;
											}
										}
										else{
											c=check(8,c1,a,b);
											if(c!=-1){
												c1[a][b]=c;
												buildans((b*48)+103,a*48,c);
												n=checkfinish(c1);
													if(n==0)
														return 0;
											}
										}
									}

									else{
										if(y<(a*48)+32){
											c=check(6,c1,a,b);
											if(c!=-1){
												c1[a][b]=c;
												buildans((b*48)+103,a*48,c);
												n=checkfinish(c1);
													if(n==0)
														return 0;
											}
										}
										else{
											c=check(9,c1,a,b);
											if(c!=-1){
												c1[a][b]=c;
												buildans((b*48)+103,a*48,c);
												n=checkfinish(c1);
													if(n==0)
														return 0;
											}
										}
									}
								}*/
								if(x>(b*48)+103&&x<(b*48)+119){
									if(y>(a*48)+10&&y<(a*48)+26)
										ans=1;
									else if(y>(a*48)+26&&y<(a*48)+42)
										ans=4;
									else
										ans=7;
								}
								else if(x>(b*48)+119&&x<(b*48)+135){
									if(y>(a*48)+10&&y<(a*48)+26)
										ans=2;
									else if(y>(a*48)+26&&y<(a*48)+42)
										ans=5;
									else
										ans=8;
								}
								else if(x>(b*48)+135&&x<(b*48)+151){
									if(y>(a*48)+10&&y<(a*48)+26)
										ans=3;
									else if(y>(a*48)+26&&y<(a*48)+42)
										ans=6;
								else
										ans=9;
								}

								c=check(ans,c1,a,b);
								if(c!=-1){
									c1[a][b]=c;
									buildans((b*48)+103,(a*48)+10,c);
									gettime(&t);
									minute=t.ti_min;
									second=t.ti_sec;
									n=checkfinish(c1);
									if(n==0){
										m=checkans(c1);
										if(m==0){
											minute=minute-min;
											second=second-sec;
											finishgame(move,minute,second);
										}
										else if(m==-1){
											incorrectsolution();
											problemset(b1,c1);
											click(b1,c1);
										}
									}
									/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
									bitmap=malloc(area);
									getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/

								}
							}
						}
						else{
							if(c1[p][q]==0){
								settextstyle(0,0,2);
								buildans((q*48)+103,(p*48)+10,0);
								/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
								bitmap=malloc(area);
								getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/
							}
							settextstyle(0,0,0);
							//op=1;
							options((b*48)+103,(a*48)+10);
							c1[a][b]=0;
							/*area=imagesize((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58);
							bitmap=malloc(area);
							getimage((b*48)+103,(a*48)+10,(b*48)+151,(a*48)+58,bitmap);*/
						}

					}
				p=a;
				q=b;
				}
			}
		tempx=x;
		tempy=y;
		setcolor(RED);
		line(144+103,10,144+103,442);
		line(288+103,10,288+103,442);
		line(103,154,432+103,154);
		line(103,298,432+103,298);
		delay(180);
		}
	}
	cleardevice();
	//menugraphics();
	escape(b1,c1);
	return 0;
}













/*int click(/*int a1[][9],int b1[][9],int c1[][9]){
	int a,b,c,button,x,y,n,p=10,q=10,i=0,j=0,k=0,d,tempx,tempy,btn;
	getmousepos(&button,&x,&y);
	//tempx=x;
	//tempy=y;

	while(!kbhit()){

		getmousepos(&button,&x,&y);
		/*if(tempx!=x||tempy!=y){
			a=y/48;
			b=x/48;
			n=b1[a][b];
			buildans(b*48,a*48,n);
		}*/
/*if(button==1){
	i++;
	button=-1;
	if(x<432&&y<432){
		a=y/48;
		b=x/48;
		if(b1[a][b]==0){
			if(a!=p||b!=q){
				if(p<9&&q<9)
					buildans(q*48,p*48,0);
				options(b*48,a*48);
			}

			else{

			}
		p=a;
		q=b;
		}
	}
	delay(200);
}


	}
}                         */



/*a=y/48;
b=(x-103)/48;

if(x>(b*48)+103&&x<(b*48)+119){
	if(y>(a*48)&&y<(a*48)+16)
		ans=1;
	else if(y>(a*48)+16&&y<(a*48)+32)
		ans=4;
	else
		ans=7;
}
else if(x>(b*48)+119&&x<(b*48)+135){
	if(y>(a*48)&&y<(a*48)+16)
		ans=2;
	else if(y>(a*48)+16&&y<(a*48)+32)
		ans=5;
	else
		ans=8;
}
else if(x>(b*48)+135&&x<(b*48)+151){
	if(y>(a*48)&&y<(a*48)+16)
		ans=3;
	else if(y>(a*48)+16&&y<(a*48)+32)
		ans=6;
	else
		ans=9;
}

c=check(ans,c1,a,b);
if(c!=-1){
c1[a][b]=c;
buildans((b*48)+103,a*48,c);
n=checkfinish(c1);
if(n==0)
return 0;*/


int checkans(int arr[][9]){

int i,j,k,ans=0;

for(i=0;i<9;i=i+3){
for(j=0;j<3;j++){
for(k=i;k<i+3;k++){
	ans=ans+arr[j][k];
}
}
if(ans!=45){
	//incorrectsolution(brr,arr);
	return -1;
	//break;
}
ans=0;
}

ans=0;
for(i=0;i<9;i=i+3){
for(j=3;j<6;j++){
for(k=i;k<i+3;k++){
	ans=ans+arr[j][k];
}
}
if(ans!=45){
	//incorrectsolution(brr,arr);
	return -1;
	//break;
}
ans=0;
}

ans=0;
for(i=0;i<9;i=i+3){
for(j=6;j<9;j++){
for(k=i;k<i+3;k++){
	ans=ans+arr[j][k];
}
}
if(ans!=45){
	//incorrectsolution(brr,arr);
	return -1;
	//problemset(arr);
	//break;
}
ans=0;
}

return 0;
//finishgame(mv,min,sec);

}

//void incorrectsolution(int brr[][9],int arr[][9]){
void incorrectsolution(){
	cleardevice();
	setbkcolor(9);
	setcolor(BLUE);
	outtextxy(10,100,"Sorry,your solution is incorrect");
	outtextxy(30,150,"Please try again");
	outtextxy(8,450,"Press any key to play the game again");

	getch();
	//problemset(brr,arr);
}

//void problemset(int brr[][9],int arr[][9]){
void problemset(int brr[][9],int arr[][9]){

//incorrectsolution();

cleardevice();
setbkcolor(8);
setfillstyle(SOLID_FILL,7);
bar(93,0,545,452);
int n;
char c[1];
for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
	settextstyle(0,0,2);
	setfillstyle(SOLID_FILL,WHITE);
	bar((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
	setcolor(BLACK);
	rectangle((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
	n=arr[i][j];
	if(n!=0){
	if(brr[i][j]==0){
		setfillstyle(SOLID_FILL,YELLOW);
		bar((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
		setcolor(BLACK);
		rectangle((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);}
	else{
		setfillstyle(SOLID_FILL,WHITE);
		bar((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
		setcolor(BLACK);
		rectangle((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);}
	itoa(n,c,10);
	setcolor(BLACK);
	outtextxy((j*48)+127,(i*48)+34,c);}
	else{
	setfillstyle(SOLID_FILL,GREEN);
	bar((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
	setcolor(BLACK);
	rectangle((j*48)+103,(i*48)+10,(j*48)+151,(i*48)+58);
	outtextxy((j*48)+127,(i*48)+34,"");
	}
	}
}
setcolor(RED);
line(144+103,0,144+103,452);
line(288+103,0,288+103,452);
line(93,154,432+113,154);
line(93,298,432+113,298);
settextstyle(0,0,1);
outtextxy(103,458,"Press ESC to go to the menu");

click(brr,arr);
}


void finishgame(int mv,int min,int sec){

	//struct time t;
	setbkcolor(9);
	setcolor(1);
	char mvh[2],mn[2],sc[2];
	cleardevice();
	settextstyle(0,0,1);
	/*gettime(&t);
	min=t.ti_min-min;
	sec=t.ti_sec-sec;*/
	setcolor(WHITE);
	outtextxy(50,50,"Congratulations,your solution is correct");
	outtextxy(100,100,"Total Moves : ");
	itoa(mv,mvh,10);
	outtextxy(210,100,mvh);
	itoa(min,mn,10);
	outtextxy(100,120,"Time");
	outtextxy(196,120,":");
	outtextxy(210,120,mn);
	outtextxy(240,120,"min");
	itoa(sec,sc,10);
	outtextxy(280,120,sc);
	outtextxy(310,120,"sec");
	outtextxy(100,140,"Hope you'll play again.");
	outtextxy(200,455,"Press any key to go to the main menu.");
	getch();
	menugraphics();
}



void escape(int brr[][9],int arr[][9]){

	int button,x,y;
	setbkcolor(9);
	cleardevice();
	setfillstyle(SOLID_FILL,BLUE);
	setcolor(14);
	settextstyle(7,0,0);
	bar3d(220,100,420,140,3,1);
	bar3d(210,200,430,240,3,1);
	bar3d(270,300,370,340,3,1);
	setcolor(RED);
	outtextxy(225,100,"NEW GAME");
	outtextxy(215,200,"MAIN MENU");
	outtextxy(275,300,"BACK");

	while(!kbhit()){
	settextstyle(0,0,2);
	setcolor(BLACK);
	getmousepos(&button,&x,&y);
	if(button==1&&x>220&&x<420&&y>100&&y<140){
		button=-1;
		cleardevice();
		setfillstyle(SOLID_FILL,BLUE);
		setcolor(14);
		bar3d(280,100,360,140,3,1);
		bar3d(260,160,380,200,3,1);
		bar3d(280,220,360,260,3,1);
		bar3d(280,280,360,320,3,1);
		outtextxy(290,110,"EASY");
		outtextxy(270,170,"MEDIUM");
		outtextxy(290,230,"HARD");
		outtextxy(290,290,"BACK");
		delay(150);
		while(!kbhit()){
			getmousepos(&button,&x,&y);
			if(button==1&&x>280&&x<360&&y>100&&y<140){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(3);
			}
			else if(button==1&&x>260&&x<380&&y>160&&y<200){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(4);
			}
			else if(button==1&&x>280&&x<360&&y>220&&y<260){
				button=-1;
				cleardevice();
				setbkcolor(8);
				setfillstyle(SOLID_FILL,7);
				bar(93,0,545,452);
				delay(100);
				menu(5);
			}
			else if(button==1&&x>280&&x<360&&y>280&&y<320){
				button=-1;
				delay(100);
				escape(brr,arr);
			}
		}
	}
	else if(button==1&&x>210&&x<430&&y>200&&y<240){
		button=-1;
		delay(150);
		menugraphics();
	}
	else if(button==1&&x>270&&x<370&&y>300&&y<340){
		button=-1;
		cleardevice();
		delay(100);
		problemset(brr,arr);
	}
}
}