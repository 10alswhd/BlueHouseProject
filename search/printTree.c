bool printTree(TreeNode *startingNode)
{
    
    TreeNode *visitingNode = NULL;
    TreeNode *sibling = NULL;
    int visitingLevelCount = 0;
    int childrenLevelCount = 0;
    
    if(startingNode == NULL)
        return NULL;
    
    clearQueue();
    
    if(!addToQueue(startingNode)) return NULL;
    visitingLevelCount++;
    while (!isQueueEmpty()) {
        visitingNode = removeFromQueue();
        visitingLevelCount--;
        if (visitingNode == NULL) {
            printf("Logic Error: NULL entry in queue\n");
            return NULL;
        }
        
        printf(" %s ", visitingNode->nodeId);
        if(visitingNode->child != NULL) {
            addToQueue(visitingNode->child);
            childrenLevelCount++;
        }
        
        sibling = visitingNode->sibling;
        while (sibling != NULL) {
            printf(" %s  ", sibling->nodeId);
            if (sibling->child != NULL)
                addToQueue(sibling->child);
                childrenLevelCount++;
                sibling = sibling->sibling;
            }
        if (visitingLevelCount == 0) {
            printf("\n");
            visitingLevelCount = childrenLevelCount;
            childrenLevelCount = 0;
        }

    }
    
    return true;
}
