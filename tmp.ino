#include <SoftwareSerial.h>
#include <math.h>
SoftwareSerial xbee(2,3);

void setup() {
  // put your setup code here, to run once:
  xbee.begin(9600);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  int V;
  float R = 9870.0;
  float logRt, Rt, T,Temp;
  float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

  if (xbee.available() > 0) {  

      int analogMSB = xbee.read(); 
      int analogLSB = xbee.read();
      
  V = calculateXBeeVolt(analogMSB,analogLSB);
  Rt = R*((1023.0/(float)V)-1.0);
  logRt = log(Rt);
  Temp = (1.0/(c1+(c2*logRt)+(c3*logRt*logRt*logRt)))-273.15;
  Temp = ((Temp*9)/5)+32;
  xbee.print(Temp);
  xbee.println('faranheit');
   }
  delay(40);
}

float calculateXBeeVolt(int analogMSB, int analogLSB) {

  int analogReading = analogLSB + (analogMSB * 256); //Turn the two bytes into an integer value

  float volt = ((float)analogReading / 1023)*1.23; //Convert the analog value to a voltage value

  return volt;

}
