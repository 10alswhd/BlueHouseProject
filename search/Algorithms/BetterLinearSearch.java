package Algorithms.com;

import java.util.Arrays;
import java.util.Random;

/**
 * Created by LogyCom on 30.06.2015.
 */
public class BetterLinearSearch {
    int[] temp_arr = new int[20];
    Random randomizer = new Random();
    BetterLinearSearch(){
        for(int i = 0; i < temp_arr.length; i++){
            temp_arr[i] = randomizer.nextInt(20);
        }
        System.out.println(Arrays.toString(temp_arr));
    }
    void search(int num){
        for(int i = 0; i < temp_arr.length; i++){
            if(temp_arr[i]==num){
                System.out.println("Индекс значения: " + i);
                return;
            }
        }
        System.out.println("Значение не найдено");
    }


}

