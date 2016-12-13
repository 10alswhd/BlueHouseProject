#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define MAX_HP    100//최대 HP
#define MIN_HP    0//최소 HP
 
typedef struct Unit//유닛 구조체 정의
{
    int seqno;//일련번호
    char *name;//이름
    int hp;//hp
}Unit;
 
Unit *NewUnit(int seqno, const char *name);//Unit 동적 생성
void DeleteUnit(Unit *unit);//Unit 메모리 해제
void Training(Unit *unit, int cnt);//훈련하다.
void Relax(Unit *unit, int cnt);//휴식하다.
int GetSeqNo(Unit *unit); //일련번호 접근자
const char *GetName(Unit *unit);//이름 접근자
int GetHP(Unit *unit);//hp 접근자
 
 
void Initialize(Unit *unit, int seqno, const char *name);//초기화
void SetHP(Unit *unit, int hp);//hp 설정자
 
Unit *NewUnit(int seqno, const char *name)
{
    Unit *unit = (Unit *)malloc(sizeof(Unit));
    Initialize(unit, seqno, name);
    return unit;
}
void Initialize(Unit *unit, int seqno, const char *name)
{
    int len;
 
    unit->seqno = seqno;
    len = strlen(name) + 1;
    unit->name = (char *)malloc(len);
    strcpy_s(unit->name, len, name);
    unit->hp = MIN_HP;
}
 
void DeleteUnit(Unit *unit)
{
    free(unit->name);
    free(unit);
}
 
void Training(Unit *unit, int cnt)
{
    printf("%d 유닛, %d번 훈련\n", unit->seqno, cnt);
    SetHP(unit, unit->hp + cnt);
}
void Relax(Unit *unit, int cnt)
{
    printf("%d번 유닛, %d번 휴식\n", unit->seqno, cnt);
    SetHP(unit, unit->hp - cnt);
}
void SetHP(Unit *unit, int hp)
{
    if (hp>MAX_HP)
    {
        hp = MAX_HP;
    }
    if (hp<MIN_HP)
    {
        hp = MIN_HP;
    }
    unit->hp = hp;
}
 
int GetSeqNo(Unit *unit)
{
    return unit->seqno;
}
const char *GetName(Unit *unit)
{
    return unit->name;
}
int GetHP(Unit *unit)
{
    return unit->hp;
}
void ViewUnit(Unit *unit)
{
    printf("<%d, %s> hp:%d\n", GetSeqNo(unit), GetName(unit), GetHP(unit));
}
 
 
int main(void)
{
    Unit *unit = 0;
 
    unit = NewUnit(1, "홍길동");
    ViewUnit(unit);
    Training(unit, 10);
    ViewUnit(unit);
    Relax(unit, 5);
    ViewUnit(unit);
    Training(unit, 100);
    ViewUnit(unit);
    Relax(unit, 200);
    ViewUnit(unit);
    printf("%d 유닛, %d번 훈련\n", unit->seqno, 200);
    unit->hp += 200;
    ViewUnit(unit);
    DeleteUnit(unit);
    return 0;
}
