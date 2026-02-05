// Teensy 4.1 - analog input/adc test
// Samples A0 at a fixed rate and streams data over USB

const int analogPin = A0;
const uint32_t sampleRate = 50000;
const uint32_t samplePeriod_us = 1000000 / sampleRate;

elapsedMicros sampleTimer;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogReadAveraging(1);
  delay(1000);
}

void loop() {
  if (sampleTimer >= samplePeriod_us) {
    sampleTimer = 0;

    uint16_t sample = analogRead(analogPin);
    Serial.println(sample);
  }
}
