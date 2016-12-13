//
//  main.c
//  Assignment-3-Answer
//
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>

void twenty_questions_level_1(); // 스무고개 레벨 1
void twenty_questions_level_2(); // 스무고개 레벨 2
void rock_paper_scissors(); // 가위 바위 보
void three_six_nine_level_1(); // 369 레벨 1
int three_six_nine_level_2(); // 369 레벨 2


int main(int argc, const char * argv[])
{
    // main 함수는 각 게임을 불러오는 역할을 한다.
    
    int cursor = 0; // 게임을 불러올 숫자를 입력 받을 변수
    
    // 게임 목록을 출력하고 입력 받은 번호의 게임을 시작한다. 게임이 끝나면 다시 목록을 출력한다.
    while (1) {
        puts("\nEnter number that you want run, then press enter.");
        puts("1. Twenty Questions Lv 1");
        puts("2. Twenty Questions Lv 2");
        puts("3. Rock, Paper, Scissors");
        puts("4. 3, 6, 9 Lv 1");
        puts("5. 3, 6, 9 Lv 2");
        
        scanf("%d", &cursor);
        
        switch (cursor) {
            case 1:
                twenty_questions_level_1();
                break;
            case 2:
                twenty_questions_level_2();
                break;
            case 3:
                rock_paper_scissors();
                break;
            case 4:
                three_six_nine_level_1();
                break;
            case 5:
                three_six_nine_level_2();
                break;
            default:
                break;
        }
    }
    return 0;
}

void twenty_questions_level_1(){
    int answer_number = 0; // 컴퓨터가 정하는 답 변수.
    int guess_number = 0; // 사용자가 맞추는 답을 입력 받는 변수.
    int count = 0; // 게임 횟수를 세는 변수.
    
    // 랜덤 함수를 현재 시간 기반으로 섞어준다. 이렇게 하면 실행할 때의 시간은 항상 다르므로 매번 실행할 때마다 rand()는 임의의 값을 가지게 된다.
    srand((unsigned int)time(NULL));
    
    answer_number = rand() % 100;
    
    puts("Please enter a number to guess number what I am thinking!(range 0 ~ 99)");
    
    // 게임 횟수가 20번을 넘어가면 종료한다.
    while (count < 20) {
        scanf("%d", &guess_number);
        if (guess_number > answer_number) {
            puts("\nYour answer is larger than my number. Guess again!");
            count++;
        } else if (guess_number < answer_number) {
            puts("\nYour answer is smaller than my number. Guess again!");
            count++;
        } else {
            puts("\nYou have guessed what I am thinking!");
            break;
        }
    }
    printf("Total guess count: %d\n", count);
    printf("Answer is %d", answer_number);
}

void twenty_questions_level_2() {
    // 이진 탐색 재귀 함수를 선언한다.
    void binary_search(int, int);
    
    puts("I'll guess number what you are thinking of! If my guess is larger than answer, please enter 1, if my guess is smaller than answer, please enter -1, or if my guess is right, please enter 0.(range 0 ~ 99)");
    
    // 이진 탐색 재귀 함수를 호출한다.
    binary_search(0, 99);
}

