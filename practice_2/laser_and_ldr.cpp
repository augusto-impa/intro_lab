// <--> CONFIG <-->
const int light_limiar = 300; // limiar to count or not count the time
// <--> CONFIG <-->

void setup() {
  Serial.begin(9600);
}

int step = 0;

void loop() {
  float r = analogRead(A0);
  float t = 0;
  //Serial.println(analogRead(A0));
  //return;

  if (!step && r < light_limiar){step += 1;};
  if (step == 1 && r > light_limiar)
  {
    step += 1;
    t = millis();
  }
  if (step == 2 && r < light_limiar){step += 1;};
  if (step == 3 && r > light_limiar)
  {
    step = 0;
    t = millis() - t;
    Serial.println("time_: " + String(t));
    Serial.println("gravity_: " + String(2/(t*t)));
    Serial.println("");
  }
}
