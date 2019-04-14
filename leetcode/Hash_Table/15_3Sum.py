"""
    开始写了一个版本超时了，后来参考了一个解答(https://leetcode.com/problems/3sum/discuss/7384/My-Python-solution-based-on-2-sum-200-ms-beat-93.37)

    这道题也可以用Two Pointers来做
"""

class Solution:
    def threeSum(self, nums: List[int]) -> List[List[int]]:
        result = set()
        nums.sort()

        for i, v in enumerate(nums[:-2]):
            if i > 1 and v == nums[i-1]:
                continue
            d = {}
            for x in nums[i+1:]:
                if x not in d:
                    d[-v-x] = 1
                else:
                    result.add((v, -v-x, x))
        return list(map(list, result))