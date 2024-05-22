import numpy as np
import cv2
from socket import *
from time import sleep

port = 2500
BUFSIZE = 1024

def clock():
    return cv2.getTickCount() / cv2.getTickFrequency()

def detect(img,cascade):
    rects = cascade.detectMultiScale(img,scaleFactor = 1.1, minNeighbors = 3,minSize=(80,80),flags = cv2.CASCADE_SCALE_IMAGE)
    
    if len(rects) == 0:
        return []
    rects[:,2:] += rects[:,:2]
    return rects

def draw_rects(img,rects,color):
    for x1,y1,x2,y2 in rects:
        cv2.rectangle(img,(x1,y1),(x2,y2),color,2)
        
class SocketInfo():
    HOST=""
    PORT=8885
    BUFSIZE=7
    ADDR=(HOST, PORT)

class socketInfo(SocketInfo):
    HOST= "127.0.0.1"
        
if __name__ == '__main__':
    cascade_fn = "haarcascade_frontalface_alt.xml"
    nested_fn = "haarcascade_eye.xml"
    cascade = cv2.CascadeClassifier(cascade_fn)
    nested = cv2.CascadeClassifier(nested_fn)
    cam = cv2.VideoCapture(0)
    cam.set(cv2.CAP_PROP_FRAME_WIDTH,320)
    cam.set(cv2.CAP_PROP_FRAME_HEIGHT,320)
    
    face = []
    pos = 0
    
    csock= socket(AF_INET, SOCK_STREAM)
    csock.connect(socketInfo.ADDR)
    print("conenct is success")
    while True:
        ret, img = cam.read()
        gray = cv2.cvtColor(img,cv2.COLOR_BGR2GRAY)
        gray = cv2.equalizeHist(gray)
        rects = detect(gray,cascade)
        vis = img.copy()
        draw_rects(vis,rects,(0,255,0))
        for x1,y1,x2,y2 in rects:
            roi = gray[y1:y2,x1:x2]
            vis_roi = vis[y1:y2,x1:x2]
            subrects = detect(roi.copy(),nested)
            draw_rects(vis_roi,subrects,(255,0,0))
            pos = (x1+x2)/2
        if(pos < 120 and pos > 0): i = 1
        elif(pos > 240): i = 2
        else : i = 0
        #conn.send(face.encode())
        to_server= int(i)
        right_method= to_server.to_bytes(4, byteorder='little')
        print("Send Data : {}, bytes len : {}, bytes : {}".format(to_server,len(right_method), right_method))
        sent= csock.send(right_method)
        cv2.imshow('facedetect',vis)
        
        key = cv2.waitKey(10)
        
        if key == ord(' '):
            print(face)
            csok.close()
            break
        
    #conn.close()
    cv2.destroyAllWindows()
    exit()
