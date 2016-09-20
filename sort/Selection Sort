#include <cstdio> // scanf e printf 
 
 
 // defino que MAXN é 1010 e INF é 2000000 (pois o valor máximo de um elemento é 1000000) 
 #define MAXN 1010 
 #define INF 2000000 
 
 
 int n, vetor[MAXN], lista[MAXN], menor, ind_menor; // declaro as variáveis que usarei 
 
 
 int main(){ 
 	 
 	scanf("%d", &n); // leio o valor de n 
 	 
 	for(int i=1; i<=n; i++) scanf("%d", &vetor[i]); // leio os n números do vetor 
 	 
 	for(int i=1; i<=n; i++){ // para cada número a ser impresso 
 		 
 		menor=INF; // faço menor começar como infinito 
 		 
 		for(int j=1; j<=n; j++){ // percorro o vetor 
 			 
 			if(lista[j]==0 && vetor[j]<menor){ // procurando um número menor que "menor" que não esteja na lista 
 				 
 				menor=vetor[j]; // faço "menor" receber seu valor 
 				ind_menor=j; // e guardo seu índice em "ind_menor" 
 			} 
 		} 
 		 
 		printf("%d ", menor); // imprimo o menr número que achei 
 		 
 		lista[ind_menor]=1; // e guardo seu índice na lista de impresos 
 	} 
 	 
 	printf("\n"); // imprimo a quebra de linha no fim da saída 
 } 
