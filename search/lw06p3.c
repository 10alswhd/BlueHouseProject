/*********************************************************/
/* lw06p3.c                                              */
/*********************************************************/
/* Author: Enes Gönültaş                                 */
/* Number: 151044030                                     */
/* Date: 24.03.2016                                      */
/*                                                       */
/* Description: Lab 6 Part 3                             */
/*                                                       */
/*********************************************************/
/* Notes:                                                */
/* References:                                           */
/*********************************************************/

/* "include" section */
#include <stdio.h>

/* Prototypes */
/*********************************************************/
/* int extremum(double a, double b, double c,            */
/*              double searchStartingPoint,              */
/*              double stepSize,                         */
/*			    double *mX, double *mY)                  */
/*********************************************************/
/* Parameters: Function takes seven parameter(s).        */
/*     a: a value of the function                        */
/*     b: b value of the function                        */
/*     c: c value of the function                        */
/*     searchStartingPoint: point to start search (x)    */
/*     stepSize: search step size                        */
/*     *mX, *mY: coordinates of the extremum point       */
/*********************************************************/
/* Return Value: Function returns an integer.            */
/*     Step count on success, -1 if inputs are invalid   */
/*********************************************************/
/* Description: extremum(a, b, c, searchStartingPoint,   */
/*                         stepSize, &mX, &mY)           */
/*     This function takes a, b and c values of a        */
/*     function. It searchs for a extremum point based   */
/*     on given searchStartingPoint and stepSize. It     */
/*     returns coordinates of the extremum point.        */
/*********************************************************/
/* Notes:                                                */
/*********************************************************/
int extremum(double a, double b, double	c,
			 double	searchStartingPoint,
		 	 double stepSize, double *mX, double *mY);

/*********************************************************/
/* double f(double a, double b, double c, double p)      */
/*********************************************************/
/* Parameters: Function takes four parameter(s).         */
/*     a: a value of the function                        */
/*     b: b value of the function                        */
/*     c: c value of the function                        */
/*     p: x value of the point                           */
/*********************************************************/
/* Return Value: Function returns a double.              */
/*     Value of the function for given point(p)          */
/*********************************************************/
/* Description: f(a, b, c, x) --> fOfX                   */
/*     This function takes a, b, c values of the         */
/*     function and a point(p). Calculates and returns   */
/*     f(x)                                              */
/*********************************************************/
/* Notes:                                                */
/*********************************************************/
double f(double a, double b, double c, double p);

/* Functions */
int main(void)
{
	int es;
	double mX, mY;

	/* f = x^2 + x + 1, searchStartingPoint = -3 */
	es = extremum(1, 1, 1, -3, 1, &mX, &mY);
	printf("%d %f %f\n", es, mX, mY);

	/* f = x^2 + x + 1, searchStartingPoint = 2 */
	es = extremum(1, 1, 1, 2, 1, &mX, &mY);
	printf("%d %f %f\n", es, mX, mY);

	/* f = -x^2 - x - 1, searchStartingPoint = -3 */
	es = extremum(-1, -1, -1, -3, 1, &mX, &mY);
	printf("%d %f %f\n", es, mX, mY);

	/* f = -x^2 - x - 1, searchStartingPoint = 2 */
	es = extremum(-1, -1, -1, 2, 1, &mX, &mY);
	printf("%d %f %f\n", es, mX, mY);


	return 0;
}

/*********************************************************/
/* Description: f(a, b, c, x) --> fOfX                   */
/*     This function takes a, b, c values of the         */
/*     function and a point(p). Calculates and returns   */
/*     f(x)                                              */
/*********************************************************/
double f(double a, double b, double c, double p)
{
	return a * (p * p) + b * p + c;
}

/*********************************************************/
/* Description: extremum(a, b, c, searchStartingPoint,   */
/*                         stepSize, &mX, &mY)           */
/*     This function takes a, b and c values of a        */
/*     function. It searchs for a extremum point based   */
/*     on given searchStartingPoint and stepSize. It     */
/*     returns coordinates of the extremum point.        */
/*********************************************************/
int extremum(double a, double b, double	c,
			 double	searchStartingPoint,
		 	 double stepSize, double *mX, double *mY)
{
	/* Step count variable */
	int stepCount;
	/* Variables for current and next values of the function */
	double cur, next;
	/* Variable for current point */
	double point;

	/* Check if inputs are invalid */
	if(a == 0 || stepSize <= 0)
	{
		return -1;
	}

	if(a > 0)
	{
		/* Initialize current point */
		point = searchStartingPoint;

		/* If f(sp + ss > f(sp)) when a > 0, it's wrong way */
		/* i.e. searchStartingPoint is on the right hand side */
		cur = f(a, b, c, point);
		next = f(a, b, c, point + stepSize);
		if(next > cur)
		{
			stepSize = -stepSize;
		}
		/* Re-assign current and next point with new stepSize */
		cur = f(a, b, c, point);
		next = f(a, b, c, point + stepSize);

		/* Initialize stepCount */
		stepCount = 0;
		/* Search for extremum point */
		while(next < cur)
		{
			stepCount += 1;
			point += stepSize;
			cur = f(a, b, c, point);
			next = f(a, b, c, point + stepSize);
		}
	}
	else
	{
		/* Initialize current point */
		point = searchStartingPoint;

		/* If f(sp + ss < f(sp)) when a < 0, it's wrong way */
		/* i.e. searchStartingPoint is on the right hand side */
		cur = f(a, b, c, point);
		next = f(a, b, c, point + stepSize);
		if(next < cur)
		{
			stepSize = -stepSize;
		}
		/* Re-assign current and next point with new stepSize */
		cur = f(a, b, c, point);
		next = f(a, b, c, point + stepSize);

		/* Initialize stepCount */
		stepCount = 0;
		/* Search for extremum point */
		while(next > cur)
		{
			stepCount += 1;
			point += stepSize;
			cur = f(a, b, c, point);
			next = f(a, b, c, point + stepSize);
		}
	}

	*mX = point;
	*mY = f(a, b, c, point);
	return stepCount;
}  /* End of extremum(a, b, c, searchStartingPoint, stepSize, &mX, &mY) */

/* EOF */
