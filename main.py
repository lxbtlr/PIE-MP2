import os
import serial
import numpy as np
import time 
import re
import math
import matplotlib.pyplot as plt

# Send commands to the arduino over serial, records the data, then maps the scan

# PanRng = input("Pan Range of the Scanner\n\t")
# TltRng = input("Tilt range of the Scanner\n\t")

ser = serial.Serial("/dev/ttyUSB0",9600) #change the port to 'COM6' if windows

endkey = re.compile(r'DONE')

def sendData(d):
    # sending whatever data we want to the arduino
    ser.write((d+"\r\n").encode())


    
def receive_data():
    # receiving data over serial from the arduino,
    # meant to be placed after submitting a command to the arduino 
    # (maybe after every y-axis scan?)

    bytesToRead = ser.inWaiting()
    if endkey.search(ser.read(bytesToRead)):
        return "0 0 0", False
    return ser.read(bytesToRead), True

def write_data(d):
    # used to record data to csv for other programs

    c = open('savefile.csv','w')
    c.write(d+'\n') # putting text into the csv
    c.close()

def trigfunc(d):
    x = []
    y = []
    z = []
    for i in len(d):
        x.append(d[i][2]*math.sin(d[i][0])*math.cos(d[i][1]))
        y.append(d[i][2]*math.sin(d[i][0])*math.sin(d[i][1])))
        z.append(d[i][2]*math.cos(d[i][0]))
    return x,y,z

# sendData(PanRng)
# sendData(TltRng)
allData = []
ex = True
while ex:
    values, ex = receive_data()
    if ex == False:
        continue
    allData.append(values.split(" "))
print("Scan Complete")

trigfunc(allData)
ax = plt.axes(projection='3d')
ax.scatter3D(x,y,z,cmap='Greens')
plt.show()