int minDistance(string word1, string word2) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int m = word1.size();
    int n = word2.size();
    int dp[m+1][n+1];
    for(int i=0; i<=m; ++i){
        dp[i][0] = i;
    }
    for(int i=0; i<=n; ++i){
        dp[0][i] = i;
    }
    for(int i=1; i<=m; ++i){
        for(int j=1; j<=n; ++j){
            dp[i][j] = min(min(dp[i-1][j] + 1, dp[i][j-1] + 1), dp[i-1][j-1] + (word1[i-1] != word2[j-1]));
        }
    }
    return dp[m][n];
}
