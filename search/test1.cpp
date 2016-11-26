#include <iostream>
using namespace std;

bool binary_search(long long int arr[],long long int elem){
	int start,mid,end;
	start = 0;
	end = 1000000;
	while(start <= end){
		mid = (start+end)/2;
		if(arr[mid] == elem){
			return true;
		}
		else if(arr[mid] < elem){
			start = mid + 1;
		}
		else if(arr[mid] > elem){
			end = mid - 1;
		}
	}
	return false;
}

bool check_if(long long int arr[],long long int num){
	for(int i=0; i<=1000000; i++){
		if(arr[i] > num){
			return false;
		}
		else if(binary_search(arr,num-arr[i]) == true){
			return true;
		}
	}
	return false;
}

int main() {
	long long int arr[1000001];
	long long int i,n;
	int t;
	for(i=0; i<=1000000; i++){
		arr[i] = i*i;
	}
	cin>>t;
	for(int testcase=0; testcase<t; testcase++){
		cin>>n;
		if(check_if(arr,n) == true){
			cout<<"Yes"<<endl;
		}
		else{
			cout<<"No"<<endl;
		}
	}
	return 0;
}
