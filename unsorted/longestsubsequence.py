input_data = [-3,5,-2,-3,10,1,2,-20,7]

length = len(input_data)
result_map = {}
def getSequenceSum(seq, start, end):
    index = (start, end)
    if index in result_map:
        return result_map[index]
    else:
        s_sum = sum(seq[start:end+1])
        result_map[index] = s_sum
        return s_sum

biggest_sum = 0
biggest_seq = (0, 0)
for i in range(length):
    for j in range(i, length):
        cur_sum = getSequenceSum(input_data, i, j)
        if cur_sum > biggest_sum:
            biggest_sum = cur_sum
            biggest_seq = (i, j)

print biggest_sum
start, end = biggest_seq
print input_data[start:end+1]