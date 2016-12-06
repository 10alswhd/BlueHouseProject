#include<stdio.h>
#include<string.h>
#include<ctype.h>

int m, n;
char letter[55][55];
int search( int path, char find[], int now, int find_length, int X, int Y )
{
    if( find_length == now ) return 1;
    if( X < 0 || X > m || Y < 0 || Y > n ) return 0;
    if( tolower(find[now]) != tolower(letter[X][Y]) ) return 0;
    int ok = 0;
    if( !path )
    {
        ok = search( 1, find, now+1, find_length, X+1, Y );
        ok = (ok) ? 1 : search( 2, find, now+1, find_length, X, Y+1 );  
        ok = (ok) ? 1 : search( 3, find, now+1, find_length, X-1, Y );  
        ok = (ok) ? 1 : search( 4, find, now+1, find_length, X, Y-1 ); 
        ok = (ok) ? 1 : search( 5, find, now+1, find_length, X-1, Y-1 );
        ok = (ok) ? 1 : search( 6, find, now+1, find_length, X+1, Y+1 );
        ok = (ok) ? 1 : search( 7, find, now+1, find_length, X+1, Y-1 );
        ok = (ok) ? 1 : search( 8, find, now+1, find_length, X-1, Y+1 );
    }
    else
    {
        switch( path )
        {
            case 1:
                return search( 1, find, now+1, find_length, X+1, Y );
            break;
            case 2:
                return search( 2, find, now+1, find_length, X, Y+1 );  
            break;
            case 3:
                return search( 3, find, now+1, find_length, X-1, Y );  
            break;
            case 4:
                return search( 4, find, now+1, find_length, X, Y-1 ); 
            break;
            case 5:
                return search( 5, find, now+1, find_length, X-1, Y-1 );
            break;
            case 6:
                return search( 6, find, now+1, find_length, X+1, Y+1 );
            break;
            case 7:
                return search( 7, find, now+1, find_length, X+1, Y-1 );
            break;
            case 8:
                return search( 8, find, now+1, find_length, X-1, Y+1 );    
            break;
        }
    }
    if( ok )
        printf( "%d %d\n", X, Y );
    return ok;
}

int main()
{
    int N;
    while( scanf( "%d", &N ) != EOF )
    {

        int i, j, k;
        for( i = 0 ; i < N ; i++ )
        {
            if( i )
                printf( "\n" );
            
            scanf( "%d%d", &m, &n );
            getchar();
            for( j = 1 ; j <= m ; j++ )
            {
                for( k = 1 ; k <= n ; k++ )
                    letter[j][k] = getchar(); 
                getchar();
            }

            scanf( "%d", &k );
            getchar();
            char find[55];
            
            for( j = 1 ; j <= k ; j++ )
            {
                gets(find);
                
                int slash, X;
                int ok = 0;
                int find_length = strlen(find);
                for( slash = 2 ; slash <= m+n && !ok ; slash++ )
                    for( X = 1 ; slash - X > 0 && !ok ; X++ )
                        ok = search( 0, find, 0, find_length, X, slash-X );
            }
        }
        
        
    }
    return 0;
}
