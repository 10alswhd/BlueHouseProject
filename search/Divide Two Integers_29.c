int divide(int dividend, int divisor) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    if(dividend == 0 || divisor == 0)
        return 0;
    bool bNeg = (dividend<0) != (divisor<0);
    /*下面的写法有坑，-2147483648的-还是它本身，但是正好与2147483648的二进制相同，所以没有出错
    **类似用法的时候要小心*/
    unsigned int lnum = dividend < 0 ? -dividend : dividend;
    unsigned int rnum = divisor < 0 ? -divisor : divisor;
    unsigned int res = 0;
    for(int i = 31; i >= 0; --i){
        if((lnum >> i) >= rnum){
            res += 1 << i;
            lnum -= rnum << i;
        }
    }
    return bNeg ? (int)-res : res;
}
