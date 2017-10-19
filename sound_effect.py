import pygame
import pygame.mixer
import datetime
import serial
import time

arduinoSerialData = serial.Serial('/dev/ttyUSB0', 9600)


pygame.init()
BLACK = (0,0,0)
WIDTH = 100
HEIGHT = 100
screen = pygame.display.set_mode((WIDTH, HEIGHT))
done = False
pygame.mixer.init(48000, -16, 1, 1024)
sndB = pygame.mixer.Sound("stranger.wav")
soundChannelA = pygame.mixer.Channel(1)
soundChannelB = pygame.mixer.Channel(2)
current_time = datetime.datetime.now().time()
print(current_time.isoformat())

while not done:
	pressed = pygame.key.get_pressed()
        if pressed[pygame.K_e]:
		print("Good Bye")
		done= True
	if pressed[pygame.K_SPACE] and not soundChannelA.get_busy():
                soundChannelA.play(sndB)
		arduinoSerialData.write('5')
                current_time = datetime.datetime.now().time()
                print(current_time.isoformat())
		print("Sound")
	for event in pygame.event.get():
                if event.type == pygame.QUIT:
                        print("Good Bye")
                        done = True
	pygame.display.flip()
	pygame.event.pump()
