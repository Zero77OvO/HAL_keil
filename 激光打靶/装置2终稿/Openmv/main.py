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
sensor.set_auto_whitebal(True)
sensor.set_auto_gain(False)
#sensor.skip_frames(10) # 让新的设置生效。

# 红色阈值

white = (50, 100, -10, 40, -10, 40)


red_threshold   = (50, 73, 23, 49, -6, 14) #(46, 69, 19, 74, 0, 35)
red_threshold2   = (60, 100, 0, 50, 0, 30)

# 设置感兴趣区域 这个区域需要把整个白板覆盖，但是露出铅笔线
roiArea = (45,35,218,172)
sensor.set_windowing(roiArea)

# 串口设置
uart = UART(3,115200)
uart.init(115200,bits=8,parity=None,stop=1)

# 结束
Lastroi = [50,50,60,60]
Lastroi2 = [50,50,60,60]
TransCnt = 0
while(True):
    img = sensor.snapshot()         # Take a picture and return the image.
    # ----------------------------------------------------


    img.binary([red_threshold])
    img.dilate(3)
    img.erode(3)

    blobs = img.find_blobs([white])
    #发送串口帧头
    uart.write(bytearray([0x2c,0x12]))
    if blobs:
    #如果找到了目标颜色
        for b in blobs:
            if b[4] > 10 :
                # 串口发送数据b
                uart.write(bytearray([b[5],b[6]]))
                img.draw_cross(b[5], b[6],color = (139,20,0), size=20) # cx, cy
                Lastroi[0] = b[5] - 10
                Lastroi[1] = b[6] - 10
                Lastroi[2] = b[5] + 20
                Lastroi[3] = b[6] + 20
                #在目标颜色区域的中心画十字形标记
                print(b[5], b[6])
                #输出目标物体中心坐标
    uart.write(bytearray([0x5B]))


