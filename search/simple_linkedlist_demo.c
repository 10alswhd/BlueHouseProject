/* Simple linked-list demo */

typedef struct node{
  void *data;
  struct node *next;
  struct node *prev;
} node;

node* create(node **ns, void *data);
node* search(node **ns, void *data);
void  insert(node **ns, void *data);
void  remove(void *data);
void  destroy(node **ns);
