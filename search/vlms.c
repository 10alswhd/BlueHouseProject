/*Voters List Management System*/
/*Username: admin Password: 123*/
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
#include<graphics.h>

/*Lines and boxes*/
void bo(int x1, int y1, int x2, int y2)
{
  int x;
  gotoxy(x1,y1);putch(201);
  gotoxy(x2,y1);putch(187);
  gotoxy(x1,y2);putch(200);
  gotoxy(x2,y2);putch(188);
  for(x=x1+1;x<x2;x++)
  {
    gotoxy(x,y1);putch(205);
    gotoxy(x,y2);putch(205);
  }
  for(x=y1+1;x<y2;x++)
  {
    gotoxy(x1,x);putch(186);
    gotoxy(x2,x);putch(186);
  }
}

void lin(int x1,int y1,int x2)
{
  int k;
  gotoxy(x1,y1);putch(204);
  gotoxy(x2,y1);putch(185);
  for(k=x1+1;k<x2;k++) { gotoxy(k,y1);putch(205);	}
}

void ver(int x1, int y1, int y2)
{
  int k;
  gotoxy(x1,y1);putch(203);
  for(k=y1+1;k<y2;k++) { gotoxy(x1,k);putch(186);	}
}

void lin2(int x1,int y1,int x2)
{
  int k;
  for(k=x1+1;k<x2;k++) { gotoxy(k,y1);putch(205); }
}

void spc(int x)
{
  int i;
  for(i=0;i<x;i++) printf(" ");
}
/*End of lines and boxes*/

struct voter
{
  char name[20],gname[20],sex,add[30],id[15],wname[20];
  int age,dd,mm,yy;
  long int wno,hno;
};

FILE *fd,*ft;
struct voter e;
long int size=sizeof(e);
char ch,vid[15],opt;
long int wn,hn,buf[100];

void scrn(long int w,long int h,int t)
{
  gotoxy(27,2);printf("Voters List Management System");
  gotoxy(4,4);printf("Ward No : %ld",w);
  gotoxy(22,4);printf("House No : %ld",h);
  lin2(0,5,80);
  if(t==1)
  {
    ver(38,5,25);
    ver(10,5,25);
    ver(48,5,25);
    gotoxy(2,6);printf("Ward No");
    gotoxy(40,6);printf("Ward No");
    gotoxy(12,6);printf("Ward Name");
    gotoxy(50,6);printf("Ward Name");
    lin2(0,7,80);
    gotoxy(38,7);putch(206);
    gotoxy(48,7);putch(206);
    gotoxy(10,7);putch(206);
  }
  if(t==2)
  {
    ver(12,5,25);
    ver(24,5,25);
    ver(36,5,25);
    ver(48,5,25);
    ver(60,5,25);
    ver(72,5,25);
    gotoxy(2,6);printf("House No");
    gotoxy(14,6);printf("House No");
    gotoxy(26,6);printf("House No");
    gotoxy(38,6);printf("House No");
    gotoxy(50,6);printf("House No");
    gotoxy(62,6);printf("House No");
    gotoxy(74,6);printf("House No");
    lin2(0,7,80);
    gotoxy(12,7);putch(206);
    gotoxy(24,7);putch(206);
    gotoxy(36,7);putch(206);
    gotoxy(48,7);putch(206);
    gotoxy(60,7);putch(206);
    gotoxy(72,7);putch(206);
  }
  if(t==3)
  {
    gotoxy(5,6);printf("ID");
    ver(11,5,25);
    gotoxy(18,6);printf("Name");
    ver(27,5,25);
    gotoxy(28,6);printf("Age");
    ver(31,5,25);
    gotoxy(34,6);printf("DOB");
    ver(40,5,25);
    gotoxy(41,6);printf("Sex");
    ver(44,5,25);
    gotoxy(48,6);printf("Father's/");
    gotoxy(45,7);printf("Husband's Name");
    ver(59,5,25);
    gotoxy(63,6);printf("Street Address");
    lin2(0,8,80);
    gotoxy(11,8);putch(206);
    gotoxy(27,8);putch(206);
    gotoxy(31,8);putch(206);
    gotoxy(40,8);putch(206);
    gotoxy(44,8);putch(206);
    gotoxy(59,8);putch(206);
  }
}

