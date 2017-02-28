unsigned long ct1,ct2,pct1,pct2,sct1,sct2;
int current,previous;
int accped1,accped2,accavg,brakeped,hv;
//digital pins
int interlock = 3;
int throttle_sw = 4;
int acc_out = 5;

int brake_out = 6;
int prech = 7;
int main_rel = 8;
int buzzer = 9;
int tsal_in = 10;
int ctrl_rel = 11;
int add_sw_in = 12;
int ok_24 = 2;

//analog pins
int accped1_in = A3;
int accped2_in = A2;
int brakeped_in = A1;
int HV = A0;

  
bool check(){
  
  if ((accped1<(0.9*1023)&&accped1>(0.1*1023))&&(accped2<(0.9*1023)&&accped2>(0.1*1023))&&(brakeped<(0.9*1023)&&brakeped>(0.1*1023))&&digitalRead(tsal_in)==HIGH&&abs((accped1-accped2)/accavg)<0.1){
      ct1 = millis();
      while  ((accped1<(0.9*1023)&&accped1>(0.1*1023))&&(accped2<(0.9*1023)&&accped2>(0.1*1023))&&(brakeped<(0.9*1023)&&brakeped>(0.1*1023))&&digitalRead(tsal_in)==HIGH&&abs((accped1-accped2)/accped1)<0.1!=true)
     { ct2 = millis();
      if(ct1-ct2>10)
      break;}
      if (ct1-ct2>8)
      {
      return true;
      }
    else{
      return false;}
     }
   }
bool ok24(){
  current = digitalRead(ok_24);
  if(current==HIGH&&previous==LOW)
  {return true;}
  else
  {return false;
    }
   previous=current;
  
  }
bool plauscheck(){

  if((accavg>0.3*(1023))&&(brakeped>0.15*1023)){
   pct1 = millis();
      while ((accavg>0.3*(1023))&&(brakeped>0.15*1023))
     { pct2 = millis();
      if(pct1-pct2>10)
      break;}
      if(pct1-pct2>8)
      {return false;}
      else{return true;}
  }
}
void buzer()      
      {
    digitalWrite(buzzer,1);     
    }
void buzzerstop(){
    digitalWrite(buzzer,0); 
    }
void precharge(){
     digitalWrite(main_rel,0);
    digitalWrite(prech,1);
    delay(5000);
    digitalWrite(prech,0);
    digitalWrite(main_rel,1);
    //turn off precharge and start mainrelay
    }        
bool startcondn(){
  if(brakeped>(0.2*1023)&&digitalRead(add_sw_in)){
    return true;
    }
    else {
      return false;}
  }
  void start(){
  digitalWrite(ctrl_rel,1);
  buzer();
  delay(3000);
  buzzerstop();
  precharge();
 
  }     
  void startloop(){
  digitalWrite(ctrl_rel,1);
  precharge();

  }     

void shtdown(){
  digitalWrite(main_rel,0);    

  }
  void tmpshtdown(){
    digitalWrite(main_rel,0);
    while(accavg>0.05*(1023)){
//precharge everytime before main rel high
      }
    startloop(); 
    }

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  pinMode(interlock,OUTPUT);//interlock
  pinMode(throttle_sw,OUTPUT);//throttle switch
  pinMode(acc_out,OUTPUT);//accn
  pinMode(brake_out,OUTPUT);//brake
  pinMode(prech,OUTPUT);//prechareg
  pinMode(main_rel,OUTPUT);//mainrelay
  pinMode(buzzer,OUTPUT);//buzzz
  pinMode(tsal_in,INPUT);//TSAL_OK
  pinMode(ctrl_rel,OUTPUT);//control relay
  pinMode(add_sw_in,INPUT);//additional SW

 digitalWrite(interlock,0);
 digitalWrite(throttle_sw,0);
 digitalWrite(acc_out,0);
 digitalWrite(brake_out,0);
 digitalWrite(prech,0);
 digitalWrite(main_rel,0);  
 digitalWrite(buzzer,0);
 digitalWrite(ctrl_rel,1);
 bailout:
 accped1 = analogRead(accped1_in);
 accped2 = analogRead(accped2_in);
 brakeped = analogRead(brakeped_in);
 previous = digitalRead(ok_24);
 accavg = (accped1+accped2)/2;
 if(check()&&plauscheck()&&startcondn())
 {
   start();
  }
 else{
    goto bailout;
  }

}


void loop() {
  // put your main code here, to run repeatedly:
repeat:
 accped1=analogRead(accped1_in);
 accped2=analogRead(accped2_in);
 brakeped=analogRead(brakeped_in);
 hv=analogRead(HV);
 accavg=(accped1+accped2)/2;
 if(check()){
  if (plauscheck()){
    analogWrite(acc_out,accavg*255/1023);
    analogWrite(brake_out,brakeped*255/1023);
    digitalWrite(throttle_sw,HIGH);
    }
    else{
      tmpshtdown();
      }
  }
  
  
  else{
    shtdown();
    goto repeat;
    }
  if(ok24())
  {precharge();
    }  

}
