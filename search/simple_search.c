int simpleSearch(int  vector[], int n, int data) { 
    for(int i=0; i<n; i++){
        if(data == vector[i]) {
            return i;
        }
    }
 
    return -1;
}
