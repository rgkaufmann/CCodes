# !/usr/bin/python2.7
import serial       # for serial port
import numpy as np  # for arrays, numerical processing
from time import sleep, time
import matplotlib.pyplot as plt
# graph plotting library:
from matplotlib.figure import Figure

# needs: python2, pyserial, numpy, matplotlib, pygtk
# 0) flash the serial temperature measurement program into the msp430
# 1) start this program
# 2) press the button the Launchpad to enter 'applcation mode'
# 3) warm the chip (eg with a light bulb or your fingers)
# 4) when you've seen enough, press the reset button on the launchpad
# 5) exit the program by pressing 'q' or clicking on the x

# define the serial port. Pick one:
port = "COM3"

# function that gets called when a key is pressed:

'''
def press(event):
    print('press', event.key)
    if event.key == 'q':
        print ('got q!')
        quit_app()
    return True
    

def quit_app():
    outFile.close()
    ser.close()
    quit()
'''

# start our program proper:
# open the serial port
try:
    ser = serial.Serial(port, 9600, timeout=0.050)
    ser.flushInput()
#    ser.baudrate=9600
# with timeout=0, read returns immediately, even if no data
except:
    print ("Opening serial port", port, "failed")
    print ("Edit program to point to the correct port.")
    print ("Hit enter to exit")
    raw_input()
    quit()


'''
# create a window to put the plot in
win = gtk.Window()
# connect the destroy signal (clicking the x in the corner)
win.connect("destroy", quit_app)
win.set_default_size(400, 300)
'''

yvals = np.zeros(50)           # array to hold last 50 measurements
times = np.arange(0, 50, 1.0)  # 50 from 0 to 49.

# create a plot:
# fig = Figure()
# ax = fig.add_subplot(111, xlabel='Time Step', ylabel='Temp (deg F)')
# ax.set_ylim(50, 100)  # set limits of y axis.
plt.ylim(50, 100)

'''
canvas = FigureCanvas(fig)  # put the plot onto a canvas
win.add(canvas)             # put the canvas in the window

# define a callback for when a key is pressed
fig.canvas.mpl_connect('key_press_event', press)

# show the window
win.show_all()
win.set_title("ready to receive data")
'''

line, = plt.plot(times, yvals)
# open a data file for the output
outFile = open("time_and_temp.txt", "w")
start_time = time()
ser.flushInput()

while True:             # loop forever
    data = ser.read(1)  # look for a character from serial port, will wait up to timeout above.
    if len(data) > 0:   # was there a byte to read? should always be true.
        yvals = np.roll(yvals, -1)  # shift the values in the array
        yvals[49] = ord(data)       # take the value of the byte
        outFile.write(str(time()-start_time)+" "+str(yvals[49])+"\n")  # write to file
        line.set_ydata(yvals)                                          # draw the line
        plt.draw()
        '''
    win.set_title("Temp: "+str(yvals[49])+" deg F")
    while gtk.events_pending():	                                        # makes sure the GUI updates
        gtk.main_iteration()
#    sleep(.05) # don't eat the cpu. This delay limits the data rate to ~ 200 samples/s
'''

