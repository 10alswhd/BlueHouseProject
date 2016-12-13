class Solution {
public:
    bool __isInterleave(const char *s1, const char *s2, const char *s3) {
        int num1 = 0, num2 = 0, num3 = 0;
        for(const char *p = s1; num1 + num2 == num3; ){
            s1 += num1, s2 += num2, s3 += num3;
            if(*s3 == '\0') return true;
            for(p = s1, num1 = 0; *p != '\0' && *p == *s3; ++num1, ++p);
            for(p = s2, num2 = 0; *p != '\0' && *p == *s3; ++num2, ++p);
            for(p = s3, num3 = 0; *p != '\0' && *p == *s3; ++num3, ++p);
        }
        if(num1 + num2 < num3) return false;
        return __isInterleave(s1+min(num1, num3), s2+num3-min(num1, num3), s3+num3) || 
                __isInterleave(s1+num3-min(num2, num3), s2+min(num2, num3), s3+num3);
    }
    bool isInterleave(string s1, string s2, string s3) {
        if(s1.size() + s2.size() != s3.size()) return false;
        return __isInterleave(s1.c_str(), s2.c_str(), s3.c_str());
    }
};
