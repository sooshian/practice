#input_data = [-3,5,-2,-3,10,1,2,-20,7]
input_data = [4,-4,-3,5,-6]

length = len(input_data)
dp = [0 for _ in range(length)]

biggest_sum = input_data[0]
biggest_seq = (0, 0)

dp[0] = input_data[0]
for i in range(1, length):
    dp[i] = max(dp[i-1] + input_data[i], input_data[i])
    if biggest_sum < dp[i]:
        biggest_sum = dp[i]

print dp
print biggest_sum