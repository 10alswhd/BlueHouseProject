#include<stdio.h> 
#include<time.h> 
#include<conio.h> 
#include<Windows.h> 
#include<stdlib.h> 
#include<string.h> 
#define SIZE 200 
   
 char* salloc(int len);									   //0.문자열 동적할당 
10 void   input_data(char *buf, char *who);				   //1.문자열을 입력받음 
11 char* search_question(char *input, int teach);			   //2.질문에 대한 대답을 찾아서 리턴, 없으면 "" 
12 void   print_answer(char *output);					       //3.대답을 프린트 해줌 
13 void    teach_answer(char *buf);						   //4.대답을 파일에 입력하게함  
14 void next_line(FILE *file, int line);					   //5.line만큼 다음줄로 이동 
15 char* nfgets(char *buf, int max, FILE *file);		       //6.개행문자를 빼고 파일입력 
16 void log_save(char* input, char* output, char* user_name); //7.Log파일 생성 
17 int filtering(char *input);								   //8.욕 필터링 
18 void textcolor(int color_number);						   //9.글씨 색변경 
19 
 
20   
21 void main() { 
22 	MessageBoxA(NULL, "사용방법 : 자신의 이름을 정하고 하고싶은 말을 마음껏 치세요. \n심심이를 가르치고 싶다면 \"/t 질문\" 형식으로 써주세요. \n+)대화를 종료하고 싶다면 \"잘가\"를 입력해 주세요\n제작자 : 전현성, 문호현, 김수민, 박상원", "심심이 설명서", MB_OK); 
23 	int i, j, k; 
24 	char *buf; 
25 	int teach; 
26 	char *input; 
27 	char *output; 
28 	char user_name[20]; 
29 	buf = salloc(SIZE); 
30 	srand((unsigned)time(NULL)); 
31 	input_data(user_name, "당신의 이름");				//이름(input) 
32 	 
33 
 
34 	//----------------------------------------대화->계속반복---------------------------------------- 
35 	while (true) { 
36 		teach = 0; 
37 
 
38 		//INPUT 
39 		input_data(buf, user_name);                   //buf에 입력받음 
40 		input = salloc(strlen(buf) + 1);             //input을 buf크기만큼 동적할당(널문자 포함) 
41 		strcpy(input, buf);                         //input에 buf를 넣음 
42 
 
43 
 
44 		//INPUT CHECK 
45 		if (filtering(input) == 1) {                  //욕검출시 intput free하고 continue() 
46 			free(input); 
47 			continue; 
48 		}	 
49 		if (!strcmp("잘가", input)) {				 //"잘가"입력시 심심이 종료 
50 			MessageBoxA(NULL, "심심이를 종료합니다. \n제작자 : 전현성, 문호현, 김수민, 박상원", "심심이 : 잘가~ 또와~~", MB_OK); 
51 			break; 
52 		} 
53  		if (!strncmp(input, "/t ", 3)) {            //if 심심이 가르치기 /t 질문 형식 일때 
54 			input = input + 3;                     //앞에 '/t '를 input에서 지움 
55 			teach = 1; 
56 		} 
57   
58 
 
59 		//OUTPUT 
60 		strcpy(buf, search_question(input, teach));     //input에 맞는 output을 찾아서 buf에 저장, 없으면 NULL 
61 		output = salloc(strlen(buf) + 1);            //output을 buf크기만큼 동적할당(널문자 포함) 
62 		strcpy(output, buf);                     //output에 buf를 넣음 
63   
64 
 
65   
66 		//PRINF & TEACH 
67 		if (strcmp(output, "")) {                  //-질문에 대한 대답있을경우  
68 	 
69 			if (teach == 1) {                     // 가르치기 상태일때 
70 				printf("이미 심심이가 알고있는 질문입니다.\n\n"); 
71 				input = input - 3;                  //할당 받은 만큼 free하기 위해 다시 input의 크기를 원래대로 해줌 
72 			} 
73 			else { 
74 				log_save(input, output,user_name);  //INPUT과 OUTPUT이 정상적으로 출력되었을때 저장 
75 			} 
76 
 
77 			print_answer(output);                   //output을 출력  
78 		 
79 		} 
80 		else {                                 //-질문에 일치하는 대답이 없을경우 
81 			printf("심심이가 모르는 말입니다. 가르쳐 주세요\n\n"); 
82 			teach_answer(input);               //심심이 가르치기 
83 			if (teach == 1) input = input - 3;      //할당 받은 만큼 free하기 위해 다시 input의 크기를 원래대로 해줌 
84 		} 
85   
86   
87 		//FREE 
88 		free(input); 
89 		free(output); 
90 	 
91 	} 
92 
 
93 } 
94   
95   
96 
 
