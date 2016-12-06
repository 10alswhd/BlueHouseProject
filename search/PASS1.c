/*
 * 11.11.2014
 * Gurupad M Mamadapur
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct input
{
	char label[10];
	char opcode[6];
	char operand[10];
	unsigned long int locctr; //unsigned long int used to store hex values.
}input;

typedef struct optab
{
	char opcode[5];
}optab;

typedef struct symtab
{
	unsigned long int locctr;
	char label[10];
}symtab;

int main()
{
	int nop=0,nsym=0;
	optab op[20];
	symtab sym[20];
	input ip[20];
	unsigned long int locctr;
	int getdata(optab op[],input ip[],int nop);
	unsigned long int pass(optab op[],input ip[],symtab sym[],int nop,int nsym);
	nop=getdata(op,ip,nop);
	locctr=pass(op,ip,sym,nop,nsym);
	printf("The length of the program is %lx\n",locctr);
	return 0;
}

int getdata(optab op[],input ip[],int nop)
{
	int i=0;
	printf("Make sure you've appropriate data in the text file\n");
	while(1)
	{
		scanf("%s",op[i].opcode);
		if((strcmp(op[i].opcode,"1"))==0)
		break;
		i++;
		if(i==21)
		break;
	}
	nop=i;
	i=0;
	while((scanf("%s",ip[i].label))!=EOF)
	{
		scanf("%s",ip[i].opcode);
		scanf("%s",ip[i].operand);
		++i;
	}
	return nop;
}

unsigned long int pass(optab op[],input ip[],symtab sym[],int nop,int nsym)
{
	int i,found,len;
	unsigned long int locctr,start_addr;
	char prog_name[10];
	int search_symtab(symtab sym[],char [],int nsym);
	int search_optab(optab op[],char [],int nop);
	int find_len(char []);
	if(strcmp(ip[0].opcode,"START")==0)
	{
		strcpy(prog_name,ip[0].label);	//Save Program name
		printf("Program Name : %s\n\n",prog_name);
		start_addr=atol(ip[0].operand);	//Save starting address
	}
	else
	{
		printf("Error as START operand not found\n");
		exit (0);
	}
	locctr=start_addr;
	i=1;
	printf("LOCCTR\tLABEL\tOPCODE\tOPERAND\n");
	printf("\t%s\t%s\t%s\n",ip[0].label,ip[0].opcode,ip[0].operand);
	while((strcmp(ip[i].opcode,"END")!=0))
	{
		if((strcmp(ip[i].label,"-")!=0))
		{
			found=search_symtab(sym,ip[i].label,nsym);
			if(found==1)
			{
				strcpy(sym[nsym].label,"ERROR");
				sym[nsym].locctr=locctr-start_addr;
				printf("Duplicate Label %s\n",ip[i].label);
				nsym++;
				i++;
				continue;	//Skip
			}
			else
			{
				strcpy(sym[nsym].label,ip[i].label);
				printf("%lx\t%s\t%s\t%s\n",locctr,ip[i].label,ip[i].opcode,ip[i].operand);
				sym[nsym].locctr=locctr-start_addr;
				nsym++;
			}
		}
		else
		printf("%lx\t\t%s\t%s\n",locctr,ip[i].opcode,ip[i].operand);
		found=search_optab(op,ip[i].opcode,nop);
		if(found==1)
		locctr+=3;
		else if((strcmp(ip[i].opcode,"WORD"))==0)
		locctr+=3;
		else if((strcmp(ip[i].opcode,"RESW"))==0)
		locctr=locctr+(3*atol(ip[i].operand));
		else if((strcmp(ip[i].opcode,"RESB"))==0)
		locctr=locctr+atol(ip[i].operand);
		else if((strcmp(ip[i].opcode,"BYTE"))==0)
		{
			len=find_len(ip[i].operand);
			locctr+=len*0x1;
		}
		else
		{
			printf("Invalid Opcode %s\n",ip[i].opcode);
			strcpy(sym[nsym].label,"ERROR");
			sym[nsym].locctr=locctr;
			nsym++;
			i++;
			continue;	//skip
		}
		i++;	//Read next line
	}//While not end
	printf("\nSYMTAB:\n");
	for(i=0;i<nsym;i++)
	printf("%lx\t%s\n",sym[i].locctr,sym[i].label);
	return((locctr)-start_addr);
}

int find_len(char operand[])
{
	char *p;
	if((strncmp(operand,"c",1))==0)
	{
		p=strtok(operand,"c ' ");
		return(strlen(p));
	}
	else
	return 1;
}

int search_symtab(symtab sym[],char label[],int nsym)
{
	int i=0;
	int temp=nsym;
	while(temp!=0)
	{
		if((strcmp(sym[i].label,label))==0)
		return 1;
		i++;
		temp--;
	}
	return 0;
}

int search_optab(optab op[],char opcode[],int nop)
{
	int i=0;
	int temp=nop;
	while(temp!=0)
	{
		if((strcmp(op[i].opcode,opcode))==0)
		return 1;
		else
		{
			i++;
			temp--;
		}
	}
	return 0;
}
