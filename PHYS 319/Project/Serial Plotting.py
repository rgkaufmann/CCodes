import serial

ser = serial.Serial()

try:
    print "Opening serial port COM3"
    ser.port = "COM3"
    ser.baudrate = 9600
    ser.timeout = 0.050
    ser.open()
    ser.reset_input_buffer()
    print "Serial port opened successfully"
except:
    print "Opening serial port COM3 failed."
    print "Edit program to point to the correct port."
    print "Press any button to exit"
    raw_input()
    quit()

while True:
    if (ser.in_waiting()>=4):
        data = ser.read(4)
        if len(data) > 3:
            print("Speed Input as: "+str(ord(data[0])+2**8*ord(data[1])))
            print("Direction Input as: "+str(ord(data[2])+2**8*ord(data[3])))
        ser.reset_input_buffer()
