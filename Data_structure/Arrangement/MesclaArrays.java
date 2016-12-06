package testes;

import java.util.Arrays;

public class MesclaArrays {

	public static void main(String[] args) {
		int primeiro[] = {1,4,7,9,6};
		int segundo[] = {2,3,5,8,10};
		int terceiro[] = new int[primeiro.length + segundo.length];
		
		// Copiando itens do primeiro array para o terceiro
		System.arraycopy(primeiro, 0, terceiro, 0, primeiro.length);
		
		// Copiando itens do segundo array para o terceiro
		System.arraycopy(segundo, 0, terceiro, primeiro.length, segundo.length);
		
		// Ordenando os itens do array
		Arrays.sort(terceiro);
		
		// Laço para imprimir itens do array
		for (int i = 0; i < terceiro.length; i++) {
			System.out.println(terceiro[i]);			
		}
		
	}
}