97 //0.문자열 동적할당 
98 char* salloc(int len) { 
99 	return (char*)malloc(sizeof(char)*len);            //len 만큼 동적할당 
100 } 
101   
102   
103 //1.문자열을 입력받음 
104 void  input_data(char *buf, char *who) { 
105 	fflush(stdin);                              //입력장치 초기화 
106 	while (true) {                              //아무것도 입력안하면 반복 -> 입력할때 까직 반복					//누구 :  
107 		textcolor(10); printf("%s : ", who); 
108 		textcolor(7); nfgets(buf, SIZE, stdin); 
109 		printf("\n"); 
110 		//내용을 SIZE만큼 프린트 stdin -> 출력장치 
111 		if (strcmp(buf, "")) break;                  //입력되면 반복문 탈출 
112 	} 
113   
114 } 
115   
116   
117 //2.질문에 대한 대답을 찾아서 리턴, 없으면 "" 
118 char* search_question(char *input, int teach) { 
119 	FILE *fp; 
120 	int output_num, random, check = 0, i; 
121 	char *buf; 
122 	char *similar; 
123 	buf = salloc(SIZE); 
124 	similar = salloc(SIZE); 
125   
126 	if ((fp = fopen("question.txt", "r")) == NULL) return "";   //파일이 없으면 리턴 
127   
128   
129 	for (i = 0; i < 2; i++) {                     //총 2번 파일을 탐색 i - 0.완벽히 일치하는가,  1.조금 일치하는가 
130 		while (!feof(fp)) {                        //파일 끝까직 탐색 
131 			fscanf(fp, "%d", &output_num);            //질문의 답이 몇개인지 output_num에 저장 
132 			nfgets(buf, SIZE, fp);                  //buf에 질문 저장 
133   
134 			if (i == 0 && !strcmp(input, buf)) check = 1;//질문과 완벽히 일치하는가 
135   
136 			if (i == 1 && strlen(buf) > 3 && strstr(input, buf) != NULL) { //if 유사한 질문이 있는가 
137 				check = 1; 
138 				if (teach == 0) printf("\n원하는 대답이 아닐경우 \"/t 질문\" 을 통해 가르쳐 주세요.\n\n"); 
139 			} 
140   
141 			if (check == 1)                        //input과 질문과 일치거나 비슷 하면 
142 			{ 
143 				random = rand() % output_num;         //질문의 답중 출력할 답을 랜덤으로 설정 
144 				next_line(fp, random);               //출력할 대답으로 이동 
145 				nfgets(buf, SIZE, fp);               //대답을 buf에 저장 
146 				fclose(fp); 
147 				return buf;                        //저장한 대답을 리턴 
148 			} 
149 			next_line(fp, output_num + 1);            //다음 질문이 있는 파일위치로 이동 
150 		} 
151 		if (teach == 1) break; 
152 		rewind(fp);                              //파일탐색 위치를 처음으로 돌림 
153 	} 
154   
155 	fclose(fp); 
156 	return ""; 
157 } 
158   
159   
160 //3.대답을 프린트 해줌 
161 void   print_answer(char *output) { 
162 	textcolor(14);  
163 	printf("┌─Simsim──────────────────────────────────┐\n"); 
164 	printf(" %s\n", output); 
165 	printf("└──────────────────────────────────────┘\n\n"); 
166 	textcolor(7); 
167 } 
168   
169   
170 //4.대답을 파일에 입력하게함  
171 void  teach_answer(char *input) { 
172 	char buf[SIZE]; 
173 	int num, i; 
174 	FILE *fp; 
175 	fp = fopen("question.txt", "a"); 
176   
177 	textcolor(12); printf("가르칠 대답의 갯수를 입력해 주세요( 0 입력시 스킵 )"); 
178 	textcolor(7); 
179 	scanf("%s", &buf); 
180 	num = atoi(buf); 
181 
 
182 	if (num == 0) { 
183 		fclose(fp); 
184 		return; 
185 	} 
186 	fprintf(fp, "%d%s\n", num, input);   //대답의 갯수와 질문을 저장         3안녕 
187 	for (i = 0; i < num; i++) {         //대답의 갯수만큼 for문            안녕안녕 
188 		input_data(buf, "TEACH");      //TEACH : 대답을 입력받음         웅 안녕 
189 		fprintf(fp, "%s\n", buf);      //입력받은 대답을 파일에 저장      반가워 
190 	} 
191 	fprintf(fp, " \n");               //공백 처리 
192   
193 	fclose(fp); 
194 } 
195   
196   
197 //5.line만큼 다음줄로 이동 
198 void next_line(FILE *file, int line) { 
199 	int i; 
200 	for (i = 0; i < line; i++) { 
201 		while (!feof(file)) 
202 		{ 
203 			if (fgetc(file) == '\n') break; 
204 		} 
205 	} 
206 } 
207   
208   
209 //6.개행문자를 빼고 파일입력 
210 char* nfgets(char *buf, int max, FILE *file) { 
211 	fgets(buf, max, file);                        //한줄불러옴 
212 	buf[strlen(buf) - 1] = '\0';                  //개행문자(엔터)를 제거해줌 
213 	return buf;                                 //개행문자 제거한걸 리턴 
214 } 
215   
216   
217 //7.Log파일 생성 
218 void log_save(char* input, char* output, char* user_name){ 
219 	FILE *fp; 
220 	fp = fopen("log.txt", "a"); 
221 	fprintf(fp, "%s : %s \n심심이 : %s\n", user_name, input, output); 
222 	fclose(fp); 
223 } 
224   
225 
 
226 //8.욕 필터링 
227 int filtering(char *input) { 
228 	int i, j; 
229 	if (strstr(input, "신발") != NULL || strstr(input, "강아지") != NULL) { 
230 		for (i = 0; i < 5; i++) { 
231 			MessageBoxA(NULL, "욕하지마세요.\n심심이한테 왜욕하세요?\n안하실거죠??", "욕하지맙시다!", MB_OK); { 
232 			} 
233 			for (j = 0; j < 2; j++){ 
234 				MessageBoxA(NULL, "욕하지마세요.\n심심이한테 왜욕하세요?\n진짜진짜진짜안하실거죠??", "욕하지맙시다!", MB_OK); 
235 			} 
236 		} 
237 		return 1; 
238 	} 
239 	return 0; 
240 } 
241 
 
242 
 
243 //9.글씨 색변경 
244 void textcolor(int color_number) { 
245 	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number); 
246 } 
