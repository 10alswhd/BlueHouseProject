#include <stdio.h>

#define MAX_COL 750
#define MAX_ROW 750

#define SQ_OFFSET 0
#define RW_OFFSET 81
#define CL_OFFSET 162
#define BX_OFFSET 243

struct str_node {
    
    struct str_node * Header;
    
    struct str_node * Left;
    struct str_node * Right;
    struct str_node * Up;
    struct str_node * Down;
    
    char IDName;
    int  IDNum;
} ;

int nCol;
int nRow;
struct str_node Matrix[MAX_COL][MAX_ROW];
struct str_node Root;
struct str_node *RootNode = &Root;
struct str_node *RowHeader[MAX_ROW];
char Data[MAX_COL][MAX_ROW];
int Result[MAX_ROW]; int nResult = 0;
char Finished;
int GlobalProgressUpdate;
int MaxK;

// --> Initialisation functions
inline int dataLeft(int i) { return i-1<0?nCol-1:i-1; }
inline int dataRight(int i) { return (i+1)%nCol; }
inline int dataUp(int i) { return i-1<0?nRow-1:i-1; }
inline int dataDown(int i) { return (i+1)%nRow; }

void CreateMatrix(void) {
    int a,b, i, j;
    //Build toroidal linklist matrix according to data bitmap
    for(a=0;a<nCol;a++) {
        for(b=0;b<nRow;b++) {
            if(Data[a][b]!=0) {
                // Left pointer
                i = a; j = b; do { i = dataLeft(i); } while (Data[i][j]==0);
                Matrix[a][b].Left = &Matrix[i][j]; 
                // Right pointer
                i = a; j = b; do { i = dataRight(i); } while (Data[i][j]==0);
                Matrix[a][b].Right = &Matrix[i][j];
                // Up pointer
                i = a; j = b; do { j = dataUp(j); } while (Data[i][j]==0);
                Matrix[a][b].Up = &Matrix[i][j];
                // Down pointer
                i = a; j = b; do { j = dataDown(j); } while (Data[i][j]==0);
                Matrix[a][b].Down = &Matrix[i][j]; 
                // Header pointer
                Matrix[a][b].Header = &Matrix[a][nRow-1];
                Matrix[a][b].IDNum = b;
                //Row Header
                RowHeader[b] = &Matrix[a][b];
            }
        }
    }
    for(a=0;a<nCol;a++) {
        Matrix[a][nRow-1].IDName = 'C';  
        Matrix[a][nRow-1].IDNum = a;
    }
    //Insert root
    Root.IDName = 'R'; 
    Root.Left = &Matrix[nCol-1][nRow-1]; Root.Right = &Matrix[0][nRow-1];
    Matrix[nCol-1][nRow-1].Right = &Root; Matrix[0][nRow-1].Left = &Root;
}

// --> DLX Algorithm functions
struct str_node *ChooseColumn(void) {
    return RootNode->Right;
}

void Cover(struct str_node *ColNode) {
    struct str_node *RowNode, *RightNode;
    ColNode->Right->Left = ColNode->Left;
    ColNode->Left->Right = ColNode->Right;
    for(RowNode = ColNode->Down; RowNode!=ColNode; RowNode = RowNode->Down) {
        for(RightNode = RowNode->Right; RightNode!=RowNode; RightNode = RightNode->Right) {
            RightNode->Up->Down = RightNode->Down;
            RightNode->Down->Up = RightNode->Up;
        }
    }
}

void UnCover(struct str_node *ColNode) {
    struct str_node *RowNode, *LeftNode;
    for(RowNode = ColNode->Up; RowNode!=ColNode; RowNode = RowNode->Up) {
        for(LeftNode = RowNode->Left; LeftNode!=RowNode; LeftNode = LeftNode->Left) {
            LeftNode->Up->Down = LeftNode;
            LeftNode->Down->Up = LeftNode;
        }
    }
    ColNode->Right->Left = ColNode;
    ColNode->Left->Right = ColNode;
}

void SolutionRow(struct str_node *RowNode) {
    Cover(RowNode->Header);
    struct str_node *RightNode;
    for(RightNode = RowNode->Right; RightNode!=RowNode; RightNode = RightNode->Right) { Cover(RightNode->Header); }
}

void PrintSolution(void);

