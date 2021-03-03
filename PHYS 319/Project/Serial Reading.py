import serial

ser = serial.Serial()

try:
    print "Opening serial port COM3"
    ser.port = "COM3"
    ser.baudrate = 9600
    ser.timeout = 0.050
    ser.open()
    ser.reset_input_buffer()
    ser.flushInput()
    print "Serial port opened successfully"
except serial.SerialTimeoutException or serial.SerialException:
    print "Opening serial port COM3 failed."
    print "Edit program to point to the correct port."
    print "Press any button to exit"
    raw_input()
    quit()

time = 0
f = open("Data.txt", "w")
while True:
    if ser.in_waiting == 4:
        time += 1
        data = ser.read(4)
        if len(data) > 3:
            speed = ord(data[0])+2**8*ord(data[1])
            direction = ord(data[2])+2**8*ord(data[3])

            print("Speed Input as: "+str(speed))
            print("Direction Input as: "+str(direction))

            f.write(str(time)+","+str(speed)+","+str(direction))
        ser.reset_input_buffer()
        ser.flushInput()
    elif ser.in_waiting > 4:
        ser.reset_input_buffer()
        ser.flushInput()