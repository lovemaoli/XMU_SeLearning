import cv2
import dlib # 人脸关键点检测
import numpy as np

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW) # 首参数camera_id为设备摄像头的id，一般为0，如果有多个摄像头，可以设置为1，2，3等，CAP_DSHOW为解决摄像头占用问题

classfier = cv2.CascadeClassifier("haarcascade_frontalface_default.xml") # 加载人脸识别分类器，这里使用的是opencv自带的分类器

color = (0, 225, 0)  # 取255，为绿色框
detector = dlib.get_frontal_face_detector() # 人脸检测器
predictor = dlib.shape_predictor("shape_predictor_68_face_landmarks.dat") # 人脸关键点检测器
while cap.isOpened():
    ret, frame = cap.read()  # 读取一帧数据，frame表示摄像头读取的图像矩阵mat类型

    gray = cv2.cvtColor(frame,
                        cv2.COLOR_BGR2GRAY) # 将图像转换为灰度图像，加快检测速度
    rects = detector(gray, 0) # 人脸检测，返回值为矩形框的左上角坐标和长宽
    for i in range(len(rects)): # 遍历每一个人脸
        landmarks = np.matrix([[p.x, p.y] for p in predictor(frame, rects[i]).parts()]) # 人脸关键点检测
        for idx, point in enumerate(landmarks): # 遍历每一个关键点
            pos = (point[0, 0], point[0, 1]) # 获取关键点坐标
            cv2.circle(frame, pos, 2, color=(0, 255, 0)) # 画出关键点
            font = cv2.FONT_HERSHEY_SIMPLEX # 设置字体
    cv2.imshow('frame', frame) # 显示图像
    if cv2.waitKey(1) & 0xFF == ord('q'):  # 按q键退出
        break

cap.release() # 释放摄像头
cv2.destroyAllWindows() # 释放窗口资源
