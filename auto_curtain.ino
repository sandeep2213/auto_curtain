// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D7
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
int temprature;

#define IR_SENSOR D1
int ir=0;

#define PIR_SENSOR D6
int pir=0;

//vars Stepper motor
#define SM_CLK D4
#define SM_CW D3
#define SM_EN D2


#define BUTTON D0
int but=0;
#define LED D5


int c_state=0;    //1-open 0-close 'something like that'  curtain state
int c_auto=1;     //1-automation ON    0-OFF

int same_value=1;  //same as c_auto to trigger motor with flag
int flag=0;        //1-toggle motor   0-inactive
int z=0;   //for loop button time


//---------------------------------------------------------------------

void setup() {

  Serial.begin(115200);
  pinMode(IR_SENSOR,INPUT_PULLUP);
  pinMode(PIR_SENSOR,INPUT_PULLUP);
  
  pinMode(SM_CLK,OUTPUT);
  pinMode(SM_CW,OUTPUT);
  pinMode(SM_EN,OUTPUT);
  
  pinMode(LED,OUTPUT);
  
  pinMode(BUTTON,INPUT);
  
  
  sensors.begin();

  delay(1000);
  digitalWrite(LED,LOW);    //on automation default
  digitalWrite(SM_EN,LOW);
  digitalWrite(SM_CW,LOW);
  
}

//---------------------------------------------------------------------

void loop() {

  sensors.requestTemperatures();
  temprature=sensors.getTempCByIndex(0);
  ir=digitalRead(IR_SENSOR);
  pir=digitalRead(PIR_SENSOR);
  but=digitalRead(BUTTON);


 while (digitalRead(BUTTON)==0){
  Serial.println("button pressed");
  delay(500);
  z++;
  c_auto=0;
  flag=1;
  digitalWrite(LED,HIGH);    //led off

  
  if (z>=4){                    //long press condition
    c_auto=1;
    flag=0;
    digitalWrite(LED,LOW);   // led on
    delay(500);
    break;
  }
  
 }
  z=0;  //reset timer button
  
  if (ir==1){
    c_state=1;
  }
  
  
  if (pir==0){
    c_state=1;
  }
    
  
  if (temprature>20){
    c_state=1;
  }

  if (ir==0 && pir==1 && temprature<=20){
    c_state=0;
  }
  
  
  if (flag==1){
    toggle_var(c_state);       //manually toggle flag condition
    flag=0;
  }
  
  
  
  if(c_state!=same_value){          //motor toggle based on previews state
  
    same_value=c_state;
  
    if (c_state==1){
      cw();
    }
    else acw();
    
  }




  Serial.print("temp:");
  Serial.println(temprature);
  Serial.print("LDR:");
  Serial.println(ir);
  Serial.print("PIR:");
  Serial.println(pir);

}

//------------------------------------------------------------
//additional functions


void toggle_var(int pin){

  if(pin==0){
    pin=1;
  }
  else pin=0;
  
}


void cw(){

    digitalWrite(SM_EN,HIGH);
    digitalWrite(SM_CW,LOW); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 400; x++) {
      digitalWrite(SM_CLK,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(SM_CLK,LOW); 
      delayMicroseconds(1000); 
    }
    delay(2000);
}


void acw(){

  digitalWrite(SM_EN,HIGH);
    digitalWrite(SM_CW,HIGH); // Enables the motor to move in a particular direction
    // Makes 200 pulses for making one full cycle rotation
    for(int x = 0; x < 400; x++) {
      digitalWrite(SM_CLK,HIGH); 
      delayMicroseconds(1000); 
      digitalWrite(SM_CLK,LOW); 
      delayMicroseconds(1000); 
    }
    delay(2000);
  
}
