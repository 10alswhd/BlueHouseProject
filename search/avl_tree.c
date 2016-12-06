#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct bstNode{
    int data;
    struct bstNode* left;
    struct bstNode* right;
}bstNode;

void SecFree( void** memRef );
bstNode* GetNewNode( int data );
bstNode* InsertNode( bstNode* root, int data );
bool SearchBst( bstNode* root, int data );

void SecFree( void** memRef ){
    if ( memRef != NULL && *memRef != NULL ){
        free ( *memRef );
        *memRef = NULL;
    }
}

bstNode* GetNewNode( int data ){
    bstNode* newNode = NULL;
    if ( ( newNode = malloc(sizeof( bstNode ) ) ) == NULL ){
        printf ( "Node create error!\n" );
        exit (-1);
    }
    newNode->data = data;
    newNode->left = NULL, newNode->right = NULL;
    return newNode;
}

bstNode* InsertNode( bstNode* root, int data ){
    if ( root == NULL )
        root = GetNewNode( data );
    else if ( data <= root->data )
        root->left = InsertNode( root->left, data );
    else
        root->right = InsertNode( root->right, data );

    return root;
}

bool SearchBst( bstNode* root, int data ){
    if ( root == NULL )
        return false;
    else if ( root->data == data )
        return true;
    else if ( data <= root->data )
        return SearchBst( root->left, data );
    else
        return SearchBst( root->right, data );
}

int GetNodeHeight( bstNode* root ){
        int left_node_height = 0;
        int right_node_height = 0;
        
        if ( !root )
            return -1;
            
        left_node_height = GetNodeHeight( root->left );
        right_node_height = GetNodeHeight( root->right );

        return 1 + ( left_node_height > right_node_height ? left_node_height : right_node_height );
}

int GetNodeBalance( bstNode* root ){
    int nb = 0;

    if ( root->left )
        nb += GetNodeHeight (root->left);
    if ( root->right )
        nb -= GetNodeHeight( root->right );
    return nb;
}

void LLNode(){
https://gist.github.com/tonious/1377768
}

void RRNode() {

}

void LRNode() {

}

void RLNode() {

}

int main ( void ){
    int value;

    bstNode* root = NULL;
    root = InsertNode (root, 15);
    root = InsertNode (root, 10);
    root = InsertNode (root, 20);
    root = InsertNode (root, 25);
    root = InsertNode (root, 8);
    root = InsertNode (root, 12);
    printf( "root: %p\n", ( void* ) root );

    printf ( "Insert a number to search:\n" );
    scanf ( "%d", &value );

    if ( SearchBst ( root, value ) )
        printf( "Found!\n" );
    else
        printf ( "Not found!\n" );
    SecFree( ( void** ) &root );
    return 0;
}
