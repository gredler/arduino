unsigned long time;
unsigned long count;

#ifndef cbi // clear register bit
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif

#ifndef sbi // set register bit
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

void setup() {
  Serial.begin(115200); // start talking to the computer
  Serial.println("Starting...");
  time = millis();
  count = 0;
  // set ADC prescale to 16 instead of the default of 128
  // sacrifices accuracy for speed
  // http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1208715493/11
  // see also ATmega328 datasheet sections 23.4 and 23.9.2
  sbi(ADCSRA, ADPS2);
  cbi(ADCSRA, ADPS1);
  cbi(ADCSRA, ADPS0);
}

// sample rate: 43.3 kHz when ADC prescale = 16
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

