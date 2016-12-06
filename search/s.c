#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // get inputs
    int intFileCount;
    printf("Please input file count: ");
    scanf("%d", &intFileCount);
    if (!intFileCount) {
        printf("Error file count.\n");
        return 1;
    }
    int intSearchCount;
    printf("Please input search count: ");
    scanf("%d", &intSearchCount);
    if (!intSearchCount || intSearchCount <= 0) {
        printf("Error search count.\n");
        return 1;
    }

    // count lines
    FILE *fleIn;
    char strFileName[100];
    char strLine;
    int  i;
    int  intLines = 0;
    for (i = 1; i <= intFileCount; i++) {
        sprintf(strFileName, "in_%d.txt", i);
        fleIn = fopen(strFileName, "rt");
        if (fleIn == NULL) {
            printf("Error openning file: \"%s\"\n", strFileName);
            return 1;
        }
        while (!feof(fleIn)) {
            strLine = fgetc(fleIn);
            if (strLine == '\n') {
                intLines++;
            }
        }
        fclose(fleIn);
    }

    // read file
    char ***arrStrIn   = (char ***)malloc(sizeof(char **) * intLines);  
    for (i = 0; i < intLines; i++) {
        arrStrIn[i]    = (char  **)malloc(sizeof(char  *) *  2);
        arrStrIn[i][0] = (char   *)malloc(sizeof(char   ) * 30);
        arrStrIn[i][1] = (char   *)malloc(sizeof(char   ) *  4);
    }
    char arrChar[30];
    int  intReadIndex = 0;
    int  intOneFile;
    int  j;
    int  k;
    int  curIdx;
    for (i = 1; i <= intFileCount; i++) {
        sprintf(strFileName, "in_%d.txt", i);
        fleIn = fopen(strFileName, "rt");
        if (fleIn == NULL) {
            printf("Error openning file: \"%s\"\n", strFileName);
            return 1;
        }
        intOneFile = 0;
        while (!feof(fleIn)) {
            strLine = fgetc(fleIn);
            if (strLine == '\n') {
                intOneFile++;
            }
        }
        rewind(fleIn);
        for (j = 0; j < intOneFile; j++) {
            fscanf(fleIn, "%s", arrChar);
            curIdx = -1;
            for (k = 0; k < intLines; k++) {
                if (!strcmp(arrStrIn[k][0], arrChar)) {
                    curIdx = k;
                    break;  
                }
            }
            if (curIdx == -1) {
                strcpy(arrStrIn[intReadIndex][0],   arrChar);
                sprintf(arrChar, "%d", 1);
                strcpy(arrStrIn[intReadIndex++][1], arrChar);
            } else {
                sprintf(arrChar, "%d", atoi(arrStrIn[curIdx][1]) + 1);
                strcpy(arrStrIn[curIdx][1], arrChar);
            }
        }
        fclose(fleIn);
    }

    // sort
    int bolFlag = 0;
    char **tmp  = (char  **)malloc(sizeof(char  *) *  2);
    tmp[0]      = (char   *)malloc(sizeof(char   ) * 30);
    tmp[1]      = (char   *)malloc(sizeof(char   ) *  4);
    for (i = 0; i < intLines - 1; i++) {
        bolFlag = 1;
        for (j = 0; j < intLines - i - 1; j++) {
            if (atoi(arrStrIn[j][1]) < atoi(arrStrIn[j + 1][1])) {
                tmp             = arrStrIn[j];
                arrStrIn[j]     = arrStrIn[j + 1];
                arrStrIn[j + 1] = tmp;
                bolFlag         = 0;
            }
        }
        if (bolFlag) {
            break;
        }
    }

    // output, free memory, return
    FILE *fleOut;
    if ((fleOut = fopen("out.txt", "wt")) == NULL) {
        printf ("Error writing file: \"out.txt\"\n");
        return 1;
    }
    printf("Result:\n");
    for (i = 0; i < intLines; i++) {
        if (atoi(arrStrIn[i][1]) >= intSearchCount) {
            printf("%s: %s\n", arrStrIn[i][0], arrStrIn[i][1]);
            fprintf(fleOut, "%s: %s\n", arrStrIn[i][0], arrStrIn[i][1]);
        }
    }
    for (i = 0; i < intLines; i++) {
        free(arrStrIn[i][0]);
        free(arrStrIn[i][1]);
        free(arrStrIn[i]);
    }
    free(arrStrIn);
    fclose(fleOut);
    return 0;
}
