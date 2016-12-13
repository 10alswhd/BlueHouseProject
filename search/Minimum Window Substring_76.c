/*chuanying的代码 https://gist.github.com/chuanying/5693925#file-minimum-window-substring-cc */

string minWindow(string S, string T) {
    //number of char we needed, zero means just ok,minus means more than need
    vector<int> char_counts(256,0);
    int need_char_num = 0; //how many unique char in T, it's what we need
    int min_window_size = INT_MAX;
    int min_window_index = -1;
    for(int i=0;i<T.length();i++) {
        char_counts[T[i]]++;
        if(char_counts[T[i]] == 1) {
            need_char_num++;
        }
    }
    for(int begin=0,end=0; end<S.length(); end++) {
        char_counts[S[end]]--;//char not in T will be always minus
        if(char_counts[S[end]]==0) {//one char in T satisfied
            need_char_num--;
        }
        while(begin < end && char_counts[S[begin]]<0) {
            //try our best to minify the window by moving begin
            char_counts[S[begin]]++;
            begin++;
        }
        if(need_char_num == 0) {//all char in the window now
            if(end-begin+1 < min_window_size) {
                min_window_size = end-begin+1;
                min_window_index = begin;
            }
        }
    }
    return min_window_index < 0 ? "" : S.substr(min_window_index,min_window_size);
}


/*画蛇添足的垃圾代码*/
class Solution {
public:
    void change(int &n, int &count, int sign) {
        if(0 == n) return ;
        n += sign;
        if(0 == n || n > 0)count += sign;
        if(0 == n) n+= sign;
    }
    string minWindow(string S, string T) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        vector<int> vec(256, 0);
        int low = 0, high = 0, count = 0, res = 0, max_len = 0;
        for(int i = 0; i < T.size(); ++vec[T[i]], ++count, ++i);
        while(high < S.size()){
            for(; count > 0 && high < S.size(); ++high){
                change(vec[S[high]], count, -1);
            }
            if(count > 0) return S.substr(res, max_len);
            
            for(; count == 0 && low < high; ++low){
                if(high - low < max_len || 0 == max_len){
                    res = low;
                    max_len = high - low;
                }
                change(vec[S[low]], count, 1);
            }
        }
        return S.substr(res, max_len);
    }
};
