"""
    anagram :
        a word, phrase, or name formed by rearranging the letters of another, such as cinema, formed from iceman.
"""
class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        OFFSET = -ord('a')
        s_vector = [ 0 for x in range(26) ]
        for ch in s:
            s_vector[ord(ch)+OFFSET] += 1
        for ch in t:
            s_vector[ord(ch)+OFFSET] -= 1
        for elem in s_vector:
            if elem != 0:
                return False
        return True