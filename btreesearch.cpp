#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

template<class T>
struct BNode
{
    T data;
    BNode<T> *left, *right;
    BNode(T dd, BNode<T> *l = 0, BNode<T> *r = 0) :
        data(dd), left(l), right(r) {}
};

template<class T>
class BTree
{
public:
    BNode<T> *r;//указатель на корень

    BTree(BNode<T> *rr)
    {
        r = rr;
    }

    BNode<T>* search3();
private:
    BNode<T>* search3(BNode<T>* node);
};

template <class T>
BNode<T>* BTree<T>::search3(BNode<T>* node)
{
    BNode<T>* resNode = NULL;
    if (node != NULL)
    {
        BNode<T>* leftSon = node->left;
        BNode<T>* leftGrandSon;
        if (leftSon != NULL && (leftGrandSon = leftSon->left) != NULL)
        {
            T x = node->data, y = leftSon->data, z = leftGrandSon->data;
            if (x>2*y && y>2*z) return node;
        }
        resNode = search3(node->left);
        if (resNode != NULL) return resNode;
        resNode = search3(node->right);
        if (resNode != NULL) return resNode;
    }
    return resNode;
}

template <class T>
BNode<T>* BTree<T>::search3()
{
    return search3(r);
}

template<class T>
void print(BNode<T> *r, int offset = 0)
{
    if (r == 0) return;
    print(r->right, offset + 3);
    for (int i = 0; i<offset; i++)
        cout << ' ';
    cout << r->data << endl;
    print(r->left, offset + 3);
}

int main()
{
    BNode<int> *tree =  new BNode<int>(10,
                                       new BNode<int>(3, new BNode<int>(1), new BNode<int>(7)),
                                       new BNode<int>(8, new BNode<int>(9), new BNode<int>(5)));
    print(tree);
    BTree<int> Tr(tree);
    string s = "";
    BNode<int>* resNode = Tr.search3();
    if (resNode == NULL)
        cout << "Node didn't find";
    else
        cout<<resNode->data << "->" << resNode->left->data << "->" << resNode->left->left->data <<endl;
    return 0;
}
