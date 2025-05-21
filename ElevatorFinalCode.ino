#include <Stepper.h>

const int stepsPerRevolution = 2048;
const int motSpeed = 13;
const long pasiEtaj = 5000;

const int buton1=4; //etaj 0
const int buton2=5; //etaj 1
const int buton3=6; //etaj 2

int etajCurent=1;

Stepper myStepper(stepsPerRevolution, 8, 10, 9, 11);

int yPin = A1;
int buton_joystick = 7;
int yVal;
int buttonStateJ;
int nrRotatii=0; //rotatiile pe care le am facut cu joystick ul

const int led0=12;
const int led1=2;
const int led2=3;

void setup() {
  Serial.begin(9600);

  pinMode(buton1, INPUT_PULLUP);
  pinMode(buton2, INPUT_PULLUP);
  pinMode(buton3, INPUT_PULLUP);

  myStepper.setSpeed(motSpeed);

  pinMode(yPin, INPUT);
  pinMode(buton_joystick, INPUT_PULLUP);

  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  digitalWrite(led0, HIGH);
}

void loop() {
  if (digitalRead(buton1) == LOW) {
    goToEtaj(1);
    delay(500);
  }
  else if (digitalRead(buton2) == LOW) {
    goToEtaj(2);
    delay(500);
  }
  else if (digitalRead(buton3) == LOW) {
    goToEtaj(3);
    delay(500);
  }
  yVal = analogRead(yPin); //522 mijlocul
  //0 1023
  if(digitalRead(buton_joystick) == LOW) {
    myStepper.step(-nrRotatii);
    delay(500);
    Serial.print("S-a revenit la etajul: ");
    Serial.println(etajCurent-1);
    nrRotatii=0;
  }
  if (yVal < 450) {
    if((etajCurent-1)*5000+nrRotatii!=0)
    {
      myStepper.step(-10);
      delay(10);
      nrRotatii=nrRotatii-10;
    }
}
else if (yVal > 570) {
  if((etajCurent-1)*5000+nrRotatii!=10000)
  {
    myStepper.step(10);
    delay(10);
    nrRotatii=nrRotatii+10;
  }
  
}
}

void goToEtaj(int etajDorit) {
  int diferenta=etajDorit-etajCurent;

  if (diferenta == 0) 
  {
    if(etajCurent==1)
    digitalWrite(led0, LOW);
    if(etajCurent==2)
      digitalWrite(led1, LOW);
    if(etajCurent==3)
      digitalWrite(led2, LOW);
    
    delay(500);

    if(etajDorit==1)
      digitalWrite(led0, HIGH);
    if(etajDorit==2)
      digitalWrite(led1, HIGH);
    if(etajDorit==3)
      digitalWrite(led2, HIGH);
    return;
  }
  

  int pasi=diferenta*pasiEtaj;

  myStepper.step(pasi);
  if(etajCurent==1)
    digitalWrite(led0, LOW);
  if(etajCurent==2)
    digitalWrite(led1, LOW);
  if(etajCurent==3)
    digitalWrite(led2, LOW);

  if(etajDorit==1)
    digitalWrite(led0, HIGH);
  if(etajDorit==2)
    digitalWrite(led1, HIGH);
  if(etajDorit==3)
    digitalWrite(led2, HIGH);

  etajCurent=etajDorit;

  Serial.print("Etajul: ");
  Serial.println(etajCurent-1);
}
