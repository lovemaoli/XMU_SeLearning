# @Author : maoli

import numpy as np

# 位图文件头
class tagBITMAPFILEHEADER:
    def __init__(self):
        self.bfType = int.to_bytes(0, 2, 'little') # 位图文件的类型，必须为BMP (2个字节)
        self.bfSize = int.to_bytes(0, 4, 'little') # 位图文件的大小，以字节为单位 (4个字节)
        self.bfReserved1 = int.to_bytes(0, 2, 'little') # 位图文件保留字，必须为0 (2个字节)
        self.bfReserved2 = int.to_bytes(0, 2, 'little') # 位图文件保留字，必须为0 (2个字节)
        self.bfOffBits = int.to_bytes(0, 4, 'little') # 位图数据的起始位置，以相对于位图 (4个字节)

# 位图信息头
class tagBITMAPINFOHEADER:
    def __init__(self):
        self.biSize = int.to_bytes(0, 4, 'little') # 本结构所占用字节数  (4个字节)
        self.biWidth = int.to_bytes(0, 4, 'little') # 位图的宽度，以像素为单位(4个字节)
        self.biHeight = int.to_bytes(0, 4, 'little') # 位图的高度，以像素为单位(4个字节)
        self.biPlanes = int.to_bytes(0, 2, 'little') # 目标设备的级别，必须为1(2个字节)
        self.biBitCount = int.to_bytes(0, 2, 'little') # 每个像素所需的位数(2个字节)
        self.biCompression = int.to_bytes(0, 4, 'little') # 位图压缩类型(4个字节)
        self.biSizeImag = int.to_bytes(0, 4, 'little') # 位图的大小，以字节为单位(4个字节)
        self.biXPelsPerMeter = int.to_bytes(0, 4, 'little') # 位图水平分辨率，每米像素数(4个字节)，一般为0
        self.biYPelsPerMeter = int.to_bytes(0, 4, 'little') # 位图垂直分辨率，每米像素数(4个字节)，一般为0
        self.biClrUsed = int.to_bytes(0, 4, 'little') # 位图实际使用的颜色表中的颜色数(4个字节)，一般为0
        self.biClrImportant = int.to_bytes(0, 4, 'little') # 位图显示过程中重要的颜色数(4个字节)，一般为0

# 位图类
class Bmp(tagBITMAPFILEHEADER, tagBITMAPINFOHEADER):
    def __init__(self, file_name):
        tagBITMAPFILEHEADER.__init__(self)
        tagBITMAPINFOHEADER.__init__(self)
        self.originalPixels = [] # 原始像素阵列
        self.newImageWidth = 0 # 新图片宽度
        self.originalWidth = 0 # 原始图片宽度
        self.Parse(file_name) # 解析图片

    @property
    def width(self): # 获取图片宽度
        return int.from_bytes(self.biWidth, 'little')

    @property
    def height(self): # 获取图片高度
        return int.from_bytes(self.biHeight, 'little')

    @property
    def bit_count(self): # 获取图片位数
        return int.from_bytes(self.biBitCount, 'little')

    # 解析图片
    def Parse(self, file_name):
        file = open(file_name, 'rb')

        # 读取文件头
        self.bfType = file.read(2)
        self.bfSize = file.read(4)
        self.bfReserved1 = file.read(2)
        self.bfReserved2 = file.read(2)
        self.bfOffBits = file.read(4)

        # 读取信息头
        self.biSize = file.read(4)
        self.biWidth = file.read(4)
        self.biHeight = file.read(4)
        self.biPlanes = file.read(2)
        self.biBitCount = file.read(2)
        self.biCompression = file.read(4)
        self.biSizeImage = file.read(4)
        self.biXPelsPerMeter = file.read(4)
        self.biYPelsPerMeter = file.read(4)
        self.biClrUsed = file.read(4)
        self.biClrImportant = file.read(4)
        self.GetPixel(file_name)

    # 获取像素阵列
    def GetPixel(self,file_name):
        file=open(file_name,'rb')
        file.seek(1078) # 54 + 1024(调色板)

        self.newImageScanWidth = int((((self.width * 24) + 31) & ~31) / 8) # 新图片每行字节数
        self.originalWidth = int((((self.width * 8) + 31) & ~31) / 8) # 原始图片每行字节数
        self.originalPixels = np.zeros((self.height, self.width), dtype=int) # 原始像素阵列
        for i in range(self.height):
            for j in range(self.width):
                self.originalPixels[i][j] = int.from_bytes(file.read(1), 'little')

            # 原始图片每行字节数不是4的倍数时，需要补齐
            for k in range(self.width , self.originalWidth, 1):
                file.read(1)

        file.seek(54)
        self.RGBQuad = np.zeros((256, 4), dtype=bytes) # 调色板
        for i in range(256):
            self.RGBQuad[i][0] = file.read(1)
            self.RGBQuad[i][1] = file.read(1)
            self.RGBQuad[i][2] = file.read(1)
            self.RGBQuad[i][3] = file.read(1)

        file.close()

    # 8位伪彩色转24位真彩色
    def Convert(self):
        bsI = int(self.newImageScanWidth * int.from_bytes(self.biHeight, 'little'))
        self.biSizeImage = int.to_bytes(bsI, 4, 'little') # 位图大小
        self.bfSize = int.to_bytes(bsI + 54, 4, 'little') # 文件大小
        self.bfOffBits = int.to_bytes(54, 4, 'little') # 数据偏移量
        self.biBitCount = int.to_bytes(24, 2, 'little') # 位数

        self.newPixels = np.zeros((self.height, self.newImageScanWidth), dtype=bytes) # 新像素阵列
        for i in range(self.height): # 逐行处理
            for j in range(self.width): # 逐列处理
                b = self.RGBQuad[self.originalPixels[i][j]][0]
                g = self.RGBQuad[self.originalPixels[i][j]][1]
                r = self.RGBQuad[self.originalPixels[i][j]][2]
                self.newPixels[i][j * 3] = b
                self.newPixels[i][j * 3 + 1] = g
                self.newPixels[i][j * 3 + 2] = r

            for k in range(self.width * 3, self.newImageScanWidth, 3): # 补齐每行字节数
                self.newPixels[i][k] = 0
                if k + 1 < self.newImageScanWidth:
                    self.newPixels[i][k + 1] = 0
                if k + 2 < self.newImageScanWidth:
                    self.newPixels[i][k + 2] = 0


    # 生成图片
    def generate(self, file_name):
        file = open(file_name, 'wb+')
        # 文件头
        file.write(self.bfType)
        file.write(self.bfSize)
        file.write(self.bfReserved1)
        file.write(self.bfReserved2)
        file.write(self.bfOffBits)
        # 信息头
        file.write(self.biSize)
        file.write(self.biWidth)
        file.write(self.biHeight)
        file.write(self.biPlanes)
        file.write(self.biBitCount)
        file.write(self.biCompression)
        file.write(self.biSizeImage)
        file.write(self.biXPelsPerMeter)
        file.write(self.biYPelsPerMeter)
        file.write(self.biClrUsed)
        file.write(self.biClrImportant)
        file.write(self.newPixels)
        file.close()


# 任务2:8位伪彩色转24位真彩色
robert = Bmp(r'Task2_8to24\robert.bmp')
robert.Convert()
robert.generate(r'Task2_8to24\robert_converted.bmp')

swift = Bmp(r'Task2_8to24\swift.bmp')
swift.Convert()
swift.generate(r'Task2_8to24\swift_converted.bmp')

trump = Bmp(r'Task2_8to24\trump.bmp')
trump.Convert()
trump.generate(r'Task2_8to24\trump_converted.bmp')