//include
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//global
int loop, i, j, k, main_command_number, search_number, change_command_number;
int replace_id, replace_shiken, replace_enshu, replace_kadai, replace_tsuishi;
int delete_place;
int result_command;
char replace_name[20];
int count = 0;

//struct
struct student {
        int id;
        char name[20];
        int shiken;
        int enshu;
        int kadai;
        int tsuishi;
};
struct student student[40];

struct sort {
        int id;
        char name[20];
        double hyouka;
        char gpa[2];
};
struct sort sort[40];

//Function prototype
int cmp_fumc(const void* p, const void* q);

void main_command();
void add();
void search();
void list();
void change();
void del();
void tsuishi();
void result();
void quit();
void change_shiken();
void change_enshu();
void change_kadai();
void change_tsuishi();
void change_all();
void result_ready();
void set_sort();
void result_sort_desc();
void result_sort();

//main
int main() {
        loop = 1;
        printf("1)add 2)search 3)list 4)change 5)delete 6)tsuishi 7)result 0)quit ");
        scanf ("%d", &main_command_number);
        while (loop) {
                switch (main_command_number) {
                case 1:
                        add();
                        main_command();
                        break;
                case 2:
                        search();
                        main_command();
                        break;
                case 3:
                        list();
                        main_command();
                        break;
                case 4:
                        change();
                        main_command();
                        break;
                case 5:
                        del();
                        main_command();
                        break;
                case 6:
                        tsuishi();
                        main_command();
                        break;
                case 7:
                        result();
                        main_command();
                        break;
                case 0:
                        quit();
                        break;
                }
        }
}

void main_command() {
        printf("1)add 2)search 3)list 4)change 5)delete 6)tsuishi 7)result 0)quit ");
        scanf ("%d", &main_command_number);
}

//main command switch
void add() {
        printf("id name shiken kadai tsuishi ? ");
        scanf("%d %s %d %d %d %d", &student[count].id, student[count].name, &student[count].shiken, &student[count].enshu, &student[count].kadai, &student[count].tsuishi);
        count++;
}

void search() {
        printf("id ? ");
        scanf("%d", &search_number);
        for (i = 0; i < count; ++i) {
                if (search_number == student[i].id) {
                        printf("%d %s %d %d %d %d\n", student[i].id, student[i].name, student[i].shiken, student[i].enshu, student[i].kadai, student[i].tsuishi);
                }
        }
}

void list() {
        for (i = 0; i < count; ++i) {
                printf("%d %s %d %d %d %d\n", student[i].id, student[i].name, student[i].shiken, student[i].enshu, student[i].kadai, student[i].tsuishi);
        }
}

//change_____
void change() {
        printf("1)shiken 2)enshu 3)kadai 4)tsuishi 5)all ? ");
        scanf("%d", &change_command_number);

        switch (change_command_number) {
        case 1:
                change_shiken();
                break;
        case 2:
                change_enshu();
                break;
        case 3:
                change_kadai();
                break;
        case 4:
                change_tsuishi();
                break;
        case 5:
                change_all();
                break;
        }
}

//delete
void del() {
        printf("id ? ");
        scanf("%d", &delete_place);
        delete_place = delete_place - 1;
        while (++delete_place < count) {
                student[delete_place - 1] = student[delete_place];
        }
        --count;
}


void tsuishi() {
        for (i = 0; i < count; ++i) {
                if (student[i].shiken < 60 && student[i].enshu >= 70) {
                        printf("%d %s %d %d %d %d\n", student[i].id, student[i].name, student[i].shiken, student[i].enshu, student[i].kadai, student[i].tsuishi);
                }
        }
}


void result() {
        printf("1)value 2)ID ? ");
        scanf("%d", &result_command);
        result_ready();
        switch (result_command) {
        //DESC value
        case 1:
                result_sort_desc();
                break;
        //ASC ID
        case 2:
                result_sort();
                break;
        }
}

void quit() {
        loop = 0;
}

//change command
void change_shiken() {
        printf("id shiken ? ");
        scanf("%d %d", &replace_id, &replace_shiken);
        for (int j = 0; j < count; ++j) {
                if (replace_id == j) {
                        student[j].id = replace_id;
                        student[j].shiken = replace_shiken;
                }
        }
}

void change_enshu() {
        printf("id enshu ? ");
        scanf("%d %d", &replace_id, &replace_enshu);
        for (int j = 0; j < count; ++j) {
                if (replace_id == j) {
                        student[j].id = replace_id;
                        student[j].enshu = replace_enshu;
                }
        }
}

