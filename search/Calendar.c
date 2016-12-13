#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include <graphics.h>

typedef struct Meetings {
	int Hour;
	char *Name;
	char *Subject;
	struct Meetings *Next;
	struct Meetings *Prev;
}Meets;

typedef struct Days {
	int Day;
	struct Days *Next;
	struct Days *Prev;
	Meets *MeetHead;
}Days;

typedef struct Button {
	int LX;
	int LY;
	int RX;
	int RY;
	char Msg[31];
	int XMsg;
	int YMsg;
}Button;

Button Coordinats1[5]={ {80,90,220,130,"Add a meeting",97,107} , {250,90,390,130,"Cancel a meeting",257,107} , {420,90,560,130,"Update a meeting",427,107} ,
					   {250,210,390,250,"Print all",284,227} , {250,330,390,370,"Exit",305,347}
					  };

Button Coordinats2[3]={ {80,90,240,130,"Change the hour",95,107} , {80,210,240,250,"Change the date",97,227} , {80,330,360,370,"Free space for the new meeting",87,347}
					  };

Button Coordinats3[4]={ {80,90,220,130,"Delete by date",94,107} , {250,210,390,250,"Delete by name",265,227} , {420,330,610,370,"Delete by time interval",425,347} ,
					   {80,330,220,370,"Back to menu",100,347}
					  };

Button Coordinats4[4]={ {250,70,390,110,"Change the date",257,87} , {250,180,390,220,"Change the time",257,197} , {250,290,390,330,"Change the name",257,307} ,
					   {250,400,420,440,"Change the subject",250,417}
					  };

Button *Menus[4]={ Coordinats1,Coordinats2,Coordinats3,Coordinats4 };

//int GraphDriver=DETECT,GraphMode,ErrorCode,MaxColors;
Days *Head;

void InitMouse();
void ShowMouse();
void HideMouse();
int MouseHit();
void MousePos(int *,int *);
void InitGraphMode();
void ShowMenu(Button *,int);
void ShowCalendar();
int MouseChoice(int,int);
int WhichButton(int,int,Button *,int);
void ButtonNewColor(Button );
void ButtonOldColor(Button );
void Cases(int);
void AddAMeeting();
void CancelAMeeting();
void UpdateAMeeting();
void GetDetails(int);
int GetHour();
int GetDay();
void DeleteByDate();
void DeleteByName();
void DeleteByInterval();
Days *InsertMeeting(int,int,char *,char *);
Days *InsertDay();
Meets *InsertMeet();
void Sort(Days *);
Days *SearchSortDays(int);
Meets *SearchSortMeets(Meets *,int);
void SearchByName(char *,Days **,Meets **);
Days *PointDay(int);
Meets *MeetUnable(int,int);
Meets *DayFull(Days *);
Days *ChangeMeetTime(int,int,char *,char *);
Days *ChangeMeetDate(int,int,char *,char *);
void UpdateDay(int,Meets *);
void UpdateTime(int,Meets *);
void UpdateName(Meets *);
void UpdateSubject(Meets *);
void DeleteMeet(Days *,Meets *);
void DeleteDay(Days *);
void DeleteMeetings(Days *,int,int);
void FreeMeet(Meets *);
void FreeDay(Days *);
void FreeAll();
void PrintDay(int,int,int,int);
void PrintAll();

void main()
{
	int Choice=0;
	clrscr();
	InitGraphMode();
	InitMouse();
	ShowMouse();
	while (Choice!=4)
	{
		ShowMenu(Menus[0],5);
		Choice=MouseChoice(0,5);
		Cases(Choice);
	}
	HideMouse();
	closegraph();
	FreeAll();
}

void InitMouse()
{
	union REGS i,o;
	i.x.ax=0;
	int86(0x33,&i,&o);
	if (o.x.ax==0)
	{
		printf("No mouse.");
		getch();
		exit(1);
	}
}

void ShowMouse()
{
	union REGS i,o;
	i.x.ax=1;
	int86(0x33,&i,&o);
}

void HideMouse()
{
	union REGS i,o;
	i.x.ax=2;
	int86(0x33,&i,&o);
}

int MouseHit()
{
	union REGS i,o;
	i.x.ax=3;
	int86(0x33,&i,&o);
	return(o.x.bx&7);
}

