ector<vector<int> > generateMatrix(int n) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<vector<int> >VecRes(n, vector<int> (n));
    int leng = 1;
    int row_min = 0;
    int col_min = 0;
    int row_max = n;
    int col_max = n;
    
    while(row_min < row_max && col_min < col_max){
        for(int i = col_min; i < col_max; ++i){
            VecRes[row_min][i] = leng++;
        }
        if(++row_min >= row_max) break;
        for(int i = row_min; i < row_max; ++i){
            VecRes[i][col_max - 1] = leng++;
        }
        if(--col_max <= col_min) break;
        for(int i = col_max - 1; i >= col_min; --i){
            VecRes[row_max - 1][i] = leng++;
        }
        if(--row_max <= row_min) break;
        for(int i = row_max - 1; i >= row_min; --i){
            VecRes[i][col_min] = leng++;
        }
        ++col_min;
    }
    return VecRes;
}
