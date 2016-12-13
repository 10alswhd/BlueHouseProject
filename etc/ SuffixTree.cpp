#include <string>
#include <unordered_map>
using std::min;
using std::string;
using std::unordered_map;

class ISuffixTree {                                       //the interface
public:
    virtual void build(const string &initial_text) = 0;   //builds the suffix tree
    virtual bool contains(const string &subtext) = 0;     //checks if text contains subtext
    virtual int go_through() = 0;                         //visits all vertices and returns their number
};

class SuffixTree : public ISuffixTree {           //implementation, building with Ukkonen algorithm
    struct node {
        int left, right;                          //information about the edge to this node from its parent
        unordered_map <char, node*> children;     //list of children
        node* suffix_link, *parent;

        node(int left, int right, node* parent) : left(left), right(right),
                                            parent(parent), suffix_link(NULL) {}
    };

    struct tree_position {
        node* vertex;
        int edge_position;

        tree_position(node* vertex, int edge_position) : vertex(vertex),
                                            edge_position(edge_position) {}
    };

    string text;
    node* root;

    void split_edge(node* vertex, int position) {
        node* middle = new node(vertex->left, position, vertex->parent);
        vertex->left = position + 1;
        middle->children[text[position + 1]] = vertex;
        vertex->parent = middle;
        middle->parent->children[text[middle->left]] = middle;
        return;
    }

    int edge_length(node* vertex, int last) {
        return min(last, vertex->right) - vertex->left + 1;
    }

    node* get_suffix_link(node* vertex, int last) {
        if (vertex->suffix_link != NULL) {
            return vertex->suffix_link;
        }
        int left = vertex->left, right = min(vertex->right, last);
        node* initial_vertex = vertex;
        if (vertex->parent->parent == NULL) {
            ++left;
        }
        vertex = get_suffix_link(vertex->parent, last);
        while (left <= right) {
            vertex = vertex->children[text[left]];
            if (right - left + 1 < edge_length(vertex, last)) {
                split_edge(vertex, right - left + vertex->left);
                vertex = vertex->parent;
            }
            left += edge_length(vertex, last);
        }
        return initial_vertex->suffix_link = vertex;
    }

    //if suffix [j, i + 1] that we currently add is already in the tree,
    //move position to its end and return false
    //else add this suffix, move position to suffix [j + 1, i] and return true
    bool go_next(tree_position &position, int last) {
        if (position.edge_position == min(position.vertex->right, last)) {
            if (position.vertex->children[text[last]] == NULL) {
                position.vertex->children[text[last]] =
                                new node(last, text.size() - 1, position.vertex);
                position.vertex = get_suffix_link(position.vertex, last);
                position.edge_position = position.vertex->right;
                return true;
            } else {
                position.vertex = position.vertex->children[text[last]];
                position.edge_position = position.vertex->left;
                return false;
            }
        } else {
            if (text[position.edge_position + 1] == text[last]) {
                position.edge_position++;
                return false;
            } else {
                split_edge(position.vertex, position.edge_position);
                node* middle = position.vertex->parent;
                middle->children[text[last]] = new node(last, text.size() - 1, middle);
                position.vertex = get_suffix_link(middle, last);
                position.edge_position = position.vertex->right;
                return true;
            }
        }
    }
public:
    void build(const string &initial_text) {
        text = initial_text + "\0";
        root = new node(0, -1, NULL);
        root->suffix_link = root;
        tree_position current_position(root, -1);
        int suffix_beginning = -1;
        for (int last = 0; last < text.size(); ++last) {
            while (suffix_beginning < last) {
                if (go_next(current_position, last)) {
                    ++suffix_beginning;
                } else {
                    break;
                }
            }
        }
    }

    bool contains(const string &subtext) {
        tree_position position(root, -1);
        for (int i = 0; i < subtext.size(); ++i) {
            if (position.edge_position == position.vertex->right) {
                if (position.vertex->children[subtext[i]] == NULL) {
                    return false;
                } else {
                    position.vertex = position.vertex->children[subtext[i]];
                    position.edge_position = position.vertex->left;
                }
            } else {
                if (text[position.edge_position + 1] != subtext[i]) {
                    return false;
                } else {
                    position.edge_position++;
                }
            }
        }
        return true;
    }

private:
    int go_through(node* vertex) {
        int count = 1;
        for (auto element: vertex->children) {
            if (element.second != NULL) {
                count += go_through(element.second);
            }
        }
        return count;
    }

public:
    int go_through() {
        return go_through(root);
    }
};
