#include<stdio.h>

int main()
{
        float lower_bound = 0.0, upper_bound, n, root;

        printf("Enter n: ");
        scanf("%f",&n);

        upper_bound = n;
        
        tolerance = 0.00001;

        // The root of a number lies between 0 and n
        // We do a binary search for the root of n in this space
        do
        {
                root = lower_bound + (upper_bound - lower_bound) / 2;
                if(root*root > n)
                        upper_bound = root;
                else
                        lower_bound = root;
        }
        while(abs(root*root - n) > tolerance);
        printf("Root of %f is %f", n, root);
}
Raw
 slope_square_root.c
#include <stdio.h>

int main()
{
        float root=1.0, n;
        //We take a guess that the root is 1.0
        float tolerance = 0.00001;

        printf("Enter n: ");
        scanf("%f",&n);

        // (n-root*root)/n
        // is a measure of how good/bad our current guess of the root is.
        // It is basically the slope of the line between the points
        // (0, n-root*root) and (n, 0)
        // It slingshots our guess of the root closer to the actual value.
        // Corrects for overshooting our mark as well.


        // tolerance is a measure of how close we want to get to
        // the actual root's value

        while((n - root*root) > tolerance)
        {
                root = root + ((n - root*root)/n);
        }

        printf("Square root of %f is %f",n,root);
}
