from socket import *
import numpy as np

class SocketInfo():
    HOST=""
    PORT=8886
    BUFSIZE=7
    ADDR=(HOST, PORT)

class socketInfo(SocketInfo):
    HOST= "127.0.0.1"

csock= socket(AF_INET, SOCK_STREAM)
csock.connect(socketInfo.ADDR)
print("conenct is success")
pos = [1,2,3,4,5,6,7]
for i in pos:
    to_server= int(i)
    right_method= to_server.to_bytes(4, byteorder='little')
    print("Send Data : {}, bytes len : {}, bytes : {}".format(to_server,len(right_method), right_method))
    sent= csock.send(right_method)

csock.close()
exit()

