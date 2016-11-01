Tetris Game in C

#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <dos.h>
#include <conio.h>

void swap(int a,int b);void bar1();void bar2();
void bar3();  void bar4();  check0(); check1();
check2(); void del(); void rod1(); void rod2();
void box1();void box2();void tee1();voidtee2();
void tee3();void tee4();check3();void insert();
void again();void print();void remove();void frame();
int score=0,spd,q,t,a=0,i,j,l[6]={300,90,315,105,301,91},p,turn,m,n;
char play='y';
static int arr[26][13];
void main(void)
{

   char ch,y;
   int gd= DETECT,gm,area,maxx,maxy,move,lmove,rmove;
   void *buff;
   initgraph(&gd,&gm,"d:\tc\bgi");
do{

   turn=1;
    score=0;
   do{
   clrscr();
   cleardevice();
   printf("
 Enter Your Choice

");
   printf(" Basic Level.......... 1
");
   printf(" Middle Level......... 2
");
   printf(" Advanced Level....... 3
");
   printf(" Experts Level........ 4
");
   printf(" Professional Level... 5
");
   y=getch();
   clrscr();
   cleardevice();
   if(y=='1') {spd=200; settextstyle(2,0,6);outtextxy(2,150,"   Basic
Level ");break;}
   if(y=='2') {spd=150; settextstyle(2,0,6);outtextxy(2,150,"   Middle
Level ");break;}
   if(y=='3') {spd=100; settextstyle(2,0,6);outtextxy(2,150,"  Advanced
Level ");break;}
   if(y=='4') {spd=75; settextstyle(2,0,6);outtextxy(2,150,"  Experts
Level ");break;}
   if(y=='5') {spd=50;  settextstyle(2,0,6);outtextxy(2,150,"Professional
Level ");break;}
      }while(1);

   frame();
   getch();
int k,ar[2],pr[2],t[6];

randomize();
ar[0]=random(2);
pr[0]=random(6);
ar[1]=random(2);
pr[1]=random(6);
while(1)
{
printf(" score= %d
",score);
a=ar[0];
p=pr[0];
l[0]=450;l[1]=250;l[2]=465;l[3]=265;l[4]=451;l[5]=251;

if(y=='1') spd=100;
if(y=='2') spd=75;
if(y=='3') spd=50;
if(y=='4') spd=30;
if(y=='5') spd=20;
print();

delay(500);
a=ar[1];
p=pr[1];

t[0]=l[0];  t[1]=l[1]; t[2]=l[2];
t[3]=l[3];  t[4]=l[4]; t[5]=l[5];

a=ar[1];
p=pr[1];

l[0]=270;l[1]=90;l[2]=285;l[3]=105;l[4]=271;l[5]=91;

do{
    k=0;
if(kbhit()){ ch=getch();
		      if(ch==0) ch=getch();
		    if(ch==77) {move=check1(); if(move==0) {l[0]+=15;l[2]+=15;l[4]+=15;
k=1;}}
		    if(ch==75) {move=check2(); if(move==0) {l[0]-=15;l[2]-=15;l[4]-=15;
k=1;}}
		    if(ch==80) spd=10;
		    if(ch==27) exit(0);

		    if(ch==32){
		 		        k=1;
		 		        if(p==4||p==5)  switch(p)
 		 		        {
		 		 		  case 4:  if(a==0) a++; else p++; break;
		 		 		  case 5:  if(a==1) a--; else p--;
 		 		        }
		 		        if(p==1||p==2) switch(p)
 		 		       {  case 1:  if(a==0) a++; else p++;
l[0]=270;l[2]=285;l[4]=271;break;
	 		 		  case 2:  if(a==1) a--; else p--; l[0]=270;l[2]=285;l[4]=271;
	 		 		 }

		 		        if(p==3)  { if(a==0) a++; else a=0;
 l[0]=270;l[2]=285;l[4]=271; }

		 		     }
		    if(a==1)    {swap(l[0],l[1]);swap(l[2],l[3]);swap(l[4],l[5]);}
		  }



move=check0();
if(move==1) break;

print();

if(k==1) delay(0); else delay(spd);

remove();

if(k==0) {l[1]+=15; l[3]+=15; l[5]+=15;}


}while(1);
print();
fflush(stdin);


insert();

check3();

a=ar[0];
p=pr[0];


l[0]=t[0];l[1]=t[1];l[2]=t[2];l[3]=t[3];
l[4]=t[4];l[5]=t[5];


remove();


ar[1]=ar[0];
pr[1]=pr[0];


ar[0]=random(2);
pr[0]=random(6);

if(pr[0]==2) pr[0]=3;
if(turn==0) break;


   }


    }while(play=='y');

}


void swap(int a,int b)
{
a=a+b;
b=a-b;
a=a-b;
}


void bar1()
{ if(a==0&&i<1) {l[0]+=15;l[2]+=15;l[4]+=15; }
  if(a==0&&i>=1){l[1]+=15;l[3]+=15;l[5]+=15; }

//  if(a==1&&i==1)
{l[0]-=15;l[2]-=15;l[4]-=15;l[1]-=15;l[3]-=15;l[5]-=15; }
  if(a==1&&i==0) {l[1]+=15;l[3]+=15;l[5]+=15; }
  if(a==1&&i>0) {l[0]-=15;l[2]-=15;l[4]-=15; }

  if(a==2&&i>=2) {l[0]-=15;l[2]-=15;l[4]-=15; }
  if(a==2&&i<2) {l[1]+=15;l[3]+=15;l[5]+=15; }
 }




void bar2()
{ if(a==0&&i>=3){l[0]-=15;l[2]-=15;l[4]-=15; }
  if(a==0&&i<3) {l[1]-=15;l[3]-=15;l[5]-=15; }

  if(a==1&&i<3) {l[0]+=15;l[2]+=15;l[4]+=15; }
  if(a==1&&i==3){l[1]-=15;l[3]-=15;l[5]-=15; }

  if(a==2&&i<2) {l[0]+=15;l[2]+=15;l[4]+=15;}
  if(a==2&&i>=2){l[1]-=15;l[3]-=15;l[5]-=15; }
   }
void bar3()
{if(a==0&&i>=3){l[0]+=15;l[2]+=15;l[4]+=15; }
 if(a==0&&i<3){l[1]+=15;l[3]+=15;l[5]+=15; }
 if(a==2&&i<2) {l[0]-=15;l[2]-=15;l[4]-=15; }
 if(a==2&&i>=2) {l[1]+=15;l[3]+=15;l[5]+=15; }
 if(a==1&&i>=1) {l[0]+=15;l[2]+=15;l[4]+=15; }
 if(a==1&&i<1) {l[1]+=15;l[3]+=15;l[5]+=15; }
   }
void bar4()
{if(a==0&&i<1){l[0]-=15;l[2]-=15;l[4]-=15; }
 if(a==0&&i>=1) {l[1]-=15;l[3]-=15;l[5]-=15; }
 if(a==2&&i>=2) {l[0]+=15;l[2]+=15;l[4]+=15; }
 if(a==2&&i<2){l[1]-=15;l[3]-=15;l[5]-=15; }
 if(a==1&&i<3) {l[0]-=15;l[2]-=15;l[4]-=15; }
 if(a==1&&i==3) {l[1]-=15;l[3]-=15;l[5]-=15; }
}
void rod1()

{

 if(a==0) {l[0]+=15;l[2]+=15;l[4]+=15; }
    else    {l[1]+=15;l[3]+=15;l[5]+=15; }
  }
void rod2()
{

 if(a==0) {l[0]-=15;l[2]-=15;l[4]-=15; }
   else  {l[1]-=15;l[3]-=15;l[5]-=15; }

 }
void box1()
{if(i<1) {l[0]-=15;l[2]-=15;l[4]-=15; }
 if(i==1) {l[1]+=15;l[3]+=15;l[5]+=15; }
 if(i==2) {l[0]+=15;l[2]+=15;l[4]+=15; }
 }
void box2()
{if(i<1) {l[0]-=15;l[2]-=15;l[4]-=15; }
 if(i==1) {l[1]-=15;l[3]-=15;l[5]-=15; }
 if(i==2) {l[0]+=15;l[2]+=15;l[4]+=15; }
 }
 void tee1()
 {
    if(a==0&&i==1) {l[0]-=15;l[2]-=15;l[4]-=15; }
    if(a==0&&i<1) {l[1]+=15;l[3]+=15;l[5]+=15; }
    if(a==0&&(i==2||i==3)) {l[0]+=15;l[2]+=15;l[4]+=15; }


    if(a>0&&i==2)
{l[0]-=15;l[2]-=15;l[4]-=15;l[1]+=15;l[3]+=15;l[5]+=15; }
    if(a>0&&i==0) {l[1]+=15;l[3]+=15;l[5]+=15; }
    if(a>0&&(i==1)) {l[0]+=15;l[2]+=15;l[4]+=15; }

      }
  void tee2()
  {
    if(a==0&&i==0) {l[0]-=15;l[2]-=15;l[4]-=15; }
    if(a==0&&i==1) {l[0]-=15;l[2]-=15;l[4]-=15; }
    if(a==0&&i==2)
{l[0]+=15;l[2]+=15;l[4]+=15;l[1]-=15;l[3]-=15;l[5]-=15; }

    if(a>0&&i==2)
{l[0]-=15;l[2]-=15;l[4]-=15;l[1]-=15;l[3]-=15;l[5]-=15; }
    if(a>0&&i==1) {l[0]+=15;l[2]+=15;l[4]+=15; }
    if(a>0&&i==0) {l[1]-=15;l[3]-=15;l[5]-=15; }


      }
   void tee3()
   {  if(a==0&&i==0) {l[0]-=15;l[2]-=15;l[4]-=15; }
      if(a==0&&i==2)
{l[0]-=15;l[2]-=15;l[4]-=15;l[1]-=15;l[3]-=15;l[5]-=15; }
      if(a==0&&i==1) {l[1]+=15;l[3]+=15;l[5]+=15;}


      if(a>0&&i==2)
{l[0]+=15;l[2]+=15;l[4]+=15;l[1]+=15;l[3]+=15;l[5]+=15; }
      if(a>0&&i==0) {l[1]+=15;l[3]+=15;l[5]+=15; }
      if(a>0&&(i==1)) {l[0]-=15;l[2]-=15;l[4]-=15; }
   }
   void tee4()
   {  if(a==0&&i==1) {l[1]+=15;l[3]+=15;l[5]+=15; }
      if(a==0&&i==0) {l[0]+=15;l[2]+=15;l[4]+=15; }
      if(a==0&&i==2)
{l[1]-=15;l[3]-=15;l[5]-=15;l[0]+=15;l[2]+=15;l[4]+=15; }

      if(a>0&&i==2)
{l[0]+=15;l[2]+=15;l[4]+=15;l[1]-=15;l[3]-=15;l[5]-=15; }
      if(a>0&&i==0) {l[1]-=15;l[3]-=15;l[5]-=15; }
      if(a>0&&i==1) {l[0]-=15;l[2]-=15;l[4]-=15; }

      }

 check0()
{ int x,y,s,d=5;

   x=(l[0]-180)/15;
   y=(l[1]-90)/15;
   if(a==0){
		  switch (p)
		   { case 0: y+=2;d=2; if(arr[y][x-1]==1) return(1); else break;
		     case 1: y+=4;x++;d=1;if(arr[y-3][x-1]==1) return(1); else break;
		     case 2: y=y+4;d=2;x+=1;break;
		     case 3: y=y+1;d=5;x+=4;break;
		     case 4: y+=2;d=3;x++;break;
		     case 5: y+=1;d=3;if(arr[y+1][x-1]==1) return(1); else break;
     }
		      for(s=1;s<d;s++,x--)
		      if(arr[y][x]==1) return(1);
		      if((arr[y][x])==0) return(0); else return(1);
		     }

      if(a==1){
		     switch (p)
		   { case 0: y+=2;d=2; if(arr[y][x-1]==1) return(1); else break;
		     case 1: y=y+2;d=4;if(arr[y][x]==1) return(1); else break;
		     case 2: y=y+2;d=4;x+=3;if(arr[y][x-3]==1) return(1); else break;
		     case 3: y=y+5;d=0;break;
		     case 4: y+=3;d=0;if(arr[y-1][x+1]==1) return(1); else break;
		     case 5: y+=3;d=0;if(arr[y-1][x-1]==1) return(1); else break;
		   }
		      for(s=1;s<d;s++,x--)
		      if(arr[y][x]==1) break;
     if((arr[y][x])==0) return(0); else return(1);
		       }


  return(0);
}


check1()
{  int x,y,s,d=5;

   x=(l[0]-150)/15;
   y=(l[1]-90)/15;

   if(a==0){
   switch (p)
    {  case 0: x=x-1;y++;d=2;break;
       case 1: x=x;d=3; y=y+3; break;
       case 2: x=x;d=4;y+=3; break;
       case 3: x=x+3;d=0;break;
       case 4: x=x;break;
       case 5: x=x-1;d=0;

     }
		    for(s=0;s<d;s++,y--)
		    if(arr[y][x]==1) break;
     if((arr[y][x])==0) return(0); else return(2);
		    }


   if(a==1)
		   {   switch(p)
   {   case 0: x=x; break;
       case 1: x=x;d=1;break;
       case 2: x=x+3;  break;
       case 3: x=x;y+=5;d=4;break;
       case 4: x=x+1;break;
       case 5: x=x;y+=2;d=2;
   }

		    for(s=0;s<d;s++,y--)
		    if(arr[y][x-1]==1) break;
   if((arr[y][x-1])==0) return(0); else return(2);
		  }
		  return(0);
}


check2()
{
 int x,y,s,d=5;
   x=(l[0]-150)/15;
   y=(l[1]-90)/15;
  if(a==0){
   switch (p)
   { case 0: x=x-1;d=1;break;
     case 1: x=x;d=3;break;
     case 2: x=x;d=3;break;
     case 3: x=x;d=0;break;
     case 4: x=x-1;d=1;break;
     case 5: x=x-2;d=0;
   }
		    for(s=0;s<d;s++,y++)
		    if(arr[y][x-3]==1) break;
    if((arr[y][x-3])==0) return(0); else return(2);
   }

    if(a==1){


    switch (p)
   { case 0: x=x-4;d=2;break;
     case 1: x=x-6;d=0;break;
     case 2: x=x-3;d=2;y-=1;break;
     case 3: x=x-3;d=5;break;
     case 4: x-=3; d=3;break;
     case 5: x-=4; d=4;
    }
		    for(s=1;s<d;s++,y++)
		    if(arr[y][x]==1) break;
     if((arr[y][x])==0) return(0); else return(2);
		    }
		 		  return(0);
}

 check3()
{

 for(t=1;t<25;t++)

 for(q=1;q<12;)
   if(arr[t][q]==1) { q++; if(q==12) {score+=100;del();}}  else break;

		  return(0);
}


void insert()
{ int x,y;
    for(i=0;i<5;i++){
    x=(l[0]-180)/15;
    y=(l[1]-90)/15;
   arr[y][x]=1;
     switch(p)
     {
       case 0: box2();break;
       case 1: bar2();break;
       case 2: bar4();break;
       case 3: rod2();break;
       case 4: tee2();break;
       case 5: tee4();
     }
		 		     }

    if(arr[0][5]==1||arr[0][6]==1)
    {
    settextstyle(3,0,4);
    outtextxy(180,100," GAME OVER ");
    fflush(stdin);
    getch();
    turn=0;
    again();
    }

}

void print()
{
  for(i=0;i<5;i++){
setcolor(WHITE);
setfillstyle(SOLID_FILL,6);
rectangle(l[0]+1,l[1]+1,l[2]-1,l[3]-1);
floodfill(l[4]+1,l[5]+1,WHITE);
if(i<4)  switch (p)
		 { case 0 : box1();break;
		   case 1 : bar1();break;
		   case 2 : bar3();break;
		   case 3 : rod1();break;
		   case 4 : tee1();break;
		   case 5 : tee3();
		 }
		        }

}

void remove()
{
for(i=0;i<5;i++){
setcolor(BLACK);
setfillstyle(SOLID_FILL,BLACK);
rectangle(l[0]+1,l[1]+1,l[2]-1,l[3]-1);
floodfill(l[4]+1,l[5]+1,BLACK);
 if(i<4) switch (p)
		 { case 0 : box2();break;
		   case 1 : bar2();break;
		   case 2 : bar4();break;
		   case 3 : rod2();break;
		   case 4 : tee2();break;
		   case 5 : tee4();
		 }
		 		  }

}

void del()
{ int m,n;
 for(;t>0;t--)
 for(q=1;q<12;q++)
 arr[t][q]=arr[t-1][q];


 for(n=0;n<25;n++)
 //delay(50);
 for(m=1;m<12;m++){

 if(arr[n][m]==1)  { setcolor(WHITE);
		 		      setfillstyle(SOLID_FILL,6);
		 		      rectangle((m*15)+181,(n*15)+91,(m*15)+194,(n*15)+104);
		 		      floodfill((m*15)+182,(n*15)+92,WHITE);
		 		     }


 else        { setcolor(BLACK);
		 		      setfillstyle(SOLID_FILL,BLACK);
		 		      rectangle((m*15)+181,(n*15)+91,(m*15)+194,(n*15)+104);
		 		      floodfill((m*15)+182,(n*15)+92,BLACK);
		 		     }


		        }
}



void frame()
{  setcolor(WHITE);
   setfillstyle(SOLID_FILL,8);

settextstyle(7,0,6);
outtextxy(140,3," TETTRIS ");
setcolor(WHITE);
settextstyle(2,0,7);
outtextxy(400,440,"Press 'Esc' To Exit");
settextstyle(2,0,5);
outtextxy(5,285,"      PRESS     ");
outtextxy(5,300,"Space To Change Shape");
outtextxy(5,315,"Use Arrow Keys To Move");



   rectangle(180,465,375,480);
   floodfill(181,466,WHITE);

   rectangle(180,90,194,480);
   floodfill(181,95,WHITE);

   rectangle(361,90,375,480);
   floodfill(362,95,WHITE);


   setcolor(WHITE);
   settextstyle(7,0,1);
   outtextxy(400,200," Next To Come ");
   setfillstyle(SOLID_FILL,0);
   rectangle(400,230,530,335);
   floodfill(401,231,WHITE);



   for(m=0;m<26;m++)
   for(n=0;n<13;n++)
   arr[m][n]=0;

   for(m=0,n=0;n<26;n++)
   arr[n][m]=1;

   for(n=12,m=0;m<26;m++)
   arr[m][n]=1;

   for(m=25,n=0;n<13;n++)
   arr[m][n]=1;

}
void again()
{
   cleardevice();
   setcolor(WHITE);
   setfillstyle(SOLID_FILL,BLACK);
   rectangle(150,175,530,335);
   floodfill(159,179,BLACK);


   setcolor(WHITE);
   settextstyle(7,0,1);
   outtextxy(175,200,"   Enter Your Choice  ");
   outtextxy(175,220," Press 'Y' To Play Again ");
   outtextxy(175,240," Press Any Key To Exit ");

 play=getch();
 if(play=='y') cleardevice();
 else exit(0);

 }
