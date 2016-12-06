#include <iostream>

using namespace std;

struct Node{
	int Data;
	Node *left;
	Node *right;
};

class BSTree{
private:
	Node *Root;

	void __Insert(Node *&root, int data){
		if (root == NULL){
			root = new Node();
			root->Data = data;
			root->left = NULL;
			root->right = NULL;
		}
		else{
			if (data < root->Data){
				__Insert(root->left, data);
			}
			else{
				__Insert(root->right, data);
			}
		}
	}

	void __Print(Node *root){
		if (root == NULL){
			return;
		} else{
			cout << root->Data << " ";	//Preorder
			__Print(root->left);
			//cout << root->Data << " "; //Inorder
			__Print(root->right);
			//cout << root->Data << " "; //Postorder
		}
	}

	int __Height(Node *root){
		if (root == NULL){
			return 0;
		} else{
			int ldepth = __Height(root->left);
			int rdepth = __Height(root->right);

			if (ldepth > rdepth){
				return 1 + ldepth;
			}else{
				return 1 + rdepth;
			}
		}
	}
public:
	BSTree(){
		Root = NULL;
	}

	void Insert(int x){
		if (Root == NULL){
			Root = new Node();
			Root->Data = x;
			Root->left = NULL;
			Root->right = NULL;
		} else{
			__Insert(Root, x);
		}
	}

	int Height(){
		return __Height(Root);
	}



	void PrintTree(){
		__Print(Root);
	}
};

void main(){
	BSTree MyTree;

	for (int i = 0; i < 1024; i++){
		int num = rand() % 100000;
		cout << num << " ";
		MyTree.Insert(num);
	}
	cout << endl << endl;

	MyTree.PrintTree();

	cout << endl << MyTree.Height() << " " << endl;
	system("pause");

}
