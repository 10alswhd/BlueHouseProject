#include <stdio.h>
#include <stdlib.h>

#define QUEENS 8 // 皇后的个数，也是棋盘的长和宽

static int total = 0;    // 可行解的总数
static int C[QUEENS] = {0};	// C[i]表示第i行皇后所在的列编号

/** 
 * @brief 输出所有可行的棋局，按行打印.
 * @return 无
 */
void output1() {
    int i, j;
    printf("No. %d\n", total);
    for (i = 0; i < QUEENS; ++i) {
        for (j = 0; j < QUEENS; ++j) {
            if (j != C[i]) {
                printf("0 ");
            } else {
                printf("1 ");
            }
        }
        printf("\n");
    }
}

/** 
 * @brief 输出所有可行的棋局，按列打印.
 *
 * http://poj.grids.cn/practice/2698/ , 这题需要按列打印
 *
 * @return 无
 */
void output() {
    int i, j;
    printf("No. %d\n", total);
    for (i = 0; i < QUEENS; ++i) {
        for (j = 0; j < QUEENS; ++j) {
            if (i != C[j]) {
                printf("0 ");
            } else {
                printf("1 ");
            }
        }
        printf("\n");
    }
}

/** 
 * @brief 检查当前位置(current, column)能否放置皇后.
 *
 * @param[in] current 当前行
 * @return 能则返回1，不能则返回0
 */
static int check(const int current, const int column) {
    int ok = 1;
    int j;
    for(j = 0; j < current; ++j) {
        // 两个点的坐标为(current, column), (j, C[j])
        // 检查是否在同一列，或对角线上
        if(column == C[j] || current - j == column - C[j] || 
            current - j == C[j] - column) {
            ok = 0;
            break;
        }
    }
    return ok;
}

/** 
 * @brief 八皇后，回溯法
 *
 * @param[in] current 搜索当前行，该再哪一列上放一个皇后
 * @return 无
 */
static void search(const int current) {
    if(current == QUEENS) {  // 递归边界，只要走到了这里，意味着找到了一个可行解
        ++total;
        output();
    } else {
        int i;
        for(i = 0; i < QUEENS; ++i) {  // 一列一列的试
            const int ok = check(current, i);
            if(ok) {  // 如果合法，继续递归
                C[current] = i;
                search(current + 1);
            }
        }
    }
}

// 表示已经放置的皇后
// 占据了哪些列
static int columns[QUEENS] = {0};
// 占据了哪些主对角线
static int principal_diagonals[2 * QUEENS] = {0};
// 占据了哪些副对角线
static int counter_diagonals[2 * QUEENS] = {0};

/** 
 * @brief 检查当前位置(current, column)能否放置皇后.
 *
 * @param[in] current 当前行
 * @return 能则返回1，不能则返回0
 */
static int check2(const int current, const int column) {
    return columns[column] == 0 && principal_diagonals[current + column] == 0 
        && counter_diagonals[current - column + QUEENS] == 0;
}

/** 
 * @brief 八皇后，回溯法，更优化的版本，用空间换时间
 *
 * @param[in] current 搜索当前行，该再哪一列上放一个皇后
 * @return 无
 */
static void search2(const int current) {
    if(current == QUEENS) {  // 递归边界，只要走到了这里，意味着找到了一个可行解
        ++total;
        output();
    } else {
        int i;
        for(i = 0; i < QUEENS; ++i) {  // 一列一列的试
            const int ok = check2(current, i);
            if(ok) {  // 如果合法，继续递归
                C[current] = i;
                columns[i] = principal_diagonals[current + i] = 
                    counter_diagonals[current- i + QUEENS] = 1;
                search2(current + 1);
                // 恢复环境
                columns[i] = principal_diagonals[current + i] = 
                    counter_diagonals[current- i + QUEENS] = 0;
            }
        }
    }
}

int main(int argc, char* args[]) {
    total = 0;
    // search(0);
    search2(0);
    return 0;
}
