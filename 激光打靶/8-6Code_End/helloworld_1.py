# Hello World Example
#
# Welcome to the OpenMV IDE! Click on the green run arrow button below to run the script!

import sensor, image, time
# 引入串口
from pyb import UART

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.

# 红色阈值
red_threshold   = (   80,   100,  -10,   40,   -10,   10)
red_threshold2   = (   0,   60,  20,   50,   0,   30)
# 设置感兴趣区域 这个区域需要把整个白板覆盖，但是露出铅笔线
roiArea = (80,15,130,130)
sensor.set_windowing(roiArea)
# 串口设置
uart = UART(3,115200)
uart.init(115200,bits=8,parity=None,stop=1)
# 结束
clock = time.clock()                # Create a clock object to track the FPS.

TransFlag = 0
TransCnt = 0
while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    # debug时候使用
    #img.draw_rectangle(roiArea,color=(139,0,0))
    if TransFlag == 0 : # 循环发送50此后不执行
        # 大津法二值化 无惧光照
        histogram = img.get_histogram()
        Thresholds = histogram.get_threshold()
        l = Thresholds.l_value()
        a = Thresholds.a_value()
        b = Thresholds.b_value()
    #    print(Thresholds) # 打印阈值
        v = Thresholds.value()
        # debug时关闭
        img.binary([(0,v)])
        # 二值化完成
        # ---------------------------------------------------
        # 发送串口帧头
        uart.write(bytearray([0x2c,0x12]))
        for r in img.find_rects() :
            # 绘制矩形大方框
            img.draw_rectangle(r.rect(),color = (0,139,0))
            # 打印四个点坐标
            print(r.corners())
            TransCnt = TransCnt + 1
            for p in r.corners() :
                # 串口发送数据
                uart.write(bytearray([p[0],p[1]]))
                # 绘制矩形四个点
                img.draw_circle(p[0],p[1],3,color = (0,240,239))
        # 发送帧尾
        uart.write(bytearray([0x5B]))
        # 串口发送结束
        # 计数 发送50次后停止发送
        if TransCnt == 50 :
            TransFlag = 1
            sensor.set_auto_whitebal(False)
            sensor.skip_frames(10) # 让新的设置生效。
        # ----------------------------------------------------
    if TransFlag == 1 :
        blobs = img.find_blobs([red_threshold])
            #find_blobs(thresholds, invert=False, roi=Auto),thresholds为颜色阈值，
            #是一个元组，需要用括号［ ］括起来。invert=1,反转颜色阈值，invert=False默认
            #不反转。roi设置颜色识别的视野区域，roi是一个元组， roi = (x, y, w, h)，代表
            #从左上顶点(x,y)开始的宽为w高为h的矩形区域，roi不设置的话默认为整个图像视野。
            #这个函数返回一个列表，[0]代表识别到的目标颜色区域左上顶点的x坐标，［1］代表
            #左上顶点y坐标，［2］代表目标区域的宽，［3］代表目标区域的高，［4］代表目标
            #区域像素点的个数，［5］代表目标区域的中心点x坐标，［6］代表目标区域中心点y坐标，
            #［7］代表目标颜色区域的旋转角度（是弧度值，浮点型，列表其他元素是整型），
            #［8］代表与此目标区域交叉的目标个数，［9］代表颜色的编号（它可以用来分辨这个
            #区域是用哪个颜色阈值threshold识别出来的）。
        print(blobs)
        if blobs:
        #如果找到了目标颜色
            for b in blobs:
                if b[4] < 60 :
                    #迭代找到的目标颜色区域
                    # Draw a rect around the blob.
                    img.draw_rectangle(b[0:4]) # rect
                    #用矩形标记出目标颜色区域
                    img.draw_cross(b[5], b[6]) # cx, cy
                    #在目标颜色区域的中心画十字形标记
                    print(b[5], b[6])
                    #输出目标物体中心坐标
        blobs2 = img.find_blobs([red_threshold2])
        if blobs2:
        #如果找到了目标颜色
            for b in blobs2:
                if b[4] < 60 :
                    #迭代找到的目标颜色区域
                    # Draw a rect around the blob.
                    img.draw_rectangle(b[0:4]) # rect
                    #用矩形标记出目标颜色区域
                    img.draw_cross(b[5], b[6],color = (139,0,0)) # cx, cy
                    #在目标颜色区域的中心画十字形标记
#    print(clock.fps())              # Note: OpenMV Cam runs about half as fast when connected
                                    # to the IDE. The FPS should increase once disconnected.
