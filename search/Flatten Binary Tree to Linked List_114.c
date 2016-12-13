/**
 * Definition for binary tree
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

/*常数空间的thread tree解法*/
void flatten(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    TreeNode *cur = root;
    TreeNode *prev;
    while(NULL != cur){
        if(NULL != cur->left){
            for(prev = cur->left; NULL != prev->right; prev = prev->right);
            prev->right = cur->right;
            cur->right = cur->left;
            cur->left = NULL;
        }
        cur = cur->right;
    }
}


/*线索树先序遍历到vector中，然后修改为list*/
void flatten(TreeNode *root) {
    // Start typing your C/C++ solution below
    // DO NOT write int main() function
    vector<TreeNode *> vec;
    TreeNode *curr = root;
    TreeNode *prev;
    while(NULL != curr){
        if(NULL == curr->left){
            vec.push_back(curr);
            curr = curr->right;
        }else{
            for(prev = curr->left; prev->right != NULL && prev->right != curr; )
                prev = prev->right;
            if(NULL == prev->right){
                vec.push_back(curr);
                prev->right = curr;
                curr = curr->left;
            }else{
                prev->right = NULL;
                curr = curr->right;
            }
        }
    }
    vec.push_back(NULL);
    for(int i=vec.size()-2; i>=0; --i){
        vec[i]->left = NULL;
        vec[i]->right = vec[i+1];
    }
}

/*递归解法*/
class Solution {
public:
    TreeNode *Myflatten(TreeNode *root, TreeNode *last){
        if(NULL == root)return last;
        root->right = Myflatten(root->left, Myflatten(root->right, last));
        root->left = NULL;
        return root;
    }
    void flatten(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        Myflatten(root, NULL);
    }
};


/*使用栈的非递归解法*/
class Solution {
public:
    void flatten(TreeNode *root) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        stack<TreeNode *>s;
        TreeNode * curr = root;
        TreeNode * tmp;
        
        if(NULL == root)
            return ;
        if(NULL != root->right)
            s.push(root->right);
        if(NULL != root->left)
            s.push(root->left);
        while(!s.empty()){
            tmp = s.top();
            s.pop();
            curr->left = NULL;
            curr->right = tmp;
            curr = tmp;
            if(NULL != tmp->right)
                s.push(tmp->right);
            if(NULL != tmp->left)
                s.push(tmp->left);
        }
    }
};
