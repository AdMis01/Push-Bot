#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int x;
  int y;
} struct_message;

struct_message joystickData;

uint8_t receiverMAC[] = {0x8C, 0x4F, 0x00, 0xAD, 0x6F, 0x54};

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Błąd inicjalizacji ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;


  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("reciver error");
    return;
  }
}

void loop() {
  joystickData.x = analogRead(34);
  joystickData.y = analogRead(35);

  esp_err_t result = esp_now_send(receiverMAC, (uint8_t *) &joystickData, sizeof(joystickData));

  if (result == ESP_OK) {
    Serial.print("x: ");
    Serial.print(joystickData.x);
    Serial.print(" y: ");
    Serial.println(joystickData.y);
  } else {
    Serial.println("sending error");
  }

  delay(100);
}
