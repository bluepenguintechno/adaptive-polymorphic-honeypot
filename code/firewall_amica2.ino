#include <ESP8266WiFi.h>

// ===== BLOCKED IP STORAGE =====
String blockedIPs[50];
int blockCount = 0;

void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("FIREWALL STARTING...");
  
  WiFi.begin("APH-Decoy", "12345678");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println();
  Serial.println("FIREWALL CONNECTED");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
  Serial.println("Monitoring for attackers...");
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    
    if (data.startsWith("ATTACK")) {
      String ip = data.substring(7);
      
      if (blockCount < 50) {
        blockedIPs[blockCount] = ip;
        blockCount++;
        Serial.print("BLOCKED|");
        Serial.println(ip);
        Serial.print("Total blocked: ");
        Serial.println(blockCount);
      }
    }
  }
  
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 5000) {
    lastPrint = millis();
    Serial.print("Firewall active. Blocked IPs: ");
    Serial.println(blockCount);
  }
}