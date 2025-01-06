#include <bits/stdc++.h>
using namespace std;
class TreeNode{
    public:
    TreeNode * left = nullptr;
    TreeNode * right = nullptr;
    int val ;
    TreeNode(TreeNode *left, int val){
        this->left = left;
        this->val = val;
    }
    TreeNode(int val){
        this->val = val;
    }
    TreeNode(TreeNode *left, int val,TreeNode *right){
        this->left = left;
        this->val = val;
        this->right = right;
    }
};
vector<vector<int>>bfs(TreeNode *root){
    vector<vector<int>>ans;
    if(!root){
        return ans;
    }

    queue<TreeNode*>q;
    q.push(root);
    while(!q.empty()){
        int n = q.size();
        vector<int>cur;
        for(int i = 0;i < n;i ++){
            auto x = q.front();
            q.pop();
            cur.push_back(x->val);
            if(x->left){
                q.push(x->left);
            }
            if(x->right){
                q.push(x->right);
            }
        }
        ans.push_back(cur);
    }
    return ans;
}