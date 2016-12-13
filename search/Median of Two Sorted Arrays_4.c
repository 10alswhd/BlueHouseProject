lass Solution {
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        long long l = INT_MIN, r = INT_MAX, t = 0, h = (m + n) / 2, is_odd = (m ^ n) & 1, l_c, u_c;
        for(; l <= r; t = (l + r) / 2) {
            if((u_c = upper_bound(A, A + m, t) - A + upper_bound(B, B + n, t) - B) <= h) l = t + 1;
            else if((l_c = lower_bound(A, A + m, t) - A + lower_bound(B, B + n, t) - B) > h) r = t - 1;
            else if(is_odd || l_c < h) return t;
            else break;
        }
        return (max(lower_bound(A, A + m, t) == A ? INT_MIN : *(lower_bound(A, A + m, t) - 1), 
            lower_bound(B, B + n, t) == B ? INT_MIN : *(lower_bound(B, B + n, t) - 1)) + t) / 2.0;
    }
};






class Solution {
public:
    double mid(int B[], int n){
        return n & 1 ? B[n/2] : (B[n/2-1]+B[n/2])/2.0;
    }
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        if(m > n) return findMedianSortedArrays(B, n, A, m);
        if(m < 3)
        {
            vector<int> vec(A, A + m);
            vec.insert(vec.end(), B + ((n-1)/2-(n>2)), B + (n/2+1+(n>2)));
            sort(vec.begin(), vec.end());
            return vec.size() & 1 ? vec[vec.size()/2] : (vec[vec.size()/2] + vec[vec.size()/2 - 1])/2.0;  
        }
        if(mid(A, m) > mid(B, n))
            return findMedianSortedArrays(A, m - ((m+1)/2-1), B + ((m+1)/2-1), n - ((m+1)/2-1));
        else
            return findMedianSortedArrays(A + ((m+1)/2-1), m - ((m+1)/2-1), B, n - ((m+1)/2-1));
    }
};





class Solution {
public:
    double mid(int B[], int n){
        if(0 == n%2){
            return ((double)(B[n/2-1]+B[n/2]))/2.0;
        }else{
            return B[n/2];
        }
    }
    void insert(int arr[], int n, int value){
        if(0 == n)arr[0] = value;
        int i;
        for(i=n; i>0; --i){
            if(arr[i-1]>value){
                arr[i] = arr[i-1];
            }else{
                break;
            }
        }
        arr[i] = value;
        return ;
    }
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        double tmp;
        int i;
        int arr[6];
        if(m>n)return findMedianSortedArrays(B, n, A, m);
        if(0 == m){
            return mid(B, n);
        }
        if(1 == m){
            if(1 == n)return ((double)(A[0]+B[0]))/2.0;
            if(0 == n%2){
                if(A[0] > B[n/2])return B[n/2];
                else if(A[0] < B[n/2-1])return B[n/2-1];
                else return A[0];
            }else{
                if(A[0] > B[n/2+1])return ((double)(B[n/2]+B[n/2+1]))/2.0;
                else if(A[0] < B[n/2-1])return ((double)(B[n/2]+B[n/2-1]))/2.0;
                else return ((double)(A[0]+B[n/2]))/2.0;
            }
        }else if(2 == m){
            insert(arr, 0, A[0]);
            insert(arr, 1, A[1]);
            if(2 == n){
                insert(arr, 2, B[0]);
                insert(arr, 3, B[1]);
                return mid(arr, 4);
            }
            if(0 == n%2){
                insert(arr, 2, B[n/2-2]);
                insert(arr, 3, B[n/2-1]);
                insert(arr, 4, B[n/2]);
                insert(arr, 5, B[n/2+1]);
                return mid(arr, 6);
            }
            insert(arr, 2, B[n/2-1]);
            insert(arr, 3, B[n/2]);
            insert(arr, 4, B[n/2+1]);
            return mid(arr, 5);
        }
        i = (m+1)/2-1;
        if(mid(A, m) > mid(B, n))
            return findMedianSortedArrays(A, m-i, B+i, n-i);
        else
            return findMedianSortedArrays(A+i, m-i, B, n-i);
    }
};
