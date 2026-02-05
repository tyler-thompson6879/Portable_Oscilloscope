const int buttonPin = 2;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  bool currentState = digitalRead(buttonPin);

  if (lastButtonState == HIGH && currentState == LOW) {
    Serial.println("Button Press Detected");
    delay(200); // debounce
  }

  lastButtonState = currentState;
}
