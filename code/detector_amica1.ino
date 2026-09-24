#include <ESP8266WiFi.h>

// ===== PINS =====
#define ATTACK_SIGNAL D1  // Connect to Arduino Pin 2
#define BLOCK_SIGNAL  D2  // Connect to Arduino Pin 3

// ===== DETECTION VARIABLES =====
int scanCount = 0;
unsigned long lastScan = 0;
const int scanThreshold = 5;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  pinMode(ATTACK_SIGNAL, OUTPUT);
  pinMode(BLOCK_SIGNAL, OUTPUT);
  digitalWrite(ATTACK_SIGNAL, LOW);
  digitalWrite(BLOCK_SIGNAL, LOW);
  
  Serial.println("DETECTOR STARTING...");
  
  WiFi.begin("APH-Decoy", "12345678");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("DETECTOR CONNECTED");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    
    if (data.startsWith("ATTACK")) {
      scanCount++;
      lastScan = millis();
      
      Serial.println("ATTACK DETECTED");
      
      digitalWrite(ATTACK_SIGNAL, HIGH);
      delay(500);
      digitalWrite(ATTACK_SIGNAL, LOW);
      
      if (scanCount >= scanThreshold) {
        blockAttacker();
        scanCount = 0;
      }
    }
  }
  
  if (millis() - lastScan > 3000) {
    scanCount = 0;
  }
}

void blockAttacker() {
  Serial.println("BLOCKING ATTACKER...");
  digitalWrite(BLOCK_SIGNAL, HIGH);
  delay(1000);
  digitalWrite(BLOCK_SIGNAL, LOW);
  Serial.println("IP BLOCKED");
}