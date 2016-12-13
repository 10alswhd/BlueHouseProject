#ifndef INPUT_PROG_H
#define INPUT_PROG_H
#include <iostream>
#include <cstdio>
#include <fstream>
void palindrome()
{
    freopen("input.txt","w",stdout);
    cout<<"COPY   START  0\n";
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
    cout<<"       LDT    BUFFER,MAXLEN-X\n";
    cout<<"       COMPR  A,T\n";
    cout<<"       JEQ    RLOOP\n";
    cout<<"       LDA    #0\n";
    cout<<"       STA    RESULT\n";
    cout<<"       JSUB   FINAL\n";
    cout<<"EXIT   LDA    #1\n";
    cout<<"       STA    RESULT\n";
    cout<<"FINAL  LDA    #0\n";
    cout<<"       LDA    RESULT\n";
    cout<<"       STA    BUFFER
    cout<<"BUFFER BYTE   C'F1'\n";
    cout<<"MAXLEN RESW   1\n";
    cout<<"RESULT RESW   1\n";
    cout<<"       END    FIRST\n";
    cout<<"       +JSUB  WRREC\n";
    cout<<"ENDFIL LDA    EOF\n";
    cout<<"       STA    BUFFER\n";
    cout<<"       LDA    #3\n";
    cout<<"       STA    LENGTH\n";
    cout<<"       +JSUB  WRREC\n";
    cout<<"       J      @RETADR\n";
    cout<<"EOF    BYTE   C'EOF'\n";
    cout<<"RETADR RESW   1\n";
    cout<<"LENGTH RESW   1\n";
    cout<<"BUFFER RESB   4096\n";
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
/*    cout<<".\n";
    cout<<".      SUBROUTINE TO WRITE RECORD INTO BUFFER\n";
    cout<<".\n";
    cout<<"WRREC  CLEAR   X\n";
    cout<<"LDT    LENGTH\n";
    cout<<"WLOOP  TD     OUTPUT\n";
    cout<<"       JEQ    WLOOP\n";
    cout<<"       LDCH   BUFFER,X\n";
    cout<<"       WD     OUTPUT\n";
    cout<<"       TIXR   T\n";
    cout<<"       JLT    WLOOP\n";
    cout<<"       RSUB\n";
    cout<<"OUTPUT BYTE   X'05'\n";
    cout<<"       END    FIRST\n";
    fclose(stdout);
}    
void palindrome()
{
    freopen("input.txt","w",stdout);
    fclose(stdout);
}    
#endif
