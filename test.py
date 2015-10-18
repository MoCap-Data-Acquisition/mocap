import numpy as np
import cv2

#Load video file
cap = cv2.VideoCapture('../videos/test4.mp4')
#cap = cv2.VideoCapture('../videos/test2.MOV')


CURRENT_FRAME_FLAG = cv2.CAP_PROP_POS_FRAMES
TOTAL_FRAMES_FLAG = cv2.CAP_PROP_FRAME_COUNT
WIN_NAME = "video"
POS_TRACKBAR = "pos_trackbar"

#Smooth, gets rid of false positives
#cv2.Smooth(color_image, color_image, cv2.CV_GAUSSIAN, 19, 0);

# params for ShiTomasi corner detection
feature_params = dict(maxCorners = 100, 
                     qualityLevel = 0.3,
                     minDistance = 7,
                     blockSize = 7)
#lk optical flow
lk_params = dict(winSize = (15,15),
                 maxLevel = 2,
                 criteria = (cv2.TERM_CRITERIA_EPS | cv2.TERM_CRITERIA_COUNT, 10, 0.03))

#random colors
color = np.random.randint(0,255,(100,3))

#Take first fram and find corners
ret, old_frame = cap.read()

old_gray = cv2.cvtColor(old_frame, cv2.COLOR_BGR2GRAY)
p0 = cv2.goodFeaturesToTrack(old_gray, mask = None, **feature_params)

mask = np.zeros_like(old_frame)

def seek_callback(x):
    global frame
    i = cv2.getTrackbarPos(POS_TRACKBAR, WIN_FRAME)
    cap.set(CURRENT_FRAME_FLAG, i-1)
    _, frame = cap.read()
    cv2.imshow(WIN_NAME, frame)

def mouse_callback(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDBLCLK:
        save_image()

#cv2.namedWindow(WIN_NAME)
#cv2.createTrackbar(POS_TRACKBAR, WIN_NAME, 0, int(cap.get(TOTAL_FRAMES_FLAG)), seek_callback)
#cv2.setMouseCallback(WIN_NAME, mouse_callback)
paused = False

while(1):
    ret, frame = cap.read()
    frame_gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    
    #calculate optical flow
    p1, st, err = cv2.calcOpticalFlowPyrLK(old_gray, frame_gray, p0, None, **lk_params)
    
    #select good points
    good_new = p1[st==1]
    good_old = p0[st==1]
    
    #draw motion tracks
    for i,(new,old) in enumerate(zip(good_new,good_old)):
        a,b = new.ravel()
        c,d = old.ravel()
        mask = cv2.line(mask, (a,b),(c,d), color[i].tolist(), 2)
        frame = cv2.circle(frame, (a,b), 5, color[i].tolist(), -1)
        img = cv2.add(frame, mask)
        
    cv2.imshow(WIN_NAME, img)
    k = cv2.waitKey(300) 
    if (k == 30):
       k = cv2.waitKey(30)
    else:
      k = cv2.waitKey(30)
    if k == 27: break
    
    #update previous frame and previous points
    old_gray = frame_gray.copy()
    p0 = good_new.reshape(-1,1,2)
cv2.destroyAllWindows()
cap.release()