void MousePos(int *PosX,int *PosY)
{
	union REGS i,o;
	i.x.ax=3;
	int86(0x33,&i,&o);
	*PosX=o.x.cx;
	*PosY=o.x.dx;
}

void InitGraphMode()
{
	initgraph(&GraphDriver,&GraphMode,"");
	ErrorCode=graphresult();
	if (ErrorCode!=grOk)
		exit(1);
	MaxColors=getmaxcolor()+1;
}

void ShowMenu(Button *Num,int Mis)
{
	int i;
	HideMouse();
	setfillstyle(SOLID_FILL,3);
	floodfill(1,1,3);
	for (i=0;i<Mis;i++)
	{
		setcolor(9);
		setlinestyle(SOLID_LINE,0,THICK_WIDTH);
		setfillstyle(SOLID_FILL,9);
		rectangle((Num+i)->LX,(Num+i)->LY,(Num+i)->RX,(Num+i)->RY);
		floodfill(((Num+i)->LX)+5,((Num+i)->LY)+5,9);
		setcolor(4);
		rectangle((Num+i)->LX,(Num+i)->LY,(Num+i)->RX,(Num+i)->RY);
		outtextxy((Num+i)->XMsg,(Num+i)->YMsg,(Num+i)->Msg);
	}
	ShowMouse();
}

void ButtonNewColor(Button Butt)
{
	HideMouse();
	setfillstyle(SOLID_FILL,4);
	floodfill(Butt.LX+5,Butt.LY+5,4);
	setcolor(9);
	outtextxy(Butt.XMsg,Butt.YMsg,Butt.Msg);
	ShowMouse();
}

void ButtonOldColor(Button Butt)
{
	HideMouse();
	setcolor(9);
	setlinestyle(SOLID_LINE,0,THICK_WIDTH);
	setfillstyle(SOLID_FILL,9);
	rectangle(Butt.LX,Butt.LY,Butt.RX,Butt.RY);
	floodfill(Butt.LX+5,Butt.LY+5,9);
	setcolor(4);
	rectangle(Butt.LX,Butt.LY,Butt.RX,Butt.RY);
	outtextxy(Butt.XMsg,Butt.YMsg,Butt.Msg);
	ShowMouse();
}

int WhichButton(int X,int Y,Button *Num,int Mis)
{
	int i=0,f=0;
	while (i<Mis && f==0)
	{
		if (X>=(Num+i)->LX && X<=(Num+i)->RX && Y>=(Num+i)->LY && Y<=(Num+i)->RY)
			f=1;
		i++;
	}
	if (f==1)
		return (i-1);
	else
		return (-1); //Not on a button.
}

int MouseChoice(int Num,int Mis)
{
	int flag=1; // The cursor is not on a button.
	int X,Y,OldX,OldY,CH,OldCH;
	while (flag!=0) // while the mouse isn't pressed.
	{
		MousePos(&X,&Y);
		if (flag==1)
		{
			CH=WhichButton(X,Y,Menus[Num],Mis);
			if (CH!=-1)
			{
				flag=2; // The cursor is on a button.
				ButtonNewColor(*(Menus[Num]+CH));
			}
		}
		else
			if (flag==2)
			{
				CH=WhichButton(X,Y,Menus[Num],Mis);
				if (CH!=OldCH)
				{
					ButtonOldColor(*(Menus[Num]+WhichButton(OldX,OldY,Menus[Num],Mis)));
					if (CH==-1)
						flag=1; // The cursor is not on a button.
				}
			}
		OldX=X;
		OldY=Y;
		OldCH=CH;
		if (MouseHit()!=0)
		{
			CH=WhichButton(X,Y,Menus[Num],Mis);
			if (CH!=-1)
				flag=0;
		}
	}
	return(CH);
}

int GetDay()
{
	int Day=0,X=0,Y=0,flag=0,MH,f1=0;
	while (flag!=1 && f1!=1)
	{
		MH=MouseHit();
		if (MH!=0)
		{
			MousePos(&X,&Y);
			if (X>=75 && Y>=65)
			{
				X=(X-75)/50+1;
				Y=(Y-65)/50+1;
			}
			if (X>=1 && X<=7 && Y>=1 && Y<=5)
				Day=(Y-1)*7+X;
		}
		if (MH==2 && (Day>=1 && Day<=30) && (Day%7!=0))
		{
			PrintDay(Day,480,30,1);
			Day=0;
		}
		if ((Day>=1 && Day<=30) && (Day%7!=0) && MH==1)
			flag=1;
		if (MH==1 && X>=5 && X<=103 && Y>=400 && Y<=440)
			f1=1;
	}
	if (flag==1)
		return (Day);
	else
		return(-1);
}

