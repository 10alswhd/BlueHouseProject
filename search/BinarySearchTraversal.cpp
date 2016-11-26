#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>

#include <iostream>
#include <string>
#include <algorithm>
#include <stack>

using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;
	Node(int _data) : data(_data), left(NULL), right(NULL) {}
	Node(int _data, Node* _left, Node* _right) : data(_data), left(_left), right(_right) {}
	~Node() { if (left) delete left; if (right) delete right; }
};

template<typename Op>
void preorder_r(Node* root, Op& op)
{
	op.visit(root);
	if (root->left)
		preorder_r(root->left, op);
	if (root->right)
		preorder_r(root->right, op);
}

template<typename Op>
void inorder_r(Node* root, Op& op)
{
	if (root->left)
		inorder_r(root->left, op);
	op.visit(root);
	if (root->right)
		inorder_r(root->right, op);
}

template<typename Op>
void postorder_r(Node* root, Op& op)
{
	if (root->left)
		postorder_r(root->left, op);
	if (root->right)
		postorder_r(root->right, op);
	op.visit(root);
}

template<typename Op>
void preorder_1(Node* root, Op& op)
{
	stack<Node*> s;
	while (true) {
		while (root) {
			op.visit(root);
			s.push(root);
			root = root->left;
		}
		if (s.empty())
			break;
		root = s.top();
		s.pop();
		root = root->right;
	}
}

template<typename Op>
void preorder_2(Node* root, Op& op)
{
	stack<Node*> s;
	s.push(root);
	while (!s.empty()) {
		Node* t = s.top();
		s.pop();
		op.visit(t);
		if (t->right)
			s.push(t->right);
		if (t->left)
			s.push(t->left);
	}
}

template<typename Op>
void inorder_1(Node* root, Op& op)
{
	stack<Node*> s;
	while (true) {
		while (root) {
			s.push(root);
			root = root->left;
		}
		if (s.empty())
			break;
		root = s.top();
		s.pop();
		op.visit(root);
		root = root->right;
	}
}

template<typename Op>
void inorder_2(Node* root, Op& op)
{
	stack<Node*> s;
	s.push(root);
	while (!s.empty()) {
		Node* t = s.top();
		s.pop();
		if (t != NULL) {
			if (t->right)
				s.push(t->right);
			s.push(t);
			s.push(NULL);
			if (t->left)
				s.push(t->left);
		}
		else {
			t = s.top();
			s.pop();
			op.visit(t);
		}
	}
}

template<typename Op>
void inorder_3(Node* root, Op& op)
{
	stack<pair<Node*, bool> > s;
	s.emplace(root, false);
	while (!s.empty()) {
		auto t = s.top();
		s.pop();
		Node* node = t.first;
		if (!t.second) {
			if (node->right)
				s.emplace(node->right, false);
			s.emplace(node, true);
			if (node->left)
				s.emplace(node->left, false);
		}
		else {
			op.visit(node);
		}
	}
}

template<typename Op>
void postorder_1(Node* root, Op& op)
{
	stack<Node*> s;
	while (true) {
		while (root) {
			s.push(root);
			root = root->left;
		}
		if (s.empty())
			break;
		while (!s.empty() && s.top()->right == root) {
			root = s.top();
			s.pop();
			op.visit(root);
		}
		if (!s.empty())
			root = s.top()->right;
		else
			root = NULL;
	}
}

template<typename Op>
void postorder_2(Node* root, Op& op)
{
	stack<Node*> s;
	s.push(root);
	while (!s.empty()) {
		Node* t = s.top();
		if (t != NULL) {
			s.push(NULL);
			if (t->right)
				s.push(t->right);
			if (t->left)
				s.push(t->left);
		}
		else {
			s.pop();
			t = s.top();
			s.pop();
			op.visit(t);
		}
	}
}

template<typename Op>
void postorder_3(Node* root, Op& op)
{
	stack<pair<Node*, bool> > s;
	s.emplace(root, false);
	while (!s.empty()) {
		auto& t = s.top();
		Node* node = t.first;
		if (!t.second) {
			t.second = true;
			if (node->right)
				s.emplace(node->right, false);
			if (node->left)
				s.emplace(node->left, false);
		}
		else {
			s.pop();
			op.visit(node);
		}
	}
}

/*****************************************************************************
*****************************************************************************/
Node* mk_test_tree()
{
	Node* a1 = new Node(1);
	Node* a3 = new Node(3);
	Node* a5 = new Node(5);
	Node* a4 = new Node(4, a3, a5);
	Node* a2 = new Node(2, a1, a4);
	Node* a6 = new Node(6, a2, NULL);
	Node* a9 = new Node(9);
	Node* a8 = new Node(8, NULL, a9);
	Node* a10 = new Node(10, a8, NULL);
	Node* a7 = new Node(7, a6, a10);
	Node* a14 = new Node(14);
	Node* a16 = new Node(16);
	Node* a17 = new Node(17, a16, NULL);
	Node* a15 = new Node(15, a14, a17);
	Node* a18 = new Node(18, a15, NULL);
	Node* a19 = new Node(19, a18, NULL);
	Node* a13 = new Node(13, NULL, a19);
	Node* a12 = new Node(12, NULL, a13);
	Node* a11 = new Node(11, a7, a12);
	return a11;
}

struct NodePrint {
	int count;
	NodePrint() : count(0) {}
	void init() { count = 0; }
	void visit(Node* node) { cout << node->data << " "; ++count; }
	void finish() { cout << " : visited " << count << " nodes" << endl; }
};


int main(int argc, char* argv[])
{
	Node* root = mk_test_tree();

	NodePrint nodeprint;
	
	nodeprint.init();
	preorder_r(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	preorder_1(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	preorder_2(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	inorder_r(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	inorder_1(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	inorder_2(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	inorder_3(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	postorder_r(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	postorder_1(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	postorder_2(root, nodeprint);
	nodeprint.finish();

	nodeprint.init();
	postorder_3(root, nodeprint);
	nodeprint.finish();

	delete root;
	return 0;
}
