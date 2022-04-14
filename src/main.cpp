/* Tiny I2C controller to control 2 DC motors and 2 servos */

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "DCMotor.h"

// pins
const uint8_t motor1_pwm_pin = 9;
const uint8_t motor1_dir_pin = 8;
const uint8_t motor2_pwm_pin = 10;
const uint8_t motor2_dir_pin = 11;

const uint8_t servo1_pin = 5;
const uint8_t servo2_pin = 6;

// objects
DCMotor m1, m2;
Servo s1, s2;

// i2c slave address
// switch this below to use a different address
#if 1
const uint8_t i2c_addr = 0x4C;
#else
const uint8_t i2c_addr = 0x5A;
#endif

// declaration of handler
void cmd_handler(int count);

// msg format
const char header = '<';
const uint8_t msg_len = 5; // including header

void setup() {
    // setup motors
    m1.attach(motor1_pwm_pin, motor1_dir_pin);
    m2.attach(motor2_pwm_pin, motor2_dir_pin);
    
    s1.attach(servo1_pin);
    s1.attach(servo2_pin);

    // begin i2c
    Wire.begin(i2c_addr);
    Wire.onReceive(cmd_handler);
}

void loop() {}

void cmd_handler(int count) {

    if (Wire.read() != header || count < msg_len) {
        // if msg doesn't start with header or msg len is less,
        // then it is an invalid msg, discard it
        while(Wire.available())
            Wire.read();
        return;
    }

    // read raw data from I2C
    int8_t rm1_speed = Wire.read();
    int8_t rm2_speed = Wire.read();
    int8_t rs1_angle = Wire.read();
    int8_t rs2_angle = Wire.read();

    // post-processing
    int m1_speed = rm1_speed * 2;
    int m2_speed = rm2_speed * 2;
    int s1_angle = rs1_angle;
    int s2_angle = rs2_angle;

    // write to actuators
    m1.write(m1_speed);
    m2.write(m2_speed);
    s1.write(s1_angle);
    s2.write(s2_angle);
}