void binary_search(int left, int right) {
    // 이진 탐색 재귀 함수는 인자로 왼쪽 끝과, 오른쪽 끝의 값을 받는다.
    // 예: 0부터 99라면 왼쪽 값으로 0을 오른쪽 값으로 99를 받는다.
    
    // 이진 탐색은 검색을 중간에서부터 시작하므로 왼쪽 끝과 오른쪽 끝을 더해 2로 나눈 값을 중간으로 정한다.
    int middle = (left + right) / 2;
    int reaction = 0; // 사용자의 응답을 입력 받는 함수.
    
    // 중간 값이 답보다 큰지, 작은지, 같은지 확인해본다.
    printf("I think the answer is %d, isn't it?(Larger: 1, Equeal: 0, Smaller: -1)\n", middle);
    scanf("%d", &reaction);
    
    // 만약 중간 값이 답보다 크다면 중간 값에서 1을 뺀 값을 오른쪽 끝으로 설정하고 다시 함수를 호출한다.
    if (reaction < 0 ) {
        puts("Oh, let me guess again...");
        
        // 왼쪽 값은 그대로 두고 오른쪽 값만 중간 값으로 바꾼다
        binary_search(left, middle - 1);
    }
    // 만약 중간 값이 답보다 작으면 중간 값에서 1을 더한 값을 왼쪽 끝으로 설정하고 다시 함수를 호출한다.
    else if (reaction > 0) {
        puts("Oh, let me guess again...");
        
        // 오른쪽 값은 그대로 두고 왼쪽 값만 중간 값으로 바꾼다.
        binary_search(middle + 1, right);
    }
    // 만약 중간 값 == 답이라면 종료한다.
    else if (reaction == 0) {
        printf("I'm right. Answer is %d\n", middle);
    }
}

void rock_paper_scissors() {
    // 가위 바위 보를 문자열로 입력 받기보다 숫자로 입력 받는 것이 좋다. 현재로썬...
    
    // 입력 받은 숫자를 문자열로 바꾸어주는 함수
    void draw_check(int);
    
    // 승패를 판별하는 함수
    int win_check(int, int);
    
    int user_input = 0; // 사용자의 입력
    int computer_input = 0; // 컴퓨터의 입력
    int win_count = 0; // 이긴 횟수
    int lose_count = 0; // 진 횟수
    int draw_count = 0; // 비긴 횟수
    int flag = 0; // 현재 승무패 상태를 저장하는 변수
    
    srand((unsigned int)time(NULL));
    while (win_count < 5) {
        puts("Enter a number to play with me!(rock: 1, paper: 2, scissor: 3)");
        
        scanf("%d", &user_input);
        printf("You draw ");
        draw_check(user_input);
        
        computer_input = rand() % 3 + 1;
        printf("Computer draw ");
        draw_check(computer_input);
        
        // 반환되는 값을 기준으로 승무패 카운터 변수를 증가시킨다.
        flag = win_check(user_input, computer_input);
        
        if (flag > 0)
            win_count++;
        else if (flag < 0)
            lose_count++;
        else
            draw_count++;
        
        printf("You won %d times, lose %d times, draw %d times.\n\n", win_count, lose_count, draw_count);
    }
}

void draw_check(int input) {
    // 가위 바위 보에 대응하는 숫자를 받아서 문자열로 출력해준다.
    switch (input) {
        case 1:
            puts("rock.");
            break;
        case 2:
            puts("paper");
            break;
        case 3:
            puts("scissor");
        default:
            break;
    }
}

int win_check(int user_input, int computer_input) {
    // 승무패를 판별하려면 가위(3) 바위(1) 보(2)에 해당하는 숫자를 서로 뺀 값을 가지고 판별하는 것이 좋다.
    int diff = user_input - computer_input; // 사용자 입력 값에서 컴퓨터 입력 값을 뺀 값으로 판단한다.
    switch (diff) {
        case 1: // 사용자: 보, 컴퓨터: 바위 || 사용자: 가위, 컴퓨터: 보
        case -2: // 사용자: 바위, 컴퓨터: 가위
            puts("You win!");
            
            // 1을 반환.
            return 1;
            break;
        case 2: // 사용자: 가위, 컴퓨터: 바위
        case -1: // 사용자: 바위, 컴퓨터: 보 || 사용자: 보, 컴퓨터: 가위
            puts("Computer win!");
            
            // -1을 반환.
            return -1;
            break;
        default: // 서로 같을 때
            puts("Draw!");
            break;
    }
    // 0을 반환.
    return 0;
}

