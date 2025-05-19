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

#define NOTIFY_LED 13

void setMotorSpeed(int speedR1, int speedR2, int speedR3, int speedR4) {
  if (speedR1 >= 0) {
    pwm.setPin(MOTOR_1_CHANNEL_A, speedR1);
    pwm.setPin(MOTOR_1_CHANNEL_B, 0);
  } else {
    pwm.setPin(MOTOR_1_CHANNEL_A, 0);
    pwm.setPin(MOTOR_1_CHANNEL_B, abs(speedR1));
  }

  if (speedR2 >= 0) {
    pwm.setPin(MOTOR_2_CHANNEL_A, speedR2);
    pwm.setPin(MOTOR_2_CHANNEL_B, 0);
  } else {
    pwm.setPin(MOTOR_2_CHANNEL_A, 0);
    pwm.setPin(MOTOR_2_CHANNEL_B, abs(speedR2));
  }

  if (speedR3 >= 0) {
    pwm.setPin(MOTOR_3_CHANNEL_A, speedR3);
    pwm.setPin(MOTOR_3_CHANNEL_B, 0);
  } else {
    pwm.setPin(MOTOR_3_CHANNEL_A, 0);
    pwm.setPin(MOTOR_3_CHANNEL_B, abs(speedR3));
  }

  if (speedR4 >= 0) {
    pwm.setPin(MOTOR_4_CHANNEL_A, speedR4);
    pwm.setPin(MOTOR_4_CHANNEL_B, 0);
  } else {
    pwm.setPin(MOTOR_4_CHANNEL_A, 0);
    pwm.setPin(MOTOR_4_CHANNEL_B, abs(speedR4));
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Motor test firmware for MakerBot 2024");

  pwm.begin();
  pwm.setPWMFreq(50); 
}

void loop() {
  /*
    In this test, we will test all motor channel both simultaneously and sequentially from 8 to 15. 
    - For sequentially test, we will set the motor to 0, then sweep from 0 to 4000 in steps of 100, with a delay of 200ms between each step.
    - For simultaneous test, we will set Motor 1 & Motor 3 to 2000, running forward, and Motor 2 & Motor 4 to 2000, running backward, with a delay of 5 seconds and vice versa.
  */
  Serial.println("Starting sequentially test...");

  // Blink the LED to notify the test is started
  for (int i = 0; i < 3; i++) {
    Serial.println(3 - i);
    digitalWrite(NOTIFY_LED, HIGH);
    delay(500);
    digitalWrite(NOTIFY_LED, LOW);
    delay(500);
  }

  for (int i = 8; i <= 15; i++) { // Test all motor channel sequentially
    for (int j = 8; j <= 15; j++) pwm.setPin(j, 0); // Set all motor to 0 before test
    
    for (int pwm_val = 0; pwm_val <= 4000; pwm_val += 200) { // Sweep from 0 to 4000 in steps of 100
      Serial.print("Motor channel ");
      Serial.print(i);
      Serial.print(" running at ");
      Serial.println(pwm_val);
      pwm.setPin(i, pwm_val);
      delay(200); // Delay 300ms between each step
    } 

    pwm.setPin(i, 0); // Set motor to 0 after test
  }

  // Test all motor channel simultaneously

  Serial.println("Starting simultaneously test...");

  // Blink the LED to notify the test is started
  digitalWrite(NOTIFY_LED, HIGH);
  delay(500);
  digitalWrite(NOTIFY_LED, LOW);
  delay(200);

  // Set Motor 1 & Motor 3 to 4000, running forward

  Serial.println("Motor 1 & Motor 3 running forward at 2000 & Motor 2 & Motor 4 running backward at 2000 for 3 seconds");
  setMotorSpeed(2000, -2000, 2000, -2000);
  delay(3000);

  Serial.println("All motor stop for 0.5 second");
  setMotorSpeed(0, 0, 0, 0);
  delay(500); // Delay 500ms before next test

  Serial.println("Motor 1 & Motor 3 running backward at 3500 & Motor 2 & Motor 4 running forward at 3500 for 3 seconds");
  setMotorSpeed(-3500, 3500, -3500, 3500);
  delay(3000);

  Serial.println("All motor stop");
  setMotorSpeed(0, 0, 0, 0);

  Serial.println("Motor 1 & Motor 3 running forward at 3500 & Motor 2 & Motor 4 running backward at 3500 for 3 seconds");
  setMotorSpeed(3500, -3500, 3500, -3500);
  delay(3000);

  Serial.println("All motor stop for 0.5 second");
  setMotorSpeed(0, 0, 0, 0);
  delay(500); // Delay 500ms before next test

  Serial.println("Motor 1 & Motor 3 running backward at 3500 & Motor 2 & Motor 4 running forward at 3500 for 3 seconds");
  setMotorSpeed(-3500, 3500, -3500, 3500);
  delay(3000);

  Serial.println("All motor stop");
  setMotorSpeed(0, 0, 0, 0);

  // Delay 5 second before starting the test again
  Serial.println("Test completed. Restarting in 5 second.");
  delay(5000);
}
