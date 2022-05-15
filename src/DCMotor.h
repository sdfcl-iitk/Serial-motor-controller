#pragma once
#include <Arduino.h>

class DCMotor {
    private:
        uint8_t pwm_pin, dir_pin;

    public:
        void attach(const uint8_t pwm_pin, const uint8_t dir_pin) {
            this->pwm_pin = pwm_pin;
            this->dir_pin = dir_pin;

            pinMode(pwm_pin, OUTPUT);
            pinMode(dir_pin, OUTPUT);
        }

        void detach() {
            pinMode(pwm_pin, INPUT);
            pinMode(dir_pin, INPUT);
        }
        
        void write(int speed) {
            /* Speed is a pwm between -255 to 255. Sign indicates direction */
            speed = constrain(speed, -255, 255);

            int pwm = abs(speed);
            bool dir = (speed >= 0);

            // write to hardware
            analogWrite(pwm_pin, pwm);
            digitalWrite(dir_pin, dir);
        }
};