void three_six_nine_level_1() {
    int player_number = 0;
    int game_counter = 1;
    int user_input = 0;
    time_t time_a = 0;
    time_t time_b = 0;
    
    puts("Enter player number.");
    scanf("%d", &player_number);
    
    printf("There are total %d player will playing in. You are last player.\n", player_number);
    puts("Game start!");
    
    while (1) {
        
        // 이 반복문은 1부터 시작해서 사용자 차례 직전까지 반복문을 실행한다.
        for (int i = 1; i < player_number; i++) {
            
            switch (game_counter % 10) {
                case 3:
                case 6:
                case 9: // 만약 끝자리가 3, 6, 9면 손뼉을 친다.
                    printf("Player %d claps his hands.\n", i);
                    game_counter++;
                    break;
                default: // 아니면 그냥 그 차례에 해당하는 숫자를 말한다.
                    printf("Player %d says: %d.\n", i, game_counter++);
                    break;
            }
        }
        puts("Your turn.");
        
        // 사용자 입력을 받기 직전에 시각을 저장.
        time_a = time(NULL);
        scanf("%d", &user_input);
        
        // 사용자 입력을 받은 뒤 시각을 저장.
        time_b = time(NULL);
        
        // 2초가 지났다면 시간 초과 처리.
        if (time_b - time_a > 2) {
            puts("Time over!");
            break;
        }
        
        // 만약 사용자 입력이 0이 아니고, 끝자리가 3, 6, 9면 패배.
        if (user_input != 0 && (game_counter % 10 == 3 || game_counter % 10 == 6 || game_counter % 10 == 9)) {
            puts("You lose!");
            break;
        }
        
        // 만약 사용자 입력이 현재 차례와 같지 않고 끝자리가 3, 6, 9가 아니면 패배.
        else if (user_input != game_counter && (game_counter % 10 != 3 && game_counter % 10 != 6 && game_counter % 10 != 9)) {
            puts("You lose!");
            break;
        }
        game_counter++;
    }
}

int three_six_nine_level_2() {
    // 컴퓨터가 틀리게 하는 부분만 제외하고는 레벨 1과 같으므로 주석은 그쪽을 참고.
    int player_number = 0;
    int game_counter = 1;
    int user_input = 0;
    int error_const = 0; // 에러 상수를 결정하는 변수
    
    time_t time_a = 0;
    time_t time_b = 0;
    
    srand((unsigned int)time(NULL));
    
    puts("Enter player number.");
    scanf("%d", &player_number);
    
    printf("There are total %d player will playing in. You are last player.\n", player_number);
    puts("Game start!");
    
    while (1) {
        for (int i = 1; i < player_number; i++) {
            
            // 에러 상수가 가지는 값의 범위는 0에서 99까지, 여기서 5이상은 틀리지 않고, 4이하는 틀리게 설정, 즉 5%의 확률로 에러 발생
            if ((error_const = rand() % 100) > 4) {
                switch (game_counter % 10) {
                    case 3:
                    case 6:
                    case 9:
                        printf("Player %d claps his hands.\n", i);
                        game_counter++;
                        break;
                    default:
                        printf("Player %d says: %d.\n", i, game_counter++);
                        break;
                }
            } else {
                // 틀리는 경우는 0부터 99까지의 임의의 수 더하기 현재 차례로 만들어 무조건 틀린 값이 나오게한다.
                printf("Player %d says: %d.\n", i, (rand() % 100) + i);
                puts("Computer was wrong!");
                puts("You win!");
                return 0;
                break;
            }
        }
        puts("Your turn.");
        time_a = time(NULL);
        scanf("%d", &user_input);
        time_b = time(NULL);
        if (time_b - time_a > 2) {
            puts("Time over!");
            break;
        }
        if (user_input != 0 && (game_counter % 10 == 3 || game_counter % 10 == 6 || game_counter % 10 == 9)) {
            puts("You lose!");
            break;
        } else if (user_input != game_counter && (game_counter % 10 != 3 && game_counter % 10 != 6 && game_counter % 10 != 9)) {
            puts("You lose!");
            break;
        }
        game_counter++;
    }
    return 0;
}
