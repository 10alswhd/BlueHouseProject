#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define FALSE 0
#define TRUE !FALSE
 
 /* Code de touche clavier renvoyée par ReadKey */
#define kbNoKey 0 /* Pas de touche */
#define kbEsc 0x011B /* Escape */
#define kbUp 0x4800 /* Up */
#define kbLeft 0x4B00 /* Flèche de gauche (Left) */
#define kbKeypad5 0x4CF0 /* 5 du bloc numérique */
#define kbRight 0x4D00 /* Flèche de droite (Right) */
#define kbDn 0x5000 /* Flèche du bas (Down) */
 
typedef struct {
  enum {tmNone,tmStart,tmPlay,tmGameOver} Mode;
  int  Level;
  long Score;
  unsigned Bar,SLevel;
  char Tbl[21][10];
  char Form,Move;
  int X,Y,Sleep;
  int Touch,Ok;
  int SleepDelay;
  unsigned FBar;
  char UpDate;
} TetrisGame;
 
char BlkHeight[7][4]  = {
  {4,1,4,1}, /* Barre */
  {2,2,2,2}, /* Boîte */
  {3,2,3,2}, /* V */
  {3,2,3,2}, /* L gauche */
  {3,2,3,2}, /*/ L droite */
  {3,2,3,2}, /* Serpent romain */
  {3,2,3,2}  /* Serpent arabe */
};
/* Largeur des objets: */
char BlkLength[7][4] = {
  {1,4,1,4}, /* Barre */
  {2,2,2,2}, /* Boîte */
  {2,3,2,3}, /* V */
  {2,3,2,3}, /* L gauche */
  {2,3,2,3}, /* L droite */
  {2,3,2,3}, /* Serpent romain */
  {2,3,2,3}  /* Serpent arabe */
};
char BlkFormatX[7][4][4]={
  {{0,0,0,0},   /* OOOO */
   {0,1,2,3},
   {0,0,0,0},
   {0,1,2,3}},
  {{0,1,0,1},   /* OO */
   {0,1,0,1},   /* OO */
   {0,1,0,1},
   {0,1,0,1}},
  {{1,0,1,1},  /* OOO */
   {1,0,1,2},   /* O */
   {0,0,1,0},
   {0,1,2,1}},
  {{0,0,0,1},
   {0,1,2,2},   /* O */
   {0,1,1,1},   /* O */
   {0,1,2,0}},  /* OO */
  {{1,1,1,0},
   {0,1,2,0},   /* O */
   {1,0,0,0},   /* O */
   {0,1,2,2}},  /* OO */
  {{0,0,1,1},
   {1,2,0,1},
   {0,0,1,1},
   {1,2,0,1}},
  {{1,0,1,0},
   {0,1,1,2},
   {1,0,1,0},   /*OO */
   {0,1,1,2}} /* OO */
  };
char BlkFormatY[7][4][4]={
  {{0,1,2,3},   /* OOOO */
   {0,0,0,0},
   {0,1,2,3},
   {0,0,0,0}},
  {{0,0,1,1},   /* OO */
   {0,0,1,1},   /* OO */
   {0,0,1,1},
   {0,0,1,1}},
  {{0,1,1,2},   /* OOO */
   {0,1,1,1},   /* O */
   {0,1,1,2},
   {0,0,0,1}},
  {{0,1,2,2},
   {1,1,1,0},   /* O */
   {0,0,1,2},   /* O */
   {0,0,0,1}},  /* OO */
  {{0,1,2,2},
   {1,1,1,0},   /* O */
   {0,0,1,2},   /* O */
   {0,0,0,1}},  /*OO */
  {{0,1,1,2},
   {0,0,1,1},
   {0,1,1,2},
   {0,0,1,1}},
  {{0,1,1,2},
   {0,0,1,1},
   {0,1,1,2},   /*OO*/
   {0,0,1,1}}  /* OO */
  };
 
 
