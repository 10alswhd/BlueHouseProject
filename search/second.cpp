// Binary search এর পার্ট
typedef long long ll ;
ll inp[1000000] ;  // size of initial flower
ll updated[1000000] , n , m , w ;
ll BinarySearch(ll expected_height, ll left)
{
    int i , j , start ;
    for ( i = 0 ; i < n ; i++ ) updated[i] = 0 ; // initially all zero
    for ( i = 0 ; i < n ; i++ )
    {
      if( i ) updated[i] += updated[i-1]; // update value if its previously updated
      ll need = expected_height - inp[i] - updated[i] ; // need to do
      if ( need > 0 ) // we need to spray water
      {
          left -= need ; //
          updated[i] += need ;
          updated[i+w] -= need ;
      }
      if(left < 0 ) return 0 ; // if left is less then zero this mean its need  more days to spray water
      // to grow flower that expected_height which is n't possible
    }
    return 1;
}



// Main এর পার্ট
 ll Ans ,  mid ;
    low = 0;
    high = 1000000000000000000 ; // large value
    while( high >= low )
    {
        mid = (high + low)/2;
      
        if(posible(mid,m)) // here m days left
        {
            Ans =  mid ;  // current best answer
          
            low  = mid  + 1 ; // check the next upper_value
        }
        else high = mid - 1; // need to check lesser value
    }
    cout << Ans << endl; 
