int next_number(int num){

  int digits[10];
  int x,y,i;
  for(i=0; i<10; i++)
     digits[i]=0;

  int divisor = 10;
  int multiplier = 1;
 /* While we have processed all digis of the number */
  while(num){
    /* get the rightmost digit in the number */
     x = num %divisor;

    /* Store it for sorting and finding next higher number than pivot */
     digits[x]++;

    /* Get the left digit of rightmost digit i.e x */
     y = (num % (divisor *10))/divisor;

 /* If left digit is less than right one,
     this digit needs to be swapped */
     if(y !=0  && y<x){
         for(i=y; i<10; i++){
          /* search for number which is least greater than y pivot */
            if(digits[i] !=0){
               digits[i]--;
               digits[y]++;
               break;
             }
          }
          /* Swap that digit with pivot i.e y */
          num  =  num /100;
          num = num *100 + i*10 ;
          break;
      }
      else{
       /* If left digit is greater than right one, 
          just remove the last digit and continue. */
          num = num/divisor;
          multiplier *= 10;
      }
   }
 /* If all the digits are in sorted order, there is no number possible */
  if(num == 0)
       return -1;

  /* Restore the number without digits  after pivot */
   num = num * multiplier;
   int temp = 0;
 /*Calculate the number with digits after pivot in non increasing order */
   for(i=0;i<10;){
       while(digits[i] != 0){
           temp = temp + (i) * multiplier;
           digits[i]--;
           multiplier/=10;
       }
       i++;
    }
    return num + temp;
} 
