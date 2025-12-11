class Solution:
    def search(self, nums: List[int], target: int) -> int:
        left = 0
        right = len(nums) - 1
        
        while left <= right:
            middleInput = (left + right) // 2
            if nums[middleInput] == target:
                return middleInput
            elif nums[middleInput] < target:
                left = middleInput + 1
            else:
                right = middleInput - 1
        
        return -1
