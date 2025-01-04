int counter = 0;

void setup() {
  
  Serial.begin(9600);
 
  TCCR1A = 0;
  TCCR1B = 4;
  TCNT1 = 3036;   
  TIMSK1 = 1;
  interrupts();
  
}

void loop() {

}


ISR(TIMER1_OVF_vect){//______ISR for when timer1A interrupts

  TCNT1 = 3036;   
  Serial.println("1 second");

}
