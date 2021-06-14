import serial
import json
import time
from txt import *

with open("config.json", "r") as read_file:
    try:
        config = json.load(read_file)
    except:
        config = {"port" : "com8", "db" : "results.db"}

try:
    global arduino
    arduino = serial.Serial(config["port"], '115200')
except:
    print("Port not found")
    exit(1)

arduino.write(b'111')

while True:
    try:
        if arduino.in_waiting > 18:
            open_txt_file(config["db"])
            values = str(arduino.read(arduino.in_waiting))

            try:
                values = values[values.index('(') + 1:values.index(')')].split(",")
                values = [int(x) for x in values]
            except ValueError:
                print("Some values are incorrect")
                continue

            write_data_to_file(int(time.time() * 1_000), values)
            close_txt_file()

    except KeyboardInterrupt:
        arduino.write(b'000')
        arduino.close()
        break