void srchv()
{
  int flag=0;
  clrscr();
  bo(25,10,56,15);
  gotoxy(37,10);printf(" SEARCH ");
  gotoxy(30,12);printf("Enter VoterID : ");
  scanf("%s",vid);fflush(stdin);rewind(fd);
  while(fread(&e,size,1,fd)==1)
  {
    if(strcmpi(e.id,vid)==0)
    {
      clrscr();
      bo(15,4,65,17); gotoxy(32,4); printf(" SEARCH RESULTS "); flag=1;
      gotoxy(20,6);printf("Voter ID");gotoxy(44,6);printf(": %s",e.id);
      gotoxy(20,7);printf("Ward No");gotoxy(44,7);printf(": %ld",e.wno);
      gotoxy(20,8);printf("Ward Name");gotoxy(44,8);printf(": %s",e.wname);
      gotoxy(20,9);printf("House No");gotoxy(44,9);printf(": %ld",e.hno);
      gotoxy(20,10);printf("Name");gotoxy(44,10);printf(": %s",e.name);
      gotoxy(20,11);printf("Age");gotoxy(44,11);printf(": %d",e.age);
      gotoxy(20,12);printf("Date of Birth");gotoxy(44,12);printf(": %d/%d/%d",e.dd,e.mm,e.yy);
      gotoxy(20,13);printf("Sex");gotoxy(44,13);printf(": %c",e.sex);
      gotoxy(20,14);printf("Father's/Husband's Name");gotoxy(44,14);printf(": %s",e.gname);
      gotoxy(20,15);printf("Address");gotoxy(44,15);printf(": %s",e.add);
      getch();
      break;
    }
  }
  if(flag==0)
  {
    gotoxy(30,12); printf("  Record Not Found!"); getch();
  }
}

void srchw()
{
  int x=5,y=8,i,c=0,flag=0;
  for(i=0;i<100;i++) buf[i]=0;
  rewind(fd);
  clrscr();
  scrn(0,0,1);
  while(fread(&e,size,1,fd) == 1)
  {
    if(x==5 && y==24)
    {
      x=43; y=8;
    }
    if(x==43 && y==24)
    {
      gotoxy(24,74); printf("Press Any Key>>"); getch();
      clrscr();
      scrn(0,0,1);
      x=5; y=2;
    }
    for(i=0;i<100;i++) if(buf[i]==e.wno) break;
    if(i==100)
    {
      buf[c]=e.wno;
      gotoxy(x,y);printf("%ld",e.wno);gotoxy(x+8,y);printf("%s",e.wname);
      y++; c++;
    }
  }
  for(i=0;i<100;i++) buf[i]=0;
  gotoxy(14,4); scanf("%ld",&wn); fflush(stdin);
  x=2; y=8; c=0; rewind(fd);
  clrscr();
  scrn(wn,0,2);
  while(fread(&e,size,1,fd) == 1)
  {
    if(x==2 && y==24)
    {
      x=14; y=8;
    }
    if(x==14 && y==24)
    {
      x=26; y=8;
    }
    if(x==26 && y==24)
    {
      x=38; y=8;
    }
    if(x==38 && y==24)
    {
      x=50; y=8;
    }
    if(x==50 && y==24)
    {
      x=62; y=8;
    }
    if(x==62 && y==24)
    {
      x=74; y=8;
    }
    if(x==74 && y==24)
    {
      getch();
      clrscr();
      scrn(wn,0,2);
      x=2; y=8;
    }
    for(i=0;i<100;i++) if(wn==e.wno && buf[i]==e.hno) break;
    if(i==100)
    {
      buf[c]=e.hno;
      if(wn==e.wno) { gotoxy(x,y); printf("%ld",e.hno); y++; c++; flag++; }
    }
  }
  if(flag==0)
  {
    clrscr();
    bo(25,10,55,14);
    gotoxy(33,12);printf("Ward Not Found!");
    getch();
  }
  else
  {
    gotoxy(33,4); scanf("%ld",&hn); fflush(stdin);
    x=2; y=9; flag=0; rewind(fd);
    clrscr();
    scrn(wn,hn,3);
    while(fread(&e,size,1,fd) == 1)
    {
      if(wn==e.wno && hn==e.hno)
      {
	gotoxy(x,y);printf("%s",e.id);
	gotoxy(x+=11,y);printf("%s",e.name);
	gotoxy(x+=15,y);printf("%d",e.age);
	gotoxy(x+=4,y);printf("%d/%d/%d",e.dd,e.mm,e.yy);
	gotoxy(x+=10,y);printf("%c",e.sex);
	gotoxy(x+=4,y);printf("%s",e.gname);
	gotoxy(x+=15,y);printf("%s",e.add);
	y++; x=2;
	flag++;
      }
    }
    if(flag==0)
    {
      clrscr();
      bo(25,10,55,14);
      gotoxy(32,12);printf("House Not Found!");
    }
    getch();
  }
}

