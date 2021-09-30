from mpl_toolkits import mplot3d
import os
import serial
import numpy as np
import time 
import re
import math
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns 
sns.set_theme()

ser = serial.Serial("/dev/cu.usbmodem14101",9600) #change the port to 'COM6' if windows, or other appropriate port

endkey = re.compile(r'DONE')
endline = re.compile(r'L')
    
def receive_data():
    # receiving data over serial from the arduino,
    # meant to be placed after submitting a command to the arduino 
    # (maybe after every y-axis scan?)
    line = ""
    while True:
        bytesToRead = ser.inWaiting()
        inny = ser.readline(bytesToRead).decode('utf-8')
        
        line += inny
        if endkey.search(line):
            return "0,0,0", False
        if endline.search(line) and len(line)>=5:
            line = line[:len(line)-1]
            print(line)

            return line, True
        if len(line) > 13:
            print(line)
            line = ""

def write_data(d):
    # used to record data to csv for other programs
    c = open('savefile.csv','w')
    for i in d:
        c.write(str(i)+',') # putting text into the csv
    c.write("\n")
    c.close()

def trigfunc(d):
    x = []
    y = []
    z = []
        # .00003196*((int(d[i][2])**2)-0.3472*((int(d[i][2]))+115.4

    for i in range(len(d)):
        
        # r = 1/(float(d[i][2])*0.0000322453+0.000824822)-171.72
        r = 1/(float(d[i][2])*0.0000704684+0.000486971)-6.14906
        
        x.append(r*math.sin(math.radians(110-float(d[i][1])))*math.cos(math.radians(float(d[i][0]))))
        y.append(r*math.sin(math.radians(110-float(d[i][1])))*math.sin(math.radians(float(d[i][0]))))
        z.append(r*math.cos(math.radians(110-float(d[i][1])))+9)
        print(r)
    return x,y,z

print("Scanning...")
allData = []
ex = True
while ex:
    values, ex = receive_data()
    if ex == False:
        continue
    allData.append(values.split(","))


print("Scan Complete")

ser.close()

print(allData)

print("Saving all data...")

write_data(allData)

x,y,z = trigfunc(allData)
print("Plotting...")

magnitude = []
for i in range(len(x)):
    magnitude.append((x[i]**2+y[i]**2+z[i]**2)**(1/2))

fig = plt.figure()
ax = plt.axes(projection='3d')

ax.scatter3D(x, y, z, c=magnitude, cmap='rainbow', s=10)
ax.set_ylabel("Y")
ax.set_xlabel("X")
ax.set_zlabel("Z")

plt.show()