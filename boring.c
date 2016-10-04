#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 200
 
char* salloc(int len);									   //0.문자열 동적할당
void   input_data(char *buf, char *who);				   //1.문자열을 입력받음
char* search_question(char *input, int teach);			   //2.질문에 대한 대답을 찾아서 리턴, 없으면 ""
void   print_answer(char *output);					       //3.대답을 프린트 해줌
void    teach_answer(char *buf);						   //4.대답을 파일에 입력하게함 
void next_line(FILE *file, int line);					   //5.line만큼 다음줄로 이동
char* nfgets(char *buf, int max, FILE *file);		       //6.개행문자를 빼고 파일입력
void log_save(char* input, char* output, char* user_name); //7.Log파일 생성
int filtering(char *input);								   //8.욕 필터링
void textcolor(int color_number);						   //9.글씨 색변경

 
void main() {
	MessageBoxA(NULL, "사용방법 : 자신의 이름을 정하고 하고싶은 말을 마음껏 치세요. \n심심이를 가르치고 싶다면 \"/t 질문\" 형식으로 써주세요. \n+)대화를 종료하고 싶다면 \"잘가\"를 입력해 주세요\n제작자 : 전현성, 문호현, 김수민, 박상원", "심심이 설명서", MB_OK);
	int i, j, k;
	char *buf;
	int teach;
	char *input;
	char *output;
	char user_name[20];
	buf = salloc(SIZE);
	srand((unsigned)time(NULL));
	input_data(user_name, "당신의 이름");				//이름(input)
	

	//----------------------------------------대화->계속반복----------------------------------------
	while (true) {
		teach = 0;

		//INPUT
		input_data(buf, user_name);                   //buf에 입력받음
		input = salloc(strlen(buf) + 1);             //input을 buf크기만큼 동적할당(널문자 포함)
		strcpy(input, buf);                         //input에 buf를 넣음


		//INPUT CHECK
		if (filtering(input) == 1) {                  //욕검출시 intput free하고 continue()
			free(input);
			continue;
		}	
		if (!strcmp("잘가", input)) {				 //"잘가"입력시 심심이 종료
			MessageBoxA(NULL, "심심이를 종료합니다. \n제작자 : 전현성, 문호현, 김수민, 박상원", "심심이 : 잘가~ 또와~~", MB_OK);
			break;
		}
 		if (!strncmp(input, "/t ", 3)) {            //if 심심이 가르치기 /t 질문 형식 일때
			input = input + 3;                     //앞에 '/t '를 input에서 지움
			teach = 1;
		}
 

		//OUTPUT
		strcpy(buf, search_question(input, teach));     //input에 맞는 output을 찾아서 buf에 저장, 없으면 NULL
		output = salloc(strlen(buf) + 1);            //output을 buf크기만큼 동적할당(널문자 포함)
		strcpy(output, buf);                     //output에 buf를 넣음
 

 
		//PRINF & TEACH
		if (strcmp(output, "")) {                  //-질문에 대한 대답있을경우 
	
			if (teach == 1) {                     // 가르치기 상태일때
				printf("이미 심심이가 알고있는 질문입니다.\n\n");
				input = input - 3;                  //할당 받은 만큼 free하기 위해 다시 input의 크기를 원래대로 해줌
			}
			else {
				log_save(input, output,user_name);  //INPUT과 OUTPUT이 정상적으로 출력되었을때 저장
			}

			print_answer(output);                   //output을 출력 
		
		}
		else {                                 //-질문에 일치하는 대답이 없을경우
			printf("심심이가 모르는 말입니다. 가르쳐 주세요\n\n");
			teach_answer(input);               //심심이 가르치기
			if (teach == 1) input = input - 3;      //할당 받은 만큼 free하기 위해 다시 input의 크기를 원래대로 해줌
		}
 
 
		//FREE
		free(input);
		free(output);
	
	}

}
 
 

