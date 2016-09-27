package Algorithms.com;

import java.util.Arrays;
import java.util.Random;

/**
 * Created by LogyCom on 30.06.2015.
 */
public class SentinelLinearSearch {
    int[] temp_arr = new int[20];
    Random randomizer = new Random();
    SentinelLinearSearch(){
        for(int i = 0; i < temp_arr.length; i++){
            temp_arr[i] = randomizer.nextInt(20);
        }
        System.out.println(Arrays.toString(temp_arr));
    }
    void search(int num){
        int last = temp_arr[temp_arr.length-1];
        temp_arr[temp_arr.length-1] = num;
        int i = 0;
        for(; temp_arr[i]!= num; i++){

        }
        temp_arr[temp_arr.length-1] = last;
        if(i < temp_arr.length - 1 || num == temp_arr[temp_arr.length-1]){
            System.out.println("Индекс значение: "+i);
        }else{
            System.out.println("Значение не найдено");
        }

    }

}