void change_kadai() {
        printf("id kadai ? ");
        scanf("%d %d", &replace_id, &replace_kadai);
        for (int j = 0; j < count; ++j) {
                if (replace_id == j) {
                        student[j].id = replace_id;
                        student[j].kadai = replace_kadai;
                }
        }
}

void change_tsuishi() {
        printf("id tsuishi ? ");
        scanf("%d %d", &replace_id, &replace_tsuishi);
        for (int j = 0; j < count; ++j) {
                if (replace_id == j) {
                        student[j].id = replace_id;
                        student[j].tsuishi = replace_tsuishi;
                }
        }
}

void change_all() {
        printf("id name shiken enshu kadai tsuishi ? ");
        scanf("%d %s %d %d %d %d", &replace_id, replace_name, &replace_shiken, &replace_enshu, &replace_kadai, &replace_tsuishi);
        for (int j = 0; j < count; ++j) {
                if (replace_id == j) {
                        student[j].id = replace_id;
                        strcpy(student[j].name, replace_name);
                        student[j].shiken = replace_shiken;
                        student[j].enshu = replace_enshu;
                        student[j].kadai = replace_kadai;
                        student[j].tsuishi = replace_tsuishi;
                }
        }
}

//result_function
void set_sort() {
        for (i = 0; i < count; ++i) {
                sort[i].id = student[i].id;
                strcpy(sort[i].name, student[i].name);
                sort[i].hyouka = (((((60 - student[i].shiken) * (student[i].tsuishi) / 100) + student[i].shiken) * 0.6) + (student[i].enshu * 0.2) + (student[i].kadai * 0.2));;

                if (sort[i].hyouka >= 90) {
                        strcpy(sort[i].gpa, "S");
                } else if (sort[i].hyouka < 90 && sort[i].hyouka >= 80) {
                        strcpy(sort[i].gpa, "A");
                } else if (sort[i].hyouka < 80 && sort[i].hyouka >= 70) {
                        strcpy(sort[i].gpa, "B");
                } else if (sort[i].hyouka < 70 && sort[i].hyouka >= 60) {
                        strcpy(sort[i].gpa, "C");
                } else if (sort[i].hyouka < 60 && sort[i].hyouka >= 40) {
                        strcpy(sort[i].gpa, "D");
                } else if (sort[i].hyouka < 40) {
                        strcpy(sort[i].gpa, "E");
                }
        }
}
void result_ready() {
        for (i = 0; i < count; ++i) {
                sort[i].id = student[i].id;
                strcpy(sort[i].name, student[i].name);
                sort[i].hyouka = (((((60 - student[i].shiken) * (student[i].tsuishi) / 100) + student[i].shiken) * 0.6) + (student[i].enshu * 0.2) + (student[i].kadai * 0.2));;

                if (sort[i].hyouka >= 90) {
                        strcpy(sort[i].gpa, "S");
                } else if (sort[i].hyouka < 90 && sort[i].hyouka >= 80) {
                        strcpy(sort[i].gpa, "A");
                } else if (sort[i].hyouka < 80 && sort[i].hyouka >= 70) {
                        strcpy(sort[i].gpa, "B");
                } else if (sort[i].hyouka < 70 && sort[i].hyouka >= 60) {
                        strcpy(sort[i].gpa, "C");
                } else if (sort[i].hyouka < 60 && sort[i].hyouka >= 40) {
                        strcpy(sort[i].gpa, "D");
                } else if (sort[i].hyouka < 40) {
                        strcpy(sort[i].gpa, "E");
                }
        }
}


void result_sort() {
        for (i = 0; i < count; ++i) {
                printf("%d %s %f %s\n", sort[i].id, sort[i].name, sort[i].hyouka, sort[i].gpa);
        }
}

void result_sort_desc() {
        qsort(sort, count, sizeof(sort[0]), cmp_fumc);
        for (i = 0; i < count; ++i) {
                printf("%d %s %f %s\n", sort[i].id, sort[i].name, sort[i].hyouka, sort[i].gpa);
        }
}

//result_sort_desc_function
int cmp_fumc(const void* p, const void* q){
        double x, y;
        x = ((struct sort*)p)->hyouka;
        y = ((struct sort*)q)->hyouka;
        if(x > y)
                return -1;
        else if(x < y)
                return 1;
        else
                return 0;
}
