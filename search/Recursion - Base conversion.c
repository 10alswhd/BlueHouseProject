//
//  main.cpp
//  Recursion
//
//  Created by Aurelia Friska on 12/1/14.
//  Copyright (c) 2014 Aurelia Friska. All rights reserved.
//

#include <stdio.h>

void convert_basis(int num,int base){
    if(num > 0){
        int rem = (num % base);
        convert_basis(num / base, base);
        printf("%d",rem);
    }
}

int main() {
    int num, base;
    printf("\t\t\tBase Conversion Numbers\n");
    printf("=============================================\n\n");
    
    do {
        printf("Input the numbers that you want to search[1-100][0 to exit]: ");
        scanf("%d", &num);
        fflush(stdin);
        if (num == 0)
            return 0;
    } while (num<1 || num>100);
    do{
        printf("Input the number of base [2-20]: ");
        scanf("%d", &base);
        fflush(stdin);
    } while (base<2 || base>20);
    printf("\n\n");
    int flag=base;
    for(int i=flag; i>1; i--){
        printf("Number %d in base %d is : ", num, base);
        convert_basis(num,base);
        base--;
        printf("\n");
        
    }
    
    printf("\n\nPress enter to continue.......");
    
    getchar();
    return 0;
}
