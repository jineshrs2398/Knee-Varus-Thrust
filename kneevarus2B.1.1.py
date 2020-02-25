import serial
import numpy
import matplotlib.pyplot as plt
from drawnow import *
import threading

tempF = []
tempF2 = []
tempD = []
pressure = []
arduinoData = serial.Serial('COM17',115200)   
arduinoData2 = serial.Serial('COM18',115200)
plt.ion()
cnt=0

def makeFig():
    plt.ylim(-180,180)
    plt.title('Angle of the knee joint')
    plt.grid('True')
    plt.ylabel('angle')
    plt.plot(tempD,'r-',label='degrees')
    plt.legend(loc='upper left')

temp=0
temp2=0
def drawFig():
    while True:
        drawnow(makeFig)
        plt.pause(.001)

def data1take():
    global temp
    while True:
        dataArray = arduinoData.readline()
        temp = float(dataArray)
         
def data2take():
    global temp2
    while True:
        dataArray2 = arduinoData2.readline()
        temp2 = float(dataArray2)
         
#def datadifftake():
#    while True:
        

t2=threading.Thread(target=data1take)
t2.start()

t3=threading.Thread(target=data2take)
t3.start()

t1=threading.Thread(target=drawFig)
t1.start()


while True:
    while(arduinoData.inWaiting()==0):
        pass
    
    
   # dataArray = arduinoData.split('.')
   
    
    tempd =180-(temp+temp2)
   # P = float( dataArray[1])
    tempD.append(tempd)
    print(str(tempd)+str('\t')+str(temp)+str('\t')+str(temp2))
   # pressure.append(p)
    
    cnt=cnt+1
    if(cnt>50):
        tempD.pop(0)
      #  pressure.pop(0)
