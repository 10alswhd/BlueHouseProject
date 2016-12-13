void nextPermutation(vector<int> &num) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    int  i = num.size() - 1;
    for(; i > 0 && num[i-1] >= num[i]; --i);
    if (i > 0){
        int j = num.size() - 1;
        for(; num[j] <= num[i-1]; --j);
        swap(num[j], num[i-1]);
    }
    reverse(num.begin() + i, num.end());
}
