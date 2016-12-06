/*
*  Implement an array converter
*  For an array, ignore ALL 0s, if a number is the same as its next number (ignore 0s), sum up the two number and put the sum in the former index. 
*  Else just put the value in the same position. 
*  Add 0s into the new until it has the same length as original array 
*  Example:  [1,0,0,1,2,3,3,4,5] -> [2,2,6,4,5,0,0,0,0] 
Quetsion:
[1,1,0,1] -> [2,1,0,0]?
or
[1,1,2,4] -> [2,2,4,0]?
*/

public int[] convertArray(int A[]){
    int[] newArr = new int[A.length];
    int k = 0;
    if(A.length==0) return newArr;
    for(int i=0;i<A.length;i++){
        if(A[i]==0) continue;
        int j=i+1;
        if(j<A.length){
            while(A[j]<A.length && A[j]==0) j++;
            if(A[i] == A[j]){
                newArr[k++]=A[i]*2;
                i = j+1;
            }else{
                newArr[k++]=A[i];
            }
        }else{
            newArr[k++]=A[i];
        }
    }
    while(k<A.length){
        newArr[k++] = 0;
    }
    return newArr;
}



/*
*  Convert an array follow the instructions below
*  Consider the array as pairs( 2 numbers forms a pair ), given two array A and B
*  For each pair in a, determine if it can be found in b, if found, put the nuumber AFTER the pair in b into the new array
*  Fill the rest of the arry with 0 until it has the same length as A
*  Example:  A = [3,2,3,3,3,4], B = [3,2,1,3,3,4,5] -> [1,4,5,0,0,0] 
You can also assume numbers in both array are less than 10, between 0 and 9  inclusvie
can I assume any pair in B is unique? Yes
Is the A.length always an even number? Yes
*/

public int[] convertArray2( int A[], int B[] ){

    Map<Integer,Integer> bmap = new HashMap<Integer, Integer>();
    int[] resultArr = new int[A.length];
    int k = 0;

    //key: pair numbers ; value:the integer after this pair (A[length-1] is not counted into the pair)
    for(int i = 0; i < B.length-2; i++){
        int pair = B[i]*10 + B[i+1];
        bmap.put(pair, B[i+2]);
    }

    for(int i = 0; i < A.length-1; i += 2){
        int pair = A[i]*10 + A[i+1];
        if(bmap.containsKey(pair){
            resultArr[k++] = bmap.get(pair);
        }
    }
    
    while(k < A.length) 
        resultArr[k++] = 0;
        
    return resultArr;
}






