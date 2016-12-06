#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NAME_LEN 30

struct linklist {
	char name[NAME_LEN];
	int amount;
	int price;
	float avgCost;
	struct linklist *next;
};

typedef struct linklist node;

node *head = NULL, *previous = NULL;
int totalCount = 0;

void stock();
void sell();
node *search(char name[NAME_LEN]);
void query();
void print();
void save();
void terminate();

int main(int argc, char **argv) {

	if( argc > 1 ) {

		printf("Reading File %s\n", argv[1]);
		
		FILE *fp = fopen(argv[1], "r");
		fscanf(fp, "%d", &totalCount);

		char name[NAME_LEN];
		int amount, price;
		float avgCost;
		while( fscanf(fp, "%s\t\t%d\t\t%d\t\t%f\n", name, &amount, &price, &avgCost) != EOF ) {
			
			node *current = (node*)malloc(sizeof(node));

			strcpy(current->name, name);
			current->amount = amount;
			current->price = price;
			current->avgCost = avgCost; 

			if( head == NULL )
				head = current;
			else 
				previous->next = current;

			current->next = NULL;
			previous = current; 

			printf("新貨品 #%s 新增完成\n", name);
		}

		fclose(fp);
		printf("檔案讀取完成！\n\n");
	} 

	printf("--------------------------\n");
	printf("---派大星進銷存管理系統---\n");
	printf("--------------------------\n");

	printf("1)進貨 2)銷貨 3)查詢 4)列表 5)儲存 6)儲存離開 7)離開\n");
	printf("請輸入代號: ");

	int oprCode = 0;
	while( scanf("%d", &oprCode) != EOF ) {
		switch(oprCode) {
			case 1:
				stock();
				break;
			case 2:
				sell();
				break;
			case 3:
				query();
				break;
			case 4:
				print();
				break;
			case 5:
				save();
				break;
			case 6:
				save();
				terminate();
				break;
			case 7:
				terminate();
				break;
		}
		printf("\n1)進貨 2)銷貨 3)查詢 4)列表 5)儲存 6)儲存離開 7)離開\n");
		printf("請輸入代號: ");
	}

	return 0;
}

void stock() {
	
	char inputName[NAME_LEN];
	printf("名稱：");
	scanf("%s", inputName);

	int amount;
	printf("數量：");
	scanf("%d", &amount);

	int price;
	printf("價格：");
	scanf("%d", &price);

	node *check = search(inputName);
	if( check == NULL ) {

		node *current = (node*)malloc(sizeof(node));

		strcpy(current->name, inputName);
		current->amount = amount;
		current->price = price;
		current->avgCost = (price * amount) / amount; 

		if( head == NULL )
			head = current;
		else 
			previous->next = current;

		current->next = NULL;
		previous = current; 

		printf("新貨品 #%s 新增完成\n", inputName);
		totalCount++;

	} else {

		check->amount += amount;
		check->price = price;
		
		printf("貨品 #%s 補貨完成\n", inputName);

	}
}

void sell() {

	char inputName[NAME_LEN];
	printf("名稱：");
	scanf("%s", inputName);

	node *check = search(inputName);
	if( check == NULL ) {
		printf("商品 #%s 不存在\n", inputName);
	} else {
		int amount;
		printf("賣出數量：");
		scanf("%d", &amount);
		
		check->amount -= amount;
		printf("賣出 %d 個 %s\n", amount, inputName);
	}

}

node *search(char name[NAME_LEN])  {

	node *it = head;
	while( it != NULL ) {
		if( strcmp(it->name, name) == 0) {
			return it;
		}
		it = it->next;
	}
	return NULL;
}

void query() {

	char inputName[NAME_LEN];
	printf("名稱：");
	scanf("%s", inputName);

	node *check = search(inputName);

	if( check != NULL ) {
		printf("數量：%d\n", check->amount);
		printf("平均成本：%f\n", check->avgCost);
	} else {
		printf("商品 #%s 不存在\n", inputName);
	}
}

void print() {

	printf("名稱\t\t數量\t\t平均成本\n");

	node *it = head;
	while( it != NULL ) {
		printf("%s\t\t%d\t\t%f\n", it->name, it->amount, it->avgCost);
		it = it->next;
	}

}

void save() {

	char inputName[NAME_LEN];
	printf("輸入儲存檔案名稱：");
	scanf("%s", inputName);
	FILE *fp = fopen(inputName, "w");

	fprintf(fp, "%d\n", totalCount);

	node *it = head;
	while( it != NULL ) {
		fprintf(fp, "%s\t\t%d\t\t%d\t\t%f\n", it->name, it->amount, it->price, it->avgCost);
		it = it->next;
	}

	fclose(fp);
	printf("檔案 %s 儲存完成\n", inputName);
}

void terminate() {
	printf("離開本程式\n");
	exit(0);
}
