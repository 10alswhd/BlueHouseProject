#include<stdio.h>
#include<conio.h>
char key[5][5];
int search(char);
void e(char*,char*);
void main(){
  char *p,*k;


	clrscr();
	printf("Enter text:");
	gets(p);
	flushall();
	printf("Enter key:");
	scanf("%s",k);
	e(p,k);
	printf("%s",p);
	getch();
}
void e(char *p,char *k){
	char ref[26]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int x=0,y,z=0,l=0,i,j;

		for(y=0;*(k+y)!='\0';y++){
			if(ref[*(k+y)-65] != '*'){
				if(*(k+y)=='I' || *(k+y)=='J'){
					key[x][z]='@';
					ref[8]='*';
					ref[9]='*';
				}
				else{
				key[x][z]=*(k+y);
				ref[*(k+y)-65]='*';
				}
				if(z==4){
					z=0;
					x++;
				}else{
					z++;
				}
			}
		}

		for(l=0;l<26;l++){
			if(ref[l]!='*'){
				if(ref[l]=='I' || ref[l]=='J'){
					key[x][z]='@';
					ref[8]='*';
					ref[9]='*';
				}
				else{
				key[x][z]=ref[l];

				}
				if(z==4){
					z=0;
					x++;
				}else{
					z++;
				}
			}

		}
		printf("\nKey Matrix:\n-----------\n");
		for(x=0;x<5;x++){
			for(y=0;y<5;y++)
			printf("%c ",key[x][y]);

			printf("\n");
		}

  ///////ENCRYPTION//////////////////////////////////////
	l=0;
	while(*(p+l)!='\0'){
		i=search(*(p+l));
		j=i%10;
		i=i/10;

		x=search(*(p+l+1));
		y=x%10;
		x=x/10;
		///////CASE 1//////////////////////////////

		*(p+l)=key[i][y];
		*(p+l+1)=key[x][j];
		l+=2;
	}
}
int search(char c){
		int x,y,RET;
		for(x=0;x<5;x++){
			RET=100;
			for(y=0;y<5;y++){
				if(key[x][y]==c){

					RET = (10*y)+x;
					break;
				}
			}
			if(RET!=100)
			break;
		 }
}
