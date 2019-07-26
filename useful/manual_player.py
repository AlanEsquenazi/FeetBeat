import pygame.mixer
import sys
import os
import serial
from pygame.mixer import *
pygame.mixer.pre_init(44100, -16, 2, 2048)
pygame.mixer.quit()
pygame.mixer.init()
fpsTime = pygame.time.Clock()
fpsTime.tick(60)

while 1:
    print("please select a song")
    data = str(input())
    pygame.mixer.music.load(data)
    pygame.mixer.music.play(0)
        #print("stop")
        #print(stop)
    stop = 1
    while pygame.mixer.music.get_busy():
        stop = int(input())
        if stop==0:
            pygame.mixer.music.pause()
        stop=int(input())
        if(stop!=0):
            pygame.mixer.music.unpause()
        pygame.time.Clock().tick(10)
                #print('playing')
