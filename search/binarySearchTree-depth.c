int  depth(Treepointer T)‏
{
	if  (T == NULL)‏
		return  0;
	else
		return  max(depth(T->left), depth(T->right)) + 1;
}

int  max(int x, int y)‏
{
	return  x > y ? x : y;
} 
