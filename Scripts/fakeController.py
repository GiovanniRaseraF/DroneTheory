import serial
import vgamepad as vg
import time
import io

gamepad = vg.VX360Gamepad()
ser = serial.Serial('COM4', 115200, timeout=0)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

while(True):
    hello = sio.readline()
    channels = hello.split()

    #print(hello)
    # press a button to wake the device up
    #gamepad.press_button(button=vg.XUSB_BUTTON.XUSB_GAMEPAD_A)
    #gamepad.update()

    # press buttons and things
    #gamepad.left_joystick_float(x_value_float=0.0, y_value_float=0.2)
    if channels:
        gamepad.right_joystick_float(x_value_float=(float(channels[0]) - 1500)/ 1000, y_value_float=(float(channels[1]) - 1500)/ 1000)
        gamepad.left_joystick_float(x_value_float=(float(channels[3]) - 1500)/ 1000, y_value_float=(float(channels[2]) - 1500)/ 1000)


    gamepad.update()

    #time.sleep(0.001)