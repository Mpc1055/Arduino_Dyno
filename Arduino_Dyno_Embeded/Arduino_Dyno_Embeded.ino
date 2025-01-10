

#define opticalSensor 2
#define LED 13

//LN298 CODE
#define ENA 8
#define IN1 9
#define IN2 10


int counter = 0;
int rps = 0;


void setup() {

   //LN298 Code Setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //LN298 Code Turn Motor On, Spin foward
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  
  attachInterrupt(digitalPinToInterrupt(opticalSensor), ISR1, RISING);

  Serial.begin(9600);

  TCCR1A = 0;
  TCCR1B = 4;
  TCNT1 = 62411;   
  TIMSK1 = 1;
  interrupts();
}

void loop() {

}

//Timmer Overflow
ISR(TIMER1_OVF_vect){//______ISR for when timer1A interrupts

  TCNT1 = 62411; 
  rps = (counter/2) *20;
  counter = 0;
  Serial.print(millis());
  Serial.print(" ");
  Serial.println(rps);
 
}
void ISR1 (){
  counter +=1; //Increment counter
}


