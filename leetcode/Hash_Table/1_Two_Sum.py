"""
    One Pass Hash Table
"""
class Solution:
    def twoSum(self, nums: 'List[int]', target: 'int') -> 'List[int]':
        t = target
        d = {}
        for i, x in enumerate(nums):
            if x not in d:
                d[t-x] = i
            else:
                return [d[x], i]