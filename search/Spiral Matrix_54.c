vector<int> spiralOrder(vector<vector<int> > &matrix) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> VecRes;
    int row_min = 0;
    int col_min = 0;
    int row_max = matrix.size();
    
    if(row_max == 0) return VecRes;
    
    int col_max = matrix[0].size();
    
    while(row_min < row_max && col_min < col_max){
        for(int i = col_min; i < col_max; ++i){
            VecRes.push_back(matrix[row_min][i]);
        }
        if(++row_min >= row_max) break;
        for(int i = row_min; i < row_max; ++i){
            VecRes.push_back(matrix[i][col_max - 1]);
        }
        if(--col_max <= col_min) break;
        for(int i = col_max - 1; i >= col_min; --i){
            VecRes.push_back(matrix[row_max - 1][i]);
        }
        if(--row_max <= row_min) break;
        for(int i = row_max - 1; i >= row_min; --i){
            VecRes.push_back(matrix[i][col_min]);
        }
        ++col_min;
    }
    return VecRes;
}
