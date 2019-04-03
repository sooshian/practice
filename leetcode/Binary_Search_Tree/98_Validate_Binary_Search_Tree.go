/**
 * Definition for a binary tree node.
 * type TreeNode struct {
 *     Val int
 *     Left *TreeNode
 *     Right *TreeNode
 * }
 */
//import "math"
/*
golang的int会根据平台来确定是int32还是int64
https://blog.cyeam.com/json/2017/12/18/go-int-size?hmsr=toutiao.io&utm_medium=toutiao.io&utm_source=toutiao.io

判断int是否是int32
const host32bit = ^uint(0)>>32 == 0
获取int的最大值
int(^uint(0) >> 1)

用math里的常量需要知道int是int32还是int64

*/

func isValidBST(root *TreeNode) bool {
    // leetcode运行golang时int是int64
    const MaxInt = int(^uint(0) >> 1)
    const MinInt = ^MaxInt
    return isValidBST_(root, MinInt, MaxInt)
}

func isValidBST_(node *TreeNode, min int, max int) bool {
    if node == nil {
        return true
    }
    if node.Val <= min {
        return false
    }
    if node.Val >= max {
        return false
    }
    return isValidBST_(node.Left, min, node.Val) && isValidBST_(node.Right, node.Val, max)
}