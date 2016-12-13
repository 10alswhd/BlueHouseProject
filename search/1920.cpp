#include <cstdio>
#include <algorithm>
using namespace std;

int N,M;
//int* N_arr;
int N_arr[100000];

void binarySearch(int left, int right, int &target){

	if(right<left){
		printf("0\n");
		return;
	}
	int mid = (left+right)/2;

	if(N_arr[mid]>(target)){
		binarySearch(left, mid-1, target);
	}
	else if(N_arr[mid]<(target)){
		binarySearch(mid+1,right,target);
	}
	else{
		printf("1\n");
		return;
	}

}

int main(){
	scanf("%d", &N);
	//N_arr = new int[N];
	for(int i=0; i<N; i++){
		scanf("%d", &N_arr[i]);
	}
	sort(N_arr, N_arr+N);
	scanf("%d", &M);
	int target_input;
	for(int i=0; i<M; i++){
		scanf("%d", &target_input);
		binarySearch(0, N-1, target_input);
	}
	return 0;
}
