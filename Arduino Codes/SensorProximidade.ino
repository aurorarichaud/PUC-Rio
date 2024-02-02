int sensorProximidade = 31;
void setup() {
  // Setup code here, to run once:
  Serial.begin(9600);
  pinMode(sensorProximidade, INPUT);
  digitalRead(sensorProximidade) == LOW;
}

void loop() {
  // Main code here, to run repeatedly:
  int valorDigital = digitalRead(sensorProximidade);
  if (valorDigital == HIGH) {
    Serial.println("Objeto Distante");
  }
  else {
    Serial.println("Objeto Perto");
  }
  delay(200);
}
