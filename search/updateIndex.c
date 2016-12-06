int UpdateIndex(InvertedIndex *index, char *word, int documentId){
    int hashNum = JenkinsHash(word, MAX_HASH_SLOT);

    // If element doesn't exist in the hashtable
    if(!InInvertedIndex(word, index)){
        // Add to hashtable and create new DocumentNode
        AddToInvertedIndex(word, index);
        DocumentNode *newDoc = (DocumentNode *)malloc(sizeof(DocumentNode));

        newDoc->doc_id = documentId;
        newDoc->freq = 1;
        newDoc->next = NULL;

        // Put DocumentNode in hashtable
        InvertedIndexNode *hNode = index->table[hashNum];
        WordNode *wNode = hNode->data;
        wNode->page = newDoc;
        
        return(1);
    }
    // If element exists
    else {
        // Search through WordNode's list of DocumentNodes to see if current document is a Node
        WordNode *wNode = index->table[hashNum]->data;
        for(DocumentNode *dNode = wNode->page; dNode != NULL; dNode = dNode->next){
            // If a matching document is found, increment frequency
            if(dNode->doc_id == documentId){
                dNode->freq = dNode->freq + 1;
                return(1);
            }
        }

        // If no DocumentNode is found, create new DocumentNode
        DocumentNode *newDoc = (DocumentNode *)malloc(sizeof(DocumentNode));

        newDoc->doc_id = documentId;
        newDoc->freq = 1;
        newDoc->next = wNode->page;

        // Put DocumentNode in hashtable
        wNode->page = newDoc;
        return(1);
    }

    return(0);
}
