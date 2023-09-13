import time

def lz77_encode():
    fileName = input("请输入text file中要编码的文件: ")
    filePath = "text file/" + fileName + ".txt"
    file = open(filePath, "r") # 打开文本文件
    text = file.read()
    n = len(text) # 计算文本长度
    text = " " + text
    file.close()

    wnd_size = int(input("请输入最大匹配长度(<=60): "))

    # 编码
    start_time = time.time()
    file = open("encode.lz77", "wb")
    i = 1
    while i <= n:
        # 计算范围
        if i <= wnd_size:
            l, r = 1, i-1
        else:
            l, r = i-wnd_size,i-1

        # 寻找最长匹配
        max_len = 0
        off = 0
        for j in range(l, r+1):
            current_len = 0
            k = j
            while k <= r and i + k - j <= n:
                if text[k] == text[i + k - j]:
                    current_len += 1
                    k += 1
                else:
                    break
            if current_len > max_len:
                max_len = current_len
                off = j - l

        # 输出三元组到二进制文件中
        i += max_len
        char = text[i]
        if max_len == 0:
            file.write(int(0).to_bytes(1, "big"))
            file.write(int(0).to_bytes(1, "big"))
            file.write(ord(char).to_bytes(1, "big"))
            print(0, 0, char)
        else:
            file.write(off.to_bytes(1, "big"))
            file.write(max_len.to_bytes(1, "big"))
            file.write(ord(char).to_bytes(1, "big"))
            print(off, max_len, char)

        i += 1

    # 计算程序运行时间
    end_time = time.time()
    cost_time = end_time - start_time
    print(f"程序运行时间: {cost_time:.6f}s")

def lz77_decode():
    file = open("encode.lz77", "rb")
    bytes = file.read()
    n = len(bytes)
    file.close()

    # 解码
    text = [0]
    index = 1
    wnd_size = int(input("请输入最大匹配长度(<=255): "))
    start_time = time.time()
    for i in range(n // 3):
        off, length, char = bytes[i * 3], bytes[i * 3 + 1], chr(bytes[i * 3 + 2])
        print(off, length, char)
        # 计算范围
        if index <= wnd_size:
            l, r = 1, index - 1
        else:
            l, r = index - wnd_size, index - 1

        # 还原原始数据
        text.extend(text[l + off : l + off + length])
        text.append(char)
        index += length + 1

    text = text[1:]
    print(text)

    # 输出到文本文件中
    file = open("decode.txt", "w")
    for i in text:
        file.write(i)
    file.close()

    # 计算程序运行时间
    end_time = time.time()
    cost_time = end_time - start_time
    print(f"程序运行时间: {cost_time:.6f}s")

while(True):
    print("1. LZ77 编码")
    print("2. LZ77 解码")
    choice = int(input("请输入选项: "))
    if choice == 1:
        lz77_encode()
    elif choice == 2:
        lz77_decode()
    else:
        print("输入错误!")
