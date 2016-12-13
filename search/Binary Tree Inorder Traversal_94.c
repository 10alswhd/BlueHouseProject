vector<int> inorderTraversal(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> VecRes;
    TreeNode *cur = root;
    TreeNode *prev;
    while(NULL != cur){
        if(NULL == cur->left){
            VecRes.push_back(cur->val);
            cur = cur->right;
        }else{
            for(prev = cur->left; prev->right != NULL && prev->right != cur; )
                prev = prev->right;
            if(prev->right == NULL){
                prev->right = cur;
                cur = cur->left;
            }else{
                VecRes.push_back(cur->val);
                cur = cur->right;
                prev->right = NULL;
            }
        }
    }
    return VecRes;
}


vector<int> inorderTraversal(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> VecRes;
    TreeNode *cur = root;
    TreeNode *prev;
    while(NULL != cur){
        if (NULL != cur->left){
            for(prev = cur->left; prev->right != NULL && prev->right != cur; )
                prev = prev->right;
            if(prev->right == NULL){
                prev->right = cur;
                cur = cur->left;
                continue;
            }else{
                prev->right = NULL;
            }
        }
        VecRes.push_back(cur->val);
        cur = cur->right;
    }
    return VecRes;
}

/*上面是常数空间的中序遍历,线索树thread tree,Morris的方法
*前一个可读性较好,后一个更短一点*/

/*下面是用stack的代码*/
vector<int> inorderTraversal(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<int> VecRes;
    stack<TreeNode *> s;
    TreeNode * cur = root;
    while(NULL != cur || !s.empty()){
        if(NULL != cur){
            s.push(cur);
            cur = cur->left;
        }else{
            cur = s.top();
            s.pop();
            VecRes.push_back(cur->val);
            cur = cur->right;
        }
    }
    return VecRes;
}