int GetHour()
{
	int H,M,Hour;
	fflush(stdin);
	do
	{
		printf("Enter the hour (9-22): ");
		scanf("%d",&H);
	}
	while(H<9 || H>22);
	do
	{
		printf("Enter the minute (0-59): ");
		scanf("%d",&M);
	}
	while(M<0 || M>59);
	Hour=H*60+M;
	return(Hour);
}

void Cases(int CH)
{
	switch(CH) {
			case 0:
				   AddAMeeting();
				   break;
			case 1:
				   CancelAMeeting();
				   break;
			case 2:
				   UpdateAMeeting();
				   break;
			case 3:
				   PrintAll();
				   break;
			default:
					break;
	}
}

void ShowCalendar()
{
	int X,Y,NumDay=1;
	char Day[2];
	setcolor(1);
	setlinestyle(SOLID_LINE,0,NORM_WIDTH);
	setfillstyle(SOLID_FILL,1);
	floodfill(1,1,1);
	for (Y=65;Y<315;Y+=50)
		for (X=75;X<425;X+=50)
		{
			setcolor(11);
			rectangle(X,Y,X+50,Y+50);
			if (NumDay%7!=0)
			{
				if (NumDay<=30)
					setfillstyle(SOLID_FILL,11);
				else
					setfillstyle(BKSLASH_FILL,11);
				floodfill(X+1,Y+1,11);
				setcolor(0);
				rectangle(X,Y,X+50,Y+50);
			}
			else
			{
				if (NumDay<=30)
					setfillstyle(INTERLEAVE_FILL,11);
				else
					setfillstyle(BKSLASH_FILL,11);
				floodfill(X+1,Y+1,11);
				setcolor(0);
				rectangle(X,Y,X+50,Y+50);
			}
			if (NumDay<=30)
			{
				strcpy(Day,itoa(NumDay,Day,10));
				outtextxy(X+25,Y+25,Day);
				NumDay=atoi(Day);
			}
			NumDay++;
		}
	setcolor(11);
	setfillstyle(SOLID_FILL,11);
	rectangle(5,400,103,440);
	floodfill(6,401,11);
	setcolor(0);
	rectangle(5,400,103,440);
	outtextxy(7,415,"Back to menu");
	outtextxy(5,5,"Left button chooses a day.");
	outtextxy(5,5+textheight("H")*2,"Right button prints all meeting on the chosen day.");
}

void AddAMeeting()
{
	int Day;
	cleardevice();
	HideMouse();
	ShowCalendar();
	ShowMouse();
	Day=GetDay();
	if (Day!=-1)
	{
		HideMouse();
		restorecrtmode();
		GetDetails(Day);
		setgraphmode(getgraphmode());
		ShowMouse();
	}
}

