package com.github.dector.rtsedu.lab2;

/**
 * @author dector
 */
public class Test {
	static long sTime;
	static long eTime;
	static long time;

	static final int ITERS = 1000000;

	public static void main(String[] args) {
		int[] array = new int[1000000];
		long[][] res = new long[4][ITERS];

		int a = 1;
		int b = 0;

		for (int t = 0; t < ITERS; t++) {
			// Array inner
			sTime = System.nanoTime();
			for (int i = 0; i < array.length; i++) {
				b = array[i] + a;
			}
			eTime = System.nanoTime();
			res[0][t] = eTime - sTime;


			// Array outer
			int length = array.length;
			sTime = System.nanoTime();
			for (int i = 0; i < length; i++) {
				b = array[i] + a;
			}
			eTime = System.nanoTime();
			res[1][t] = eTime - sTime;

			// Array iterator
			sTime = System.nanoTime();
			for (int i : array) {
				b = i + a;
			}
			eTime = System.nanoTime();
			res[2][t] = eTime - sTime;

			// Array header trick
			sTime = System.nanoTime();
			for (int i = 0, size = array.length; i < size; i++) {
				b = array[i] + a;
			}
			eTime = System.nanoTime();
			res[3][t] = eTime - sTime;
		}

		System.out.println("ITERATIONS: " + ITERS);
		System.out.println("[Inner] Avg. Time passed: \t" + avg(res[0]));
		System.out.println("[Outer] Avg. Time passed: \t" + avg(res[1]));
		System.out.println("[Iterator] Avg. Time passed: \t" + avg(res[2]));
		System.out.println("[Header trick] Avg. Time passed: \t" + avg(res[3]));
	}

	private static long avg(long[] array) {
		long s = 0;

		for (int i = 0; i < array.length; i++) {
			s += array[i];
		}

		return s / array.length;
	}
}
