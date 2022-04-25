/* Tiny I2C controller to control 2 DC motors and 2 servos */

#include <Arduino.h>
#include <Wire.h>
#include <Servo.h>
#include "DCMotor.h"

// pins
const uint8_t motor1_pwm_pin = 5;
const uint8_t motor1_dir_pin = 7;
const uint8_t motor2_pwm_pin = 6;
const uint8_t motor2_dir_pin = 8;

const uint8_t servo1_pin = 9;
const uint8_t servo2_pin = 10;

// objects
DCMotor m1, m2;
Servo s1, s2;

// i2c slave address
const uint8_t i2c_addr = 0x4C;

// declaration of handler
void cmd_handler(int count);
void req_handler();

// registers
const uint8_t ping_reg = 0x2C;
const uint8_t cmd_reg =  0x3C;
const uint8_t cmd_len = 5; // including header

// responses
const uint8_t ack = 0x31;
const uint8_t nack = 0x17;

uint8_t curr_reg;

void setup() {
    // setup motors
    m1.attach(motor1_pwm_pin, motor1_dir_pin);
    m2.attach(motor2_pwm_pin, motor2_dir_pin);
    
    s1.attach(servo1_pin);
    s2.attach(servo2_pin);

    // begin i2c
    Wire.begin(i2c_addr);
    Wire.onReceive(cmd_handler);
    Wire.onRequest(req_handler);
}

void loop() {}

void cmd_handler(int count) {

    curr_reg = Wire.read();

    if (curr_reg == cmd_reg) {
        // if msg doesn't start with header or msg len is less,
        // then it is an invalid msg, discard it

        if (count < cmd_len)
            return;
        
        // read raw data from I2C
        int8_t rm1_speed = Wire.read();
        int8_t rm2_speed = Wire.read();
        int8_t rs1_angle = Wire.read();
        int8_t rs2_angle = Wire.read();

        // post-processing
        int m1_speed = (int)rm1_speed * 2;
        int m2_speed = (int)rm2_speed * 2;
        int s1_angle = 90 + (int)rs1_angle;
        int s2_angle = 90 + (int)rs2_angle;

        // write to actuators
        m1.write(m1_speed);
        m2.write(m2_speed);
        s1.write(s1_angle);
        s2.write(s2_angle);
    }
}

void req_handler() {
    if (curr_reg == ping_reg) {
        Wire.write(ack);
        return;
    }
    Wire.write(nack);
}