class Solution:
    def _threeSum(self, nums: List[int], target: int) -> List:
        result = set()

        t = target
        for i, v in enumerate(nums[:-2]):
            if i > 1 and v == nums[i-1]:
                continue
            d = {}
            for x in nums[i+1:]:
                if x not in d:
                    d[t-v-x] = 1
                else:
                    result.add((v, t-v-x, x))
        return list(result)

    def fourSum(self, nums: List[int], target: int) -> List[List[int]]:
        nums.sort()
        result = set()
        
        for i, v in enumerate(nums[:-3]):
            for res in self._threeSum(nums[i+1:], target - v):
                result.add((v, ) + res)
        return list(map(list, result))