void shuttlesort (int  a[ ], int n)	 
{
	int temp, i, j;
	
	for  (i = 0; i < n – 1; i++)    	//  primary pass
	{
		if  (a[i] > a[i + 1])   
		{
			j = i – 1;
			temp = a[i + 1];	//  small value to move back
			a[i + 1] = a[i];
			while  (j >= 0  &&  a[j] > temp)	//  go back
			{
				a[j + 1] = a[j];	//  shuffle values forward
				j = j – 1;
			}	//  end secondary pass
			a[j + 1] = temp;	//  insert small value further back
		}			//  else no secondary pass
	}		//  end all passes
}
