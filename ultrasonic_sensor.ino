int trigpin=10;
int echopin=9;
int ledpin=13;
float duration;

float distance;
void setup() {
  Serial.begin(9600);
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(ledpin,OUTPUT);
  
  
  // put your setup code here, to run once:

}

void loop() {
  digitalWrite(ledpin,LOW); 
  digitalWrite(trigpin,LOW);
  delay(2);
  digitalWrite(trigpin,HIGH);
  delay(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=duration*.034/2;
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" ");
  delay(500); 
  if(distance>=30)
  {digitalWrite(ledpin,LOW);
    }
    delay(50);
  if(distance<30)
  {digitalWrite(ledpin,HIGH);
    }
  
  delay(50);
  // put your main code here, to run repeatedly:

}
