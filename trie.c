struct TrieNode {
    unsigned char v;
    struct TrieNode* children[26];
};
 
#define CACHE_SIZE 100000
 
static struct TrieNode node_cache[CACHE_SIZE];
static int used_cache_size = 0;
 
struct TrieNode* allocTrieNode(void)
{
    return &node_cache[used_cache_size++];
}
 
/** Initialize your data structure here. */
struct TrieNode* trieCreate(void) {
    return allocTrieNode();
}
 
/** Inserts a word into the trie. */
void insert(struct TrieNode* node, char* word) {
    while(*word){
        if (!node->children[*word - 'a']){
            node->children[*word - 'a'] = allocTrieNode();
        }
        node = node->children[*word - 'a'];
        word++;
    }
    node->v += 1;
}
/*return TrieNode pointer matching prefix string*/
struct TrieNode* _startsNode(struct TrieNode* node,char* prefix){
    while(*prefix){
        if(node = node->children[*prefix - 'a']){
            /*pass*/
        }else{
            return NULL;
        }
        prefix++;
    }
    return node;
}
/** Returns if the word is in the trie. */
bool search(struct TrieNode* node, char* word) {
    struct TrieNode* prefix_node = _startsNode(node,word);
    if(prefix_node && prefix_node->v){
        return 1;
    }else{
        return 0;
    }
}
 
/** Returns if there is any word in the trie
    that starts with the given prefix. */
bool startsWith(struct TrieNode* node, char* prefix) {
    struct TrieNode* prefix_node = _startsNode(node,prefix);
    if(prefix_node){
        return 1;
    }else{
        return 0;
    }
}
 
/** Deallocates memory previously allocated for the TrieNode. */
void trieFree(struct TrieNode* root) {
    return;
}
