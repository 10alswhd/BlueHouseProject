/********************************/
/****       Stu_Control.c     ****/
/****       Date:2016/1/12   ****/
/********************************/

#include<stdio.h>				// 头文件
#include<stdlib.h>				// 头文件
#include<conio.h>				// 头文件

typedef struct student			// 定义学生信息结构体
{
	int num;					// 学号
	int grade;					// 成绩
	char name[30];				// 姓名
	struct student *next;		// 用指针保存下一个节点
} STU;

int print_find_stu(STU * p);	// 打印找到的学生
void print_interface();			// 打印初始界面
void start();					// 开始
void open_old_list();			// 打开旧链表
void create_new_list();			// 创建新链表
void print_all_stu(STU * p);	// 打印所有学生
void control_find_stu(int num);	// 管理找到的学生
void save_list();				// 保存数据到文件
void sort_stu();				// 排序学生
void free_stu(STU * stu);		// 释放内存
STU *create_stu(int i);			// 创建链表
STU *search_stu(int i, STU * p);	// 查找学生 
STU *delete_stu(int i, STU * p);	// 删除学生
STU *insert_stu(int i, STU * p);	// 添加学生
STU *open_list();				// 打开文件并加载数据
STU *sort_stu_num(STU * p);		// 按学号排序学生
STU *sort_stu_grade(STU * p);	// 按成绩排序学生
STU *student = 0;				// 初始化学生信息结构体指针

/****************************************************************/
int main()						// 主函数（简化主函数）
{
	start();
	return 0;
}

/****************************************************************/

void print_interface()
{
	printf("##########################################\n");
	printf("##         欢迎使用学生管理系统！       ##\n");
	printf("##########################################\n");
	printf("##           1:创建新的学生组           ##\n");
	printf("##           2:打开旧的学生组           ##\n");
	printf("##           3:退出                     ##\n");
	printf("##########################################\n");
}

void start()
{
	char input;
	for (;;)
	{
		print_interface();
		input=getch();
		if (input == '1')
		{
			create_new_list();
		}
		else if (input == '2')
		{
			open_old_list();
		}
		else if (input == '3')
		{
			free_stu(student);
			return;
		}
	}
}

STU *create_stu(int i)
{
	STU *head = 0, *middle, *last;
	int n;
	for (n = 0; n < i; n++)
	{
		last = (STU *) malloc(sizeof(STU));
		last->next = 0;
		printf("输入学号：");
		scanf("%d", &last->num);
		printf("输入名字：");
		scanf("%s", last->name);
		printf("输入成绩：");
		scanf("%d", &last->grade);
		if (head == 0)
		{
			head = last;
		}
		else
		{
			middle->next = last;
		}
		middle = last;
		printf("\n");
		clrscr();
	}
	return head;
}

STU *search_stu(int i, STU * p)
{
	if (p->num == i)
	{
		return p;
	}
	while (p->next != 0 && p->num != i)
	{
		p = p->next;
		if (p->num == i)
		{
			return p;
		}
		else if (p->next == 0 && p->num != i)
		{
			return 0;
		}
	}
}

STU *delete_stu(int i, STU * p)
{
	STU *a, *b;
	a = p;
	if (a->num == i && a == p && a->next != 0)
	{
		p = a->next;
		free(a);
		return p;
	}
	else if (a == p && a->next == 0 && a->num == i)
	{
		p = a->next;
		free(a);
		return p;
	}
	while (a->num != i && a->next != 0)
	{
		b = a;
		a = a->next;
		if (a->num == i)
		{
			b->next = a->next;
			free(a);
			return p;
		}
	}
}

STU *insert_stu(int i, STU * p)
{
	STU *a, *b, *c;
	a = p;
	if (a == p && a->num == i)
	{
		b = a->next;
		c = (STU *) malloc(sizeof(STU));
		printf("输入学号：");
		scanf("%d", &c->num);
		printf("输入名字：");
		scanf("%s", c->name);
		printf("输入成绩：");
		scanf("%d", &c->grade);
		a->next = c;
		c->next = b;
		return p;
	}
	while (a->num != i && a->next != 0)
	{
		a = a->next;
		if (a->num == i)
		{
			b = a->next;
			c = (STU *) malloc(sizeof(STU));
			printf("输入学号：");
			scanf("%d", &c->num);
			printf("输入名字：");
			scanf("%s", c->name);
			printf("输入成绩：");
			scanf("%d", &c->grade);
			a->next = c;
			c->next = b;
			printf("添加成功！\n");
			return p;
		}
	}
}

void print_all_stu(STU * p)
{
	printf("\n");
	while (p)
	{
		printf("名字：%s\t\t学号：%d\t\t成绩：%d\n", p->name, p->num, p->grade);
		p = p->next;
	}
	printf("\n");
}

int print_find_stu(STU * p)
{
	printf("\n");
	if (p == 0)
	{
		printf("没有此学生!\n\n");
		return 0;
	}
	else
	{
		printf("你要查找的学生是：%s\n\n", p->name);
		return p->num;
	}
}

