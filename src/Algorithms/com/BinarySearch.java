package Algorithms.com;


/**
 * Created by LogyCom on 06.07.2015.
 */
public class BinarySearch {
    //инициализация массива
    int[] temp_arr = new int[1001];

    public BinarySearch(){
        //заполнение массива
        for (int i = 0; i < 1001; i++){
            temp_arr[i] = i;
        }
    }

    void search(int num){
        //инициализация служебных переменных
        int answer = -1, begin = 0, end = temp_arr.length -1;
        //цикл бинарного поиска
        while (begin <= end){
            //инициализация переменной mid середина текущего массива/подмассива (сдвиг байтов) деление на два
            int mid = (begin + end) >>> 1;
            if (temp_arr[mid] == temp_arr[num]){
                //если элемент в центре массива/подмассива равен искомому элементу присваеваем служебной переменной индекс и прерываем цикл
                answer = mid;
                break;
            }else if (temp_arr[mid] > temp_arr[num]){
                //если элемент в середине массива/подмассива больше искомого значения, то переставляем верхнюю границу на mid-1
                end = mid - 1;
            }else if (temp_arr[mid] < temp_arr[num]){
                //если элемент в середине массива/подмассива меньше искомого значения, то переставляем нижнюю границу на mid+1
                begin = mid + 1;
            }
        }
        //вывод сообщения
        System.out.println(answer == -1? "Значение не найдено":"Индекс значения: " + answer);
    }
}

