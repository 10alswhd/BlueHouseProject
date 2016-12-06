// Cite 'n' subtypes of order 'o' for a given node 'str'
void sub_types(char *str, int n, int o){
  // find the given node
  node *par = find_node(str);
  int size = par->size;

  // check if it exists and if we have valid parameters 
  if (par == NULL)
    printf("Node not found");
  else if (n > size || n < 0){
    printf("Invalid number");
  }
  else if (o < 0)
    printf("Your order specifier is invalid (below 0)");
  else{		// If the parameters are valid, do a depth first search to find if there are children of order 'o'
    int i;	// for a given graph node 'str'
    printf("The %d subtypes are: ", n);

    node *temp;
    int counter = 0;
    for(i = 0; i < size; i++){
    	for(temp = par; temp != NULL; temp = temp->child[j++]){ // loop to iterate through the children *unfinished*
   		counter++;
    	}
    }
    for(i = 0; i < n; i++)
      printf("%s ", par->children[i]->name);
  }
}
