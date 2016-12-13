
    printf("프로그램 종료\n");
}
 
int SelectMenu()
{
    int key = 0;
    printf("성적 관리 프로그램 0:종료\n");
    printf("1: 학생 데이터 입력 2: 학생 데이터 삭제 3: 학생 검색 4: 목록 보기 \n");
    scanf_s("%d", &key);
    return key;
}
 
int IsAvailNum(int num);//유효한 번호인지 판별
int IsAvailScore(int score);//유효한 성적인지 판별
void AddStudent()
{
    int num = 0;
    Student *stu = 0;
    int s = 0;
 
    printf("추가할 학생 번호(1~%d): ", max_student);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1])//학생 데이터가 있다면
    {
        printf("이미 추가하였습니다\n");
        return;
    }
 
 
    stu = (Student *)malloc(sizeof(Student));//학생 구조체 동적 메모리 할당
    stues[num - 1] = stu;//할당한 메모리 주소를 배열에 설정   
    stu->num = num;
    printf("이름: ");
    scanf_s("%s", stu->name, sizeof(stu->name));
 
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%s 성적:", stitles[s]);
        scanf_s("%d", stu->scores + s);
 
        if (IsAvailScore(stu->scores[s]) == 0)//유효한 성적이 아닐 때
        {
            stu->scores[s] = -1;
            printf("입력한 성적이 유효하지 않아서 %s 성적은 입력 처리하지 않았습니다.\n", stitles[s]);
        }
    }
}
int IsAvailNum(int num)
{
    return (num >= 1) && (num <= max_student);
}
int IsAvailScore(int score)
{
    return (score >= 0) && (score <= 100);
}
void RemoveStudent()
{
    int num = 0;
 
    printf("삭제할 학생 번호(1~%d): ", max_student);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1] == 0)//학생 데이터가 없을 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }
 
    free(stues[num - 1]);//메모리 해제
    stues[num - 1] = 0;
 
    printf("삭제하였습니다.\n");
}
void ViewStuData(Student *stu);
void FindStudent()
{
    int num = 0;
 
    printf("검색할 학생 번호(1~%d): ", max_student);
    scanf_s("%d", &num);
 
    if (IsAvailNum(num) == 0)//유효한 번호가 아닐 때
    {
        printf("범위를 벗어난 학생 번호입니다.\n");
        return;
    }
 
    if (stues[num - 1] == 0)//학생 데이터가 없을 때
    {
        printf("데이터가 없습니다.\n");
        return;
    }
 
    ViewStuData(stues[num - 1]);
}
void ViewStuData(Student *stu)
{
    int i = 0;
    int s = 0;
 
    printf("%4d %10s ", stu->num, stu->name);
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%4d ", stu->scores[s]);
    }
    printf("\n");
}
void ListStudent()
{
    int i = 0;
    int s = 0;
 
    printf("%4s %10s ", "번호", "이름");
    for (s = 0; s<MAX_SUBJECT; s++)
    {
        printf("%4s ", stitles[s]);
    }
    printf("성적이 -1인 곳은 미입력\n");
 
    for (i = 0; i<max_student; i++)
    {
        if (stues[i])
        {
            ViewStuData(stues[i]);
        }
    }
}
void Exit()
{
    int i = 0;
 
    for (i = 0; i<max_student; i++)
    {
        if (stues[i])
        {
            free(stues[i]);
        }
    }
    free(stues);
}
