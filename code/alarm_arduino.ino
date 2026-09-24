#define ATTACK_SIGNAL 2
#define BLOCK_SIGNAL  3
#define BUZZER_PIN    8
#define LED_PIN       9

void setup() {
  Serial.begin(9600);
  pinMode(ATTACK_SIGNAL, INPUT);
  pinMode(BLOCK_SIGNAL, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  Serial.println("ALARM READY");
}

void loop() {
  if (digitalRead(ATTACK_SIGNAL) == HIGH) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    Serial.println("ATTACK DETECTED");
  }
  
  if (digitalRead(BLOCK_SIGNAL) == HIGH) {
    Serial.println("IP BLOCKED");
  }
  
  delay(100);
}