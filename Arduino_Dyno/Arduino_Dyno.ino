/*
Dynometer Code for Tony B
Written by Michael Caiozzo

Note Optical Sensor must be hooked up
to Pin 2

*/

#define opticalSensor 2
#define LED 13

unsigned long was = 0; // Used to store or "now time"
unsigned long now = 0;

int  counter    = 0; // Store number of beam breaks
int  RPS        = 0; // Revolutions Perr Second
int  LED_State  = 0; // Used to Toggle Led ON and off

//LN298 CODE
#define ENA 8
#define IN1 9
#define IN2 10

void setup() {
  
  pinMode(opticalSensor, INPUT);// Set optical Sensor to INPUT 
  pinMode(LED, OUTPUT);         // Set LED to OUTPUT
  Serial.begin(9600);           //Intialize Serial Monitor

  // Activate Pin 2's interupt to call ISR1 function on the Rising edge of signal
  attachInterrupt(digitalPinToInterrupt(opticalSensor), ISR1, RISING);
 
  //LN298 Code Setup
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  //LN298 Code Turn Motor On, Spin foward
  digitalWrite(ENA, HIGH);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

}

void loop() {
  was = millis();           // Set was to current time
  LED_State = ~LED_State;   // Invert State of LED

while( (millis() - was) < 1000){
  digitalWrite(LED, LED_State); // Toggle LED on and off based on LED_State
} 

 RPS = (counter/2);             // Calculate RPS by dividing toal # of beam breaks by number of slits in wheel
 now = millis();
 counter = 0;                 // Reset counter

//  Serial.print("RPS ");
 Serial.print(RPS);
//Serial.print(" Time ");
 Serial.print(" "); 
 Serial.println(now);
 counter = 0;                 // Reset counter

}

//Interupt Service Routine Function
void ISR1 (){
  counter +=1; //Increment counter
}

