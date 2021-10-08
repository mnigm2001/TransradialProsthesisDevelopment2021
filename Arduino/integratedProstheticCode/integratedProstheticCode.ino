#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int measCount = 0;
int minVoltage = 450;
float totalMv = 0.0;
float voltageAvg = 0.0;
int movCount = 0;

#define SERVOMIN1  120 // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX1  570 // This is the 'maximum' pulse length count (out of 4096)
#define SERVOMIN2  120
#define SERVOMAX2  570
#define SERVOMIN3  100 
#define SERVOMAX3  480
#define SERVOMIN4  110
#define SERVOMAX4  510
#define SERVOMIN5  100
#define SERVOMAX5  500

#define USMIN  600 // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX  2400 // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50 // Analog servos run at ~50 Hz updates

// our servo # counter
uint8_t servonum = 12;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);
  delay(10);
  
}

float readVoltage(){
  float sensorValue = analogRead(A0);
  float millivolt = ((sensorValue/1023) * 5)*1000;
  //Serial.print("Sensor Value:"); Serial.println(sensorValue);
  //Serial.print("Voltage: ");Serial.print(millivolt);Serial.println("mv");
  return millivolt;
}

//Return servos to initial or 0 position
void allMin(){
  setPosition(4, SERVOMIN1);
  setPosition(12, SERVOMIN2);
  setPosition(13, SERVOMIN3);
  setPosition(14, SERVOMIN4);
  setPosition(15, SERVOMIN5);
}

//Move servos to maximum or 180 degree position
void allMax(){
  setPosition(4, SERVOMAX1);
  setPosition(12, SERVOMAX2);
  setPosition(13, SERVOMAX3);
  setPosition(14, SERVOMAX4);
  setPosition(15, SERVOMAX5);
}

//Rotate a servo between maximums
void rotateMax(int servo, int servoMin, int servoMax){
  Serial.println(servo);
  for (uint16_t pulselen = servoMin; pulselen < servoMax; pulselen = pulselen +5) {
    if((pulselen == servoMin)){
      delay(1000);
    }
    if((pulselen == servoMax)){
      delay(1000);
    }
    pwm.setPWM(servo, 0, pulselen);
    Serial.print("pulselen= ");
    Serial.println(pulselen);
    delay(50);
  }
}

void setPosition(int servo, int pulseLen){
  pwm.setPWM(servo, 0, pulseLen);
  delay(500);
}

void maping(int angle, int pulseMin, int pulseMax){
  int pulse = map(angle, 0, 180, pulseMin, pulseMax);
  Serial.print("Angle = "); Serial.println(angle);
  Serial.print("Pulse = "); Serial.println(pulse);
  setPosition(12, pulse);
}


void loop() {

  
  int sampleAMT = 20;
  
  //unsigned long StartTime = micros();           //Start time measurement
  totalMv = 0;
  voltageAvg = 0;
  
  while(1){
    /*
    allMax(); 
    delay(50);
    allMin();
    delay(50);*/

    
    //2 Approaches: Long delay, small sample size or short delay large size
    
    //Read the MiAware voltage measurement
    float measMilli = readVoltage();
    //Serial.print("measCount = "); Serial.println(measCount);
    Serial.print("measMilli = "); Serial.println(measMilli);
    delay(1);
    
    measCount++;                  
    totalMv += measMilli;         //Addup up measurements

    //Once number of samples reached, take average
    if(measCount == sampleAMT){
      voltageAvg = (totalMv)/sampleAMT;
      Serial.print("\t totalMv = "); Serial.println(totalMv);
      Serial.print("\t voltageAvg = "); Serial.println(voltageAvg);
      Serial.println("");
      
      if(voltageAvg < 1000){
        Serial.println("");Serial.println("\t INSUFFICIENT VOLTAGE");Serial.println("");
        delay(1);
  
        
      }
      else if(voltageAvg > 1000){
        Serial.println("");Serial.println("\t SUFFICIENT VOLTAGE: MOVING ARM");Serial.println("");
        delay(1);
        movCount++;
        if((movCount%2) != 0){
          allMax(); 
        }
        else{
          allMin();
        }
      }
      else{
        Serial.println("");Serial.println("\t ERROR");Serial.println("");
        delay(1);
      }
        
      measCount = 0;
      totalMv = 0;
      voltageAvg = 0;
    }

    
    delay(10);
    
  }
  
}