void Search(int k) {
    /*if(GlobalProgressUpdate < k) {
        printf("== Search(%d)\n", k);
        PrintSolution();
        GlobalProgressUpdate = k;
    }*/
    if((RootNode->Left == RootNode && RootNode->Right==RootNode) || k == (81-MaxK)) {
        //Valid solution!
        printf("----------- SOLUTION FOUND -----------\n");
        PrintSolution();
        Finished = 1;
        return;
    }
    struct str_node *Column = ChooseColumn();
    Cover(Column);
    
    struct str_node *RowNode;
    struct str_node *RightNode;
    for(RowNode = Column->Down; RowNode!=Column && !Finished; RowNode = RowNode->Down) {
        // Try this row node on!
        Result[nResult++] = RowNode->IDNum;
        for(RightNode = RowNode->Right; RightNode!=RowNode; RightNode = RightNode->Right) {
            Cover(RightNode->Header);
        }
        Search(k+1);
        // Ok, that node didn't quite work
        for(RightNode = RowNode->Right; RightNode!=RowNode; RightNode = RightNode->Right) {
            UnCover(RightNode->Header);
        }
        Result[--nResult] = 0;
    }
    
    UnCover(Column);
}

// --> Sudoku to Exact Cover conversion

// Functions that extract data from a given 3-digit integer index number in the format [N] [R] [C].
inline int retNb(int N) { return N/81; }
inline int retRw(int N) { return (N/9)%9; }
inline int retCl(int N) { return N%9; }
inline int retBx(int N) { return ((retRw(N)/3)*3) + (retCl(N)/3); }
inline int retSq(int N) { return retRw(N)*9 + retCl(N); }
inline int retRn(int N) { return retNb(N)*9 + retRw(N); }
inline int retCn(int N) { return retNb(N)*9 + retCl(N); }
inline int retBn(int N) { return retNb(N)*9 + retBx(N); }
// Function that get 3-digit integer index from given info
inline int getIn(int Nb, int Rw, int Cl) { return Nb*81 + Rw*9 + Cl; }

void PrintSolution(void) {
    int a,b,c;
    int Sudoku[9][9] = {};
    for(a=0;a<9;a++) for(b=0;b<9;b++) Sudoku[a][b] = -1;
    for(a=0;a<nResult;a++) {
        Sudoku[retRw(Result[a])][retCl(Result[a])] = retNb(Result[a]);
    }    
    for(a=0;a<9;a++) {
        for(b=0;b<9;b++) {
            if(a>0&&a%3==0&&b==0) { for(c=0;c<9;c++) printf("--"); printf("\n"); } //horizontal lines
            if(Sudoku[a][b]>=0) printf("%d%c", Sudoku[a][b]+1, b%3==2?'|':' ' );
            else printf(". ");
        } printf("\n");
    }
}

void BuildData(void) {
    int a,b,c;
    int Index;
    nCol = 324; nRow = 729 + 1;
    for(a=0;a<9;a++) {
        for(b=0;b<9;b++) {
            for(c=0;c<9;c++) {
                Index = getIn(c, a, b);
                Data[SQ_OFFSET + retSq(Index)][Index] = 1; //Constraint 1: Only 1 per square
                Data[RW_OFFSET + retRn(Index)][Index] = 1; //Constraint 2: Only 1 of per number per Row
                Data[CL_OFFSET + retCn(Index)][Index] = 1; //Constraint 3: Only 1 of per number per Column
                Data[BX_OFFSET + retBn(Index)][Index] = 1; //Constraint 4: Only 1 of per number per Box
            }
        }
    }
    for(a=0;a<nCol;a++) { Data[a][nRow-1] = 2; }
    CreateMatrix();
    for(a=0;a<RW_OFFSET;a++) { Matrix[a][nRow-1].IDName = 'S'; Matrix[a][nRow-1].IDNum = a; }
    for(a=RW_OFFSET;a<CL_OFFSET;a++) { Matrix[a][nRow-1].IDName = 'R'; Matrix[a][nRow-1].IDNum = a-RW_OFFSET; }
    for(a=CL_OFFSET;a<BX_OFFSET;a++) { Matrix[a][nRow-1].IDName = 'C'; Matrix[a][nRow-1].IDNum = a-CL_OFFSET; }
    for(a=BX_OFFSET;a<nCol;a++) { Matrix[a][nRow-1].IDName = 'B'; Matrix[a][nRow-1].IDNum = a-BX_OFFSET; }
}

inline void AddNumber(int N, int R, int C) {
    SolutionRow(RowHeader[getIn(N, R, C)]);
    MaxK++;
    Result[nResult++] = getIn(N, R, C);
}

void LoadPuzzle(char *FileName) {
    FILE * a_file = fopen(FileName, "r");
    if(a_file==NULL) { printf("File load fail!\n"); return; } 
    int a,b; char temp;
    for(a=0;a<9;a++) {
        for(b=0;b<9;b++) {
            if(!fscanf(a_file, "%c\n", &temp)) {printf("File loading error!\n"); return; }
            if(temp>='1'&&temp<='9') { AddNumber((temp-'0')-1, a, b);}
        }
    }
}

int main(void) {
    BuildData();
    LoadPuzzle("puzzle.txt");
    Search(0);
    return 0;
}
