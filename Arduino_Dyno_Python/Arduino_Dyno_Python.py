import serial 

ser = serial.Serial('COM11',baudrate=9600, timeout=1)

while True:
    values = ser.readline()
    print(values)
