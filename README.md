# i2c-motor-controller
Tiny I2C controller to control 2 DC motors and 2 servos. It is mainly used to reduce wiring and computational complexity for the host controller.

## Wiring
This PlatformIO project has been tested on an Arduino Nano ATMega328P. On this board, the SDA pin is A4 and the SCL pin is A5. Connect these pins to the I2C bus and also make the ground common.

| Arduino Nano | I2C Bus |
| --- | --- |
| A4 | SDA |
| A5 | SCL |
| GND | GND |

The motors and servos are connected as follows (this can be changed in the code):

| Device | Arduino Nano Pin |
| --- | --- |
| Motor1 PWM | D9 |
| Motor1 DIR | D8 |
| Motor2 PWM | D10 |
| Motor2 DIR | D11 |
| Servo1 | D5 |
| Servo2 | D6 |

## Connecting and accessing registers
By default, the device is accessible at address 0x4C. This can be changed in the code. The device has 2 registers - 0x2C and 0x3C. 0x2C is the ping register and 0x3C is the command register. You can read a byte from the ping register - if it returns 0x31 (ACK), then it means the device is properly connected. In case of any error, it return 0x17 (NACK). To control the connected motors and servos, send a 4-byte packet to the command register as shown below.

## Packet format
To control the motors and servos, transmit a 4-byte packet to register 0x3C in this format:

| Motor1 PWM | Motor2 PWM | Servo1 Angle | Servo2 Angle |
| --- | --- | --- | --- |

- Motor1 PWM is half of the real pwm. The sign indicates the direction. For example, if we want the motor to spin with 100 pwm in reverse, transmit -50.
- Motor2 PWM is same as Motor1 PWM.
- Servo1 Angle is the servo angle in degrees.
- Servo2 Angle is the same as Servo1 angle.
