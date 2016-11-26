class Solution {
public:
    int numTrees(int n) {
        if(n<=1) return 1; 
        int *a = new int[n+1];
        memset(a, 0, sizeof(int)*(n+1));
        a[1] = 1;
        a[0] = 1;
        for(int i=2; i<=n; i++)
        {
            for(int j=1; j<=i; j++)
            {
                a[i] += (a[j-1] * a[i-j]);
            }
        }
        int ret = a[n];
        delete []a;
        return ret;
    }
};