void control_find_stu(int num)
{
	char input;
	printf
		("\n输入1删除这名学生\n输入2在此处添加一名新学生信息\n输入3返回\n输入：");
	input=getch();
	if (input == '1')
	{
		student = delete_stu(num, student);
		printf("删除成功!\n\n");
		clrscr();
	}
	else if (input == '2')
	{
		student = insert_stu(num, student);
		printf("添加成功!\n\n");
		clrscr();
	}
	else if (input == '3')
	{
		return;
	}
}

void save_list()
{
	FILE *save;
	char name[255];
	clrscr();
	printf("输入文件名称:");
	scanf("%s", &name);
	getchar();
	save = fopen(name, "wt+");
	while (student != 0)
	{
		fprintf(save, "%d %d %s\n", student->num, student->grade, student->name);
		student = student->next;
	}
	printf("保存成功!\n\n");
	fclose(save);
}

STU *open_list()
{
	FILE *open;
	STU *head = 0, *middle, *last;
	char name[255];
	int a;
	printf("输入文件名称:");
	scanf("%s", &name);
	getchar();
	open = fopen(name, "rt+");
	if (open == 0)
	{
		printf("文件未找到！\n");
		return;
	}
	do
	{
		last = (STU *) malloc(sizeof(STU));
		last->next = 0;
		fscanf(open, "%d %d %s\n", &last->num, &last->grade, last->name);
		if (head == 0)
		{
			head = last;
		}
		else
		{
			middle->next = last;
		}
		middle = last;
		a = feof(open);
	}
	while (a == 0);
	printf("打开成功!\n\n");
	fclose(open);
	clrscr();
	return head;
}

STU *sort_stu_grade(STU * p)
{
	int c, d;
	STU *head = 0;
	int num;
	int grade;
	char name[30];
	STU *stu, *next;
	do
	{
		head = p;
		c = 0;
		do
		{
			d = 0;
			if (head->grade > head->next->grade)
			{
				next = head->next;
				num = head->num;
				grade = head->grade;
				strcpy(next->name, head->name);
				head->num = next->num;
				head->grade = next->grade;
				next->num = num;
				next->grade = grade;
				d++;
			}
			head = head->next;
			c += d;
		}
		while (head->next != 0);
	}
	while (c);
	head = p;
	return head;
}

STU *sort_stu_num(STU * p)
{
	int c, d;
	STU *head = 0;
	int num;
	int grade;
	char name[30];
	STU *stu, *next;
	do
	{
		head = p;
		c = 0;
		do
		{
			d = 0;
			if (head->num > head->next->num)
			{
				next = head->next;
				num = head->num;
				grade = head->grade;
				strcpy(next->name, head->name);
				head->num = next->num;
				head->grade = next->grade;
				next->num = num;
				next->grade = grade;
				d++;
			}
			head = head->next;
			c += d;
		}
		while (head->next != 0);
	}
	while (c);
	head = p;
	return head;
}

void sort_stu()
{
	char input;
	clrscr();
	printf("输入1按学号排序\n输入2按成绩排序\n输入3退出\n输入：");
	input=getch();
	if (input == '1')
	{
		printf("排序中…");
		student = sort_stu_num(student);
	}
	else if (input == '2')
	{
		printf("排序中…");
		student = sort_stu_grade(student);
	}
	if (student != 0)
	{
		clrscr();
		printf("排序成功！\n");
	}
}

void create_new_list()
{
	int count, num, a;
	char input;
	STU *stu;
	do
	{
		printf("需要保存的人数：");
		scanf("%d", &count);
		getchar();
	}
	while (count <= 0);
	clrscr();
	student = create_stu(count);
	for (;;)
	{
		if (student == 0)
		{
			printf("此为空表\n");
			printf("输入回车退出...");
			return;
		}
		printf
			("\n输入1查看所有学生\n输入2按学号查找学生\n输入3按排序学生\n输入4保存链表\n输入5退出\n输入：");
		input=getch();
		if (input == '1')
		{
			print_all_stu(student);
			printf("输入回车继续...");
		}
		else if (input == '2')
		{
			clrscr();
			printf("输入要查询的学号：");
			scanf("%d", &num);
			getchar();
			stu = search_stu(num, student);
			a = print_find_stu(stu);
			if (a != 0)
			{
				control_find_stu(a);
			}
		}
		else if (input == '3')
		{
			sort_stu();
		}
		else if (input == '4')
		{
			save_list();
		}
		else if (input == '5')
		{
			clrscr();
			return;
		}
	}
}

void open_old_list()
{
	int num, a;
	char input;
	STU *stu;
	student = open_list();
	for (;;)
	{
		printf
			("\n输入1查看所有学生\n输入2按学号查找学生\n输入3按排序学生\n输入4保存链表\n输入5退出\n输入：");
		input=getch();
		if (input == '1')
		{
			print_all_stu(student);
		}
		else if (input == '2')
		{
			clrscr();
			printf("输入要查询的学号：");
			scanf("%d", &num);
			getchar();
			stu = search_stu(num, student);
			a = print_find_stu(stu);
			if (a != 0)
			{
				control_find_stu(a);
			}
		}
		else if (input == '3')
		{
			sort_stu();
		}
		else if (input == '4')
		{
			save_list();
		}
		else if (input == '5')
		{
			clrscr();
			return;
		}
	}
}

void free_stu(STU * stu)
{
	STU *a, *b;
	a = stu;
	do
	{
		b = a->next;
		free(a);
		a = b;
	}
	while (b != 0);
}
