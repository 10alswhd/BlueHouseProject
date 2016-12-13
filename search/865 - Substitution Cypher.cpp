#include <iostream> 
#include <map> 
using namespace std;

int main(){ 
	int N,i;
	map<char,char>cypher;
	string plaintext, substitute,inputCase;
	cin >> N; 
	cin.ignore(100, '\n');
  	cin.ignore(100, '\n');

	while( N-- ){
		cypher.clear(); 
		getline(cin,plaintext);
		getline(cin,substitute); 
		for(i = 0; i < plaintext.size(); i++){
			cypher[ plaintext[ i ] ] = substitute[ i ];
		}
		cout<<substitute<<endl;
		cout<<plaintext<<endl;
		while( getline(cin,inputCase) ){
			 if (inputCase == "")
        		break;
			for(i = 0; i < inputCase.size(); i++){
				if(cypher.find(inputCase[i]) == cypher.end()){
					cout<<inputCase[i];
				}
				else{
					cout<<cypher[inputCase[i]];
				} 
			}
			cout<<endl;
		}
		if(N) cout<<endl;
	}
}
