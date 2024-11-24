# Hướng dẫn kết nối và điều khiển servo với mạch VIA

Bạn có thể kết nối servo vào 1 trong 6 cổng servo trên mạch công suất
**Lưu ý:** ghi nhớ kênh PWM của các cổng servo
![](via_motorshield_ports.png)

## Các bước khởi tạo
Để điều khiển servo, chúng ta vẫn sử dụng thư viện Adafruit_PWMServoDriver và thực hiện các bước khởi tạo tương tự động cơ DC thường đã hướng dẫn ở bài trước. Lưu ý sử dụng xung PWM ở tần số 50Hz.

```cpp
pwm.setPWMFreq(50);
```

Cách điều khiển góc (đối với Servo 180) dựa theo độ rộng xung bật như hình bên

Đối với Servo 360 ta không điều khiển được góc mà chỉ điều khiển được tốc độ quay và chiều quay dựa vào độ rộng xung bật tương tự như servo 180

## Điều khiển servo sử dụng hàm băm xung PWM
Tính độ giá trị PWM dựa theo thời gian ví dụ ở góc 180 độ

```cpp
pwm_val = T_on/(Ts/4096) = 2/(20/4096) = 409.6
```

Vậy để set góc 180 độ ta cần sử dụng:

```cpp
pwm.setPWM(5, 0, 410); // chọn kênh servo số 5
```

## Điều khiển sử dụng hàm set thời gian
Đưa vào giá trị thời gian chính xác ở đơn vị micro giây

```cpp
pwm.writeMicroseconds(kênh PWM, microsec); //Microsec, thời gian xung ở mức cao trong 1 chu kì (trạng thái bật)
```

Ví dụ set góc 180 độ:

```cpp
pwm.writeMicroseconds(5, 2000); // chọn kênh servo số 5
```
## Ví dụ mẫu điều khiển servo

[Firmware .ino](/firmwares/example-servo/makerbot-2024-servo-test/makerbot-2024-servo-test.ino)