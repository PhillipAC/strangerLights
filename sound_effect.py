import pygame
import pygame.mixer
import RPi.GPIO as GPIO
import datetime
import serial
import time
import os

# Setup the serial for sending information to arduino
arduinoSerialData = serial.Serial('/dev/ttyUSB0', 9600)

# Setup GPIO for wired button detection
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.IN, pull_up_down=GPIO.PUD_UP)

pygame.init()
BLACK = (0,0,0)
WIDTH = 100
HEIGHT = 100
screen = pygame.display.set_mode((WIDTH, HEIGHT))
# Index of current song being played (or that was just played)
currentSongIndex = 0
done = False
lightShow = False
pygame.mixer.init(48000, -16, 1, 1024)
musicChannel = pygame.mixer.music
current_time = datetime.datetime.now().time()
print(current_time.isoformat())

# List to hold music file paths
musicLibrary = []
# Loop through every file in the Music folder
for file in os.listdir("Music"):
	# If the file is a MP3
	if file.endswith(".mp3"):
		# Print that the music is being loaded
		print("Loading Music/" + file)
		# Add music path to the list
		musicLibrary.append("Music/" + file)

print 'All music loaded'

while not done:
	# Get the state of the button
	input_state = GPIO.input(18)
	pressed = pygame.key.get_pressed()
        if pressed[pygame.K_e]:
		print("Good Bye")
		done= True
	if (pressed[pygame.K_SPACE] or not input_state ) and not lightShow:
		print("Starting Light Show")
		lightShow = True
                musicChannel.load('stranger.wav')
		musicChannel.play()
		arduinoSerialData.write('5'.encode())
                current_time = datetime.datetime.now().time()
                print(current_time.isoformat())
	if not musicChannel.get_busy() and lightShow == True:
		lightShow = False
	if not musicChannel.get_busy() and lightShow == False:
	        # Look at the next song
		currentSongIndex+=1
		# Check that you were not already at the last song and if you were
		if currentSongIndex > len(musicLibrary):
			#Shuffle the song list and startover
			print "Reached end of song list"
			currentSongIndex = 0
		# Load the next song and start playing it
		else:
			print "Starting Song: " + musicLibrary[currentSongIndex-1]
        		musicChannel.load(musicLibrary[currentSongIndex-1])
			musicChannel.play()		
	for event in pygame.event.get():
                if event.type == pygame.QUIT:
                        print("Good Bye")
                        done = True
	pygame.display.flip()
	pygame.event.pump()
