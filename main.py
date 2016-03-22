import argparse
import sys
import serial

def sendCommand(port, baudrate):
  ser = serial.Serial(port, baudrate)

  while True:
    input = raw_input(">> ")
    if input == 'exit':
      ser.close()
      exit()
    else:
      ser.write(input + '\n')

if __name__ == "__main__":
  parser = argparse.ArgumentParser()
  parser.add_argument("-p", "--port", help="Use serial port (default: /dev/ttyACM0", default="/dev/ttyACM0")
  parser.add_argument("-b", "--baudrate", help="Set serial baudrate (default: 9600)", type=int, default=9600)

  args = parser.parse_args()

  sendCommand(args.port, args.baudrate)