void GetDetails(int day)
{
	int hour,Choice;
	char subject[30],name[20],*PName=NULL,*PSubject=NULL;
	Days *P;
	hour=GetHour();
	do
	{
		fflush(stdin);
		printf("Enter the name: ");
		gets(name);
	}
	while(strlen(name)==0);
	PName=(char *)malloc(strlen(name)*sizeof(char)+1);
	if (PName==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	strcpy(PName,name);
	printf("Enter the subject of the meeting: ");
	gets(subject);
	PSubject=(char *)malloc(strlen(subject)*sizeof(char)+1);
	if (PSubject==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	strcpy(PSubject,subject);
	if (MeetUnable(day,hour)!=NULL)
	{
		printf("Unable to set up the meeting.");
		getch();
		setgraphmode(getgraphmode());
		ShowMouse();
		ShowMenu(Menus[1],3);
		Choice=MouseChoice(1,3);
		HideMouse();
		restorecrtmode();
		if (Choice==0)
			P=ChangeMeetTime(day,hour,PName,PSubject);
		else
			if (Choice==1)
				P=ChangeMeetDate(day,hour,PName,PSubject);
			else
			{
				DeleteMeet(PointDay(day),MeetUnable(day,hour));
				if (MeetUnable(day,hour)!=NULL)
					DeleteMeet(PointDay(day),MeetUnable(day,hour));
				P=InsertMeeting(day,hour,PName,PSubject);
			}
	}
	else
		P=InsertMeeting(day,hour,PName,PSubject);
	if (P!=NULL)
		Sort(P);
}

Days *InsertMeeting(int Day,int Hour,char *Name,char *Subject)
{
	Days *p;
	p=InsertDay();
	p->Day=Day;
	p->MeetHead=InsertMeet();
	(p->MeetHead)->Hour=Hour;
	(p->MeetHead)->Name=Name;
	(p->MeetHead)->Subject=Subject;
	(p->MeetHead)->Next=NULL;
	(p->MeetHead)->Prev=NULL;
	return(p);
}

Days *InsertDay()
{  //Allocates space for a new structure
	Days *p;
	p=(Days *)malloc(1*sizeof(Days));
	if(p==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	return (p);
}

Meets *InsertMeet()
{  //Allocates space for a new structure
	Meets *p;
	p=(Meets *)malloc(1*sizeof(Meets));
	if(p==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	return (p);
}

Days *DayBefore(Days *EndSearch)
{
	Days *Pnt=Head;
	while(Pnt->Next!=EndSearch)
		Pnt=Pnt->Next;
	return (Pnt);
}

Meets *MeetBefore(Meets *Pnt,Meets *EndSearch)
{
	while(Pnt->Next!=EndSearch)
		Pnt=Pnt->Next;
	return (Pnt);
}

void Sort(Days *p)
{
	Days *PntDays;
	Meets *PntMeets;
	if (Head==NULL)
	{
		Head=p;
		Head->Next=NULL;
		Head->Prev=NULL;
		(Head->MeetHead)->Next=NULL;
		(Head->MeetHead)->Prev=NULL;
	}
	else
	{
		PntDays=PointDay(p->Day);
		if (PntDays==NULL)
		{
			PntDays=SearchSortDays(p->Day);
			if (PntDays==Head)
			{
				p->Prev=NULL;
				p->Next=PntDays;
				PntDays->Prev=p;
				Head=p;
			}
			else if(PntDays==NULL)
			{
				p->Next=NULL;
				p->Prev=DayBefore(NULL);
				(p->Prev)->Next=p;
			}
			else
			{
				p->Next=PntDays;
				p->Prev=PntDays->Prev;
				(PntDays->Prev)->Next=p;
				PntDays->Prev=p;
			}
		}
		else
		{
			PntMeets=SearchSortMeets(PntDays->MeetHead,(p->MeetHead)->Hour);
			if (PntMeets==PntDays->MeetHead)
			{
				(p->MeetHead)->Prev=NULL;
				(p->MeetHead)->Next=PntMeets;
				//PntMeets->Prev=(p->MeetHead);
				PntDays->MeetHead=p->MeetHead;
			}
			else if(PntMeets==NULL)
			{
				(p->MeetHead)->Next=NULL;
				(p->MeetHead)->Prev=MeetBefore(PntDays->MeetHead,NULL);
				((p->MeetHead)->Prev)->Next=p->MeetHead;
			}
			else
			{
				(p->MeetHead)->Next=PntMeets;
				(p->MeetHead)->Prev=PntMeets->Prev;
				(PntMeets->Prev)->Next=p->MeetHead;
				PntMeets->Prev=p->MeetHead;
			}
		}
	}
}

Days *SearchSortDays(int Day)
{
	Days *Temp=Head;
	while (Day>Temp->Day && Temp!=NULL)
		Temp=Temp->Next;
	return(Temp); //The pointer to the day after the day to be added
}

Meets *SearchSortMeets(Meets *p,int Hour)
{
	Meets *Temp=p;
	while (Hour>Temp->Hour && Temp!=NULL)
		Temp=Temp->Next;
	return(Temp); //The pointer to the meet after the meet to be added
}

void SearchByName(char *Name,Days **p1,Meets **p2)
{
	int f=0,temp;
	Days *PDay=Head;
	Meets *PMeet;
	while (PDay!=NULL && f==0)
	{
		PMeet=PDay->MeetHead;
		while (PMeet!=NULL && f==0)
		{
			temp=strcmpi(PMeet->Name,Name);
			if (temp==0)
				f=1;
			else
				PMeet=PMeet->Next;
		}
		if (f==0)
			PDay=PDay->Next;
	}
	if (f==1)
	{
		*p2=PMeet;
		*p1=PDay;
	}
	else
	{
		*p1=NULL;
		*p2=NULL;
	}
}

Days *PointDay(int Day)
{
	Days *Temp=Head;
	while (Day!=Temp->Day && Temp!=NULL)
		Temp=Temp->Next;
	return(Temp); //The pointer to Day
}

Meets *PointMeet(Days *PDay,int Hour)
{
	Meets *PMeet=PDay->MeetHead;
	while (Hour!=PMeet->Hour && PMeet!=NULL)
		PMeet=PMeet->Next;
	return(PMeet); //The pointer to the meeting set on Hour
}

Meets *MeetUnable(int Day,int Hour)
{
	Days *p1;
	Meets *p2;
	p1=PointDay(Day);
	if(p1!=NULL)
	{
		p2=p1->MeetHead;
		while (p2!=NULL && (abs(p2->Hour-Hour)>=30))
			p2=p2->Next;
		return(p2);
	}
	else
		return (NULL);
}

Meets *DayFull(Days *P)
{
	Meets *PMeet;
	if (P!=NULL)
	{
		PMeet=P->MeetHead;
		while (PMeet->Next!=NULL && ((PMeet->Next)->Hour-PMeet->Hour)<60)
			PMeet=PMeet->Next;
		return(PMeet);
	}
	else
		return(Head->MeetHead-1); //addres that's diffrent than NULL
}

Days * ChangeMeetTime(int day,int hour,char *name,char *subject)
{
	int H,M,timeMeet,f=1;
	int Choice;
	Meets *p;
	do
	{
		timeMeet=GetHour();
		p=MeetUnable(day,timeMeet);
		if (p!=NULL)
		{
			printf("The meeting still cannot be set!");
			getch();
			setgraphmode(getgraphmode());
			ShowMouse();
			ShowMenu(Menus[1],3);
			Choice=MouseChoice(1,3);
			HideMouse();
			restorecrtmode();
			if (Choice==0)
				return(ChangeMeetTime(day,hour,name,subject));
			else
				if (Choice==1)
					return(ChangeMeetDate(day,hour,name,subject));
				else
				{
					DeleteMeet(PointDay(day),MeetUnable(day,hour));
					if (MeetUnable(day,hour)!=NULL)
						DeleteMeet(PointDay(day),MeetUnable(day,hour));
					return(InsertMeeting(day,hour,name,subject));
				}
		}
		else
			f=0;
	}
	while (f==1);
	if (f==0)
		return (InsertMeeting(day,timeMeet,name,subject));
	else
		return (NULL);
}

Days * ChangeMeetDate(int day,int hour,char *name,char *subject)
{
	int Day1,f=0,Choice;
	setgraphmode(getgraphmode());
	do
	{
		ShowCalendar();
		ShowMouse();
		Day1=GetDay();
		if (Day1==day)
		{
			HideMouse();
			cleardevice();
			setcolor(3);
			settextstyle(4,0,0);
			outtextxy(0,220,"You entered the same date!");
			outtextxy(0,220+textheight("H"),"Press any key to choose a new date.");
			getch();
			settextstyle(0,0,0);
		}
		else
		if (Day1==-1)
			f=2;
		else
		{
			if (MeetUnable(Day1,hour)!=NULL)
			{
				restorecrtmode();
				printf("The meeting still cannot be set!");
				getch();
				setgraphmode(getgraphmode());
				ShowMouse();
				ShowMenu(Menus[1],3);
				Choice=MouseChoice(1,3);
				HideMouse();
				restorecrtmode();
				if (Choice==0)
					return(ChangeMeetTime(Day1,hour,name,subject));
				else
					if (Choice==1)
						return(ChangeMeetDate(Day1,hour,name,subject));
					else
					{
						DeleteMeet(PointDay(Day1),MeetUnable(Day1,hour));
						if (MeetUnable(Day1,hour)!=NULL)
							DeleteMeet(PointDay(Day1),MeetUnable(Day1,hour));
						return(InsertMeeting(Day1,hour,name,subject));
					}
			}
			else
				f=1;
		}
	}
	while(f==0);
	if (f!=1)
		return (NULL);
	else
		return (InsertMeeting(Day1,hour,name,subject));
}

void CancelAMeeting()
{
	int Choice;
	HideMouse();
	cleardevice();
	if (Head!=NULL)
	{
		ShowMenu(Menus[2],4);
		ShowMouse();
		Choice=MouseChoice(2,4);
		if (Choice==0)
			DeleteByDate();
		else
			if (Choice==1)
				DeleteByName();
			else
				if (Choice==2)
					DeleteByInterval();
	}
	else
	{
		setcolor(3);
		settextstyle(4,0,0);
		outtextxy(0,220,"There are no meetings to delete at all!");
		outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
		getch();
		settextstyle(0,0,0);
	}
	cleardevice();
	ShowMouse();
}

void DeleteByDate()
{
	int Day;
	Days *Pnt;
	HideMouse();
	ShowCalendar();
	ShowMouse();
	Day=GetDay();
	Pnt=PointDay(Day);
	if (Pnt!=NULL)
		DeleteDay(Pnt);
	else
	{
		HideMouse();
		cleardevice();
		setcolor(3);
		settextstyle(4,0,0);
		outtextxy(0,220,"There are no meetings on this date!");
		outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
		getch();
		settextstyle(0,0,0);
		cleardevice();
		ShowMouse();
	}
}

void DeleteByName()
{
	char Name[20],ch,*PName;
	Days *PDay;
	Meets *PMeet;
	int f=0;
	HideMouse();
	restorecrtmode();
	do
	{
		do
		{
			fflush(stdin);
			printf("Enter a name: ");
			gets(Name);
		}
		while(strlen(Name)==0);
		PName=(char *)malloc(strlen(Name)*sizeof(char));
		strcpy(PName,Name);
		SearchByName(PName,&PDay,&PMeet);
		if (PMeet==NULL)
		{
			printf("The name wasn't found!\n");
			do
			{
				fflush(stdin);
				printf("Would you like to enter a new name? (Y/N): ");
				scanf("%c",&ch);
			}
			while (ch!='y' && ch!='Y' && ch!='n' && ch!='N');
			if (ch=='n' || ch=='N')
				f=1;
		}
		else
		{
			do
			{
				DeleteMeet(PDay,PMeet);
				SearchByName(PName,&PDay,&PMeet);
			}
			while(PDay!=NULL);
			f=1;
		}
	}
	while (f==0);
	setgraphmode(getgraphmode());
	ShowMouse();
}

void DeleteByInterval()
{
	int Day,HourBeg,HourEnd,H,M;
	Days *Pnt;
	HideMouse();
	ShowCalendar();
	ShowMouse();
	Day=GetDay();
	Pnt=PointDay(Day);
	if (Pnt!=NULL)
	{
		HideMouse();
		restorecrtmode();
		do
		{
			printf("Enter the hour you want to start deleting from (9-22): ");
			scanf("%d",&H);
		}
		while (H<9 || H>22);
		do
		{
			printf("Enter the minute you want to start deleting from (0-59): ");
			scanf("%d",&M);
		}
		while (M<0 || M>59);
		HourBeg=H*60+M;
		do
		{
			printf("Enter the last hour you want to delete (9-22): ");
			scanf("%d",&H);
		}
		while (H<9 || H>22);
		do
		{
			printf("Enter the last minute you want to delete (0-59): ");
			scanf("%d",&M);
		}
		while (M<0 || M>59);
		HourEnd=H*60+M;
		if (HourBeg>HourEnd)
		{
			H=HourBeg;
			HourBeg=HourEnd;
			HourEnd=H;
		}
		if ((MeetBefore(Pnt->MeetHead,NULL))->Hour<HourBeg)
		{
			setgraphmode(getgraphmode());
			setcolor(3);
			settextstyle(4,0,0);
			outtextxy(0,220,"There are no meetings to delete on this period of time!");
			outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
			getch();
			settextstyle(0,0,0);
			cleardevice();
			ShowMouse();
		}
		else
		{
			DeleteMeetings(Pnt,HourBeg,HourEnd);
			setgraphmode(getgraphmode());
			ShowMouse();
		}
	}
	else if (Day!=-1)
	{
		HideMouse();
		cleardevice();
		setcolor(3);
		settextstyle(4,0,0);
		outtextxy(0,220,"There are no meetings on this date!");
		outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
		getch();
		settextstyle(0,0,0);
		cleardevice();
		ShowMouse();
	}
}

void UpdateAMeeting()
{
	int Choice,Day,Hour,f=0;
	char ch;
	Meets *PMeet;
	HideMouse();
	if (Head!=NULL)
	{
		ShowCalendar();
		ShowMouse();
		Day=GetDay();
		if (PointDay(Day)!=NULL)
		{
			HideMouse();
			do
			{
				restorecrtmode();
				Hour=GetHour();
				PMeet=PointMeet(PointDay(Day),Hour);
				if (PMeet!=NULL)
				{
					setgraphmode(getgraphmode());
					ShowMenu(Menus[3],4);
					ShowMouse();
					Choice=MouseChoice(3,4);
					switch (Choice) {
									case 0:
										   UpdateDay(Day,PMeet);
										   break;
									case 1:
										   UpdateTime(Day,PMeet);
										   break;
									case 2:
										   UpdateName(PMeet);
										   break;
									case 3:
										   UpdateSubject(PMeet);
										   break;
					}
					f=0;
				}
				else
				{
					printf("There is no meeting on this exect time!\n");
					do
					{
						fflush(stdin);
						printf("Would you like to enter a new time? (Y/N): ");
						scanf("%c",&ch);
					}
					while (ch!='y' && ch!='Y' && ch!='n' && ch!='N');
					if (ch=='y' || ch=='Y')
						f=1;
					else
						f=0;
				}
			}
			while (f==1);
		}
		else if (Day!=-1)
		{
			HideMouse();
			cleardevice();
			setcolor(3);
			settextstyle(4,0,0);
			outtextxy(0,220,"There are no meetings on this date!");
			outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
			getch();
			settextstyle(0,0,0);
			cleardevice();
		}
	}
	else
	{
		cleardevice();
		setcolor(3);
		settextstyle(4,0,0);
		outtextxy(0,220,"There are no meetings to update at all!");
		outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
		getch();
		settextstyle(0,0,0);
		cleardevice();
	}
	setgraphmode(getgraphmode());
	ShowMouse();
}

void UpdateDay(int day,Meets *PMeet)
{
	Days *P;
	int Hour=PMeet->Hour;
	char *Name=PMeet->Name,*Subject=PMeet->Subject;
	restorecrtmode();
	DeleteMeet(PointDay(day),PMeet);
	P=ChangeMeetDate(day,Hour,Name,Subject);
	if (P!=NULL)
		Sort(P);
	setgraphmode(getgraphmode());
}

void UpdateTime(int day,Meets *PMeet)
{
	Days *P;
	int Hour=PMeet->Hour;
	char *Name=PMeet->Name,*Subject=PMeet->Subject;
	restorecrtmode();
	DeleteMeet(PointDay(day),PMeet);
	P=ChangeMeetTime(day,Hour,Name,Subject);
	if (P!=NULL)
		Sort(P);
	setgraphmode(getgraphmode());
}

void UpdateName(Meets *PMeet)
{
	char name[20],*PName=NULL;
	restorecrtmode();
	clrscr();
	do
	{
		fflush(stdin);
		printf("Enter the new name: ");
		gets(name);
	}
	while(strlen(name)==0);
	PName=(char *)malloc(strlen(name)*sizeof(char)+1);
	if (PName==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	strcpy(PName,name);
	PMeet->Name=PName;
	setgraphmode(getgraphmode());
}

void UpdateSubject(Meets *PMeet)
{
	char subject[20],*PSubject=NULL;
	restorecrtmode();
	clrscr();
	fflush(stdin);
	printf("Enter the new subject: ");
	gets(subject);
	PSubject=(char *)malloc(strlen(subject)*sizeof(char)+1);
	if (PSubject==NULL)
	{
		printf("Don't you think you're over-reacting?\n");
		exit(1);
	}
	strcpy(PSubject,subject);
	PMeet->Subject=PSubject;
	setgraphmode(getgraphmode());
}

void DeleteMeet(Days *PDay,Meets *PMeet)
{
	if (PMeet==PDay->MeetHead)
	{
		PDay->MeetHead=PMeet->Next;
		if (PMeet->Next!=NULL)
			(PMeet->Next)->Prev=NULL;
	}
	else
	{
		(PMeet->Prev)->Next=PMeet->Next;
		if (PMeet->Next!=NULL)
			(PMeet->Next)->Prev=PMeet->Prev;
	}
	FreeMeet(PMeet);
	if (PDay->MeetHead==NULL)
		DeleteDay(PDay);
}

void DeleteDay(Days *PDay)
{
	if (PDay==Head)
	{
		Head=PDay->Next;
		if (PDay->Next!=NULL)
			(PDay->Next)->Prev=NULL;
	}
	else
	{
		(PDay->Prev)->Next=PDay->Next;
		if (PDay->Next!=NULL)
			(PDay->Next)->Prev=PDay->Prev;
	}
	FreeDay(PDay);
}

void DeleteMeetings(Days *PDay,int HourBeg,int HourEnd)
{
	Meets *PMeet=PDay->MeetHead,*Temp;
	while (PMeet->Hour<=HourEnd && PMeet!=NULL)
	{
		Temp=PMeet->Next;
		if (PMeet->Hour<=HourEnd && PMeet->Hour>=HourBeg)
			DeleteMeet(PDay,PMeet);
		PMeet=Temp;
	}
}

void FreeMeet(Meets *Pnt)
{
	free(Pnt->Name);
	free(Pnt->Subject);
	free(Pnt);
}

void FreeDay(Days *Pnt)
{
	Meets *p=Pnt->MeetHead,*Temp;
	while (p!=NULL)
	{
		Temp=p->Next;
		FreeMeet(p);
		p=Temp;
	}
	free(Pnt);
}

void FreeAll()
{
	Days *p=Head,*Temp;
	while (p!=NULL)
	{
		Temp=p->Next;
		FreeDay(p);
		p=Temp;
	}
	free(Head);
}

void PrintDay(int Day,int X,int Y,int flag)
{
	Meets *PMeet;
	Days *PDay;
	char H[3],M[3],day[3];
	int X1,Y1=0;
	if (flag==1)
	{
		cleardevice();
		HideMouse();
		ShowCalendar();
		ShowMouse();
	}
	outtextxy(X,Y,"Meetings on day ");
	outtextxy(X+textwidth("Meetings on day "),Y,itoa(Day,day,10));
	PDay=PointDay(Day);
	if (PDay!=NULL)
	{
		PMeet=PDay->MeetHead;
		setcolor(9);
		while (PMeet!=NULL)
		{
			strcpy(H,itoa((PMeet->Hour)/60,H,10));
			strcpy(M,itoa((PMeet->Hour)%60,M,10));
			if (strlen(H)==1)
				X1=textwidth("H");
			else
				X1=textwidth("HH");
			outtextxy(X,Y1+20+Y,H);
			outtextxy(X1+X,Y1+20+Y,":");
			X1+=textwidth(":");
			outtextxy(X1+X,Y1+20+Y,M);
			if (strlen(M)==1)
				X1+=textwidth("HH");
			else
				X1+=textwidth("HHH");
			outtextxy(X1+X,Y1+20+Y,PMeet->Name);
			Y1+=textheight("H");
			outtextxy(X1+X,Y1+20+Y,PMeet->Subject);
			X1=0;
			Y1+=textheight("H");
			PMeet=PMeet->Next;
		}
	}
}

void PrintAll()
{
	int X=30,Y=30;
	Days *PDay=Head;
	HideMouse();
	cleardevice();
	if (Head==NULL)
	{
		setcolor(3);
		settextstyle(4,0,0);
		outtextxy(0,220,"There are no meetings at all!");
		outtextxy(0,220+textheight("H"),"Press any key to go back to the main menu.");
		getch();
		settextstyle(0,0,0);
		cleardevice();
	}
	else
	{
		while (PDay!=NULL)
		{
			HideMouse();
			PrintDay(PDay->Day,X,Y,0);
			ShowMouse();
			PDay=PDay->Next;
			X+=150;
			if (X>=600)
			{
				X=30;
				Y+=220;
			}
			if(Y>250)
			{
				outtextxy(435,460,"Press any key to continue");
				getch();
				cleardevice();
				X=30;
				Y=30;
			}
		}
		if (X!=30)
			getch();
	}
	ShowMouse();
}
