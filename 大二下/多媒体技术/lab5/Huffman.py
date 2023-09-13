# @Author: 黄勖22920212204392
import sys
import os
from bitarray import bitarray # 位数组，用于压缩文件时的位操作

sys.setrecursionlimit(1000000)  # 递归深度限制,防止压缩大文件时栈溢出

# 定义哈夫曼树的节点类
class node(object):

    def __init__(self, value=None, left=None, right=None, father=None):
        self.value = value # 权值
        self.left = left # 左子节点
        self.right = right # 右子节点
        self.father = father # 父节点

    def build_father(left, right):
        n = node(value=left.value + right.value, left=left, right=right) # 构建父节点
        left.father = right.father = n # 子节点指向父节点
        return n

    def encode(n):
        if n.father == None:
            return b''
        if n.father.left == n:  # 递归编码，左子节点编码为0，右子节点编码为1
            return node.encode(n.father) + b'0'
        else:
            return node.encode(n.father) + b'1'


class Huffman:
    def __init__(self):
        # 数据初始化
        self.node_dict = {}  # 建立原始数据与编码节点的映射，便于稍后输出数据的编码
        self.count_dict = {} # 建立原始数据与权值的映射，便于稍后构建哈夫曼树
        self.ec_dict = {} # 建立原始数据与编码的映射，便于稍后输出数据的编码
        self.nodes = [] # 结点列表，用于构建哈夫曼树
        self.inverse_dict = {} # 建立编码与原始数据的映射，便于稍后解码

    # 哈夫曼树构建
    def build_tree(self, l):
        if len(l) == 1:
            return l
        sorts = sorted(l, key=lambda x: x.value, reverse=False) # 对所有根节点进行排序
        n = node.build_father(sorts[0], sorts[1]) # 构建父节点
        sorts.pop(0) # 删除已经构建过的节点
        sorts.pop(0)
        sorts.append(n) # 将新构建的节点加入列表
        return self.build_tree(sorts) # 递归构建

    def encode(self, echo):
        for x in self.node_dict.keys():
            self.ec_dict[x] = node.encode(self.node_dict[x]) # 构建编码表
            if echo == True:  # 输出编码表（用于调试）
                print(x) # 输出原始数据
                print(self.ec_dict[x]) # 输出编码

    def encodefile(self, inputfile, flag_bytes=True):
        print("正在读取文件...")
        f = open(inputfile, "rb")
        bytes_width = 1  # 每次读取的字节宽度
        i = 0

        f.seek(0, 2)
        count = f.tell() / bytes_width
        print("文件大小:", count, "字节")
        nodes = []  # 结点列表，用于构建哈夫曼树
        buff = [b''] * int(count)
        f.seek(0)

        # 计算字符频率,并将单个字符构建成单一节点
        while i < count:
            buff[i] = f.read(bytes_width) # 读取一个字节
            if self.count_dict.get(buff[i], -1) == -1: # 如果字典中没有该字符，则添加
                self.count_dict[buff[i]] = 0
            self.count_dict[buff[i]] = self.count_dict[buff[i]] + 1 # 字典中该字符的权值加1
            i = i + 1
        print("读取文件完成")
        print(self.count_dict)  # 输出权值字典

        # 将单个字符构建成单一节点
        for x in self.count_dict.keys():
            self.node_dict[x] = node(self.count_dict[x])
            nodes.append(self.node_dict[x])

        f.close()
        tree = self.build_tree(nodes)  # 哈夫曼树构建
        self.encode(False)  # 构建编码表
        print("编码表构建完成")

        head = sorted(self.count_dict.items(), key=lambda x: x[1], reverse=True)  # 对所有根节点进行排序
        bit_width = 1
        print("head:", head[0][1])  # 动态调整编码表的字节长度，优化文件头大小
        if head[0][1] > 255:
            bit_width = 2
            if head[0][1] > 65535:
                bit_width = 3
                if head[0][1] > 16777215:
                    bit_width = 4
        print("bit_width:", bit_width)
        i = 0
        raw = 0b1
        last = 0
        name = inputfile.split('.')
        if flag_bytes:
            o = open(name[0] + "_encode.huffman", 'wb')
        else:
            o = open(name[0] + "_encode.txt", 'wb')
        name = inputfile.split('/')
        o.write((name[len(name) - 1] + '\n').encode(encoding="utf-8"))  # 写出原文件名
        if flag_bytes:
            o.write(int.to_bytes(len(self.ec_dict), 2, byteorder='big'))  # 写出结点数量
            o.write(int.to_bytes(bit_width, 1, byteorder='big'))  # 写出编码表字节宽度
        else:
            o.write(self.str2bits(str(len(self.ec_dict))).encode(encoding="utf-8"))  # 写出结点数量
            o.write(self.str2bits(str(bit_width)).encode(encoding="utf-8"))  # 写出编码表字节宽度
        for x in self.ec_dict.keys():  # 编码文件头
            if flag_bytes:
                o.write(x)
                o.write(int.to_bytes(self.count_dict[x], bit_width, byteorder='big'))
            else:
                o.write(self.str2bits(str(x)).encode(encoding="utf-8"))
                o.write(self.str2bits(str(self.count_dict[x])).encode(encoding="utf-8"))

        print('开始压缩数据...')
        while i < count:  # 开始压缩数据
            for x in self.ec_dict[buff[i]]: # 读取编码表
                raw = raw << 1
                if x == 49:
                    raw = raw | 1 # 将编码表中的字符转换为二进制
                if raw.bit_length() == 9: # 如果已经读取了一个字节
                    raw = raw & (~(1 << 8)) # 去掉最高位的1
                    if flag_bytes:
                        o.write(int.to_bytes(raw, 1, byteorder='big')) # 写入文件
                    else:
                        o.write(self.str2bits(str(raw)).encode(encoding="utf-8")) 
                    o.flush()
                    raw = 0b1
                    tem = int(i / len(buff) * 100)
                    if tem > last:
                        print("压缩:", tem, '%')  # 输出压缩进度
                        last = tem
            i = i + 1

        if raw.bit_length() > 1:  # 处理文件尾部不足一个字节的数据
            raw = raw << (8 - (raw.bit_length() - 1))
            raw = raw & (~(1 << raw.bit_length() - 1))
            if flag_bytes:
                o.write(int.to_bytes(raw, 1, byteorder='big'))
            else:
                o.write(self.str2bits(str(raw)).encode(encoding="utf-8"))

        o.close()
        print("压缩完成")

    def decodefile(self, inputfile):
        print("开始解压...")
        count = 0
        raw = 0
        last = 0
        f = open(inputfile, 'rb')

        # 获取文件大小
        f.seek(0, 2)
        eof = f.tell()

        # 获取文件名
        f.seek(0)
        name = inputfile.split('/')
        outputfile = inputfile.replace(name[len(name) - 1], f.readline().decode(encoding="utf-8"))
        outputfile = outputfile.replace('\n', '')
        temp = os.path.splitext(outputfile)
        outputfile = os.path.splitext(outputfile)[0] + "_decode" + os.path.splitext(outputfile)[1]

        # 读取文件头
        o = open(outputfile, 'wb')
        count = int.from_bytes(f.read(2), byteorder='big')  # 取出结点数量
        bit_width = int.from_bytes(f.read(1), byteorder='big')  # 取出编码表字宽
        i = 0
        de_dict = {}
        while i < count:  # 解析文件头
            key = f.read(1)
            value = int.from_bytes(f.read(bit_width), byteorder='big')
            de_dict[key] = value
            i = i + 1
        for x in de_dict.keys():
            self.node_dict[x] = node(de_dict[x])
            self.nodes.append(self.node_dict[x])
        tree = self.build_tree(self.nodes)  # 重建哈夫曼树
        self.encode(False)  # 建立编码表
        for x in self.ec_dict.keys():  # 反向字典构建
            self.inverse_dict[self.ec_dict[x]] = x
        i = f.tell()
        data = b''
        while i < eof:  # 开始解压数据
            raw = int.from_bytes(f.read(1), byteorder='big')
            i = i + 1
            j = 8
            while j > 0:
                if (raw >> (j - 1)) & 1 == 1:
                    data = data + b'1'
                    raw = raw & (~(1 << (j - 1)))
                else:
                    data = data + b'0'
                    raw = raw & (~(1 << (j - 1)))
                if self.inverse_dict.get(data, 0) != 0:
                    o.write(self.inverse_dict[data])
                    o.flush()
                    data = b''
                j = j - 1
            tem = int(i / eof * 100)
            if tem > last:
                print("解压:", tem, '%')  # 输出解压进度
                last = tem
            raw = 0

        f.close()
        o.close()
        print("文件解压成功！")

    def str2bits(self, s):
        ret = ''.join([bin(int('1' + hex(c)[2:], 16))[3:] for c in s.encode("utf-8")])
        return ret

    def bits2str(self, bits):
        b = bitarray(bits)
        return b.tobytes().decode("utf-8")


if __name__ == '__main__':
    my_huffman = Huffman()
    if input("哈夫曼编解码程序\n1: 压缩文件\n2: 解压文件\n请输入操作对应数字:") == '1':
        file = input("请输入要压缩的文件：")
        my_huffman.encodefile(file)
        my_huffman.encodefile(file,False)
    else:
        my_huffman.decodefile(input("请输入要解压的文件："))
