/*漂亮的代码*/
int longestValidParentheses(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int numofParentheses = 0;
    int max = 0;
    int len = 0;
    for(int i = 0; i<s.size(); ++i){
        if(s[i] == '('){
            ++numofParentheses;
        }else{
            --numofParentheses;
        }
        ++len;
        if(numofParentheses<0){
            len = 0;
            numofParentheses = 0;
        }else if(numofParentheses == 0){
            max = max>len?max:len;
        }
    }
    len = 0;
    numofParentheses = 0;
    for(int i = s.size() - 1; i>=0; --i){
        if(s[i] == ')'){
            ++numofParentheses;
        }else{
            --numofParentheses;
        }
        ++len;
        if(numofParentheses<0){
            len = 0;
            numofParentheses = 0;
        }else if(numofParentheses == 0){
            max = max>len?max:len;
        }
    }
    return max;
}


/*丑陋的扫描两遍,修改不可能的位置的值*/
int longestValidParentheses(string s) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int numofParentheses = 0;
    int len = 0;
    int max = 0;
    int i;
    for(i = s.size()-1; i>=0; --i){
        if(s[i] == ')'){
            ++numofParentheses;
        }else{
            --numofParentheses;
            if(numofParentheses<0){
                numofParentheses = 0;
                s[i] = ']';
            }
        }
    }
    for(numofParentheses = 0, i = 0; i < s.size(); ++i){
        if(s[i] == '('){
            ++numofParentheses;
        }else if(s[i] == ']'){
            max = max>len?max:len;
            numofParentheses = 0;
            len = 0;
        }else{
            --numofParentheses;
            if(numofParentheses<0){
                max = max>len?max:len;
                numofParentheses = 0;
                len = 0;
            }else{
                len += 2;
            }
        }
    }
    return max>len?max:len;
}
