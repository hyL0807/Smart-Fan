import cv2

cam = cv2.VideoCapture(0)
cam.set(cv2.CAP_PROP_FRAME_WIDTH,320)
cam.set(cv2.CAP_PROP_FRAME_HEIGHT,240)

while True:
	ret,img = cam.read()
	cv2.imshow('Video Capture',img)
	key = cv2.waitKey(5)
	if key == 27:
		break
	if key == ord(' '):
		cv2.imwrite('capture.jpg',img)