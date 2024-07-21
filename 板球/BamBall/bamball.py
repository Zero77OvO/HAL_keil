# Blob Detection and uart transport
import sensor, image, time, math, pyb
from pyb import UART
import json
import ustruct
# For color tracking to work really well you should ideally be in a very, very,
# very, controlled enviroment where the lighting is constant...A

# You may need to tweak the above settings for tracking green things...
# Select an area in the Framebuffer to copy the color settings.


sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)       #设置图像大小QVGA大小为320*240，所以中心坐标应该是（160，120）
#sensor.set_hmirror(True)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False)             # must be turned off for color tracking
sensor.set_auto_whitebal(False)         # must be turned off for color tracking


#yellow_threshold=(41, 49, 9, 51, -128, 127)
yellow_threshold=(48, 66, 17, 127, -128, 127)


clock = time.clock()


uart = UART(3, 9600)
uart.init(9600, bits=8, parity=None, stop=1) # OpenMV端初始化与STM端配置一样即可。
#[57,8]   [273,4]
#[61,207]  [275,216]
#
#**************************传输数据的函数************************************
def sending_data(cx,cy):
    global uart;
    #frame=[0x2C,18,cx%0xff,int(cx/0xff),cy%0xff,int(cy/0xff),0x5B];
    #data = bytearray(frame)
    data = ustruct.pack("<bbhhb",               #格式为俩个字符俩个短整型(2字节)
                   0x2C,                        #帧头1
                   0x12,                        #帧头2
                   int(cx-60), # up sample by 4    #数据1
                   int(cy-6), # up sample by 4    #数据2
                   0x5B)
    uart.write(data);   #必须要传入一字节的数组，这个函数似乎不能发送单个字节，必须得一次发送多个字节
#**************************************************************************

#**************************找到最大的色块函数*******************************#
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob.pixels() > max_size:
            max_blob=blob
            max_size = blob.pixels()
    return max_blob
#**************************************************************************#


while(True):
    img = sensor.snapshot().lens_corr(strength = 1.7)
    img = img.rotation_corr(180,180,0,0,0,1)

    blobs = img.find_blobs([yellow_threshold])
    if blobs:
        max_blob=find_max(blobs)
        #print('sum :', len(blobs))
        img.draw_rectangle(max_blob.rect())
        img.draw_cross(max_blob.cx(), max_blob.cy())
        output_str="[%d,%d]" % (max_blob.cx()-60,max_blob.cy()-6)

        print('you send:',output_str)            #打印色块中心点坐标到串行终端便于数据核验
        sending_data(max_blob.cx(),max_blob.cy())#发送色块框的中心点坐标
        #FH = bytearray([0x2C,0x12,blobs[0].cx(),blobs[0].cy(),0x5B])

        #uart.write(FH)
    else:
        print('not found!')
        #sending_data(567,789)#如果没有找到符合条件的色块，那么发送一个不可能出现的坐标
        #FH = bytearray([0x2C,0x12,0x77,0x55,0x5B])

        #uart.write(FH)
