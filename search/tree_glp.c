/*
	takes the root of the tree, a new node
	where the last parent will be written to,
	a counter passed as 0, and max = inf
	
	The recursions can be unwrapped in the 
	following pseudocode, based on Depth 
	First Search
	visited = {}
	leaves = {}
	myNode = root
	add root in visited
	if ( myNode->_right != NULL and myNode not in visited ){
		myNode = myNode->_right
		add myNode in visited
		if (myNode->_left == NULL or myNode->_right == NULL ) {
			add myNode in leaves
		}
	} else {
		myNode = myNode->_parent
		if (myNode->_left != NULL and myNode->_left not in visited )
		myNode = myNode->_left
		add myNode in visited
		if (myNode->_left == NULL or myNode->_right == NULL ) {
			add myNode in leaves
		}
	}
	lastParent = leaves.getLastElement()
*/


node* tree_glp(node* nP, node** newP, long int ctr, int* max) {
    printf("@depth %lu: %d\n" , ctr, nP->_data);
    if ((nP->_left == NULL) || (nP->_right == NULL)){
        if (ctr <= *max) {
            *max = ctr; 
            *newP = nP;
        }
        ctr=0;
        return *newP;
    } else {
        ctr++;
        tree_glp(nP->_right, newP, ctr, max);
        tree_glp(nP->_left, newP, ctr, max);
     
    }
}
