#include <stdio.h>
#include <string.h>

struct tea {
    char name[50];
    char topping[50];
    int size;
    long price;
}data[100];

int count=0;
struct tea temp;
FILE *p;

void readfile(){
    p=fopen("tea.txt", "r");
    while (!feof(p)) {
        fscanf(p, "%[^#]#%[^#]#%d#%ld\n", data[count].name, data[count].topping, &data[count].size, &data[count].price);
        count++;
    }
    fclose(p);
}

void menu(){
    printf("1. Buy BreakTime Tea\n");
    printf("2. View History\n");
    printf("3. Search History\n");
    printf("4. Delete History\n");
    printf("5. Sorting Ascending by Price\n");
    printf("6. Exit\n");
}

void buy(){
    do {
        printf("Choose your Tea [Olong/Green Tea/Jasmine]: ");
        gets(data[count].name);
    } while(strcmp(data[count].name, "Jasmine")!=0 && strcmp(data[count].name, "Olong")!=0 && strcmp(data[count].name, "Green Tea")!=0);
    do {
        printf("Choose your Topping [Bubble Jelly/Coffee Jelly/Grass Jelly]: ");
        gets(data[count].topping);
    } while(strcmp(data[count].topping, "Bubble Jelly")!=0 && strcmp(data[count].topping, "Coffee Jelly")!=0 && strcmp(data[count].topping, "Grass Jelly")!=0);
    do {
        printf("Choose your size of cup BreakTime [8/12/16/18]oz: ");
        scanf("%d", &data[count].size);
        fflush(stdin);
    } while(data[count].size!=8 && data[count].size!=12 && data[count].size!=16 && data[count].size!=18);
    data[count].price = data[count].size * strlen(data[count].name) * strlen(data[count].topping) * 20;
    
    printf("\n\nDetail Purchase:\n");
    printf("Name\t\t: %s\n", data[count].name);
    printf("Topping\t\t: %s\n", data[count].topping);
    printf("Size\t\t: %d\n", data[count].size);
    printf("Total Price\t: %ld\n", data[count].price);
    printf("Data successfully added..\n\n");
    count++;
}

void view(){
    printf("No.\t| Name\t\t\t\t| Topping\t\t\t| Size\t| Price\n");
    printf("============================================================\n");
    for (int i=0; i<count; i++) {
        printf("%d\t| %-10s\t\t| %s\t\t| %d oz\t | %ld\n", i+1, data[i].name, data[i].topping, data[i].size, data[i].price);
    }
    printf("\n");
}

void search(){
    char search[100];
    int flag=-1;
    do {
        printf("Choose your Tea [Olong/Green Tea/Jasmine] that you want to search: ");
        gets(search);
    } while(strcmp(search, "Jasmine")!=0 && strcmp(search, "Olong")!=0 && strcmp(search, "Green Tea")!=0);
    for(int i = 0; i<count;  i++){
        if(strcmp(data[i].name, search)==0){
            flag=i;
        }
    }
    if(flag!=-1){
        printf("Tea: %s\n", data[flag].name);
        printf("Topping: %s\n", data[flag].topping);
        printf("Size: %d\n", data[flag].size);
        printf("Price: %ld\n", data[flag].price);
    }
    else{ printf("Data not found.\n"); }
}

void deletehistory(){
    int index;
    do {
        printf("Input index that want to delete [1..%d]: ", count);
        scanf("%d", &index);
        fflush(stdin);
    } while(index<1 || index>count);
    for (int i=index-1; i<count-1; i++) {
        data[i]=data[i+1];
    }
    printf("Data successfully delete..\n\n");
    count--;
}

void sort(){
    for (int i=0; i<count-1; i++) {
        for (int j=count-1; j>i; j--) {
            if (data[j].price<data[j-1].price) {
                temp=data[j-1];
                data[j-1]=data[j];
                data[j]=temp;
            }
        }
    }
}

void exit(){
    p=fopen("tea.txt", "w");
    for (int i=0; i<count; i++) {
        fprintf(p, "%s#%s#%d#%ld\n", data[i].name, data[i].topping, data[i].size, data[i].price);
    }
    fclose(p);
}

int main() {
    int choice;
    readfile();
    do {
        printf("Welcome to BreakTime Tea\n");
        printf("========================\n");
        menu();
        do {
            printf("Input your choice[1..6]: ");
            scanf("%d", &choice); fflush(stdin);
        } while (choice<1 || choice>6);
        
        switch (choice) {
            case 1:
                buy();
                break;
            case 2:
                view();
                break;
            case 3:
                search();
                break;
            case 4:
                deletehistory();
                break;
            case 5:
                sort();
                break;
        }
    } while (choice!=6);
    exit();
    getchar();
    return 0;
}
