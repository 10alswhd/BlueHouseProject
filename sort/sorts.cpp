void insertionsort(vector<int> &input){
    for(int i = 0 ; i< input.size(); i++){
        int cur = input[i];
        int j = i-1;
        for(; j >=0 && input[j]>cur;j--)
            input[j+1] = input[j];
        input[j+1] = cur;
    }
    
}

void quick(vector<int> & input, int start, int end){
    if(start >= end) return;
    int wall = start;
    for(int i = start + 1; i <= end; i++){
        if(input[i] < input[start]){
            swap(input[i], input[++wall]);
        }
    }
    swap(input[wall], input[start]);
    quick(input, start, wall -1);
    quick(input, wall+1, end);
}

void quicksort(int arr[], int left, int right){
	int i(left);
	int j(right);
	int tmp;
	int pivot = arr[(left+right)/2];
	while(i <= j){
		while(arr[i]<pivot) i++;
		while(arr[j]>pivot) j--;
		if(i <=j){
			swap(arr[i],arr[j]);
			i++;
			j--;
		}
	}

	if(left < j){
		quicksort(arr, left, j);
	}
	if(i < right){
		quicksort(arr, i, right);
	}
}
