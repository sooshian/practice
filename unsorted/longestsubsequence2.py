input_data = [-3,5,-2,-3,10,1,2,-20,7]

length = len(input_data)
result_table = [ [0] * length for i in range(length) ]

biggest_sum = 0
biggest_seq = (0, 0)

for i in range(length):
    for j in range(i, length):
        if j == i:
            result_table[i][j] = input_data[j]
        else:
            result_table[i][j] = result_table[i][j-1] + input_data[j]
        if result_table[i][j] > biggest_sum:
            biggest_sum = result_table[i][j]
            biggest_seq = (i,j)

print biggest_sum
start, end = biggest_seq
print input_data[start:end+1]