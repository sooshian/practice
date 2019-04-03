/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
#include <limits.h>

bool isValidBST_(struct TreeNode* node, long min, long max);

bool isValidBST(struct TreeNode* root) {
    // []
    // [INT_MAX]
    // [INT_MIN,null,INT_MAX]
    // [INT_MAX,INT_MAX]
    // 有这些case，直接用int不够，所以转换到long
    
    return isValidBST_(root, LONG_MIN, LONG_MAX);
}

bool isValidBST_(struct TreeNode* node, long min, long max) {
    long val;
    if(node == NULL) return true;
    
    val = (long) node->val;
    if(val >= max) return false;
    
    if(val <= min) return false;
 
    return isValidBST_(node->left, min, val) && isValidBST_(node->right, val, max);
}