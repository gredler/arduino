unsigned long time;
unsigned long count;

void setup() {
  Serial.begin(115200); // start talking to the computer
  Serial.println("Starting...");
  time = millis();
  count = 0;
}

// sample rate: 8.3 kHz
// http://arduino.cc/en/Reference/analogRead
void loop() {
  int sample = analogRead(A0); // read from analog input 0
  count++;
  unsigned long delta = millis() - time;
  if(delta >= 1000) {
    Serial.println(count);
    Serial.println(sample);
    time = millis();
    count = 0;
  }
}

