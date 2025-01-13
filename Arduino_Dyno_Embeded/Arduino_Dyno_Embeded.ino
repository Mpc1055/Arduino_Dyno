#define opticalSensor 2
#define LED 13

//LN298 CODE
#define ENA 8
#define IN1 9
#define IN2 10

float counter = 0;
float rps = 0;

long TCNT1_value = 0;
int  TCCR1B_value = 0;

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

  //calculate timer 1 values (tcnt1 & tccR1b)
  timer1_init(250 * pow(10,-3));

  //Timer 1 Setup
  TCCR1A = 0;
  TCCR1B = TCCR1B_value;
  TCNT1 = TCNT1_value;   
  TIMSK1 = 1;
  interrupts();

}

void loop() {

}

//Timmer Overflow
ISR(TIMER1_OVF_vect){//______ISR for when timer1A interrupts
  TCNT1 = TCNT1_value; 
  rps = (counter/2) *20;
  counter = 0;
  Serial.println(rps);
 
}
void ISR1 (){
  counter +=1; //Increment counter
}

void timer1_init(float period){
  double clk = 1.0/16000000;

    // No Prescale
  if ( (period / clk ) < 65535 ){
    TCCR1B_value = 1;
    TCNT1_value = 65535 - (period / clk);
    }
    //8 Prescale
    else if ((period / (clk* 8) ) < 65535 ){
      TCCR1B_value = 2;
      TCNT1_value = 65535 - (period / (clk* 8));
    } 

    //64 Prescale
    else if ((period / (clk* 64) )< 65535 ){
      TCCR1B_value = 3;
      TCNT1_value = 65535- (period / (clk* 64));
    } 
    // 256 Prescale
    else if ((period / (clk* 256) )< 65535 ){
      TCCR1B_value = 4;
      TCNT1_value = (pow(2,16)-1) - (long(period / (clk* 256)));
    }
    // 1024 Prescale 
    else if ( (period / (clk* 1024)) < 65535 ){
      TCCR1B_value = 5;
      TCNT1_value = 65535 - (period / (clk* 1024));
    }  
    else {
      Serial.println("Invalid Period Selected");
      Serial.println("Max is 4194 ms");
    }


}

