void counting_sort(int a[], int n) {
    //chek than input data are correct
    if (!arr_check(a, n)) {
        throw invalid_argument("array can not contain elements less or equal 0!");
    }
    
    int k = max(a, n); //value of maximum array element
    int *b = new int[n]; //
    int *c = new int[k + 1];
    
    for (int i = 0; i <= k; i++) {
        c[i] = 0;
    }
    
    for (int i = 0; i < n; i++) {
        c[a[i]]++;
    }
    
    for (int j = 1; j <= k; j++) {
        c[j] += c[j - 1];
    }
    
    for (int i = n - 1; i >= 0; i--) {
        b[c[a[i]] - 1] = a[i];
        c[a[i]]--;
    }
    
    memcpy(a, b, sizeof(int) * n);
    
    //clean up
    delete [] b;
    delete [] c;
    b = nullptr;
    c = nullptr;
}
