class Solution {
public:
    bool search(vector<vector<char> > &board, int i, int j, string &word, int n) {
        if(board[i][j] != word[n]){
            return false;
        }
        if(n == word.size() - 1)
            return true;
        char tmp = board[i][j];
        board[i][j] = '\0';
        if(i>0 && search(board, i-1, j, word, n+1))
            return true;
        if(i<board.size()-1 && search(board, i+1, j, word, n+1))
            return true;
        if(j>0 && search(board, i, j-1, word, n+1))
            return true;
        if(j<board[0].size()-1 && search(board, i, j+1, word, n+1))
            return true;
        board[i][j] = tmp;
        return false;
    }
    bool exist(vector<vector<char> > &board, string word) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        for(int i = 0; i<board.size(); ++i){
            for(int j = 0; j<board[0].size(); ++j){
                if(search(board, i, j, word, 0))
                    return true;
            }
        }
        return false;
    }
};
