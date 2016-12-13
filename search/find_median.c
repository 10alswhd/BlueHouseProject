#include<stdio.h>
#define max(a,b) (a>b)?a:b
#define min(a,b) (a>b)?b:a

int find_median_1(int a[], int n){

        if(n%2 ==0)
                return (a[n/2] + a[n/2+1])/2;
        else
                return a[n/2];
}

int find_median(int a[], int b[],int n){

        //Case where there is one element in each array
        if(n == 1)
                return (a[0] + b[0])/2;
        //Case where size of both array is 2
        if(n == 2){
                return (max(a[0], b[0]) + min(a[1],b[1]))/2;
        }

        int median_1  = find_median_1(a,n);
        int median_2  = find_median_1(b,n);
	//If both medians are equal
        if(median_1 == median_2)
                return median_1;
	// else search in appropriate parts of array
        else if(median_1 < median_2){
                if(n%2 ==0){
                	//If no. of elements are even, then do not include the middle element in next step
                        return find_median(a+n/2-1, b, n-n/2);
                }
                else{
                	//If no. of elements are odd, then include the middle element in next step
                        return find_median(a+n/2, b, n-n/2);
                }
        }
        else if(median_1 > median_2){
                if(n%2 ==0){
                        return find_median(b+n/2-1, a, n-n/2);
                }
                else{
                        return find_median(b+n/2, a, n-n/2);
                }
        }
        return -1;
}
int main(){

        int a[] = {10,30,40,50,60};
        int b[] = {30,50,100,110, 200};

        int size  = sizeof(a)/sizeof(a[0]);

        int median ;

        median = find_median(a,b, size);

        printf("\n Median of two sorted array is : %d", median);
        return 0;
}
