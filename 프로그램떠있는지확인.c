#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int CheckProcess(char *pfile)
{
	FILE *fp;
	char pid[16];
	char process[256];
	int rtv = 0;

	fp = fopen(pfile, "r");
	if (fp == NULL)
	{
		return 0;
	}

	if (fgets(pid, sizeof(pid) - 1, fp) == NULL) 
	{
		fclose(fp);
		return 0;
	}
	fclose(fp);


	pid[strlen(pid)-1] = 0x00;
	sprintf(process, "/proc/%s/exe", pid);
	if (access(process, F_OK) == 0)
	{
		return atoi(pid);
	}
	return 0;
}

int WritePid(char *pfile)
{
	FILE *fp;
	char pid[16];
	sprintf(pid, "%d\n", getpid());
	fp = fopen(pfile,"w");
	fputs(pid, fp);
	fclose(fp);
}
