#define RPWM 5   // Right motor forward
#define LPWM 6   // Right motor reverse

#define RPWM2 9  // Left motor forward
#define LPWM2 10 // Left motor reverse

char data;

unsigned long lastSignalTime = 0;

void setup() {
  Serial.begin(9600);

  pinMode(RPWM, OUTPUT);
  pinMode(LPWM, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
}

void loop() {

  if (Serial.available()) {
    data = Serial.read();
    lastSignalTime = millis();

    switch (data) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
    }
  }

  // Safety: signal lost → STOP
  if (millis() - lastSignalTime > 2000) {
    stopMotors();
  }
}

void forward() {
  analogWrite(RPWM, 200);
  analogWrite(LPWM, 0);

  analogWrite(RPWM2, 200);
  analogWrite(LPWM2, 0);
}

void backward() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 200);

  analogWrite(RPWM2, 0);
  analogWrite(LPWM2, 200);
}

void left() {
  analogWrite(RPWM, 200);
  analogWrite(LPWM, 0);

  analogWrite(RPWM2, 0);
  analogWrite(LPWM2, 0);
}

void right() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  analogWrite(RPWM2, 200);
  analogWrite(LPWM2, 0);
}

void stopMotors() {
  analogWrite(RPWM, 0);
  analogWrite(LPWM, 0);

  analogWrite(RPWM2, 0);
  analogWrite(LPWM2, 0);
}
