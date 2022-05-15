/* Tiny serial controller to control 2 DC motors and 2 servos */

#include <Arduino.h>
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

// device id
constexpr uint8_t dev_id = 0x4C;

// registers
constexpr uint8_t ping_reg = 0x2C;
constexpr uint8_t cmd_reg =  0x3C;
constexpr uint8_t cmd_len = 4;

void setup() {
    // serial
    Serial.begin(115200);

    // setup motors
    m1.attach(motor1_pwm_pin, motor1_dir_pin);
    m2.attach(motor2_pwm_pin, motor2_dir_pin);
    
    s1.attach(servo1_pin);
    s2.attach(servo2_pin);
}

void loop() {
    if (Serial.available() > 0) {
        uint8_t reg = Serial.read();

        if (reg == ping_reg) {
            Serial.write(dev_id);
        
        } else if (reg == cmd_reg) {

            // wait until all bytes have been received
            while (Serial.available() < cmd_len)
                delay(1);

            // read raw data from Serial
            int8_t rm1_speed = Serial.read();
            int8_t rm2_speed = Serial.read();
            int8_t rs1_angle = Serial.read();
            int8_t rs2_angle = Serial.read();

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
}
