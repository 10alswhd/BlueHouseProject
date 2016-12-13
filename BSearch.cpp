#include <iostream>
using namespace std;
bool BSearch(int i,int * array);
void mergesort(int a,int b,int * array);
void merge(int a,int p,int c,int * array);
bool BSearch(int item,int a,int b,int * array);
int main()
{
    int N,b,c;
    cout << "Enter the number of elements of the array : " << endl;
    cin >> N;
    int * array = new int[N];
    cout << "Enter the elements : " << endl;
    for(int i=0;i<N;i++)
    {
        cin >> array[i];
    }
    mergesort(0,N-1,array);
    for(int i=0;i<N;i++)
    {
        cout << array[i] << " ";
    }
    BSearch(5,0,N-1,array);
    return 0;
}

bool BSearch(int item,int a,int b,int * array)
{
    int p = (a+b)/2 + 1;
    if((b-a) <= 0)
    {
        return false;
    }
    else if(array[p] == item)
    {
        cout << "Index : " << p << endl;
        return true;
    }
    //search in the second sub array
    else if(item > array[p])
    {
        BSearch(item,p,b,array);
    }
    //search in the first sub array
    else
    {
        BSearch(item,a,p,array);
    }
    return false;
}

void mergesort(int a,int b,int * array)
{
    if(a < b)
    {
        int p = (a + b)/2;
        mergesort(a, p, array);
        mergesort(p+1, b, array);
        merge(a, p, b, array);
    }
}

void merge(int a,int p,int b,int * array)
{
    int * L1 = new int[p-a+2];
    int * L2 = new int[b-p+1];
    L1[p-a+1] = L2[b-p] = INT_MAX;
    for(int i=0;i<=p-a;i++)
    {
        L1[i] = array[i+a];
    }
    for(int j=0;j<b-p;j++)
    {
        L2[j] = array[p+1+j];
    }
    int i=0,j=0;
    for(int k=a;k<=b;k++)
    {
        if(L1[i] > L2[j])
        {
            array[k] = L2[j];
            j++;
        }
        else
        {
            array[k] = L1[i];
            i++;
        }
    }
}
