/*O(1)空间滚动变量的DP*/
int numDecodings(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int a = 0, b = 1, c = 0;
    for(int i=s.size()-1; i>=0; c = b, b = a, --i){
        a = 0;
        if(s[i] != '0'){
            a = b;
            if(10 * (s[i] - '0') + s[i+1] - '0' <= 26)
                a += c;
        }
    }
    return a;
}

/*O(N)空间的DP*/
int numDecodings(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if(0 == s.size()) return 0;
    int dp[s.size()+2];
    dp[s.size()] = 1;
    dp[s.size()+1] = 0;
    for(int i = s.size() - 1; i>=0; --i){
        if(s[i] == '0'){
            dp[i] = 0;
            continue;
        }
        dp[i] = dp[i+1];
        if(10 * (s[i] - '0') + s[i+1] - '0' <= 26)
            dp[i] += dp[i+2];
    }
    return dp[0];
}
