Treepointer delete(Treepointer T, char item[ ])‏
{
	char upnode[21];
	if  (T == NULL)‏
                return NULL;
	else
	if  (strcmp(item,  T -> data) < 0)‏
	{	T -> left = delete(T -> left, item);
                return T;
	}
	else
	if  (strcmp(item,  T -> data) > 0)	
	{	T -> right = delete(T -> right, item);
                return T;  
	}    
	else		//  item == T -> data, so delete node T
                if  (T -> left    ==  NULL)		//  CASE  1 & 2b
                        return T -> right;		//  right single branch or leaf
                else
                if  (T -> right  ==  NULL) 		//  CASE 2a
                        return T -> left;			//  left single branch
                else				//  CASE 3  find predecessor             
		{       T -> left = find_null_right_branch (T -> left, item);
                        strcpy(T -> data, item);		//  replace with predecessor data
                        return T;
		}
}

Treepointer find_null_right_branch (Treepointer T, char  upitem[ ])‏
{
	if  (T -> right  !=  NULL)‏
	{
               T -> right = find_null_right_branch (T -> right, upitem);
  		return T;
	}        
      else        
  	{
		strcpy(upitem, T -> data);	//  send back up predecessor data item
               return T -> left;		//  link in left branch to parent node
	}
}
