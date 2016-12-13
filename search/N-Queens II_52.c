class Solution {
public:
    void solve(int &res, unsigned int *board, int n, int index) {
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
                ++res;
                return;
            }
            solve(res, board, n, index+1);
        }
    }
    int totalNQueens(int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int res = 0;
        unsigned int board[32] = {0};
        solve(res, board, n, 0);
        return res;
    }
};
