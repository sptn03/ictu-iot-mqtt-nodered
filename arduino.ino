#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>

// Cấu hình WiFi
const char* ssid = "Linh";
const char* password = "huongchuyen19";

// Cấu hình MQTT
const char* mqtt_server = "nz03.com";
const int mqtt_port = 1883;
const char* mqtt_user = "";
const char* mqtt_password = "";

// Cấu hình chân
#define RELAY1_PIN D1
#define RELAY2_PIN D2
#define DHTPIN D4
#define DHTTYPE DHT11  // Hoặc DHT11 tùy loại cảm biến của bạn

// Khởi tạo đối tượng
WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHTPIN, DHTTYPE);

unsigned long lastMsg = 0;
const long interval = 5000;  // Gửi dữ liệu mỗi 5 giây

void setup() {
  Serial.begin(115200);
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  dht.begin();
  
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
}

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Đang kết nối tới ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Đã kết nối WiFi");
  Serial.println("Địa chỉ IP: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  
  if (String(topic) == "relay1") {
    digitalWrite(RELAY1_PIN, message.equals("ON") ? HIGH : LOW);
  } else if (String(topic) == "relay2") {
    digitalWrite(RELAY2_PIN, message.equals("ON") ? HIGH : LOW);
  }
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Đang kết nối MQTT...");
    if (client.connect("ArduinoClient", mqtt_user, mqtt_password)) {
      Serial.println("đã kết nối");
      client.subscribe("relay1");
      client.subscribe("relay2");
    } else {
      Serial.print("lỗi, rc=");
      Serial.print(client.state());
      Serial.println(" thử lại sau 5 giây");
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;
    
    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println("Lỗi đọc từ cảm biến DHT!");
      return;
    }

    char tempString[8];
    char humString[8];
    dtostrf(t, 1, 2, tempString);
    dtostrf(h, 1, 2, humString);

    client.publish("temperature", tempString);
    client.publish("humidity", humString);

    Serial.print("Nhiệt độ: ");
    Serial.print(t);
    Serial.print(" °C, Độ ẩm: ");
    Serial.print(h);
    Serial.println(" %");
  }
}