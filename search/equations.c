/* 
 * Date:	March 21st, 2014
 * Author: 	James Earle, 5017843
 * Email: 	je11zi@brocku.ca
 * 
 * COSC 2P91 - Procedural Programming
 * Assign. 2, Section 3: Solving Tricky Equations
 * 
 * The program below will read in user input for the 
 * value of a, computing a*x and sin(x), and using
 * an iterative binary search approach to finding 
 * all of the solutions (roots) where sin(x) = a*x.
 * 
 * See example output in equations_output.txt.
 * 	
 */ 
#include <stdio.h>
#include <math.h>
#define E 0.00001
#define PI 3.14159265359

int binarySearch( float x, float xlow, float xhigh, float a, int ctr);
int main( void )
{
	
	while ( 1 ) {
		float a, xlow, xhigh, x;
		printf("\nEnter a value of 'a' to solve for \"sin(x) = (a * x)\"\nAlternately you may enter any non-numerical character to exit.\n");
		if ( scanf("%f",&a) != 1 ) {
			printf("\n\nExiting. Goodbye!\n");
			break;
		}
		int ctr=0,i=1;
		while ( (a*x) < 1 && (a*x) > -1 ) {
			int k = (2*i);
			
			/* There is an interval in the sin wave every (oddInt)Pi/2
			 * so for the first search, xlow is zero while xhigh is 
			 * 3Pi/2, but for every other interval xlow is xhigh's 
			 * previous value while xhigh increments to the next 
			 * interval location. e.g., the second interval xlow is
			 * 3Pi/2, xhigh is 5Pi/2, and this continues for as long
			 * as is neeeded.
			 */
			xhigh = ( (k+1) * PI ) / 2.0;
			
				if( i == 1 ) {
					xlow = 0;
				} else {
					xlow = ( (k-1) * PI ) / 2.0;
				} 
				
			x = (xlow+xhigh) / 2.0;
			
			ctr = binarySearch(x,xlow,xhigh,a,ctr);
			i++;
		}
		
		printf("\nNumber of solutions: %d, including 0.\n",(2*ctr)+1);
		
	}
	return 0;
}

/* Iterative binary search technique, using x, xlow, xhigh, a, and a 
 * counter integer to keep track of the number of solutions that is 
 * incremented and returned after every successful intercept is found.
 */
int binarySearch ( float x, float xlow, float xhigh, float a, int ctr) 
{
	
	while ( (a*x) < 1 && (a*x) > -1 ) {
		
		if( fabs( sin(x) - (a*x) ) <= E ) {
			
			/* Alternate print format for negative
			 * inputs of a.
			 */
			if ( a < 0 ) {
				printf("X = -%.8f, %.8f\n",x,x);
			} else {
				printf("X = %.8f, -%.8f\n",x,x);
			}
			ctr++;
			return ctr;
			
		} else {
			
			/* If the slope is negative, our conditions
			 * for the search are the inverse of if the
			 * slope is positive. 
			 */
			if ( cos(x) < 0 ) {
				
				/* When sin is decreasing, sin > a*x implies the
				 * current x value is left of the intercept.
				 */
				if ( sin(x) > (a*x) ) {
					xlow = x;
					x = (xlow+xhigh) / 2.0;
				} else {
					xhigh = x;
					x = (xlow+xhigh) / 2.0;
				}
				
			} else if ( cos(x) > 0 ) {
				
				/* When sin is increasing, sin > a*x implies the 
				 * current x value is right of the intercept. 
				 */
				if ( sin(x) > (a*x) ) {
					xhigh = x;
					x = (xlow+xhigh) / 2.0;
				} else {
					xlow = x;
					x = (xlow+xhigh) / 2.0;
				}
			} 
		}
	}
	return ctr;	
}
