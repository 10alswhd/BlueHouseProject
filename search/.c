/* -------------------------------------------------------
 File   : Mile4.c
 Purpose: Simple menu processing for Project
 Author : Akilan kanagaratnam
 Date   : April,1,2016
 -------------------------------------------------------
 I declare that the attached assignment is wholly my own
 work in accordance with Seneca Academic Policy. No part
 of this assignment has been copied manually or
 electronically from any other source (other student, or
 web site) or distributed to other students.
 
 Signature:
 -------------------------------------------------------*/
#include<stdio.h>
#define MAX_CART_SIZE 10
#define INVENTORY_SIZE 5

struct Cart {
    int size;
    int quantity[MAX_CART_SIZE];
    int item    [MAX_CART_SIZE];
    float price [MAX_CART_SIZE];
    float totalPrice;
};

/* declaring all the function that is going be used in my program */

void printTitle(void);
int getMenuChoice(void);
void clearScreen(int n);
void printGoodbye(void);
void displayShop(int n, int item[],float price[]);
void findPrice(int n, int item[],float price[]);
int searchShop(int n, int item[],int keyItem);


/*
 Function  : displayCart
 Purpose   : to print cart
 Parameters: struct mainCart
 return    : void
 */
void displayCart( struct Cart *pShoppingCart){
    
    int i=0;
    
    int totalItems = 0;
    
    for (int n = 0; n < 5; n++) {
        totalItems += pShoppingCart->quantity[n];
    }
    
    if (totalItems > 0){
        printf("=====   Cart   =====\n");
        printf("Qty     Item   Price\n");
        printf("---     ----   -----\n");
        for(i=0;i < 5;i++){
            
            if(pShoppingCart->quantity[i] > 0) {
                printf("%d       %d   %.2f\n",pShoppingCart->quantity[i],pShoppingCart->item[i],pShoppingCart->price[i]);
            }
        
        }
        printf("====================\n");
    }
    else
    {
        printf("=====   Cart   =====\n");
        printf("---    empty   -----\n");
        printf("====================\n");
    }
}

/*
 Function  : addCart
 Purpose   : to add items in the cart
 Parameters: struct Cart * pShoppingCart, int item[], float price[]
 return    : void
 */
void addCart (struct Cart * pShoppingCart, int item[], float price[]){
    int choice;
    int quantity = 0;
    int i=0;
    
    printf("Which item would like to add to the cart? ");
    scanf("%d",&choice);
    
    // finding the item
    
    i = searchShop(5,item,choice);
    
    //  p=item[i];
    
    if(i != -1) {
        
        printf("how many quantity ?");
        scanf("%d",&quantity);
        pShoppingCart->quantity[i] += quantity;
        printf("quantity added %d", pShoppingCart->quantity[i]);
        
    }
    else {
        printf("\n");
        printf("*** Item not found ***\n");
    }
}

/*
 Function  : removeCart
 Purpose   : to remove all items in the cart
 Parameters: struct Cart * pShoppingCart
 return    : void
 */
void removeCart (struct Cart * pShoppingCart){
    int i=0;
    int totalItems = 0;
    
    for (int m = 0; m < 5; m++) {
        totalItems += pShoppingCart->quantity[m];
    }
    
    if(totalItems == 0) {
        printf("***  Already empty ***\n");
    } else {
        
        for ( i = 0; i < 5; i++) {
            pShoppingCart->quantity[i] = 0;
            pShoppingCart-> size = 0;
            pShoppingCart->totalPrice=0;
            
        }
        
        printf("Cart is successfully removed\n");
    }
}

/*
 Function   : checkout
 Purpose    : to calcuale total price
 Parameters : struct Cart * pShoppingCart
 Return     : none
 */
void checkout ( struct Cart * pShoppingCart){
    int i;
    float totalprice = 0.0;
    
    for(i=0;i<5;i++){
        totalprice += pShoppingCart->quantity[i] * pShoppingCart->price[i];
        
    }
    
    printf("$ %.2f is the total cost\n",totalprice);
}
/*
 Function   : main
 Purpose    : to processthe choice menu
 Parameters : none
 Return     : none
 */
