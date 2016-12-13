#include<iostream>
#include<queue>
using namespace std;

class Node {
public:
	Node(int data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
	int data; 
	Node* left;
	Node* right;
};
 

void insertNode(Node* &root,int data) {
	if(root == NULL)
		root = new Node(data);
	else if(data <= root->data)
		insertNode(root->left,data);
	else
		insertNode(root->right,data);
}

bool search(Node* root,int data) {
	if(root == NULL)
		return false;
	else if(root->data == data)
		return true;
	else if(data <= root->data)
		return search(root->left,data);
	else
		return search(root->right,data);
}

int getMinimumElement(Node* root){
	if(root == NULL){
		cout<<"Tree is empty !"<<endl;
		return -1;
	}
	while(root->left !=NULL){
		root = root->left;
	}
	//At the end root holds the adrress of the leftmost node
	return root->data;
}

int getMinimumElementByRecursion(Node* root){
	if(root == NULL){
		cout<<"Tree is empty !"<<endl;
		return -1;
	}
	else if(root->left == NULL){
		return root->data;
	}
	//search in left sub tree
	return getMinimumElementByRecursion(root->left);
}

int getMaximumElement(Node* root){
	if(root == NULL){
		cout<<"Tree is empty !"<<endl;
		return -1;
	}
	while(root->right !=NULL){
		root = root->right;
	}
	//At the end root holds the adrress of the leftmost node
	return root->data;
}

int getMaximumElementByRecursion(Node* root){
	if(root == NULL){
		cout<<"Tree is empty !"<<endl;
		return -1;
	}
	else if(root->right == NULL){
		return root->data;
	}
	//search in right sub tree
	return getMaximumElementByRecursion(root->right);
}

int max(int&a, int&b){
	if(a>=b) return a;
	return b;
}

int getHeight(Node* root){
	if(root == NULL) return -1; //For empty tree we define height as -1 for convenience
	return max(getHeight(root->left),getHeight(root->right)) + 1;
}

void levelOrderTraversal(Node* root){
	if(root == NULL) return;
	queue<Node*> q;
	q.push(root);

	while(!q.empty()) {
		Node* current = q.front();
		q.pop(); // removing the element at front
		cout<<current->data<<" ";
		//As we are moving from a node we are storing the refernces of the children in a queue
		if(current->left != NULL) q.push(current->left);
		if(current->right != NULL) q.push(current->right);
	}
}


void preOrderTraversal(struct Node *root) {
	if(root == NULL) return;
 
	cout<<root->data<<" ";
	preOrderTraversal(root->left);
	preOrderTraversal(root->right);
}
 
void inOrderTraversal(Node *root) {
	if(root == NULL) return;
 
	inOrderTraversal(root->left);
	cout<<root->data<<" ";  
	inOrderTraversal(root->right);
}

void postOrderTraversal(Node *root) {
	if(root == NULL) return;
 
	postOrderTraversal(root->left);
	postOrderTraversal(root->right); 
	cout<<root->data<<" ";
}

Node* getMinimumNodeAddress(Node* root)
{
	while(root->left != NULL) root = root->left;
	return root;
}

void deleteNode(Node* &root, int data) {
	if(root == NULL) return;
	else if(data < root->data) deleteNode(root->left,data);
	else if (data > root->data) deleteNode(root->right,data);
	// Wohoo... I found you, Get ready to be deleted	
	else {
		// Case 1:  No child
		if(root->left == NULL && root->right == NULL) { 
			delete root;
			root = NULL;
		}
		//Case 2: One child 
		else if(root->left == NULL) {
			Node *temp = root;
			root = root->right;
			delete temp;
		}
		else if(root->right == NULL) {
			Node *temp = root;
			root = root->left;
			delete temp;
		}
		// case 3: 2 children
		else { 
			Node *temp = getMinimumNodeAddress(root->right);
			root->data = temp->data;
			deleteNode(root->right,temp->data);
		}
	}
}

//Function to find some data in the tree
Node* getNodeAddress(Node* root, int data) {
	if(root == NULL) return NULL;
	else if(root->data == data) return root;
	else if(root->data < data) return getNodeAddress(root->right,data);
	else return getNodeAddress(root->left,data);
}

//Function to find Inorder Successor in a BST
Node* getInorderSuccessor(Node* root,int data) {
	// Search the Node - O(h)
	Node* current = getNodeAddress(root,data);
	if(current == NULL) return NULL;
	if(current->right != NULL) {  //Case 1: Node has right subtree
		return getMinimumNodeAddress(current->right); // O(h)
	}
	else {   //Case 2: No right subtree  - O(h)
		Node* successor = NULL;
		Node* ancestor = root;
		while(ancestor != current) {
			if(current->data < ancestor->data) {
				successor = ancestor; // so far this is the deepest node for which current node is in left
				ancestor = ancestor->left;
			}
			else
				ancestor = ancestor->right;
		}
		return successor;
	}
}

int main() {
	Node* root = NULL;

	insertNode(root,15);	
	insertNode(root,10);	
	insertNode(root,20);
	insertNode(root,25);
	insertNode(root,8);
	insertNode(root,12);
	insertNode(root,2);
	deleteNode(root,2);
	cout<<"Maximum element in the bimary search tree is: "<<getMaximumElement(root)<<endl;
	cout<<"Minimum element in the bimary search tree is: "<<getMinimumElement(root)<<endl;
	cout<<"The height of the binary search tree is: "<<getHeight(root)<<endl;
	cout<<"Level order traversal of binary search tree is: "; levelOrderTraversal(root); cout<<endl;
	cout<<"Preorder traversal of binary search tree is: "; preOrderTraversal(root); cout<<endl;
	cout<<"Inorder traversal of binary search tree is: "; inOrderTraversal(root); cout<<endl;
	cout<<"Postorder traversal of binary search tree is: "; postOrderTraversal(root); cout<<endl;


	int number;
	cout<<"Enter number be searched: ";
	cin>>number;
	
	if(search(root,number)){ 
		cout<<"Found !"<<endl;
		Node* successor = getInorderSuccessor(root,number);
		cout<<"Inorder successor of "<<number<<" is: "<<successor->data<<endl;
	}
	else cout<<"Not Found !"<<endl;
}
