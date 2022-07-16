import serial
import vgamepad as vg
import time
import io

gamepad = vg.VX360Gamepad()
ser = serial.Serial('COM4', 115200)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))

while(True):
    hello = sio.readline()
    #print(hello)
    # press a button to wake the device up
    #gamepad.press_button(button=vg.XUSB_BUTTON.XUSB_GAMEPAD_A)
    #gamepad.update()

    # press buttons and things
    #gamepad.left_joystick_float(x_value_float=0.0, y_value_float=0.2)
    #gamepad.right_joystick_float(x_value_float=0, y_value_float=0)
    #gamepad.update()

    #time.sleep(0.001)