void srch()
{
  char op;
  do
  {
    clrscr();
    bo(25,8,56,16); lin(25,14,56); gotoxy(37,8); printf(" SEARCH ");
    gotoxy(27,10); printf("V : Search By VoterID");
    gotoxy(27,11); printf("W : Search By Wards");
    gotoxy(27,12); printf("Esc : Main Menu");
    gotoxy(27,15); printf("Choose Your Option"); op=getch();
    switch(op)
    {
      case 118: case 86: srchv();break;
      case 119: case 87: srchw();break;
      case 27: break;
      default : gotoxy(27,15);printf("Invalid Choice!   ");getch();
    }
  }while(op!=27);
}

int search(char id[])
{
  int n=1;
  rewind(fd);
  while(fread(&e,size,1,fd) == 1)
  {
    if(strcmp(e.id,id)!=0)   continue;
    else   { n=0; break;}
  }
  return(n);
}

void add()
{
  int num;
  do
  {
    clrscr();
    bo(10,4,70,20);gotoxy(32,4);printf(" ADD NEW RECORD ");
    lin(10,17,70);gotoxy(33,17);printf(" NOTIFICATIONS ");
    gotoxy(15,6);printf("Voter ID");gotoxy(39,6);printf(":");
    gotoxy(15,7);printf("Ward No");gotoxy(39,7);printf(":");
    gotoxy(15,8);printf("Ward Name");gotoxy(39,8);printf(":");
    gotoxy(15,9);printf("House No");gotoxy(39,9);printf(":");
    gotoxy(15,10);printf("Name");gotoxy(39,10);printf(":");
    gotoxy(15,11);printf("Age");gotoxy(39,11);printf(":");
    gotoxy(15,12);printf("Date of Birth");gotoxy(39,12);printf(":   /  /   (DD/MM/YY)");
    gotoxy(15,13);printf("Sex");gotoxy(39,13);printf(":");
    gotoxy(15,14);printf("Father's/Husband's Name");gotoxy(39,14);printf(":");
    gotoxy(15,15);printf("Address");gotoxy(39,15);printf(":");
    gotoxy(41,6);gets(vid);
    num=search(vid);
    if(num==0)
    {
      gotoxy(20,18); printf("Record Already Exists! Overwrite? (Y/N)");
      opt=getch();
      if(opt=='Y' || opt=='y')  num=1;
    }
    if(num==1)
    {
      strcpy(e.id,vid);
      gotoxy(41,7);scanf("%ld",&e.wno);fflush(stdin);
      gotoxy(41,8);gets(e.wname);fflush(stdin);
      gotoxy(41,9);scanf("%ld",&e.hno);fflush(stdin);
      gotoxy(41,10);gets(e.name);fflush(stdin);
      gotoxy(41,11);scanf("%d",&e.age);fflush(stdin);
      gotoxy(41,12);scanf("%d",&e.dd);fflush(stdin);
      gotoxy(44,12);scanf("%d",&e.mm);fflush(stdin);
      gotoxy(47,12);scanf("%d",&e.yy);fflush(stdin);
      gotoxy(41,13);scanf("%c",&e.sex);fflush(stdin);
      gotoxy(41,14);gets(e.gname);
      gotoxy(41,15);gets(e.add);fflush(stdin);
      fwrite(&e,size,1,fd); gotoxy(20,18); spc(41); gotoxy(27,18); printf("Record Added Successfully!");
    }
    gotoxy(28,19);printf("Add Another Record? (Y/N)"); opt=getch();
  }while(opt=='Y' || opt=='y');
}
void mod()
{
  int n=1;
  do
  {
    clrscr();
    bo(25,10,55,14);
    gotoxy(37,10);printf(" MODIFY ");
    gotoxy(30,12);printf("Enter VoterID : ");
    scanf("%s",vid);fflush(stdin);rewind(fd);clrscr();
    bo(10,8,70,20);gotoxy(33,8);printf(" ENTER NEW DATA ");
    while(fread(&e,size,1,fd)==1)
    {
      if(strcmpi(e.id,vid)==0)
      {
	gotoxy(15,10);printf("Ward No");gotoxy(39,10);printf(":");
	gotoxy(15,11);printf("Ward Name");gotoxy(39,11);printf(":");
	gotoxy(15,12);printf("House No");gotoxy(39,12);printf(":");
	gotoxy(15,13);printf("Name");gotoxy(39,13);printf(":");
	gotoxy(15,14);printf("Age");gotoxy(39,14);printf(":");
	gotoxy(15,15);printf("Date of Birth");gotoxy(39,15);printf(":   /  /   (DD/MM/YY)");
	gotoxy(15,16);printf("Sex");gotoxy(39,16);printf(":");
	gotoxy(15,17);printf("Father's/Husband's Name");gotoxy(39,17);printf(":");
	gotoxy(15,18);printf("Address");gotoxy(39,18);printf(":");
	gotoxy(41,10);scanf("%ld",&e.wno);fflush(stdin);
	gotoxy(41,11);gets(e.wname);fflush(stdin);
	gotoxy(41,12);scanf("%ld",&e.hno);fflush(stdin);
	gotoxy(41,13);gets(e.name);fflush(stdin);
	gotoxy(41,14);scanf("%d",&e.age);fflush(stdin);
	gotoxy(41,15);scanf("%d",&e.dd);fflush(stdin);
	gotoxy(44,15);scanf("%d",&e.mm);fflush(stdin);
	gotoxy(47,15);scanf("%d",&e.yy);fflush(stdin);
	gotoxy(41,16);scanf("%c",&e.sex);fflush(stdin);
	gotoxy(41,17);gets(e.gname);
	gotoxy(41,18);gets(e.add);fflush(stdin);
	fseek(fd,-size,SEEK_CUR);
	fwrite(&e,size,1,fd);
	n=0;break;
      }
    }
    clrscr();
    bo(24,10,56,15);
    gotoxy(37,10);printf(" MODIFY ");
    if(n==0) { gotoxy(26,12); printf("Record Modified Successfully!"); }
    else  { gotoxy(32,12); printf("Record Not Found!"); }
    gotoxy(27,13); printf("Modify Another Record?(Y/N)"); opt=getch();
  }while(opt=='Y' || opt=='y');
}
void del()
{
  do
  {
    int n=1;
    ft=fopen("DUP.TXT","wb+");
    clrscr();
    bo(25,10,56,15);
    gotoxy(37,10);printf(" DELETE ");
    gotoxy(30,12);printf("Enter VoterID : ");
    scanf("%s",vid);fflush(stdin);rewind(fd);
    gotoxy(30,12);spc(16);
    while(fread(&e,size,1,fd) == 1)
    {
      if(strcmpi(e.id,vid)!=0)  fwrite(&e,size,1,ft);
      else  n=0;
    }
    fclose(ft);
    if(n==0)
    {
      fclose(fd);
      remove("DATA.TXT");
      rename("DUP.TXT","DATA.TXT");
      fd=fopen("DATA.TXT","rb+");
      gotoxy(27,12); printf("Record Deleted Successfully!");
    }
    else  { gotoxy(32,12); printf("Record Not Found!"); }
    gotoxy(27,13); printf("Delete Another Record? (Y/N)"); opt=getch();
  }while(opt=='Y' || opt=='y');
}

