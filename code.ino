#define irSensorPin 3
#define buzzerPin 2
#define relayPin 4

unsigned long detectionStartTime = 0;
bool buzzerActivated = false;

void setup() {
  Serial.begin(9600);
  pinMode(irSensorPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);  // Ensure relay is initially off
}

void loop() {
  int irSensorValue = digitalRead(irSensorPin);

  if (irSensorValue == HIGH) {
    // Object detected
    delay(10);  // Debouncing delay

    if (digitalRead(irSensorPin) == HIGH) {
      // Object detected for 5 seconds
      unsigned long elapsedTime = millis() - detectionStartTime;

      if (elapsedTime >= 5000 && !buzzerActivated) {
        digitalWrite(buzzerPin, HIGH);
        delay(5000);  // Buzzer on for 5 seconds
        digitalWrite(buzzerPin, LOW);
        buzzerActivated = true;
        digitalWrite(relayPin, HIGH);  // Turn off motor after buzzer
      }
    }
  } else {
    // Object not detected
    digitalWrite(buzzerPin, LOW);
    buzzerActivated = false;
    detectionStartTime = millis();  // Reset detection start time
  }
}
