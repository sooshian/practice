class Solution:
    def uniquePaths(self, m: int, n: int) -> int:
        result_table = [[ 0 for j in range(n)] for i in range(m)]
        
        for i in range(m):
            for j in range(n):
                if i == 0:
                    result_table[i][j] = 1
                    continue
                
                if j == 0:
                    result_table[i][j] = 1
                    continue
                    
                result_table[i][j] = result_table[i][j-1] + result_table[i-1][j]
        
        return result_table[m-1][n-1]