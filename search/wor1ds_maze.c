#include<stdio.h>
#include<stdlib.h>

#define N 4

int search_key(Node *current, char key){
   int index  =  GET_CHAR_INDEX(key);

   if(current->children[index] == NULL) return false;

   return true;
}

enum direction {
        NORTH =1,
        SOUTH,
        LEFT,
        RIGHT
};

void update_params(int row, int col, int *new_row, int *new_col, int dir){
   switch(dir){
      case NORTH:
           *new_row = --row;
           *new_col = col;
      break;
      case SOUTH:
           *new_row = ++row;
           *new_col = col;
      break;
      case LEFT:
           *new_col =  ++col;
           *new_row = row;
      break;
      case RIGHT:
           *new_col =  --col;
           *new_row = row;
      break;
     }
}


void find_words_wrapper(trie *t, char maze[][N]){

  int i,j,len, prefix_found = false;
  for(i=0; i<N; i++){
     for(j=0; j<N; j++){

    /*Consider all length words which can be formed stating with maze[i][j] char */

      for(len =1; len <N*N; len++){
        /* To check if we need to check for further length 
           1. if prefix_found = false, don't check, 
           no words possible for larger length 
           2. if prefix_found = true, continue looking*/

           prefix_found = false;

           /* If finally reached at the leaf of trie starting 
              with maze[i][j] and length = len */

              if(find_words(t->root, maze, len,i,j, &prefix_found)){
                 printf(" Word found at (%d %d)\n", i,j);
              }
              else if(prefix_found == false)
                 break;
       }
     }
   }
}

int valid_position(int row, int col){
        if(row<0 || row>N-1 || col <0 || col>N-1) return false;

        return true;
}

int find_words(Node *t, char maze[][N], int curr_len, 
               int curr_row, int curr_col, int *prefix){
       
       int new_row, new_col;
       int  dir,i;
       char key = maze[curr_row][curr_col];

       Node * current = t->children[GET_CHAR_INDEX(key)];

    /* Before finish the prefix we hit the null, prefix is not present */
       if(current == NULL) return false;

       /* If reach the prefix of len = curr_len but its not a word, 
        we can look forward with len = curr_len +1 */
       if(curr_len == 1 && current->value != LEAF_NODE){
                *prefix = true;
                return false;
       }
     /* If we reach at the leaf node, for this length, 
      we found a word with length = curr_len */
       if(curr_len == 1 && current->value == LEAF_NODE)
                return true;

       /* For every character look in all direction */
       for(dir = NORTH; dir<= RIGHT; dir++){

         /* if the key is present */
         if(search_key(t, key)){
         /* Move to next character based on direction of movement */
            update_params(curr_row, curr_col, &new_row, &new_col, dir);

            /*Validate that we are good in maze */
             if(valid_position(new_row, new_col)){

             /*Find word with len -1 in remaining trie */
              if(find_words(current, maze, curr_len-1, new_row, new_col, prefix)) {
                   return true;
               }
             }
          }
          else{
              return false;
          }
       }
}
void main(){

        trie t;
        initialize(&t);
        int i;

        char *dict []  = {"cat", "dog", "word"};

        char maze[N][N]  = { 'a' , 'c', 'a', 't',
                             'd' , 'w', 'o', 'r',
                             'o',  'g', 'd', 'd',
                             'p', 'p',  'p', 'p'
                           } ;
        for(i =0; i <3; i++){
                insert(&t, dict[i]);
        }

         find_words_wrapper(&t, maze);
}
