/*
 * I don't have g++ for c++ on windows right now
 * so I had to write this in actual C
 * but it is still valid c++ and should compile
 * 
 */

// Just think of this header file as C's version of iostream
#include <stdio.h>

int main()
{
    double x; // Create a double called x

    // This line is just like cout in C++. Prints formatted text out to standard output
    // We are prompting the user to enter a number
    printf("Enter a double to find the square root of!");

    // This line is just like cin in C++. Asks the users for a value from standard input
    // and stores it as a double at the address of x in memory
    scanf("%lf", &x); 

    // Printing out that we will find the square root of the entered number
    printf("Finding the sqrt of %lf using binary search!\n", x);

    
    // Only need to estimate the sqrt if x is greater than 1
    // Otherwise we can cut things short
    if(x > 1.0)
    {
        double a = 1.0, b = x; // Create a and b, and assign them to one and x
        double mid; // Create an empty mid variable
        
        // The poor man's le loop
        while(1)
        {
            // If there is less than a 0.00001 difference between a and b
            // break out of the loop
            // I could of put this condition in the while loop instead of this if block
            // But I wrote this part of the loop last
            // And had already started writing this comment
            // And now I am too lazy to move it
            if(b - a < 0.00001)
                break;

            mid = (a + b) / 2.0; // Find the half way point of a and b
            double square = mid * mid; // Square the midpoint

            if(square < x)
            {
                // The root is bigger than this midpoint
                // so we can eliminate all smaller numbers from the search
                // by assigning a to mid
                a = mid;
            }
            else
            {
                // The root is smaller than this midpoint
                // so we can eliminate all larger numbers from the search
                // by assigning b to mid
                b = mid;
            }
        }

        // Print out the value of mid!
        printf("I estimated the sqrt of %lf was %lf!", x, mid);
    }
    else // Other wise its over
    {
        printf("Enter a bigger number next time!\n");
    }

    return 0;
}
