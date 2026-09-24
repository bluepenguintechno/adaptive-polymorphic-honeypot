#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// ===== CONFIGURATION =====
const char* ssid = "APH-Decoy";
const char* password = "12345678";

ESP8266WebServer server(80);

// ===== 10 FAKE IDENTITIES =====
String identities[] = {
  "TP-Link Router",
  "Hikvision Camera",
  "HP Printer",
  "Netgear Switch",
  "D-Link Modem",
  "Logitech Webcam",
  "Honeywell Thermostat",
  "Amazon Speaker",
  "Samsung TV",
  "Ring Doorbell"
};

int totalIdentities = 10;
int currentIdentity = 0;
unsigned long lastChange = 0;
const unsigned long changeInterval = 10000; // 10 seconds

int attackCount = 0;
String lastAttackerIP = "None";

// ===== FAKE LOGIN PAGE =====
String getLoginPage() {
  String page = "<!DOCTYPE html><html><head><title>";
  page += identities[currentIdentity];
  page += "</title></head><body style='background:#0d1117;color:#fff;font-family:Arial;text-align:center;padding:50px;'>";
  page += "<h1 style='color:#f0b429;'>" + identities[currentIdentity] + "</h1>";
  page += "<p>Please login to continue</p>";
  page += "<form><input type='text' placeholder='Username' style='padding:10px;margin:5px;'><br>";
  page += "<input type='password' placeholder='Password' style='padding:10px;margin:5px;'><br>";
  page += "<button style='padding:10px 30px;background:#f0b429;border:none;margin-top:10px;'>Login</button></form>";
  page += "</body></html>";
  return page;
}

// ===== DASHBOARD PAGE =====
String getDashboard() {
  String page = "<!DOCTYPE html><html><head><title>APH Dashboard</title>";
  page += "<meta http-equiv='refresh' content='2'>";
  page += "<style>body{background:#0d1117;color:#e6edf3;font-family:Arial;padding:20px;text-align:center;}";
  page += "h1{color:#f0b429;} .card{background:#161b22;border:1px solid #30363d;border-radius:10px;padding:20px;margin:15px auto;max-width:500px;}";
  page += ".value{color:#7ee787;font-size:24px;font-weight:bold;} .label{color:#8b949e;font-size:12px;}</style></head><body>";
  page += "<h1>APH DASHBOARD</h1>";
  page += "<div class='card'><div class='label'>CURRENT STATE</div><div class='value'>" + identities[currentIdentity] + "</div></div>";
  page += "<div class='card'><div class='label'>TOTAL ATTACKS</div><div class='value'>" + String(attackCount) + "</div></div>";
  page += "<div class='card'><div class='label'>LAST ATTACKER</div><div class='value'>" + lastAttackerIP + "</div></div>";
  page += "</body></html>";
  return page;
}

// ===== HANDLE REQUESTS =====
void handleRoot() {
  attackCount++;
  lastAttackerIP = server.client().remoteIP().toString();
  Serial.print("ATTACK|");
  Serial.println(lastAttackerIP);
  server.send(200, "text/html", getLoginPage());
}

void handleDashboard() {
  server.send(200, "text/html", getDashboard());
}

void handleNotFound() {
  attackCount++;
  lastAttackerIP = server.client().remoteIP().toString();
  Serial.print("SCAN|");
  Serial.println(server.uri());
  server.send(404, "text/plain", "Not Found");
}

// ===== SETUP =====
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("APH DECOY STARTING...");
  
  WiFi.softAP(ssid, password);
  Serial.print("AP IP: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("Connect to APH-Decoy and open 192.168.4.1/dashboard");
  
  server.on("/", handleRoot);
  server.on("/dashboard", handleDashboard);
  server.onNotFound(handleNotFound);
  server.begin();
  
  Serial.println("DECOY READY");
}

// ===== LOOP =====
void loop() {
  server.handleClient();
  
  if (millis() - lastChange > changeInterval) {
    lastChange = millis();
    currentIdentity = (currentIdentity + 1) % totalIdentities;
    Serial.print("MUTATE|");
    Serial.println(identities[currentIdentity]);
  }
}