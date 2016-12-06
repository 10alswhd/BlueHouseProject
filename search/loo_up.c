
double look_up_stock_price(char search_name[MAX_STOCK_NAME_LENGTH],struct Node_stock* head){

  double result_price;
     
  while( head != NULL){

    if(strcmp(search_name,head->data.stock_name)){
      result_price =  head->data.stock_price;
      return result_price;
    }
    head = head->next;
  }
 
  return -1e3;
}
