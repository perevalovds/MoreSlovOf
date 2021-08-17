byte pedal_pin1 = 2;
byte pedal_pin2 = 3;


void setup() {
  Serial.begin(57600);
  Serial.println("Pedal, pins "); Serial.print(pedal_pin1); Serial.print(" "); Serial.println(pedal_pin2);  
  pinMode(pedal_pin1, OUTPUT);
  digitalWrite(pedal_pin1,0);
  pinMode(pedal_pin2, INPUT_PULLUP);

  print_state();
}

byte state = 0;

void print_state() {
  Serial.println(state);
}

void loop() {
  byte v = digitalRead(pedal_pin2);
  if (v != state) {
    state = v;
    print_state();
  }
  delay(3);
}
