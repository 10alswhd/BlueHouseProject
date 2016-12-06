package com.gmail.vhrushyn;

import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Random rn = new Random();
		int [] a = new int[5 + rn.nextInt(15)];
		for (int i = 0; i < a.length; i++) {
			a[i] = rn.nextInt(20);
		}
		System.out.println(Arrays.toString(a));
		Scanner sc = new Scanner(System.in);
		System.out.println("enter number which need to find");
		int n = sc.nextInt();
		
		if (search(a, n) != -1) {
			System.out.println("number index is "+ search(a, n));
		}
		else {
			System.out.println("there is no such number in array");
		}
		sc.close();
	}
	static int search(int[] a, int b) {
		int n = -1;
		for (int i = 0; i < a.length; i++) {
			if (a[i] == b) {
				n = i;
				break;
			}
		}
		return n;
	}
}
