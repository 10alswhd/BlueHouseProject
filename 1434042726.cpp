#include <stdio.h>
#include <stdlib.h>
#define MAX 100

struct SNode
{
	int info;
	struct SNode *pLeft;
	struct SNode *pRight;
};
typedef struct SNode *TreeNode;

TreeNode MakeNode(int x)
{
	TreeNode p;
	p = (TreeNode)malloc(sizeof(struct SNode));
	p->info = x;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}

void PreOrder(TreeNode tn)
{
	if (tn!=NULL)
	{
		printf("\n%d", tn->info);
		PreOrder(tn->pLeft);
		PreOrder(tn->pRight);
	}
}

void InOrder(TreeNode tn)
{
	if (tn!=NULL)
	{
		InOrder(tn->pLeft);
		printf("\n%d", tn->info);
		InOrder(tn->pRight);
	}
}	

void PostOrder(TreeNode tn)
{
	if (tn!=NULL)
	{
		PostOrder(tn->pLeft);
		PostOrder(tn->pRight);
		printf("\n%d", tn->info);
	}
}

TreeNode Search(TreeNode root, int x)
{
	TreeNode p;
	if (root->info == x)
		return root;
	if (root == NULL)
		return NULL;
	p = Search(root->pLeft, x);
	if (p == NULL)
		p = Search(root->pRight, x);
	return p;
}

void FreeNode(TreeNode p)
{
	free(p);
}

void ClearTree(TreeNode root)
{
	if (root!=NULL)
	{
		ClearTree(root->pLeft);
		ClearTree(root->pRight);
		FreeNode(root);
	}
}

void SetLeft(TreeNode p, int x)
{
	if (p == NULL)
		printf("\nNut khong ton tai ! ");
	else
		if (p->pLeft != NULL)
			printf("\nNut p da co con ben trai.");
		else
			p->pLeft = MakeNode(x);
}

void SetRight(TreeNode p, int x)
{
	if (p == NULL)
		printf("\nNut khong ton tai ! ");
	else
		if (p->pRight != NULL)
			printf("\Nut p da cos con ben phai.");
		else
			p->pRight = MakeNode(x);
}

int DelLeft(TreeNode p)
{
	TreeNode q;
	int x;
	if (p == NULL)
	{
		printf("\n Nut khong ton tai !");
	}
	else
	{
		q = p->pLeft;
		x = q->info;
		if (q == NULL)
			printf("\nNut khong co con ben trai !");
		else
		{
			if (q->pLeft != NULL || q->pRight != NULL)
				printf("\nNut khong phai la la !");
			else
			{
				p->pLeft = NULL;
				FreeNode(p->pLeft);
				return x;
			}
		}
	}
}

TreeNode SearchBST(TreeNode root, int x)
{
	TreeNode p;
	p = root;
	if (p!=NULL)
	{
		if (x < root->info)
			p = SearchBST(root->pLeft, x);
		else if (x>root->info)
			p = SearchBST(root->pRight, x);
		return p;
	}
}

void Insert(TreeNode p, int x)
{
	if (x == p->info)
	{
		printf("\n Noi dung bi trung !");
		return;
	}
	if (x < p->info&&p->pLeft == NULL)
	{
		SetLeft(p, x);
		return;
	}
	if (x>p->info&&p->pRight == NULL)
	{
		SetRight(p, x);
		return;
	}
	if (x < p->info)
		Insert(p->pLeft, x);
	else
		Insert(p->pRight, x);
}

TreeNode Remove(TreeNode p)
{
	TreeNode rp, f;
	if (p==NULL)
	{
		printf("Nut khong ton tai ! ");
		return NULL;
	}else
	{
		if (p->pRight == NULL)
			rp = p->pLeft;
		else
		{
			if (p->pLeft = NULL)
				rp = p->pRight;
			else
			{
				f = p;
				rp = p->pRight;	
				while (rp->pLeft != NULL)
				{
					f = rp;
					rp = rp->pLeft;
				}	
				if (f != p)
				{
					f->pLeft = rp->pRight;
					rp->pRight = p->pRight;
				}
				rp->pLeft = p->pLeft;
			}
		}
		free(p);
		return rp;
	}
}

int main()
{
	
}
