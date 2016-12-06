void * malloc(int size, char * mem){
	
	/*
	
	create hash table with keys as pointers that point to first byte of
		memory blocks. Keys point to end pointers associated with start
		pointers.
	
	sequencial search for free byte in 'mem', 'byte'
		if 'byte' has 'size-1' free bytes after it
			return pointer to 'byte'
			starting at and including 'byte', mark 'size' bytes as taken/used
		else
			continue sequencial search starting from next used byte
		
	
	
	*/
	
}


void free(void * ptr){
	
	/*
	check for 'ptr' in hash map
	if found
		remove 'ptr' from hash map keys
	else
		return error
	
	*/
	
}
