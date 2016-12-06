public static List<Integer> makeList( int N )
{
ArrayList<Integer> lst = new ArrayList<>( );
for( int i = 0; i < N; i++ )
{
lst.add( i );
lst.trimToSize( );
}
}
