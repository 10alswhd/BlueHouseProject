int hash (int table_size, char* data)
{
    unsigned h = 0, g;
    int len = strlen (data);
    int i;
      
    for ( i = 0; i < len; i++ ) {
        h = ( h << 4 ) + data[i];
        g = h & 0xf0000000L;
      
        if ( g != 0 )
                h ^= g >> 24;
      
        h &= ~g;
    }
  
    return (h % table_size);
}
