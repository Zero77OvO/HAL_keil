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
red_threshold   = (0, 100, 15, 50, 0, 50)#(8, 100, 0, 50, 0, 30)
red_threshold2   = (60, 100, 15, 50, 0, 50)#(5, 69, 1, 46, 0, 30)
white = (50,100,0,40,0,40)
# 设置感兴趣区域 这个区域需要把整个白板覆盖，但是露出铅笔线
roiArea = (80,30,145,145)
sensor.set_windowing(roiArea)
# 串口设置
uart = UART(3,115200)
uart.init(115200,bits=8,parity=None,stop=1)
# 结束
clock = time.clock()                # Create a clock object to track the FPS.
Lastroi = [50,50,60,60]
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
#            sensor.set_auto_gain(False)
            sensor.skip_frames(10) # 让新的设置生效。
        # ----------------------------------------------------
    if TransFlag == 1 :
         #发送串口帧头
        uart.write(bytearray([0x2c,0x12]))

        blobs = img.find_blobs([red_threshold2])
        blobs2 = img.find_blobs([red_threshold],roi = Lastroi)
        if blobs:
        #如果找到了目标颜色
            for b in blobs:
                if b[4] < 80 :
                    # 串口发送数据b
                    uart.write(bytearray([b[5],b[6]]),)
                    img.draw_cross(b[5], b[6]) # cx, cy
                    Lastroi[0] = b[5] - 10
                    Lastroi[1] = b[6] - 10
                    Lastroi[2] = b[5] + 20
                    Lastroi[3] = b[6] + 20
                    #在目标颜色区域的中心画十字形标记
                    #输出目标物体中心坐标
        elif blobs2:
        #如果找到了目标颜色
            for b in blobs2:
                if b[4] < 80 :
                    # 串口发送数据
                    uart.write(bytearray([b[5],b[6]]))
                    img.draw_cross(b[5], b[6],color = (139,0,0)) # cx, cy
                    #在目标颜色区域的中心画十字形标记
       # 发送帧尾
        uart.write(bytearray([0x5B]))

