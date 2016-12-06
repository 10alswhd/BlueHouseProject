int linkedListContains (struct linkedList *lst, TYPE e) {
   /* Declare a temp variable to use to move through the list. */
   struct dlink * t = lst->frontSentinel;

   /* While the next link isn't the back sentinel... */
   while(t->next != lst->backSentinel){
      t = t->next;
      if(EQ(e,t->value)) 
        return 1;
   }

   return 0;
}

void linkedListRemove (struct linkedList *lst, TYPE e) {

   /* Declare a temp variable to use to move through the list. */
   struct dlink * t = lst->frontSentinel;

   /* While the next link isn't the back sentinel... */
   while(t->next != lst->backSentinel){
      t = t->next;
      if(EQ(e,t->value)){
        _removeLink(lst,t);
        return; /* Only remove one instance of the search value. */
      }      
   }

}
