//  * Definition for a binary tree node.
    struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode() : val(0), left(nullptr), right(nullptr) {}
        TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
        TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
    };

#include<iostream>
#include<vector>

class Solution {
public:
    void inorder(TreeNode* root, std::vector<TreeNode*>& vec){
        if(root==nullptr) return;
        inorder(root->left, vec);
        vec.push_back(root);
        inorder(root->right, vec);
    }

    TreeNode* build(std::vector<TreeNode*>&vec, int l, int r){
        if(l > r) return nullptr;
        int mid = l + (r-l)/2;
        TreeNode* root = vec[mid];
        root->left = build(vec, l, mid-1);
        root->right = build(vec, mid+1, r);
        return root;
    } 

    TreeNode* balanceBST(TreeNode* root) {
        std::vector<TreeNode*> nodes;
        inorder(root, nodes);
        return build(nodes, 0, nodes.size()-1);
    }
};