#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long J[31268+1];
char S[145234+1];
int s_idx;

void init() {
    memset(J, 0, sizeof(J));
    memset(S, '\0', sizeof(S));
    
    J[1] = 1;
    J[2] = 3;
    J[3] = 6;
    
    S[0] = '1';
    S[1] = '2';
    S[2] = '3';
    
    s_idx = 3;
    
    int i;
    for (i=4; i<=31268; i++) {
        /* J[i] = J[i-1] + len(S[i]) where
           len(S[i]) = len(S[i-1] + str(i)) = J[i-1] - J[i-2] + len(str(i)) */
        
        int len = (int) (log10((double) i) + 1);
        
        int s_i = J[i-1] - J[i-2] + len;
        J[i] = J[i-1] + s_i;
        
        sprintf(S+s_idx, "%d", i);
        s_idx = s_idx + len;
    }
}

int main() {
    init();
    
    int T;
    scanf("%d", &T);
    
    while (T--) {
        int query;
        scanf("%d", &query);
        
        int i;
        for(i=0; i<31268; i++) {
            if (J[i] < query && query <= J[i+1]) {
                printf("%c\n", S[query - J[i] - 1]);
                break;
            }
        }
    }
    
    return 0;
}
