public:
    void solve(vector<vector<string> > &res, unsigned int *board, int n, int index) {
        for(int i=0; i<n; ++i){
            board[index] = (1<<i);
            bool flag = false;
            for(int j=0; j<index; ++j){
                if((board[j] & board[index]) || 
                    (board[j] & (board[index]<<(index-j))) || 
                    (board[j] & (board[index]>>(index-j)))){
                        flag = true;
                        break;
                    }
            }
            if(flag)continue;
            if(index == n-1){
                vector<string> r(n, string(n, '.'));
                for(int j=0; j<n; ++j){
                    for(int k=0; k<n; ++k){
                        if(board[j] == (1<<k)){
                            r[j][k] = 'Q';
                            break;
                        }
                    }
                }
                res.push_back(r);
                return;
            }
            solve(res, board, n, index+1);
        }
    }
    
    vector<vector<string> > solveNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<vector<string> > res;
        unsigned int board[32] = {0};
        solve(res, board, n, 0);
        return res;
    }
};
