// https://www.tinkercad.com/things/igzCqjypuRp-one-sonar-measure-the-local-gravity?sharecode=cTpmCBnQSDFXFy6wpis0XhbHT21W4m1dzYUPCdWXlvI
// <--> CONFIGURAÇÕES <-->
float distancia_prox = 10; // distancia minima para começar
float distancia_max = 100; // distancia maxima de medição
int delay_micros = 0; // delay entre as medições (0 = nulo)
const int max_values = 50; // máximo de valores para captação

int trig_pin = 4; // pino trig do sonar
int echo_pin = 3; // pino echo do sonar
// <--> CONFIGURAÇÕES <-->

float measure_cm(float t = 10){ // define the function to measure a sonar
  float duration, distance;

  digitalWrite(trig_pin, LOW); // turn off, turn on, turn off = send a pulse
  delayMicroseconds(t*0.2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(t);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH);
  distance = (duration*.0343)*0.5;
  return distance;
}

void setup() {
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  //
  Serial.begin(9600);
}

float tempo_inicial = 0;
float valores[max_values][2];
int v = 0;
int step = 0;

void loop() {
  float d = measure_cm();
  
  if (step == 0 && d < distancia_prox){
  	step += 1;
    Serial.println("<#> Objeto Detectado");
  }
  if (step == 1 && d > distancia_prox+5){
    step += 1;
    tempo_inicial = micros();
    Serial.println("<#> Objeto Saiu");
  }
  
  while(step == 2 && d < distancia_max){
    if (v == (max_values-1)) {break;}
    
    v += 1;
    valores[v][0] = measure_cm();
    valores[v][1] = (micros()-tempo_inicial)*0.000001;
    if (delay_micros) {delayMicroseconds(delay_micros);}
  }
  
  if (step == 2 && (v == (max_values-1) || d >= distancia_max)) {
    step = 3;
  }
  
  if (step == 3) {
    step = 0;
    tempo_inicial = 0;
    Serial.println("<#> Valores Obtidos");
    
    for (int i = 0; i < max_values; i++){
      Serial.println(String(valores[i][0],4) + " " +  String(valores[i][1],4));
    }
    v = 0;
  }
}