int main(void){
    
    
    int item[5]={1200,3333,8888,5000,2000};
    float price[5]={20,15,31.50,11.11,1.23};
    int n=5;
    int choice = 0;
    
    struct Cart mainCart;
    
    for (int a = 0; a < 5; a++) {
        mainCart.item[a] = item[a];
        mainCart.price[a] = price[a];
    }
    
    /*  calling printTitle function and getMenuchoice function */
    
    printTitle();
    
    // switch statement to process the menu choice
    
    while(choice!=8)   {
        
        choice = getMenuChoice();
        
        switch (choice){
                
                // calling displayShop function
                
            case 1: displayShop(n,item,price);printf("\n");break;
                
                // calling findPrice function
                
            case 2: findPrice(n,item,price);break;
                
            case 3: displayCart(&mainCart);break;
                
            case 4: addCart(&mainCart, item,price);break;
                
            case 5: removeCart(&mainCart);break;
                
            case 6: checkout(&mainCart);break;
                
                // calling sclearScreen function
            case 7: clearScreen(20); break;
                
                // calling printGoodbye function
            case 8: printGoodbye(); break;
                
                return 0;
                
        }
    }
    printf("\n");
    
    return 0;
    
}

/*
 Function   : printTitle
 Purpose    : print title of the shop
 Parameters : none
 Return     : none
 */
void printTitle(void){
    
    printf("+------------------------------------------------+\n");
    printf("| Welcome to Akilan Kanagaratnam's Grocery Store |\n");
    printf("+------------------------------------------------+\n\n");
    
}

/*
 Function   : getMenuChoice
 Purpose    : display menu and check if valid choice is enetered or not
 Parameters : none
 Return     : choice
 */
int getMenuChoice(void){
    
    int choice;
    printf("\n");
    
    printf("What do you want to do?\n\n");
    
    printf("1 – What’s in the shop?\n");
    printf("2 – What’s the price of an item?\n");
    printf("3 – What’s in my cart?\n");
    printf("4 – Add an item to my cart\n");
    printf("5 – Remove an item from my cart\n");
    printf("6 – Pay for items in my cart\n");
    printf("7 – Clear screen\n");
    printf("8 – Leave the shop\n\n");
    
    printf("Enter your choice ==> ");
    scanf("%d",&choice);
    
    printf("\n");
    
    while( choice <=0 || choice >8){
        
        printf("*** That choice is not valid ***\n");
        printf("\n");
        printf("Enter your choice ==> ");
        scanf("%d",&choice);
        printf("\n");
        
    }
    
    return choice;
    
}

/*
 Function   : clearScreen
 Purpose    : print 20 blank lines
 Parameters : int n
 Return     : none
 */

void clearScreen(int n){
    
    int count=0;
    
    while(count<n){
        printf("\n");
        count ++;
    }
    
}

/*
 Function   : printGoodbye
 Purpose    : print goodbye message
 Parameters : none
 Return     : none
 */

void printGoodbye (void){
    
    printf("Thank you for shopping at ");
    printf("Akilan kanagaratnam's Grocery Store\n\n");
    
}

/*
 Function   : displayShop
 Purpose    : to disply item and price in the shop
 Parameters : int n , int item[],floar[]
 Return     : none
 */

void displayShop(int n, int item[],float price[]){
    
    int i;
    printf("\n");
    printf("=== Inventory ===\n");
    printf("Item        Price\n");
    printf("---         -----");
    
    printf("\n");
    for(i=0;i<n;i++){
        printf("%d        %.2f\n",item[i],price[i]);
    }
    printf("=================");
}

/*
 Function   : findPrice
 Purpose    : prompt user for an item number,
 Parameters : int n , int item[],float price[]
 Return     : price or not found
 */

void findPrice(int n, int item[],float price[]){
    
    int itemNumber;
    int index;
    float p;
    
    printf("Enter an item number==> ");
    scanf("%d",&itemNumber);
    printf("\n");
    index = searchShop(n,item,itemNumber);
    
    if (index == -1) {
        printf("*** Item not found ***\n");
    } else {
        p = price[index];
        printf("price of the item is $%.2f\n",p);
    }
    
}

/*
 Function   : searchShop
 Purpose    : search item array for required key
 Parameters : int n , int item[], int keyItem
 Return     : index or -1 if not found
 */

int searchShop(int number, int item[],int keyItem ){
    
    int index = -1,i;
    
    for ( i = 0; i < number; i++) {
        if (item[i] == keyItem) {
            index = i;
        }
    }
    
    return index;
}