char TetrisInit(TetrisGame *Q);
void TetrisStart(TetrisGame *Q);
void TetrisRefresh(TetrisGame *Q);
unsigned TetrisPlay(TetrisGame *Q);
 
#define HomeX 15
#define HomeY 2
 
void WaitRetrace() {
 delay((int *)(1000/60));
}
 
#define Chr(X) (X & 0xFF)
 
void TextAttr(char Attr) {
 textcolor(Attr & 0xF);
 textbackground(Attr >> 4);
}
 
void BarSpcHor(char X1,char Y,char X2) {
 window(X1,Y,X2,Y);
 clrscr();
 window(1,1,40,25);
}
 
char TetrisInit(TetrisGame *Q) {
 memset(&(*Q),0,sizeof((*Q)));
 (*Q).Level=1;
 (*Q).Mode=tmStart;
}
 
void TetrisStart(TetrisGame *Q) {
 char I;
 memset(&(*Q).Tbl,FALSE,sizeof((*Q).Tbl));
 memset(&(*Q).Tbl[20],TRUE,sizeof((*Q).Tbl[20]));
 (*Q).Score=0;(*Q).Bar=0;(*Q).SleepDelay=25;(*Q).Level=(*Q).SLevel;
 for(I=0;I<(*Q).SLevel;I++) if((*Q).SleepDelay>6) (*Q).SleepDelay-=2;
 (*Q).FBar=(*Q).Level << 4;
 (*Q).Mode=tmStart;
}
 
void TetrisRefresh(TetrisGame *Q) {
 char I,J;
 textbackground(1+(*Q).Level);
 clrscr();
 gotoxy(3,2);printf("Niveau:");
 gotoxy(4,3);printf("%i",(*Q).Level);
 gotoxy(3,5);printf("Pointage:");
 gotoxy(4,6);printf("0");
 gotoxy(3,8);printf("Ligne:");
 gotoxy(4,9);printf("%i",(*Q).Bar);
 window(HomeX,HomeY,HomeX+9,HomeY+19);
 textbackground(BLACK);
 clrscr();
 window(1,1,40,25);
 if((*Q).Mode==tmPlay || (*Q).Mode==tmGameOver) {
  for(J=0;J<=19;J++) for(I=0;I<=9;I++) if((*Q).Tbl[J][I]) {
   gotoxy(HomeX+I,HomeY+J);printf("þ");
  }
 }
}
 