//0.문자열 동적할당
char* salloc(int len) {
	return (char*)malloc(sizeof(char)*len);            //len 만큼 동적할당
}
 
 
//1.문자열을 입력받음
void  input_data(char *buf, char *who) {
	fflush(stdin);                              //입력장치 초기화
	while (true) {                              //아무것도 입력안하면 반복 -> 입력할때 까직 반복					//누구 : 
		textcolor(10); printf("%s : ", who);
		textcolor(7); nfgets(buf, SIZE, stdin);
		printf("\n");
		//내용을 SIZE만큼 프린트 stdin -> 출력장치
		if (strcmp(buf, "")) break;                  //입력되면 반복문 탈출
	}
 
}
 
 
//2.질문에 대한 대답을 찾아서 리턴, 없으면 ""
char* search_question(char *input, int teach) {
	FILE *fp;
	int output_num, random, check = 0, i;
	char *buf;
	char *similar;
	buf = salloc(SIZE);
	similar = salloc(SIZE);
 
	if ((fp = fopen("question.txt", "r")) == NULL) return "";   //파일이 없으면 리턴
 
 
	for (i = 0; i < 2; i++) {                     //총 2번 파일을 탐색 i - 0.완벽히 일치하는가,  1.조금 일치하는가
		while (!feof(fp)) {                        //파일 끝까직 탐색
			fscanf(fp, "%d", &output_num);            //질문의 답이 몇개인지 output_num에 저장
			nfgets(buf, SIZE, fp);                  //buf에 질문 저장
 
			if (i == 0 && !strcmp(input, buf)) check = 1;//질문과 완벽히 일치하는가
 
			if (i == 1 && strlen(buf) > 3 && strstr(input, buf) != NULL) { //if 유사한 질문이 있는가
				check = 1;
				if (teach == 0) printf("\n원하는 대답이 아닐경우 \"/t 질문\" 을 통해 가르쳐 주세요.\n\n");
			}
 
			if (check == 1)                        //input과 질문과 일치거나 비슷 하면
			{
				random = rand() % output_num;         //질문의 답중 출력할 답을 랜덤으로 설정
				next_line(fp, random);               //출력할 대답으로 이동
				nfgets(buf, SIZE, fp);               //대답을 buf에 저장
				fclose(fp);
				return buf;                        //저장한 대답을 리턴
			}
			next_line(fp, output_num + 1);            //다음 질문이 있는 파일위치로 이동
		}
		if (teach == 1) break;
		rewind(fp);                              //파일탐색 위치를 처음으로 돌림
	}
 
	fclose(fp);
	return "";
}
 
 
//3.대답을 프린트 해줌
void   print_answer(char *output) {
	textcolor(14); 
	printf("┌─Simsim──────────────────────────────────┐\n");
	printf(" %s\n", output);
	printf("└──────────────────────────────────────┘\n\n");
	textcolor(7);
}
 
 
//4.대답을 파일에 입력하게함 
void  teach_answer(char *input) {
	char buf[SIZE];
	int num, i;
	FILE *fp;
	fp = fopen("question.txt", "a");
 
	textcolor(12); printf("가르칠 대답의 갯수를 입력해 주세요( 0 입력시 스킵 )");
	textcolor(7);
	scanf("%s", &buf);
	num = atoi(buf);

	if (num == 0) {
		fclose(fp);
		return;
	}
	fprintf(fp, "%d%s\n", num, input);   //대답의 갯수와 질문을 저장         3안녕
	for (i = 0; i < num; i++) {         //대답의 갯수만큼 for문            안녕안녕
		input_data(buf, "TEACH");      //TEACH : 대답을 입력받음         웅 안녕
		fprintf(fp, "%s\n", buf);      //입력받은 대답을 파일에 저장      반가워
	}
	fprintf(fp, " \n");               //공백 처리
 
	fclose(fp);
}
 
 
//5.line만큼 다음줄로 이동
void next_line(FILE *file, int line) {
	int i;
	for (i = 0; i < line; i++) {
		while (!feof(file))
		{
			if (fgetc(file) == '\n') break;
		}
	}
}
 
 
//6.개행문자를 빼고 파일입력
char* nfgets(char *buf, int max, FILE *file) {
	fgets(buf, max, file);                        //한줄불러옴
	buf[strlen(buf) - 1] = '\0';                  //개행문자(엔터)를 제거해줌
	return buf;                                 //개행문자 제거한걸 리턴
}
 
 
//7.Log파일 생성
void log_save(char* input, char* output, char* user_name){
	FILE *fp;
	fp = fopen("log.txt", "a");
	fprintf(fp, "%s : %s \n심심이 : %s\n", user_name, input, output);
	fclose(fp);
}
 

//8.욕 필터링
int filtering(char *input) {
	int i, j;
	if (strstr(input, "신발") != NULL || strstr(input, "강아지") != NULL) {
		for (i = 0; i < 5; i++) {
			MessageBoxA(NULL, "욕하지마세요.\n심심이한테 왜욕하세요?\n안하실거죠??", "욕하지맙시다!", MB_OK); {
			}
			for (j = 0; j < 2; j++){
				MessageBoxA(NULL, "욕하지마세요.\n심심이한테 왜욕하세요?\n진짜진짜진짜안하실거죠??", "욕하지맙시다!", MB_OK);
			}
		}
		return 1;
	}
	return 0;
}


//9.글씨 색변경
void textcolor(int color_number) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}
