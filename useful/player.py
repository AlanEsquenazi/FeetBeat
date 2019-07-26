import pygame.mixer
import sys
import os
import serial
from pygame.mixer import *
arduino = serial.Serial('COM10', 9600, timeout=.1)
pygame.mixer.pre_init(44100, -16, 2, 2048)
pygame.mixer.quit()
pygame.mixer.init()
fpsTime = pygame.time.Clock()
fpsTime.tick(60)

while 1:
    data = arduino.readline()[:-2]
    if data:
        print(data)
        pygame.mixer.music.load(data)
        pygame.mixer.music.play(0)
        #print("stop")
        #print(stop)
        stop = 1
        while pygame.mixer.music.get_busy() and stop!=0:
            stop = int(input())
            if stop==0:
                pygame.mixer.music.pause()
            stop=int(input())
            if(stop!=0):
                pygame.mixer.music.unpause()
            pygame.time.Clock().tick(10)
                #print('playing')
