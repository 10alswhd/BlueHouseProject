#include<stdio.h>

int number_of_trees(int n){
        if(n <= 1) return 1;
        int i;
        int sum =0;
        int left=0, right =0;

        for(i=1; i<=n; i++){
                left = number_of_trees(i-1);
                right = number_of_trees(n-i);
                sum=  sum + (left * right);
        }
        return sum;
}
int main(){
        printf("\n%d", number_of_trees(3));
        return 0;
}
