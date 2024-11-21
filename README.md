# VIA VRC 2024
Mạch VIA Bánh Mì phiên bản tối ưu cho cuộc thi VRC 2024.

## 1. Hướng dẫn cài đặt môi trường cho Arduino IDE

### Kết nối mạch VIA B – Bánh Mì với máy tính

Khi kết nối với máy tính, máy tính sẽ tự động tiến hành cài đặt driver cho mạch VIA B, sau khi cài đặt driver xong trên máy tính sẽ xuất hiện thiết bị *Silicon Labs CP210x USB to UART Bridge.

### Xác định cổng COM đang được kết nối với mạch VIA B

***Đối với Windows***
- Sau khi cài đặt driver, mạch VIA B sẽ được gán với 1 cổng COM trên máy, điền bên cạnh tên thiết bị. Ví dụ: *Silicon Labs CP210x USB to UART Bridge (COM 3)*
- Để kiểm tra, mở Device Manager > Port (COM&LPT)
- Chú ý ghi nhớ tên cổng COM này

***Đối với Linux***
Có thể kiểm tra bằng lệnh *lsusb* và lệnh *ls /dev/ttyUSB* hoặc ls /dev/ttyACM**

***Đối với MacOS***
- Vào "System Preferences" -> "Security & Privacy"
- Ở góc dưới cửa sổ sẽ có chữ "System software from developer "SiLabs" was blocked from loading."
- Ấn nút "Allow"
- Khởi động lại Mac
- Sau khi hoàn thành Mac sẽ nhận cổng COM với tên “/dev/cu.SLAB_USBtoUART “

### Cài đặt môi trường lập trình cho VIA B với Arduino IDE
Do mạch VIA B sử dụng vi điều khiển ESP32, nên để lập trình cho mạch VIA bằng Arduino IDE, chúng ta cần cài đặt thêm ESP 32 qua Board Manager.
Hướng dẫn cài đặt ESP32 trên Arduino:
- Mở **Arduino IDE > File > Preferences**
- Chèn thêm đường link bên dưới tại phần **Additional Board Manager URLs:**
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json, http://arduino.esp8266.com/stable/package_esp8266com_index.json
```
- Vào **Tool** > **Board** > **Boards Manager**
- Tìm kiếm với từ khóa “esp32” , trong danh sách kết quả chọn “**ESP32 by Espressif Systems”** và nhấn **Install**

### Sử dụng ví dụ mẫu Blink để thử lập trình và nạp code cho mạch VIA
Khởi chạy phần mềm Arduino và thực hiện các bước sau:

- Mở File > Examples > Basics > Blink
- Khai báo chân LED_BUILTIN là chân số 13
- Tại mục Tools chọn Board > ESP32 Dev Module; Port > COM (chọn cổng COM đã xác định được ở bước trên).
- Verify và nạp code (dấu tick và mũi tên góc trên bên trái giao diện Arduino IDE):

``` cpp
#define LED_BUILTIN = 13; 

void setup() {
pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
delay(1000);                      // wait for a second
digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
delay(1000);                      // wait for a second
}
```

## 2. Firmware ví dụ cho cuộc thi VRC 2024

| Hướng dẫn | Đường dẫn |
| --- | --- |
| Firmware test động cơ | [README](/firmwares/example-motor/README.md) |
| Firmware test servo | [README](/firmwares/example-servo/README.md) |
| Firmware test PS2 và động cơ | [README](/firmwares/example-ps2/README.md) |
| Firmware kiểm tra I2C | [.ino](/firmwares/makerbot-2024-i2c-test/i2c_scan.ino) |