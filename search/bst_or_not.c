int isBST(Node * node){

  if(!node)
       return 1;
  int is_left  = isBST(node->left);
  int is_right  = isBST(node->right);

  if(is_left && is_right){
  /* Since we already know that left sub tree and
 right sub tree are Binary search tree, finding min and max in them would be easy */
   
   Node *max   = find_maximum(node->left);
   Node *min   = find_minimum(node->right);

   //case 1 : Leaf node
    if(!max && !min)
        return 1;
   //Case 2 : only left sub tree is there
    if(max && !min)
        return node->value > max->value;
   //Case 3 : Only right sub tree is there
    if(!max && min)
       return node->value < min->value;
   //Case 4 : Both left and right sub tree are there
    if(node->value > max->value && node->value < min->value)
       return 1;
   }
   return 0;
}
