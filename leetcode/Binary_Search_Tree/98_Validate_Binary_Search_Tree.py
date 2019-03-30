# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, x):
#         self.val = x
#         self.left = None
#         self.right = None

class Solution:
    def isValidBST(self, root: TreeNode) -> bool:
        '''
            边界条件比较多，空输入返回真，只有一个子树的节点判断。
        '''
        if root == None:
            return True
        if root.left == None and root.right == None:
            return True
        isBST, leftSmall, leftBig = self.getNodeValue(root.left)
        if isBST == False:
            return False
        isBST, rightSmall, rightBig = self.getNodeValue(root.right)
        if isBST == False:
            return False
        if leftBig == None:
            if root.val < rightSmall:
                return True
            else:
                return False
        elif rightSmall == None:
            if root.val > leftBig:
                return True
            else:
                return False
        elif leftBig < root.val and rightSmall > root.val:
            return True
        else:
            return False
        
    def getNodeValue(self, node: TreeNode) -> (bool, int, int):
        if node == None:
            return True, None, None

        if node.left == None and node.right == None:
            return True, node.val, node.val

        isBST, leftSmall, leftBig = self.getNodeValue(node.left)
        if isBST == False:
            return False, None, None

        isBST, rightSmall, rightBig = self.getNodeValue(node.right)
        if isBST == False:
            return False, None, None

        if leftBig == None:
            if node.val < rightSmall:
                return True, node.val, rightBig
            else:
                return False, None, None
        elif rightSmall == None:
            if node.val > leftBig:
                return True, leftSmall, node.val
            else:
                return False, None, None
        elif leftBig < node.val and rightSmall > node.val:
            return True, leftSmall, rightBig
        else:
            return False, None, None