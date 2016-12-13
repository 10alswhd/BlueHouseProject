int reverse(int x) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int res = 0;
    int flag = 0;
    if(x<0){
        flag = 1;
        x = -x;
    }
    while(x){
        res *= 10;
        res += x%10;
        x /= 10;
    }
    if(flag)
        return -res;
    else
        return res;
}
Raw
