#ifndef INPUT_PROG_H
#define INPUT_PROG_H
#include <iostream>
#include <cstdio>
#include <fstream>
void fib()
{
    freopen("input.txt","w",stdout);
    cout<<"COPY   START  1000\n";
    cout<<"FIRST  STL    RETADR\n";
    cout<<"       +JSUB  RDREC\n";
    cout<<"       LDX    #0\n";
    cout<<"       LDT    N\n";
    cout<<"       LDA    #0\n";
    cout<<"       STA    ALPHA\n";
    cout<<"       LDA    #1\n";
    cout<<"       STA    BETA\n";
    cout<<"ADDLP  LDS    ALPHA\n";
    cout<<"       LDA    BETA\n";
    cout<<"       STA    GAMMA\n";
    cout<<"       ADDR   S,A\n";
    cout<<"       STA    BETA\n";
    cout<<"       LDA    GAMMA\n";
    cout<<"       STA    ALPHA\n";
    cout<<"       TIXR   T\n";
    cout<<"       JLT    ADDLP\n";
    cout<<"       LDA    BETA\n";
    cout<<"       STA    FIBN\n";    
    cout<<"       +JSUB  WRREC\n";
    cout<<"       J      @RETADR\n";
    cout<<"RETADR RESW   1\n";
    cout<<"N      RESW   1\n";
    cout<<"ALPHA  RESW   1\n";
    cout<<"BETA   RESW   1\n";
    cout<<"GAMMA  RESW   1\n";
    cout<<"FIBN   RESW   1\n";
    cout<<".\n";
    cout<<".      SUBROUTINE TO READ RECORD INTO BUFFER\n";
    cout<<".\n";
    cout<<"RDREC  TD     INPUT\n";
    cout<<"       JEQ    RDREC\n";
    cout<<"       RD     INPUT\n";
    cout<<"       STA    N\n";
    cout<<"       RSUB\n";
    cout<<"INPUT  BYTE   X'F1'\n";
    cout<<".\n";
    cout<<".      SUBROUTINE TO WRITE RECORD INTO BUFFER\n";
    cout<<".\n";
    cout<<"WRREC  TD     OUTPUT\n";
    cout<<"       JEQ    WRREC\n";
    cout<<"       LDA    FIBN\n";
    cout<<"       WD     OUTPUT\n";
    cout<<"       RSUB\n";
    cout<<"OUTPUT BYTE   X'05'\n";
    cout<<"       END    FIRST\n";
    fclose(stdout);
}    
void palindrome()
{
    freopen("input.txt","w",stdout);
    cout<<"COPY   START  4000\n";
    cout<<"FIRST  STL    RETADR\n";
    cout<<"       LDB    #LENGTH\n";
    cout<<"       BASE   LENGTH\n";
    cout<<"       +JSUB  RDREC\n";
    cout<<"       LDA    LENGTH\n";
    cout<<"       COMP   #0\n";
    cout<<"       JEQ    ENDFILL\n";
    cout<<"       LDS    LENGTH\n";
    cout<<"       LDX    #0\n";
    cout<<"RLOOP  COMPR  X,S\n";
    cout<<"       JEQ    EXIT\n";
    cout<<"       LDA    BUFFER,X\n";
    cout<<"       LDT    #1\n";
    cout<<"       ADDR   X,T\n";
    cout<<"       LDT    BUFFER,LENGTH-X\n";
    cout<<"       COMPR  A,T\n";
    cout<<"       JEQ    RLOOP\n";
    cout<<"       LDA    #0\n";
    cout<<"       JSUB   FINAL\n";
    cout<<"EXIT   LDA    #1\n";
    cout<<"FINAL  STA    PALIN\n";  
    cout<<"       +JSUB  WRREC\n";
    cout<<"       J      @RETADR\n";
    cout<<"RETADR RESW   1\n";
    cout<<"LENGTH RESW   1\n";
    cout<<"BUFFER RESB   4096\n";
    cout<<"PALIN  RESW   1\n";
    cout<<"FINAL  RESW   1\n";
    cout<<".\n";
    cout<<".      SUBROUTINE TO READ RECORD INTO BUFFER\n";
    cout<<".\n";
    cout<<"RDREC  CLEAR   X\n";
    cout<<"       CLEAR   A\n";
    cout<<"       CLEAR   S\n";
    cout<<"       +LDT    #4096\n";
    cout<<"RLOOP  TD      INPUT\n";
    cout<<"       RD      INPUT\n";
    cout<<"       COMPR   A,S\n";
    cout<<"       JEQ     EXIT\n";
    cout<<"       STCH    BUFFER,X\n";
    cout<<"       TIXR    T\n";
    cout<<"       JLT     RLOOP\n";
    cout<<"EXIT   STX     LENGTH\n";
    cout<<"       RSUB\n";
    cout<<"INPUT  BYTE    X'F1'\n";
    cout<<".\n";
    cout<<".      SUBROUTINE TO WRITE RECORD INTO BUFFER\n";
    cout<<".\n";
    cout<<"WRREC  TD     OUTPUT\n";
    cout<<"       JEQ    WRREC\n";
    cout<<"       LDA    PALIN";
    cout<<"       WD     OUTPUT\n";
    cout<<"       RSUB\n";
    cout<<"OUTPUT BYTE   X'05'\n";
    cout<<"       END    FIRST\n";
    fclose(stdout);
}
#endif
