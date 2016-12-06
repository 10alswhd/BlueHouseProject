#include<stdio.h>
#include<math.h>
//передаем масив, степень в какую подносить элементы, количество элементов
float summ(float x[], int stepin, int count) {
    float sum = 0.0;
    int i;
    //проходим и суммируем
    for( i = 0; i < count; i++ )
    {
        sum = sum + pow( x[i], stepin );
    }
    return sum;
}               

void main() {
    const size = 10; //размер масива
    float a[size]; // масив указанного размера
    float c; // результат
    puts( "Input array: \n" );
    int k;
    //цикл ввода значений масива
    for( k = 0; k < size; k++ )
    {
        printf("Input a[%d]: ", k);
        scanf("%f",&a[k]);
    }
    //считаем результат
    c = ( summ( a, 1, size ) + summ( a, 2, size ) ) / 10.0; 
    //выводим
    printf( "Result: c=%f", c );
}
