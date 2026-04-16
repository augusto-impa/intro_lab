// <--> CONFIGURAÇÕES <-->
int sonars[2][2] = {
  {2, 3},
  {5, 4}
  // primeiro valor = trigger_pin, segundo valor = echo_pin
  // {1,2} => trigger_pin = 1 & echo_ping = 2 ;)
};

// quantos centimetros próximo para considerar o objeto
int limiar_proximidade = 50;

// quantos centimetros afastado para desconsiderar o objeto
int limiar_afastamento = 150;
// <--> CONFIGURAÇÕES <-->


// --


// codigo importantissimo daqui pra baixo
float measure_cm(int sonar[2], float t = 10){ // define the function to measure a sonar
  float duration, distance;
  int trig = sonar[0];
  int echo = sonar[1];
  digitalWrite(trig, LOW); // turn off, turn on, turn off = send a pulse
  delayMicroseconds(t*0.2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(t);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = (duration*.0343)*0.5;
  return distance;
}

void setup() {
  for (int i = 0; i < 2; i++){ // config all the sonars based on the array "sonars"
    pinMode(sonars[i][0], OUTPUT);
    pinMode(sonars[i][1], INPUT);
  }
  //
  Serial.begin(9600);
}

int step = 0;
float t = 0;

void loop() {
  if (step==0 && measure_cm(sonars[0]) < limiar_proximidade){
    step += 1;
    Serial.println("<1> Objeto Obstruindo");
  }
  else if (step == 1 && measure_cm(sonars[0]) > limiar_afastamento){
    step += 1;
    t = micros();
    Serial.println("<1> Objeto Saiu");
  }
  else if (step == 2 && measure_cm(sonars[1]) < limiar_proximidade){
    step += 1;
    Serial.println("<2> Objeto Obstruindo");
  }
  else if (step == 3 && measure_cm(sonars[1]) > limiar_afastamento){
    step = 0;
    t = micros() - t;
    t = t * 0.000001;
    
    Serial.println("<2> Objeto Saiu");
    Serial.println();
    
    Serial.println("Tempo: " + String(t,4));
    Serial.println("G:     " + String(2/(t*t), 4));
	Serial.println();
  }
}
