int sound = A0;
int light = A1;
int nReset = 8;
int nStatus = HIGH;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(200);

  Serial.println("Start");
  
  pinMode(light, OUTPUT);
  pinMode(sound, OUTPUT);
  pinMode(nReset, INPUT_PULLUP);
  
  digitalWrite(light, nStatus);
  digitalWrite(sound, nStatus);
}

bool setStatus(String status) {
  bool isValid = false;
  
  if (status.equals("on")) {
    isValid = true;
    nStatus = LOW;
  }else if (status.equals("off")) {
    isValid = true;
    nStatus = HIGH;
  }else if (status.equals("toggle")) {
    isValid = true;
    nStatus = nStatus == HIGH ? LOW : HIGH;
  }

  if (isValid) {
    digitalWrite(light, nStatus);
    digitalWrite(sound, nStatus);
  }
  
  return isValid;
}

void resetInterrupt() {
  if (digitalRead(nReset))
    return;

  // Check the signal i times
  for(int i = 0; i < 7; i++) {
    delay(100);
    if (digitalRead(nReset))
      return;
  }
  
  if (nStatus == LOW) {
    setStatus("off");
    Serial.println("Reset");
  }
}

void loop() {
  resetInterrupt();
  
  while(Serial.available()) {
    
    String str = Serial.readStringUntil('\n');
    bool isValid = setStatus(str);

    if (isValid) {
      Serial.println("ok");
    }
  }
}