void TetrisPutForm(TetrisGame *Q, char Clr) {
  char Chr;
  char I,Attr,X,Y;
  X=HomeX+(*Q).X;
  Y=HomeY+(*Q).Y;
  if(Clr) {
   Chr=' ';Attr=7;
  } else {
   Chr='þ';Attr=0x71+(*Q).Form;
  }
  for(I=0;I<=3;I++) {
   gotoxy(X+BlkFormatX[(*Q).Form][(*Q).Move][I],Y+BlkFormatY[(*Q).Form][(*Q).Move][I]);
   TextAttr(Attr);
   putch(Chr);
   TextAttr(7);
  }
 }
 
 void TetrisInitGame(TetrisGame *Q) {
  (*Q).Form=(rand() % 6);
  if((*Q).Form==5) (*Q).Form+=(rand() % 2);
  (*Q).X=5;(*Q).Y=0;
  (*Q).Move=0;(*Q).Sleep=0;
  TetrisPutForm(Q,FALSE);
 }
 
 char TetrisUpDateData(TetrisGame *Q) {
  char H,I,J,JK;
  char Bonus;
  char LnChk;
  char result;
  result=TRUE;(*Q).Sleep=0;
  TetrisPutForm(Q,FALSE);
  (*Q).Touch=0;(*Q).Ok=FALSE;
  TetrisPutForm(Q,TRUE);
  (*Q).Y++;
  for(I=0;I<=3;I++) {
   (*Q).Touch=(*Q).Touch || (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][(*Q).Move][I]][(*Q).X+BlkFormatX[(*Q).Form][(*Q).Move][I]];
  }
  if((*Q).Touch) (*Q).Y--;
  TetrisPutForm(Q,FALSE);
  if((*Q).Touch) {
   while((*Q).Sleep>(*Q).SleepDelay) (*Q).Sleep--;
   (*Q).Sleep=0;(*Q).Ok=TRUE;
   for(I=0;I<=3;I++) (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][(*Q).Move][I]][(*Q).X+BlkFormatX[(*Q).Form][(*Q).Move][I]]=TRUE;
   if(Q->Level>7) {
    (*Q).Score+=((long) 5)*(*Q).Level;
    gotoxy(4,6);printf("%l",(*Q).Score);
   }
   Bonus=0;
   for(J=0;J<=19;J++) {
    (*Q).Touch=TRUE;
    for(I=0;I<=9;I++) (*Q).Touch=(*Q).Touch && (*Q).Tbl[J][I];
    if((*Q).Touch) Bonus++;
   }
   if(Bonus>0) Bonus--;
   (*Q).Touch=FALSE;
   for(JK=0;JK<=7;JK++) {
    for(J=0;J<=19;J++) {
     LnChk=TRUE;
     for(I=0;I<=9;I++) LnChk=LnChk && (*Q).Tbl[J][I];
     if(LnChk) {
      if(!(*Q).Touch) {
       (*Q).Touch=TRUE;
      }
      if(JK & 1==0) TextAttr(0xFF);
               else TextAttr(7);
      BarSpcHor(HomeX,HomeY+J,HomeX+9);
     }
    }
    WaitRetrace();WaitRetrace();WaitRetrace();
   }
   for(J=0;J<=19;J++) {
    (*Q).Touch=TRUE;
    for(I=0;I<=9;I++) (*Q).Touch=(*Q).Touch && (*Q).Tbl[J][I];
    if((*Q).Touch) {
     memcpy(&(*Q).Tbl[1][0],&(*Q).Tbl[0][0],10*J);
     memset(&(*Q).Tbl[0][0],FALSE,10);
     movetext(HomeX,HomeY,HomeX+9,HomeY+J-1,HomeX,HomeY+1);
     (*Q).Score+=((long) 5)+(Bonus*4)*((*Q).Level+1)+10*(*Q).Level; (*Q).Bar++;
     gotoxy(4,6);printf("%i",(*Q).Score);
     gotoxy(4,9);printf("%i",(*Q).Bar);
     I=((*Q).Bar+(*Q).FBar) >> 4;
     if((*Q).Level!=I) {
      (*Q).Level=I;
      gotoxy(4,3);printf("%i",(*Q).Level+1);
      if((*Q).SleepDelay>6) (*Q).SleepDelay-=2;
     }
    }
   }
   if((*Q).Y<=1) return FALSE;
   TetrisInitGame(Q);
  }
  return result;
 }
 
 unsigned TetrisGameOver(TetrisGame *Q) {
  gotoxy(10,7);printf("Partie Terminer");
  if((*Q).UpDate) {
   (*Q).UpDate=0;
  }
  return kbEsc;
 }
 
void TetrisFirstTime(TetrisGame *Q) {
 TetrisStart(Q);
 TetrisRefresh(Q);
 TetrisInitGame(Q);
 (*Q).Mode=tmPlay;(*Q).UpDate=TRUE;
}
 
