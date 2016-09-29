package Algorithms.com;
import java.util.Arrays;
import java.util.Random;
/**
 * Created by LogyCom on 22.06.2015.
 */
public class LinearSearch {
    int[] temp_arr = new int[20];
    Random randomizer = new Random();
    LinearSearch(){
        for(int i = 0; i < temp_arr.length; i++){
            temp_arr[i] = randomizer.nextInt(20);
        }
        System.out.println(Arrays.toString(temp_arr));
    }
    void search(int num){
        int answer = -1;
        for(int i = 0; i < temp_arr.length; i++){
            if(temp_arr[i]==num){
                answer = i;
            }
        }
        System.out.println(answer == -1? "Значение не найдено":"Индекс значения: " + answer);
    }
}

