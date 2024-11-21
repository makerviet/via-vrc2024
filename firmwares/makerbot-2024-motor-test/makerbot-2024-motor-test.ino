#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define MOTOR_1_CHANNEL_A 8
#define MOTOR_1_CHANNEL_B 9
#define MOTOR_2_CHANNEL_A 10
#define MOTOR_2_CHANNEL_B 11
#define MOTOR_3_CHANNEL_A 12
#define MOTOR_3_CHANNEL_B 13
#define MOTOR_4_CHANNEL_A 14
#define MOTOR_4_CHANNEL_B 15

void setMotorSpeed(int speedR1, int speedR2, int speedR3, int speedR4) {
  if (speedR1 >= 0) {
    pwm.setPWM(R1_A, 0, speedR1);
    pwm.setPWM(R1_B, 0, 0);
  } else {
    pwm.setPWM(R1_A, 0, 0);
    pwm.setPWM(R1_B, 0, abs(speedR1));
  }

  if (speedR2 >= 0) {
    pwm.setPWM(R2_A, 0, speedR2);
    pwm.setPWM(R2_B, 0, 0);
  } else {
    pwm.setPWM(R2_A, 0, 0);
    pwm.setPWM(R2_B, 0, abs(speedR2));
  }

  if (speedR3 >= 0) {
    pwm.setPWM(R3_A, 0, speedR3);
    pwm.setPWM(R3_B, 0, 0);
  } else {
    pwm.setPWM(R3_A, 0, 0);
    pwm.setPWM(R3_B, 0, abs(speedR3));
  }

  if (speedR4 >= 0) {
    pwm.setPWM(R4_A, 0, speedR4);
    pwm.setPWM(R4_B, 0, 0);
  } else {
    pwm.setPWM(R4_A, 0, 0);
    pwm.setPWM(R4_B, 0, abs(speedR4));
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Servo test firmware for MakerBot 2024");

  pwm.begin();
  pwm.setPWMFreq(50); 
}

void loop() {
  /*
    In this test, we will test all motor channel both simultaneously and sequentially from 8 to 15. 
    - For sequentially test, we will set the motor to 0, then sweep from 0 to 4000 in steps of 100, with a delay of 200ms between each step.
    - For simultaneous test, we will set Motor 1 & Motor 3 to 2000, running forward, and Motor 2 & Motor 4 to 2000, running backward, with a delay of 5 seconds and vice versa.
  */

  for (int i = 8; i <= 15; i++) { // Test all motor channel sequentially

    for (int j = 8; j <= 15; j++) pwm.setPin(j, 0, true); // Set all motor to 0 before test
    
    for (int pwm_val = 0; pwm_val <= 4000; pwm_val += 200) { // Sweep from 0 to 4000 in steps of 100
      pwm.setPin(i, pwm_val, true);
      delay(200); // Delay 300ms between each step
    }
    
    pwm.setPin(i, 0, true); // Set motor to 0 after test
  }

  // Test all motor channel simultaneously

  // Set Motor 1 & Motor 3 to 4000, running forward
  setMotorSpeed(2000, -2000, 2000, -2000);
  delay(3000);
  setMotorSpeed(0, 0, 0, 0);
  delay(500); // Delay 500ms before next test
  setMotorSpeed(-2000, 2000, -2000, 2000);
  delay(3000);

  // Delay 5 second before starting the test again
  Serial.println("Test completed. Restarting in 5 second.");
  delay(5000);
}