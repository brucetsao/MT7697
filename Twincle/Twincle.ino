#define LedPin 2
void setup() {
  // put your setup code here, to run once:
      pinMode(LedPin,OUTPUT) ;
      digitalWrite(LedPin,LOW) ;
}

void loop() {
  // put your main code here, to run repeatedly:
       digitalWrite(LedPin,HIGH) ;
       delay(2000) ;
        digitalWrite(LedPin,LOW) ;
        delay(1000) ;
}
