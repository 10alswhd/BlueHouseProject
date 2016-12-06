bool check(const char* word)
{
    fseek(fp,0,SEEK_SET);
    
    int i = 0;
    string map[count];
    
    int probe = hash_it(word);
   
    int value = hash_it(word);

   for(i=0;i<count;i++)
   {
        if(map[probe]==value)
            return true;
        probe = fmod((probe+1),count);
    }
    return false;
}
