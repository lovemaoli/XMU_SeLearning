import cv2

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)  # 首参数camera_id为设备摄像头的id，一般为0，如果有多个摄像头，可以设置为1，2，3等，CAP_DSHOW为解决摄像头占用问题

classfier = cv2.CascadeClassifier("haarcascade_frontalface_default.xml") #加载人脸识别分类器，这里使用的是opencv自带的分类器

color = (0, 225, 0) #人脸框的颜色

while cap.isOpened(): # 循环读取每一帧，直到读取失败，即视频播放完毕
    ret, frame = cap.read()  # 读取一帧数据，frame表示摄像头读取的图像矩阵mat类型

    # 人脸检测
    gray = cv2.cvtColor(frame,
                        cv2.COLOR_BGR2GRAY) # 将图像转换为灰度图像，加快检测速度
    faceRects = classfier.detectMultiScale(gray, 1.05, 3) # 人脸检测，返回值为矩形框的左上角坐标和长宽
    if len(faceRects) > 0: # 如果检测到人脸
        for faceRect in faceRects:  # 遍历每一个人脸
            x, y, w, h = faceRect  # 获取矩形框的左上角坐标和长宽
            cv2.rectangle(frame, (x - 10, y - 10), (x + w - 10, y + h - 10), color, 2) # 画出矩形框
    cv2.imshow('frame', frame) # 显示图像
    if cv2.waitKey(1) & 0xFF == ord('q'):  # 按q键退出
        break
cap.release() # 释放摄像头
cv2.destroyAllWindows() # 释放窗口资源