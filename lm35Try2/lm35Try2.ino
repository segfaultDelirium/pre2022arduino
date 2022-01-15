/*
LM35 thermometer, no floats, no delays

  http://www.ti.com/lit/gpn/lm35
*/


const byte sampleBin = 8,
           aInPin = A0;

const int8_t fudge = 90; // adjust for calibration 

const int kAref = 1090, // analog ref voltage * 1000
          kSampleBin = sampleBin * 1000,
          fin = 2000;
int tempC,
    tempF;
    
uint32_t temp,
         start;

void setup()
{
  Serial.begin(9600);
  analogReference(INTERNAL);
  analogRead(aInPin);
  for(int i = 0;i < sampleBin;i++)
    temp += analogRead(aInPin);
}
void loop()
{
  if(millis() - start > fin){
    start = millis();
    temp -= (temp / sampleBin);
    temp += analogRead(aInPin);
    tempC = temp * kAref / (kSampleBin + fudge);
    tempF = (tempC * 18 + 3200) / 10;
    Serial.print(analogRead(aInPin));
    Serial.print("\t");
    Serial.print(temp);
    Serial.print("\t");
    prntTempC();
    prntTempF();
    Serial.println();
  }
}
    
void prntTempC(){
  Serial.print(tempC / 10);
  Serial.print(".");
  Serial.print(tempC % 10);
  Serial.print("\t");
}
void prntTempF(){  
  Serial.print(tempF / 10);
  Serial.print(".");
  Serial.print(tempF % 10);
  Serial.print("\t");
}
