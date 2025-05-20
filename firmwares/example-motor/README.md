# Kết nối động cơ DC với mạch VIA

Bạn có thể kết nối động cơ vào 1 trong 4 cổng động cơ trên mạch công suất
**Lưu ý:** ghi nhớ kênh PWM của các cổng động cơ
![](via_motorshield_ports.png)

## Các bước khởi tạo
**Sử dụng thư viện Adafruit PCA9685:**
Link tải thư viện
*https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library*
Tài liệu
http://adafruit.github.io/Adafruit-PWM-Servo-Driver-Library/html/class_adafruit___p_w_m_servo_driver.html

**Ví dụ mẫu điều khiển servo:**
*File->examples->Adafruit-PWM-Servo-Driver-Library>servo*
**Ví dụ mẫu băm xung PWM:**
*File->examples->Adafruit-PWM-Servo-Driver-Library->PWMtest*
**Tài liệu tham khảo về PWM:**
*http://arduino.vn/reference/xung-pwm*

**Khai báo thư viện**
``` cpp
#include <Wire.h> //thư viện I2c của Arduino, do PCA9685 sử dụng chuẩn giao tiếp i2c nên thư viện này bắt buộc phải khai báo 
#include <Adafruit_PWMServoDriver.h> // thư viện PCA9685
```

**Khởi tạo class của thư viện với địa chỉ gốc**
``` cpp
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
```

Hoặc khởi tạo với địa chỉ tùy biến khi kết nối nhiều mạch
``` cpp
Adafruit_PWMServoDriver pwm1 = Adafruit_PWMServoDrive(0x70); //địa chỉ i2c
Adafruit_PWMServoDriver pwm2 = Adafruit_PWMServoDrive(0x71);
```

**Khởi tạo trong hàm setup**
``` cpp
pwm.begin(); //khởi tạo PCA9685 

// cài đặt tần số dao động 
pwm.setOscillatorFrequency(27000000); 

// cài đặt tần số PWM. Tần số PWM có thể được cài đặt trong khoảng 24-1600 HZ, tần số này được cài đặt tùy thuộc vào nhu cầu xử dụng. Để điều khiển được cả servo và động cơ DC cùng nhau, tần số PWM điều khiển được cài đặt trong khoảng 50-60Hz.
pwm.setPWMFreq(50);


// cài đặt tốc độ giao tiếp i2c ở tốc độ cao nhất(400 Mhz). Hàm này có thể bỏ qua nếu gặp lỗi hoặc không có nhu cầu tử dụng I2c tốc độ cao
Wire.setClock(400000); 
```

## Điều khiển động cơ DC

Đối với mạch VIA Bánh Mì trong cuộc thi VRC 2024, động cơ DC sẽ được điều khiển bằng hàm `pwm.setPin(channel, value, invert)` trong đó:
- `channel`: là số kênh của PCA9685, tương ứng với cổng động cơ DC trên mạch VIA Bánh Mì
- `value`: là giá trị PWM từ 0 đến 4095, tương ứng với tốc độ quay của động cơ DC
- `invert`: là giá trị boolean, mặc định là `false`, nếu `true` thì giá trị PWM sẽ bị đảo ngược. Trong trường hợp sử dụng mạch VIA Bánh Mì, giá trị này không cần thiết phải thay đổi.
Ví dụ: Để động cơ DC có chân 8, 9 quay với tốc độ 50%
``` cpp
pwm.setPin(8, 2048);
pwm.setPin(9, 0);

// Hoặc điều khiển ngược lại

pwm.setPin(8, 0);
pwm.setPin(9, 2048);
```

## Ví dụ mẫu điều khiển động cơ 

[Firmware .ino](/firmwares/example-motor/makerbot-2024-motor-test/makerbot-2024-motor-test.ino)