void help()
{
  clrscr();
  bo(10,4,70,23);bo(23,3,55,5);gotoxy(24,4);printf(" VOTERS LIST MANAGEMENT SYSTEM ");
  gotoxy(35,7);printf("***HELP***");
  gotoxy(12,9);printf("This software allows you to manage voter details of voters");
  gotoxy(12,10);printf("of different wards. You can store, manipulate, remove and");
  gotoxy(12,11);printf("retrive voter details and search for them wards wise.");
  gotoxy(12,13);printf("The main features of this software are : ");
  gotoxy(15,14);printf("* Search Records Ward Wise & By VoterID");
  gotoxy(15,15);printf("* Add Voter Details");
  gotoxy(15,16);printf("* Modify Existing Records");
  gotoxy(15,17);printf("* Delete Existing Records");
  gotoxy(12,19);printf("This software is not case-sensitive!");
  gotoxy(35,21);printf("Coded & Designed By : Harikrishna.K");
  getch();
}

void quit()
{
  clrscr();
  bo(25,10,55,15);
  gotoxy(30,12);printf("Thank You For Using!");gotoxy(32,13);printf("Have A Nice Day!");
  getch();
  exit(0);
}

void main()
{
  int k,flag=0,l;
  char us[10],pw[10];
  fd=fopen("DATA.TXT","rb+");
  if(fd==NULL)
  {
    fd=fopen("DATA.TXT","wb+");
    if(fd==NULL)
    {
      printf("\nCan't Open File -> DATA.TXT");
    }
  }
  clrscr();
  /*splash screen*/
  textcolor(9);
  gotoxy(28,7);printf("VOTERS LIST MANAGEMENT SYSTEM");
  bo(10,5,75,23);
  lin(10,18,75);
  gotoxy(35,18);printf(" NOTIFICATIONS ");
  gotoxy(30,20);printf("Checking Files & Folders");
  lin(10,9,75);
  for(k=12;k<74;k++)
  {
    gotoxy(k,21);
    printf("º");
  }
  for(k=12;k<74;k++)
  {
    gotoxy(k,21);
    putch(219);
    delay(75);
  }
  /*end of the splash*/
  bo(31,11,54,16);gotoxy(39,11);printf(" LOGIN ");gotoxy(33,13);printf("Username : ");gotoxy(33,14);printf("Password : ");
  do
  {
    gotoxy(44,13);gets(us);gotoxy(44,14);gets(pw);
    l=strlen(pw);
    gotoxy(44,14);
    for(k=0;k<l;k++) printf("*");
    if(strcmpi(us,"admin")==0 && strcmpi(pw,"123")==0)
    {
      gotoxy(30,20);spc(25);
      gotoxy(36,20);printf("Loading Menu");
      for(k=12;k<74;k++)
      {
	gotoxy(k,21);
	printf("º");
      }
      for(k=12;k<74;k++)
      {
	gotoxy(k,21);
	putch(219);
	delay(75);
      }
      flag=0;
    }
    else
    {
      flag=1;
      gotoxy(12,21);spc(62);
      gotoxy(19,20);printf("Invalid Username Or Password! Hit Esc To Quit!");ch=getch();
      if(ch==27)
      {
	quit();
      }
      gotoxy(19,20);spc(46);gotoxy(44,13);spc(10);gotoxy(44,14);spc(10);
    }
  }while(flag!=0);
  do
  {
    clrscr();
    textcolor(9);
    bo(20,3,60,5);
    bo(20,6,60,23);
    gotoxy(27,4);printf("VOTERS LIST MANAGEMENT SYSTEM");
    gotoxy(35,6);printf(" MAIN MENU ");
    gotoxy(22,8);printf("S: Search Records");
    gotoxy(22,10);printf("A: Add Records");
    gotoxy(22,12);printf("M: Modify Records");
    gotoxy(22,14);printf("D: Delete Records");
    gotoxy(22,16);printf("H: Help");
    gotoxy(22,18);printf("Esc: Exit");
    lin(20,20,60);
    gotoxy(22,21);printf("Choose an option!");
    ch=getch();
    switch(ch)
    {
      case 115: case 83: srch();break;
      case 97: case 65: add();break;
      case 109: case 77: mod();break;
      case 100: case 68: del();break;
      case 104: case 72: help();break;
      case 27: quit();break;
      default : gotoxy(22,22);printf("Invalid Choice!");getch();
    }
  }while(ch!=27);
}
