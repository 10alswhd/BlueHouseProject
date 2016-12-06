#include <conio.h>
#include <stdio.h>
#include <string.h>

main(){
char s[80]= "Война и Мир", *p,
     a[80]= "Гитара",
     str[]= "ар",
     ch= 'и';
p = strchr(s,ch);
if (p){
   printf ("Первая буква '%c, ее номер - %d\n", ch, p-s);
   p = strrchr(s,ch);
   printf("Вторая буква '%c' ее номер - %d\n", ch,p-s);
   *p = 'и';
   }
p = strstr(a, str);
if (p)
   printf("Нашли <%s> â [%s]\n", str,a);
else
    printf("Не нашли <%s> â [%s]\n", str,a);
getch();
}
