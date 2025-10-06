#!/usr/bin/python3

# Copyright (C) 2022 Infineon Technologies & pmdtechnologies ag
#
# THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
# KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
# PARTICULAR PURPOSE.

"""This sample shows how to use openCV on the depthdata we get back from either a camera or an rrf file.
The Camera's lens parameters are optionally used to remove the lens distortion and then the image is displayed using openCV windows.
Press 'd' on the keyboard to toggle the distortion while a window is selected. Press esc to exit.

Additionally this sample implements the YOLO v3 network for object detection. We convert the image to rgb and then feed this image
into the network. Then we draw bounding boxes around the found object.
"""

#TODO:
#1. modify the code to adapt the color scheme based on the scene
#2. edge detection
#3. surface roughness: mean amplitude; surface porosity: std of amplitude

import warnings
warnings.filterwarnings("ignore", category=FutureWarning)

import argparse
import queue
import sys
import threading
# import scipy.misc

import numpy as np
import cv2
import time
from matplotlib import pyplot as plt
import os

import sys




# insert the path to your Royale installation here:
# note that you need to use \\ or / instead of \ on Windows
ROYALE_DIR = "C:\\Sheng\\tof\\EmptyObjectDetectionProject_0929\\Resources\\5.12.0.3089_royale\\python"

sys.path.append(ROYALE_DIR)

try:
    from roypypack import roypy  # package installation
except ImportError:
    import roypy  # local installation
from roypy_sample_utils import CameraOpener, add_camera_opener_options
from roypy_platform_utils import PlatformHelper

#import the ball detection functions
import keyboard

from roypy_sample_utils import CameraOpener, add_camera_opener_options, select_use_case
from new_tof_functions import show_overlay

# setup shared memory for showing image in another code
# --------------------------------------------------------------------------------------------------------------------

# --------------------------------------------------------------------------------------------------------------------


# YOLO code from: https://github.com/arunponnusamy/object-detection-opencv/blob/master/yolo_opencv.py

#choose yolo model
#pytorch
# model = torch.hub.load('ultralytics/yolov5', 'custom', path='yolov5n.pt')


save_directory = 'Resources/data_collection/OZT_378'
save_photo = True
sampling_rate = 2.0
# mode 1: gray and depth; mode 2: overlay, gray and depth; mode 3: only depth; mode 4: overlay and depth
mode = 2
#check if tab key is pressed, if so, exit the program
def check_for_exit():
    if keyboard.is_pressed('tab'):
        print("\nTab key pressed. Exiting program...")
        plt.close('all')  # Close all plots
        sys.exit()


