THRESHOLD = (8, 62, -4, 93, -9, 51)# Grayscale threshold for dark things...
#THRESHOLD=(0, 10, -1, 127, -128, 127)
#???,????????????(96, 100, -13, 5, -11, 18)
import sensor, image, time,ustruct
from pyb import UART

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QQVGA) # 80x60 (4,800 pixels) - O(N^2) max = 2,3040,000.
#sensor.set_windowing([0,20,80,40])
sensor.skip_frames(time = 2000)     # WARNING: If you use QQVGA it may take seconds
clock = time.clock()                # to process a frame sometimes.

uart = UART(3,115200)   #???????3????
uart.init(115200, bits=8, parity=None, stop=1) # init with given parameters

#???????
roi1 =     [
            (0, 20, 30, 90),        #  ??  x y w h
            (130,20,30,90),# ??
            (50,0,60,30),#??
            ]

#***********************************??????**********************************#
def find_max(blobs):
     max_size=0
     for blob in blobs:
         if blob[2]*blob[3] > max_size:
             max_blob=blob
             max_size = blob[2]*blob[3]
             return max_blob
#***************************************************************************#




def send_data(theta,cx,cy,move_flag):

    data = ustruct.pack("<bbhhb",               #?????????????????????(2???)
                   0x2C,                        #??1
                   0x12,
                   int(theta),
                   int(cx),
                   int(cy),
                   int(move_flag), # up sample by 4    #????1
                   0x5B)
    uart.write(data);
while(True):
    img = sensor.snapshot().binary([THRESHOLD])
#    img = sensor.snapshot()
    line = img.get_regression([(100,100)],roi =(30,0,90,160),robust = True)
#    line = img.get_regression([(100,100)], robust = True)

    left_flag,right_flag,up_flag=(0,0,0)
    for rec in roi1:
        img.draw_rectangle(rec, color=(0,0,255))#?????roi????

    if (line):
           rho_err = abs(line.rho())-img.width()/2
           if line.theta()>90:
               theta_err = line.theta()-180
           else:
               theta_err = line.theta()

           img.draw_line(line.line(), color = 127)
           theta=line.theta()
           theta_x=line.x1()

    if img.find_blobs([ (96, 100, -13, 5, -11, 18)],roi=[58,44,36,25]):
            red_blobs = img.find_blobs([(96, 100, -13, 5, -11, 18)],roi=[58,44,36,25],merge=True)
            max_blob = find_max(red_blobs)
            if max_blob:
             x = max_blob.cx()
             y = max_blob.cy()
             img.draw_cross(max_blob.cx(), max_blob.cy(),color = (0,255,0))


            if img.find_blobs([ (96, 100, -13, 5, -11, 18)],roi=roi1[0]):  #left
                left_flag=1
            else:
                left_flag=0

            if img.find_blobs([(96, 100, -13, 5, -11, 18)],roi=roi1[1]):  #right

                right_flag=1
            else:
                right_flag=0

            if img.find_blobs([(96, 100, -13, 5, -11, 18)],roi=roi1[2]):  #up

                up_flag=1

            else:
                up_flag=0
            if left_flag==1 and right_flag==1:
                if  up_flag==1 :
                    print('shizi')
                    OUT_DATA =bytearray([0x2C,0x12,theta,theta_x,max_blob.cy(),1,0x5B])
                    uart.write(OUT_DATA)

                elif up_flag==0:
                    print('Txing')
                    OUT_DATA =bytearray([0x2C,0x12,theta,theta_x,max_blob.cy(),2,0x5B])
                    uart.write(OUT_DATA)
            else:
                OUT_DATA =bytearray([0x2C,0x12,theta,theta_x,max_blob.cy(),0,0x5B])
                uart.write(OUT_DATA)




#    if (line):
#        rho_err = abs(line.rho())-img.width()/2
#        if line.theta()>90:
#            theta_err = line.theta()-180
#        else:
#            theta_err = line.theta()

#        img.draw_line(line.line(), color = 127)

        #print(rho_err,line.magnitude(),rho_err)






