# KẾT THÚC MÔN IOT - NHÓM 3
## DỰ ÁN "TÌM HIỂU VỀ MQTT VÀ ỨNG DỤNG"

### 1. Cài đặt Arduino IDE và ESP8266

1. Tải và cài đặt Arduino IDE từ [trang chủ Arduino](https://www.arduino.cc/en/software)

2. Thêm hỗ trợ cho ESP8266:
   - Mở Arduino IDE
   - Vào File → Preferences
   - Thêm URL sau vào Additional Board Manager URLs:
     ```
     http://arduino.esp8266.com/stable/package_esp8266com_index.json
     ```
   - Vào Tools → Board → Boards Manager
   - Tìm và cài đặt "ESP8266"

3. Cài đặt thư viện cần thiết:
   - Vào Tools → Manage Libraries
   - Tìm và cài đặt các thư viện sau:
     - PubSubClient
     - DHT sensor library
     - Adafruit Unified Sensor

4. Cấu hình board:
   - Board: "NodeMCU 1.0 (ESP-12E Module)"
   - Upload Speed: "115200"
   - Port: Chọn cổng COM kết nối với ESP8266

### 2. Cài đặt Node-RED

1. Cài đặt Node.js từ [nodejs.org](https://nodejs.org/)

2. Cài đặt Node-RED:
   ```bash
   npm install -g --unsafe-perm node-red
   ```

3. Khởi động Node-RED:
   ```bash
   node-red
   ```

4. Truy cập Node-RED tại: http://localhost:1880

5. Cài đặt các node cần thiết:
   - Mở Menu → Manage palette
   - Cài đặt các node sau:
     - node-red-dashboard
     - node-red-contrib-mqtt-broker

### 3. Cấu hình và Chạy Chương Trình

1. Cấu hình ESP8266:
   - Mở file arduino.ino trong Arduino IDE
   - Chỉnh sửa thông tin WiFi:
     ```cpp
     const char* ssid = "Tên_WiFi_Của_Bạn";
     const char* password = "Mật_Khẩu_WiFi";
     ```
   - Upload code lên ESP8266

2. Cấu hình Node-RED:
   - Import flow từ file nodered.json
   - Cấu hình MQTT broker:
     - Double-click vào node MQTT
     - Cập nhật Server: "nz03.com"
     - Port: 1883
   - Deploy flow

3. Kiểm tra hoạt động:
   - Mở Dashboard UI tại: http://localhost:1880/ui
   - Theo dõi nhiệt độ, độ ẩm và điều khiển relay
   - Kiểm tra Serial Monitor trong Arduino IDE để debug

### 4. Sơ đồ Kết nối Phần cứng

1. Kết nối DHT11:
   - VCC → 3.3V
   - GND → GND
   - DATA → D4

2. Kết nối Relay:
   - Relay 1: D1
   - Relay 2: D2
   - VCC → 3.3V
   - GND → GND

