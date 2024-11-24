#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SERVO_1_CHANNEL 2
#define SERVO_2_CHANNEL 3
#define SERVO_3_CHANNEL 4
#define SERVO_4_CHANNEL 5
#define SERVO_5_CHANNEL 6
#define SERVO_6_CHANNEL 7

#define NOTIFY_LED 13

void setServo(uint8_t channel, uint16_t pulse) {
  pwm.setPWM(channel, 0, pulse);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Servo test firmware for MakerBot 2024");

  pwm.begin();
  pwm.setPWMFreq(50); 

  pinMode(NOTIFY_LED, OUTPUT);
}

void loop() {
  /*
    In this test, we will sweep all servos from 0 to 4000 in steps of 100, with a delay of 300ms between each step. All servos will be tested sequentially from channel 2 to 7.
  */
  Serial.println("Servo test started in...");

  // Blink the LED to notify the test is started
  for (int i = 0; i < 3; i++) {
    Serial.println(3 - i);
    digitalWrite(NOTIFY_LED, HIGH);
    delay(500);
    digitalWrite(NOTIFY_LED, LOW);
    delay(500);
  }

  for (int i = 2; i < 8; i++) { // Test all servos sequentially

    // Set servo to 0 before test
    setServo(i, 0); 

    // Sweep from 0 to 4000 in steps of 100
    for (int j = 0; j <= 4000; j+= 100) { 
      Serial.print("Setting servo ");
      Serial.print(i);
      Serial.print(" running at ");
      Serial.println(j);
      setServo(i, j);
      delay(300); // Delay 300ms between each step
    }

    // Set servo to 0 after test
    setServo(i, 0); 

    Serial.println("Change to next servo...");
    
    // Blink the LED to notify the test is started
    digitalWrite(NOTIFY_LED, HIGH);
    delay(500);
    digitalWrite(NOTIFY_LED, LOW);
  }

  // Delay 5 second before starting the test again
  Serial.println("Test completed. Restarting in 5 second.");
  delay(5000);
}