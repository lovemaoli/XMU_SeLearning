import random

def get_probability(char_li):
    p_space = {}
    chars = set(char_li)
    len_char_li = len(char_li)
    for char in chars:
        times = char_li.count(char) # 统计字符出现次数
        p_space.update({char: times/len_char_li}) # 计算概率
    return p_space

def arithmetic_encode(p_space, origin_code): # origin_code 为待编码的字符串
    code = 0
    arit = 1
    keys = list(p_space.keys()) # 字符集
    for char in origin_code: # 对每个字符进行编码
        index = keys.index(char) # 字符在字符集中的位置
        pd = 0
        for i in range(index): # 计算累加概率
            pd = pd + p_space[keys[i]]
        code = code + pd * arit # 累加概率乘以区间长度
        arit = p_space[char] * arit # 区间长度缩小
        # print(char, code, arit)
    interval = [code, code + arit] # 返回编码区间
    return interval


def arithmetic_decode(p_space, interval, l): # l 为待译码的字符长度
    decoding_code = [] # 译码结果
    arit_range = {} # 每个字符对应的区间
    c = 0
    for char in p_space.keys():
        a = p_space[char]
        arit_range.update({char: (c, c+a)}) # 计算每个字符对应的区间
        c += a
    code = random.uniform(interval[0], interval[1])
    ori_range = arit_range.copy()
    while len(decoding_code) < l:
        for char, rang in ori_range.items():
            if rang[0] < code < rang[1]:
                decoding_code.append(char)
                c = rang[0]
                for ch, ran in arit_range.items():
                    a = ran[1] - ran[0]
                    ori_range.update({ch: (c, c + a * (rang[1] - rang[0]))})
                    c = c + a * (rang[1] - rang[0])
                break
    return decoding_code

# origin_txt 的内容必须出自统计字符样本文件test.txt
origin_txt = "gotointer"
with open("test.txt", "r", encoding="gbk") as text:
    ori = text.readline() # 读取样本文件
    p_space = get_probability(ori) # 计算概率空间
    print("样本文件中字符集为： ", p_space)
    interval = arithmetic_encode(p_space, origin_txt) # 对 origin_txt 进行编码
decoding = arithmetic_decode(p_space, interval, len(origin_txt))
print(origin_txt + " 对文章符号编码结果为： ", interval)
print("对文章符号译码结果为： ", decoding)

