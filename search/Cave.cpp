#include "cave.h"
#include<iostream>
#include<algorithm>
using namespace std;

// Main
//	int tryCombination(int N, int S[])
//	void answer(int N, int S[], int D[])

bool vis[5002];
int n, R[5002], D[5002];

void change( int i, int j ){
    for( ; i <= j; i++ )
        if( !vis[i] )
            R[i] = ( R[i] + 1 ) % 2;
}

void open( int i ){

    int s, ps, r, b, e, m;
    r = tryCombination( n, R );
    s = r > i || r == -1 ? 0 : 1;

    b = 0; e = n - 1;
    while( b != e ){
        m = (b + e) / 2;
        change( b, m );
        r = tryCombination( n, R );
        ps = r > i || r == -1 ? 0 : 1;
        change( b, m );
        if( ps != s )
            e = m;
        else
            b = m + 1;
    }

    D[b] = i;
    R[b] = s;
    vis[b] = 1;

}

void exploreCave(int N) {
	n = N;
	for( int i = 0; i < n; i++ )
        open( i );
    answer( n, R, D );
}
