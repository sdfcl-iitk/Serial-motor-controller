# Serial-motor-controller
Tiny serial controller to control 2 DC motors and 2 servos. It is mainly used to reduce wiring and computational complexity for the host controller.

## Wiring
This PlatformIO project has been tested on an Arduino Nano ATMega328P. The motors and servos are connected as follows (this can be changed in the code):

| Device | Arduino Nano Pin |
| --- | --- |
| Motor1 PWM | D9 |
| Motor1 DIR | D8 |
| Motor2 PWM | D10 |
| Motor2 DIR | D11 |
| Servo1 | D5 |
| Servo2 | D6 |

## Packet format
Multiple serial motor controllers can be used together. To help distinguish between multiple controllers, each controller can be set an id in the `dev_id` variable. The controllers support 2 commands - a ping command, and a write command. The ping command returns the device id and the write command can be used to control the motors. To get the device id, send the byte `0x2C` to the serial port (baud rate 115200). It should return the device id (1 byte). To control the motors and servos, transmit a 5-byte packet to the serial port in this format:

| Write Command | Motor1 PWM | Motor2 PWM | Servo1 Angle | Servo2 Angle |
| --- | --- | --- | --- | --- |

- Write Command is the fixed byte `0x3C`.
- Motor1 PWM is half of the real pwm. The sign indicates the direction. For example, if we want the motor to spin with 100 pwm in reverse, transmit -50.
- Motor2 PWM is same as Motor1 PWM.
- Servo1 Angle is the servo angle in degrees.
- Servo2 Angle is the same as Servo1 angle.
