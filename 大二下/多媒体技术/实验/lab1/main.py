data = [1, 2, 3, 12, 20, 100, 6, 9, 12, 8, 8, 3]

# 求平均值函数
def average(data):
    return sum(data) / len(data)

# 求最大值函数
def max_value(data):
    return max(data)

# 冒泡排序函数
def bubble_sort(data):
    for i in range(len(data)):
        for j in range(len(data) - 1 - i):
            if data[j] > data[j + 1]:
                data[j], data[j + 1] = data[j + 1], data[j]
    return data

# 输出结果
print("平均值为：", average(data))
print("最大值为：", max_value(data))
sorted_data = bubble_sort(data)
print("排序后的结果为：", sorted_data)
