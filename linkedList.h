//Programming Fun: linkedList.h
//A C-style Linked List, Singly-Linked
//Rudra Chakraborty
//Tweet questions comments @gortonfishman

#ifndef h_linkedlist
#define h_linkedlist

//Our generic linked list node
typedef struct node
{
  void* data; //what the node actually holds
  node* next; //pointer to the next element
} node;

node* head = NULL; 

//writing a new list to memory
void scribeList(void* element)
{
  head.data = element;
  head->next = NULL;
}

//add an element to the list recursively
void append(void* element, node* n)
{
  if(n == NULL)
    {
      n->data = element;
      n->next = NULL;
    }
  else append(element, n->next);
}

//reverses the list
//It's important to understand that you are only changing the pointers themselves, NOT
//the contents of the node!
node* reverse(node* head)
{
  node* newHead = NULL;
  
  while (head)
  {
    node* next = head->next;
    head-> next = newHead;
    newHead = head;
    head = next;
  }
  
  return newHead;
}

//search for and strike an element from the list
int strike(void* element, node* n)
{
  if(n->next != NULL)
    {
      if (n->next->data == element)
        {
          n->next = n->next->next; //reassign previous node pointer to node following deleted node
          free(n->next);
        }
      else strike(element, n->next);
    }

  return -1; //default/error case
}

//remove all elements of the list
void eraseList(node* n)
{
  //temporarily store the current node, then recursively delete
  node* tmp;
  tmp = n;
  
  free(n);
  if(tmp->next != NULL) eraseList(tmp->next);
  free(tmp);
}

//iterate and print list
void showTell(node* n)
{
  if(n)
    {
      printf("%p\n", n->data);
      showTell(n->next);
    }
}

#endif //h_linkedlist
