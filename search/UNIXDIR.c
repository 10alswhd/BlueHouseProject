#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	char * A[5];
	int dir;
	struct node * sub[5];
};

void insert(struct node *, char **, int);
void print(struct node *, int);
int search(struct node *, char **, int);
char ** list(char *, const char);

struct node * root;

int main()
{
	int n;
	scanf("%d",&n);

	root = (struct node *)malloc(sizeof(struct node));
	root->dir = 0;

	while(n--)
	{
		char A[200];
		scanf("%s",A);

		char ** split = list(A,'/');

		insert(root,split,0);
	}

	scanf("%d",&n);

	while(n--)
	{
		char A[200];
		scanf("%s",A);

		char ** split = list(A,'/');

		if(search(root,split,0))
			printf("YES\n");
		else
			printf("NO\n");
	}	

}

void insert(struct node * root, char ** list, int level)
{
	if(*(list + level) == NULL)
		return ;
	else
	{
		int i;
		int f = 1;
		int n = root->dir;
		//Dir-level exists
		for(i=0;i<n;i++)
		{
			if(strcmp(*(root->A+i),*(list+level)) == 0)
			{
				insert(root->sub[i],list,level+1);
				f = 0;
				break;
			}
		}

		//Node not found
		if(f) 
		{
			(root->dir)++;
			*(root->A+i) = (char *)malloc(sizeof(*(list+level) + 1));
			strcpy(*(root->A+i),*(list+level));
			root->sub[i] = (struct node *)malloc(sizeof(struct node));
			(root->sub[i])->dir = 0;
			insert(root->sub[i],list,level+1);
		}
	}
}

void print(struct node * root, int level)
{
	int n = root->dir;
	char ** X = root->A;

	if(root == NULL)
		return;

	for(int i=0;i<n;i++)
	{
		for(int j=0;j<level;j++)
			printf("-");
		printf("%s\n",X[i]);
		print(root->sub[i],level+1);
	}
}

int search(struct node * root, char ** list, int level)
{
	if(*(list + level) == NULL)
		return 1;
	else
	{
		int n = root->dir;
		for(int i=0;i<n;i++)
			if(strcmp(*(root->A+i),*(list+level)) == 0)
				return search(root->sub[i],list,level+1);
		return 0;
	}
}

char ** list(char* A, const char d)
{
    char** result = 0;
    int count = 0;
    char* tmp = A;
    char* last = 0;
    char delim[2];
    delim[0] = d;
    delim[1] = 0;

    while (*tmp)
    {
        if (d == *tmp)
        {
            count++;
            last = tmp;
        }
        tmp++;
    }

    count += last < (A + strlen(A) - 1);

    count++;

    result = (char **)malloc(sizeof(char*) * count);

    if (result)
    {
        int idx  = 0;
        char* token = strtok(A, delim);

        while (token)
        {
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        *(result + idx) = 0;
    }

    return result;
}
