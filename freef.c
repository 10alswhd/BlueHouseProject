/* free block with user-pointer p (block actually starts at p - TAGSIZE)     */
void freef(char *p)
{
        /* you write the  code for the freef function here */

        printf("freef called with p=%p\n", (void *) p);

        if(p < allocbuf || p > allocbuf + ALLOCSIZE) {
                printf("freef: BAD POINTER!, %p\n", (void*)p);
                return;
        }

        p = p-TAGSIZE;  //alloc() returns location past TAGSIZE
        struct blockl *lb = (struct blockl *)p; //pointer to struct blockl
        struct blockr *rb = (struct blockr *)(p +lb->size - TAGSIZE);   //point to right block
        if(lb->tag != USEDTAG || rb->tag != USEDTAG) {
                printf("freef: BLOCK BEING FREED NOT USED, %p\n",p);
                return;
        }

        lb->tag = (rb->tag = FREETAG); //update tags for left and right block
        rb->size = lb->size;            //update sizes (not necessary)

        //Now use rb pointer to search for place to coalesce
        //point to right block of previous block
        rb = (struct blockr*)(p - TAGSIZE);
        struct blockl *temp;                            //temp. left block pointer 
        if((char*)rb >= allocbuf && rb->tag == FREETAG) {
                temp = (struct blockl*)(p - rb->size);  //point to left header of block to the left
                p -= rb->size;
                coalesce(temp,lb);
                lb=temp;
        }
        else    //if no free block to the left, then add lb (where p is pointing to) to free list.
                enchain(lb);

        //check if block to the right is free, to coalesce      
        //p points to block that was to the left of the original used block. 
        //OR p points to same used block now freed. 
        temp = (struct blockl *)(p + lb->size);
        if((char*)temp < allocbuf + ALLOCSIZE && temp->tag == FREETAG) {
                unchain(temp);
                coalesce(lb,temp);
        }
}
