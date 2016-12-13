int atoi(const char *str)
{
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    long long res = 0;
    int sign = 1;
    
    while(isspace(*str))++str;
    if('+' == *str){
        ++str;
    }else if('-' == *str){
        sign = -1;
        ++str;
    }
    for(; isdigit(*str); ++str){
        res *= 10;
        if(sign > 0)
            res += (*str - '0');
        else
            res -= (*str - '0');
        if(res >= INT_MAX)return INT_MAX;
        else if(res <= INT_MIN)return INT_MIN;
    }
    return res;
}
