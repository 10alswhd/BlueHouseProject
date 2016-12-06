public int size() {   
	int size = 0;
	Node cur = head;
	
	while(cur != null) {
		size++;
		cur = cur.next();
	}
	return size;
}
