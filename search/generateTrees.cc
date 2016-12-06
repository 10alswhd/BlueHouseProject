class Solution {
public:
    void _genBST(int start, int end, vector<TreeNode *> &res)
    {
        if(start > end)
        {
            res.push_back(NULL);
            return;
        }
        else
        {
            for(int i = start; i<=end; ++i)
            {
                vector<TreeNode *> lres, rres;
                _genBST(start, i-1, lres);
                _genBST(i+1, end, rres);
                // generate all combinations
                for(int j = 0; j<lres.size(); ++j)
                    for(int k = 0; k<rres.size(); ++k)
                    {
                        TreeNode * root = new TreeNode(i);
                        root->left = lres[j];
                        root->right = rres[k];
                        res.push_back(root);
                    }
            }
        }
    }
    vector<TreeNode *> generateTrees(int n) {
        // Get all. Use recursion
        vector<TreeNode *> res;
        _genBST(1,n,res);
        return res;
    }
};
