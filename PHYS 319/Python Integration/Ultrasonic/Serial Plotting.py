import serial
import numpy as np
from time import sleep, time
import pygtk as gtk
from matplotlib.figure import Figure
from matplotlib.backends.backend_gtk3agg import FigureCanvasGTK3Agg as FigureCanvas

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

ser = serial.Serial()
try:
    ser.port = "COM3"
    ser.baudrate = 9600
    ser.timeout = 0.050
    ser.open()
except:
    print ("Opening serial port COM3 failed")
    print ("Edit program to point to the correct port.")
    print ("Hit enter to exit")
    raw_input()
    quit()

win = gtk.Window()
win.connect("destroy", quit_app)
win.set_default_size(400, 300)

yvals = np.zeros(50)
times = np.arange(0, 50, 1.0)

fig = Figure()
ax = fig.add_subplot(111, xlabel='Time Step', ylabel='Temp (deg F)')
ax.set_ylim(50, 100)

canvas = FigureCanvas(fig)
win.add(canvas)
fig.canvas.mpl_connect('key_press_event', press)

win.show_all()
win.set_title("ready to receive data")

line, = ax.plot(times, yvals)
outFile = open("time_and_temp.txt", "w")
start_time = time()

ser.flushInput()
while True:
    data = ser.read(2)
    if len(data) > 1:
        yvals = np.roll(yvals, -1)
        yvals[49] = (ord(data[0])+ord(data[1])*2**8)/(58.0)
        outFile.write(str(time() - start_time) + " " + str(yvals[49]) + "\n")
        line.set_ydata(yvals)
        fig.canvas.draw()
    win.set_title("Temp: "+str(yvals[49])+" deg F")
    while gtk.events_pending():
        gtk.main_iteration()
