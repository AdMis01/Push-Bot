#include <esp_now.h>
#include <WiFi.h>

int M1A = 21;
int M1B = 19;
int M2A = 18;
int M2B = 5;

typedef struct struct_message {
  int x;
  int y;
} struct_message;

struct_message incomingData;

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingDataBytes, int len) {
  memcpy(&incomingData, incomingDataBytes, sizeof(incomingData));
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Błąd inicjalizacji ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
  
  pinMode(M1A, OUTPUT);
  pinMode(M1B, OUTPUT);
  pinMode(M2A, OUTPUT);
  pinMode(M2B, OUTPUT);
  
  digitalWrite(M1A, LOW);
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);
  digitalWrite(M2B, LOW);
}

void loop() {
  Serial.print("x: ");
  Serial.print(incomingData.x);
  Serial.print(" y: ");
  Serial.println(incomingData.y);
  int x = incomingData.x;
  int y = incomingData.y;

  if (y > 3000) { 
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
  } 
  else if (y < 1500) { 
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
  } 
  else if (x > 3000) {
    digitalWrite(M1A, HIGH);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, HIGH);
  } 
  else if (x < 1500) {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, HIGH);
    digitalWrite(M2A, HIGH);
    digitalWrite(M2B, LOW);
  } 
  else {
    digitalWrite(M1A, LOW);
    digitalWrite(M1B, LOW);
    digitalWrite(M2A, LOW);
    digitalWrite(M2B, LOW);
  }
  delay(100);
}