# OPENCV SAMPLE + INTEGRATED OBJECT DETECTION WITH YOLO
class MyListener(roypy.IDepthDataListener):
    def __init__(self, q):
        super(MyListener, self).__init__()
        self.frame = 0
        self.done = False
        self.undistortImage = True
        self.lock = threading.Lock()
        self.once = False
        self.queue = q
        self.last_save_time = time.time()  # Initialize last save time
        # self.overlay_shape = (480, 640, 3)  # Adjust to match your overlay shape
        # self.overlay_dtype = np.uint8
        # self.overlay_size = int(640 * 480 * 3)
        # try:
        #     self.shm_overlay = shared_memory.SharedMemory(name='overlay_shm', create=True, size=self.overlay_size)
        # except FileExistsError:
        #     self.shm_overlay = shared_memory.SharedMemory(name='overlay_shm', create=False)
        # self.overlay_array = np.ndarray(self.overlay_shape, dtype=self.overlay_dtype, buffer=self.shm_overlay.buf)
    
    def onNewData(self, data):
        p = data.npoints()
        self.queue.put(p)
        
        # for ply file
        #-----------------------------------------------------------------------------------------------
        numPoints = data.getNumPoints()

    def paint (self, data):
        """Called in the main thread, with data containing one of the items that was added to the
        queue in onNewData.
        """
        
        # mutex to lock out changes to the distortion while drawing
        self.lock.acquire()

        #type ndarray
        #x in 3d data
        x3d = data[:, :, 0]
        #y in 3d data   
        y3d = data[:, :, 1]
        #depth in 3d data
        depth = data[:, :, 2]
        #amplitude in 3d data
        gray = data[:, :, 3]
        #confidence in 3d data
        confidence = data[:, :, 4]

        zImage = np.zeros(depth.shape, np.float32)
        grayImage = np.zeros(depth.shape, np.float32)

        # iterate over matrix, set zImage values to z values of data
        # also set grayImage adjusted gray values
        xVal = 0
        yVal = 0
        for x in zImage:        
            for y in x:
                if confidence[xVal][yVal]> 0:
                  zImage[xVal,yVal] = self.adjustZValue(depth[xVal][yVal])
                  grayImage[xVal,yVal] = self.adjustGrayValue(gray[xVal][yVal])
                yVal=yVal+1
            yVal = 0
            xVal = xVal+1
        
        # for x in zImage:        
        #     for y in x:
        #         if confidence[xVal][yVal]> 0:
        #           zImage[xVal,yVal] = depth[xVal][yVal]
        #           grayImage[xVal,yVal] = gray[xVal][yVal]
        #         yVal=yVal+1
        #     yVal = 0
        #     xVal = xVal+1

        #zimage[y, x]
        # zImage8 = np.uint8(zImage)
        zImage8 = np.uint8(zImage)
        grayImage8 = np.uint8(grayImage)

        # apply undistortion
        if self.undistortImage: 
            zImage8 = cv2.undistort(zImage8,self.cameraMatrix,self.distortionCoefficients)
            #grayimage8 is a np array
            grayImage8 = cv2.undistort(grayImage8,self.cameraMatrix,self.distortionCoefficients)

        
        #do the ball detection  
        #------------------------------------------------------------------------------------------------------------------------------------
        overlay, grayscale_bgr, depth_colored = show_overlay(grayImage, zImage)


        
        
        if save_photo == True:
            # Check if 2 seconds have passed since the last save
            current_time = time.time()
            if current_time - self.last_save_time >= sampling_rate:
                # Save the overlay image
                save_path = f"overlay_{int(current_time)}.png"  # Save with a timestamp
                cv2.imwrite(os.path.join(save_directory, f"overlay_{int(current_time)}.png"), overlay)
                print(f"Saved overlay image as {save_path} in {save_directory}")
                
                save_path_gray = f"gray_{int(current_time)}.png"  # Save with a timestamp
                cv2.imwrite(os.path.join(save_directory, f"gray_{int(current_time)}.png"), grayscale_bgr)
                print(f"Saved gray image as {save_path_gray} in {save_directory}")
                self.last_save_time = current_time  # Update last save time
                # print(int(current_time))
        
        if mode == 1:
            Cont_img = np.concatenate((grayscale_bgr, depth_colored), axis=1)
        elif mode == 2:
            Vert = np.concatenate((grayscale_bgr, depth_colored), axis=0)
            Vert = cv2.resize(Vert, (320, 480))
            Cont_img = np.concatenate((Vert, overlay), axis=1)
        elif mode == 3:
            Cont_img = depth_colored
        elif mode == 4:
            Cont_img = np.concatenate((depth_colored, overlay), axis=1)
        
        cv2.namedWindow('Image', cv2.WINDOW_NORMAL | cv2.WINDOW_AUTOSIZE)

        cv2.imshow("Image", Cont_img)

        
        
        

        self.lock.release()
        self.done = True

    def setLensParameters(self, lensParameters):
        # Construct the camera matrix
        # (fx   0    cx)
        # (0    fy   cy)
        # (0    0    1 )
        self.cameraMatrix = np.zeros((3,3),np.float32)
        self.cameraMatrix[0,0] = lensParameters['fx']
        self.cameraMatrix[0,2] = lensParameters['cx']
        self.cameraMatrix[1,1] = lensParameters['fy']
        self.cameraMatrix[1,2] = lensParameters['cy']
        self.cameraMatrix[2,2] = 1

        # Construct the distortion coefficients
        # k1 k2 p1 p2 k3
        self.distortionCoefficients = np.zeros((1,5),np.float32)
        self.distortionCoefficients[0,0] = lensParameters['k1']
        self.distortionCoefficients[0,1] = lensParameters['k2']
        self.distortionCoefficients[0,2] = lensParameters['p1']
        self.distortionCoefficients[0,3] = lensParameters['p2']
        self.distortionCoefficients[0,4] = lensParameters['k3']

    def toggleUndistort(self):
        self.lock.acquire()
        self.undistortImage = not self.undistortImage
        self.lock.release()

    # Map the gray values from the camera to 0..255
    def adjustGrayValue(self,grayValue):
        clampedVal = min(2000,grayValue) # try different values, to find the one that fits your environment best
        newGrayValue = clampedVal / 2000 * 255
        return newGrayValue
    
    # Map the depth values from the camera to 0..255
    def adjustZValue(self,zValue):
        clampedDist = min(2.5,zValue)
        newZValue = clampedDist / 2.5 * 255
        return newZValue

def main ():
    platformhelper = PlatformHelper()
    parser = argparse.ArgumentParser (usage = __doc__)
    add_camera_opener_options (parser)
    options = parser.parse_args()
   
    opener = CameraOpener (options)

    try:
        cam = opener.open_camera ()
        
        # curUseCase = select_use_case(cam)
        useCases = cam.getUseCases()
        # for i in range (0, len (useCases)):
        #     print(useCases[i])
        curUseCase = useCases[10]
    except:
        print("could not open Camera Interface")
        sys.exit(1)

    try:
        # retrieve the interface that is available for recordings
        replay = cam.asReplay()
        print ("Using a recording")
        print ("Framecount : ", replay.frameCount())
        print ("File version : ", replay.getFileVersion())
    except SystemError:
        print ("Using a live camera")

    q = queue.Queue()
    l = MyListener(q)
    cam.registerDataListener(l)
    # cam.registerIRImageListener(l)
    
    print ("Setting use case : " + curUseCase)
    
    cam.setUseCase(curUseCase)
    
    
    cam.startCapture()

    lensP = cam.getLensParameters()
    l.setLensParameters(lensP)

    process_event_queue (q, l)

    cam.stopCapture()
    print("Done")
    
    # time.sleep(0.3) # Delay for 0.5 seconds

def process_event_queue (q, painter):
    # t_end = time.time() + 15
    # while time.time() < t_end:
    while True:
        try:
            check_for_exit()
            # try to retrieve an item from the queue.
            # this will block until an item can be retrieved
            # or the timeout of 1 second is hit
            if len(q.queue) == 0:
                item = q.get(True, 1)
            else:
                for i in range (0, len (q.queue)):
                    item = q.get(True, 1)
        except queue.Empty:
            # this will be thrown when the timeout is hit
            break
        else:
            painter.paint(item)
            # waitKey is required to use imshow, we wait for 1 millisecond
            currentKey = cv2.waitKey(1)
            if currentKey == ord('d'):
                painter.toggleUndistort()
            # close if escape key pressed
            if currentKey == 27: 
                break

if (__name__ == "__main__"):
    main()
