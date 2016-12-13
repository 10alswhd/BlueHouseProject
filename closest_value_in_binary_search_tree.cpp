#include <math.h>
#include <vector>
#include <stack>

// Given a binary search tree whose elements are all integer. How to
// get the node which has the closest value comparing with a given
// float number 

struct Node
{
    Node* left;
    Node* right;
    int value;
};

Node* GetClosest_recursive(Node const* root, float value) 
{
    if (root == NULL)
    {
        return NULL;
    }

    Node* result = root;
    float distance = abs(value - result->value);

    if (Node* node = GetClosest_recursive(root->left, value))
    {
        float const thisDistance = abs(value - node->value);
        if (thisDistance < distance)
        {
            distance = thisDistance;
            result = node;
        }
    }

    if (Node* node = GetClosest_recursive(root->right, value))
    {
        float const thisDistance = abs(value - node->value);
        if (thisDistance < distance)
        {
            distance = thisDistance;
            result = node;
        }
    }

    return result;
}


// map the binary search tree to the axis of number
Node* GetClosest(Node const* root, float value)
{
    Node* node = root;
    
    while (node != NULL) 
    {
        float const distance = node->value - value;

        if (distance > 0 && node->left != NULL)
        {
            float const leftDistance = node->left->value - value;

            if (leftDistance > 0) {
                node = node->left;
                continue;
            }
            else {
                return distance > -leftDistance ? node->left : node;
            }
        }

        if (distance < 0 && node->right != NULL)
        {
            float const rightDistance = node->right->value - value;

            if (rightDistance < 0) {
                node = node->right;
                continue;
            }
            else {
                return -distance > rightDistance ? node->right : node;
            }
        }

        break;
    }

    return node;
}

Node* GetClosest_best(Node const* root, float value)
{
    if (root == NULL)
    {
        return NULL;
    }
    
    Node* node = root;
    float distance = abs(node->value - value);
    Node* result = node;
    while (node != NULL)
    {
        float newDistance = abs(node->value - value);
        if (newDistance < distance)
        {
            result = node;
            distance = newDistance;
        }
        
        if (node->value > value)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    
    return result;
}

Node* GetClosest_simple(Node const* root, float value)
{
    if (root == NULL) {
        return NULL;
    }
    
    Node* node = root;
    Node* left = NULL;
    Node* right = NULL;
    
    while (node != NULL) {
        if (node->value > value)
        {
            right = node;
            node = node->left;
        }
        else
        {
            left = node;
            node = node->right;
        }
    }
    
    if (left)
    {
        if(!right) {
            return left
        }
    }
    else if(right) {
        return right;
    }
    else {
        return value - left->value > right->value - value ? right : left;
    }
    
    return NULL;
}


Node* SelectCloseNode(std::stack<Node*>& lefts, std::stack<Node*>& rights, float value)
{
    Node* node = NULL;
    
    // choose the next closest node
    if (lefts.empty()) {
        if (! rights.empty()) {
            node = rights.top();
            rights.pop();
        }
    }
    else if (rights.empty()) {
        node = lefts.top();
        lefts.pop();
    }
    else {
        if (value - lefts.top()->value > rights.top()->value - value) {
            node = rights.top();
            rights.pop();
        }
        else {
            node = lefts.top();
            lefts.pop();
        }
    }
    return node;
}

// How to get the most closest *k* nodes? Is it possible to get it done within O(n) complexity?
std::vector<Node*> GetClosest(Node* const root, float const value, int const k)
{
    std::vector<Node*> results;
    if (root == NULL)
    {
        return results;
    }

    // first we track closest node and keep the tracks
    Node* node = root;
    
    std::stack<Node*> lefts;
    std::stack<Node*> rights;
    
    while (node != NULL)
    {
        if (value < node->value) 
        {
            rights.push(node);
            node = node->left;
        }
        else
        {
            lefts.push(node);
            node = node->right;
        }
    }

    while (results.size() < k) {
        Node* node = SelectCloseNode(lefts, rights, value);
        if (node == NULL) {
            break;
        }
        
        results.push_back(node);

        if (node->value > value) {
            Node* n = node->right;
            while (n) {
                lefts.push(n);
                n = n->left;
            }
        }
        else {
            Node* n = node->left;
            while (n) {
                rights.push(n);
                n = n->right;
            }
        }
    }

    return results;
}
