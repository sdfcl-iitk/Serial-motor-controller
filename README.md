# i2c-motor-controller
Tiny I2C controller to control 2 DC motors and 2 servos. It is mainly used to reduce wiring and computational complexity for the host controller.

## Wiring
This PlatformIO project has been tested on an Arduino Nano ATMega328P. On this board, the SDA pin is A4 and the SCL pin is A5. Connect these pins to the I2C bus and also make the ground common.

| Arduino Nano | I2C Bus |
| --- | --- |
| A4 | SDA |
| A5 | SCL |
| GND | GND |

## Packet format
To control the motors and servos, transmit a 5-byte packet to the board in this format:

| Header | Motor1 PWM | Motor2 PWM | Servo1 Angle | Servo2 Angle |
| --- | --- | --- | --- | --- |

- Header is a constant byte '<' (0x3C)
- Motor1 PWM is half of the real pwm. The sign indicates the direction. For example, if we want the motor to spin with 100 pwm in reverse, transmit -50.
- Motor2 PWM is same as Motor1 PWM.
- Servo1 Angle is the servo angle in degrees.
- Servo2 Angle is the same as Servo1 angle.
