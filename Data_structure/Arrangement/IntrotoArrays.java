public class IntrotoArrays {

	public static void main(String[] args) {
		
		int myArray[] = {3, 6, 13, 67, 83, 2, 192, 83, 44, 92, 71, 142, 110, 173, 3, 90, 94, 1, 19, 67};
		
		int sum = 0;
		for (int i=0;i<myArray.length;i++){
			sum+=myArray[i];
		}
		System.out.println(sum);
		
		
		System.out.println(sum/myArray.length);
		
		
		for (int i=myArray.length-1;i>=0;i--){
			System.out.print(myArray[i] + " ");
		}
		System.out.println();
		
		
		/*for (int i=0;i<2;i++){
			if (i == 1)System.out.print(myArray[myArray.length-1] + " ");
			for (int j=0;j<myArray.length-i;j++){
				System.out.print(myArray[j] + " ");				
				if (j == myArray.length-1)j++;
			}
			if (i == 1)System.out.print(myArray[0]);
			System.out.println();
		}
		no clue what the hell i did
		*/
		int temp = myArray[0];
		myArray[myArray.length-1] = myArray[0];
		myArray[myArray.length-1] = temp;
		
		int least = myArray[0];
		for (int i=1;i<myArray.length;i++){
			if (myArray[i] < least)least = myArray[i];
		}
		System.out.println(least);
		
		sum = 0;
		for (int i=1;i<myArray.length;i+=2){
			myArray[i] *= -1;
			sum+=myArray[i] + myArray[i-1];
			System.out.print(myArray[i-1] + " " + myArray[i] + " ");
		}
		System.out.println();
		System.out.println(sum);
		
		
		int counter = 0;
		for (int i=0;i<myArray.length;i++){
			if (myArray[i] % 2 != 0)counter++;
		}
		System.out.println(counter);
		
		
		for (int i=0;i<myArray.length;i++){
			if (myArray[i] < 10)sum+=myArray[i]*10;
			else sum+=myArray[i];
		}
		
		
		int x = 67;
		counter = 0;
		for (int i=0;i<myArray.length;i++){
			if (x == myArray[i])counter++;
		}
		System.out.println(counter == 0 ? "Number does not appear." : counter);
		
		int sum2 = 0;
		sum = 0;
		for (int i=0;i<10;i++){
			sum+=myArray[i];
			sum2+=myArray[(myArray.length-1)-i];			
		}
		System.out.println(sum > sum2 ? "1st is larger" : "2nd is larger");
		
		
		x = 67;
		counter = 0;
		int counter2 = 0;
		for (int i=0;i<10;i++){
			if (myArray[i]<=x)counter++;
			if (myArray[(myArray.length-1)-i]<=x)counter2++;
		}
		System.out.println(counter > counter2 ? "first has more" : "second has more");
		
		
		int most = 0;
		for (int i=0;i<myArray.length;i++){
			if (myArray[i]>most){
				most = myArray[i];
				System.out.println(myArray[i] + " " + i);
			}
		}
		
		
		x = 3;
		sum = 0;
		for (int i=0;i<myArray.length;i++){
			if (i!=x)sum+=myArray[i];
		}
		System.out.println(sum);
		
		
		sum = 0;
		int element = 0;
		for (int i=1;i<myArray.length;i++){
			if (myArray[i-1] + myArray[i] > sum){
				sum = myArray[i-1] + myArray[i];
				element = i;
			}			
		}
		System.out.println(element + " " + (element-1) + " " + sum);
			
			
		sum = 0;
		element = 0;
		for (int i=0;sum<=50;i++){
			sum+=myArray[i];
			element = i;
		}
		System.out.println(sum + " " + element);
		
		
		counter = 0;
		for (int i=2;i<myArray.length;i++){
			if (Math.abs(myArray[i-1] - myArray[i]) < 5 || Math.abs(myArray[i-1] - myArray[i-2]) < 5){
				counter++;
			}
		}
		System.out.println(counter);
		
		
		sum = 0;
		most = 0;
		element = 0;
		for (int i=0;i<myArray.length;i++){
			for (int j=1;j<myArray.length;j++){
				if (myArray[i] == myArray[j])sum++;
			}
			if (sum > most){
				most = sum;
				element = myArray[i];
			}
			sum = 0;
		}
		System.out.println(most + " " + element);
		
	}

}
