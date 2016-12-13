inline double f(double x){
	return x*x-2*x+1;
}

/*假設邊界為-10~10*/
printf("%.5f\n",ternary_search(f,-10,10,1e-6));