unsigned TetrisRun(TetrisGame *Q) {
 char I,J,H,XT;
 unsigned XJ,YJ,K;
 char NoAction;
 K=0;
 do {
  do {
   if((*Q).Sleep>(*Q).SleepDelay) if(!TetrisUpDateData(Q)) {
    (*Q).Mode=tmGameOver;
    return;
   }
   WaitRetrace();
   (*Q).Sleep++;
  } while(!kbhit());
  K=getch();
  if(K==0) K=K | (getch() << 8);
  if(Chr(K)=='2') K=kbDn;
  if(Chr(K)=='4') K=kbLeft;
  if(Chr(K)=='6') K=kbRight;
  NoAction=FALSE;
  switch(K) {
   case kbLeft:
    if((*Q).X>0) {
     (*Q).Touch=FALSE;
     for(I=0;I<=3;I++) (*Q).Touch=(*Q).Touch || (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][(*Q).Move][I]][(*Q).X+BlkFormatX[(*Q).Form][(*Q).Move][I]-1];
      if(!(*Q).Touch) {
       TetrisPutForm(Q,TRUE);
       (*Q).X--;
       TetrisPutForm(Q,FALSE);
      }
     }
     break;
   case kbRight:
    if((*Q).X+BlkLength[(*Q).Form][(*Q).Move]-1<9) {
     (*Q).Touch=FALSE;
     for(I=0;I<=3;I++) (*Q).Touch=(*Q).Touch || (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][(*Q).Move][I]][(*Q).X+BlkFormatX[(*Q).Form][(*Q).Move][I]+1];
     if(!(*Q).Touch) {
      TetrisPutForm(Q,TRUE);
      (*Q).X++;
      TetrisPutForm(Q,FALSE);
     }
    }
    break;
   case kbDn:
    while(TRUE) {
     if(!TetrisUpDateData(Q)) {
      (*Q).Mode=tmGameOver;
      return;
     }
     if((*Q).Ok) break;
    }
    break;
   default:
    NoAction=TRUE;
    break;
  }
  if(NoAction) {
   if((K==kbKeypad5)||(Chr(K)==' ')||(Chr(K)=='5')) {
    (*Q).Touch=FALSE;
    for(I=0;I<=3;I++) {
     XT=(*Q).X+BlkFormatX[(*Q).Form][((*Q).Move+1) & 3][I]; (*Q).Touch=(*Q).Touch || (XT>9);
     (*Q).Touch=(*Q).Touch || (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][((*Q).Move+1)& 3][I]][XT];
    }
    if(!(*Q).Touch) {
     TetrisPutForm(Q,TRUE);
     (*Q).Move=((*Q).Move+1) & 3;
     TetrisPutForm(Q,FALSE);
    } else {
     (*Q).Touch=FALSE;
     for(I=0;I<=3;I++) {
      XT=(*Q).X;
      if(XT>0) XT--;
      XT+=BlkFormatX[(*Q).Form][((*Q).Move+1) & 3][I]; (*Q).Touch=(*Q).Touch || (XT>9);
      (*Q).Touch=(*Q).Touch || (*Q).Tbl[(*Q).Y+BlkFormatY[(*Q).Form][((*Q).Move+1) & 3][I]][XT];
     }
     if(!(*Q).Touch) {
      TetrisPutForm(Q,TRUE);
      (*Q).X--; (*Q).Move=((*Q).Move+1) & 3;
      TetrisPutForm(Q,FALSE);
     }
    }
   }
    else
   break;
  }
  if((K==kbEsc)||(Chr(K)=='Q')) break;
 } while(TRUE);
 return K;
}
 
unsigned TetrisPlay(TetrisGame *Q) {
 char I,J,H,XT;
 unsigned XJ,YJ,K;
 char NoAction;
 
 textmode(1);
 TetrisRefresh(Q);
 K=0;
 do {
  switch((*Q).Mode) {
   case tmStart:
    TetrisFirstTime(Q);
    break;
   case tmPlay:
    K=TetrisRun(Q);
    break;
   case tmGameOver:
    K=TetrisGameOver(Q);
    break;
  }
_Exit:;
 } while(K==0);
 return K;
}
 
void main() {
 TetrisGame Game;
 TetrisInit(&Game);
 TetrisPlay(&Game);
}
