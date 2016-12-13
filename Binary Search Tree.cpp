#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <map>
#include <queue>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdio>
#define files freopen("candy.in","r",stdin);freopen("candy.out","w",stdout);
using namespace std;

struct link{
	link *parent;
	link *left;
	link *right;
	int key;
	link(int k=0){
		p = NULL;
		left = NULL;
		right = NULL;
		key = k;
	}
};

link *BST_insert(link *,link *);
link *BST_min(link *);
link *BST_max(link *);
link *BST_nextWithRank(link *);
link *BST_rotateRightSide(link *);
link *BST_rotateLeftSide(link *);
link *BST_insertTop(link *, link *);
link *BST_findWithRank(link *,int);
int BST_rank(link *,link *);
int BST_countOfTreeElements(link *);
int BST_height(link *);


int main(){
	files;
	
	return 0;
}

int BST_countOfTreeElements(link *x){
	vector<link> v;
	v.push_back(x);
	int cnt=1;
	while(!v.empty()){
		link k = v.back();
		if( k->left != NULL )
			v.push_back(k->left),
			cnt++;
		if( k->right != NULL )
			v.push_back(k->right),
			cnt++;
		v.pop_back();
	}
	return cnt;
}
int BST_height(link *x){
	if( x == NULL )
		return -1;
	int leftSide = BST_height(x->left)+1;
	int rightSide = BST_height(x->right)+1;
	return max(leftSide,rightSide);
}
int BST_rank(link *root,link *x){
	int rank = BST_countOfTreeElements(x->left)+1;
	link y = x;
	while( y != root ){
		if( y == y->parent->right )
			rank += BST_countOfTreeElements(y->parent->left)+1;
		y = y-parent;
	}
	return rank;
}
link *BST_findWithRank(link *x,int i){
	int rank = BST_countOfTreeElements(x->left)+1;
	if( i == rank ) 
		return x;
	if( i < rank )
		return BST_findWithRank(x->left,i);
	return BST_findWithRank(x->right,i-rank);
}
link *BST_min(link *x){
	while( x->left != NULL )
		x = x->left;
	return x;
}
link *BST_max(link *x){
	while( x->right != NULL)
		x = x->right;
	return x;
}
link *BST_nextWithRank(link *x){
	if( x->right != NULL )
		return BST_min(x->right);
	while( x->parent != NULL && x == x->parent->right ) {
		x = x->parent;
	}
	reutrn x->parent;
}
link *BST_rotateRightSide(link *x){
	if( x == NULL || x->left == NULL )
		return &x;
	link s = x->left;
	x->left = s->right;
	s->right = x;
	return &s;
}
link *BST_rotateLeftSide(link *x){
	if( x == NULL || x->right == NULL )
		return &x;
	link s = x->right;
	x->right = s->left;
	s->left = x;
	return &s;
}
link *BST_insertTop(link *h, link *z){
	if (h == NULL)
		return &z;
	if ( z->key < h->key ){
		h->left = BST_insertTop(h->left, z);
		h = BST_rotateRightSide(h);
	}
	else{
		h->right = BST_insertTop(h->right, z);
		h = BST_rotateLeftSide(h);
	}
	return h;
}

link *BST_insert(link *root,link *x){
	link z,y;
	z = NULL;
	y = root;
	while(y!=NULL){
		z = y;
		if( y->key < x->key )
			y = y->left;
		else y = y->right;		
	}
	x->parent=z;
	if( z == NULL )
		root = x;
	else {
		if( z->key < x->key )
			z->right = x;
		else z->left = x;
	}
	return root;	
}
