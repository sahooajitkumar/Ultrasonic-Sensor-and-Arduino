//--------------------------------------------------------Ajit Kumar Sahoo------------------------------------------------------------------------------------------------------------
//Devices: Ulrasonic sensor  HC-SR04 (range 2cm---400cm ),Temp and Humidity DHT-22  and Arduino microcontroller
//The program consider temp and humidity values while  calculating distacne to compensate environmental effects
//the millis() or micros() function is used to measure the execution time.(for better resoltion use micros():
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------
// Include DHT Libraries from Adafruit
// Dependant upon Adafruit_Sensors Library
#include "DHT.h";
#include "NewPing.h" // Include NewPing Library
// Define Constants
#define DHTPIN 7       // DHT-22 Output Pin connection
#define DHTTYPE DHT22   // DHT Type is DHT 22 (AM2302)
#define TRIGGER_PIN  10 //
#define ECHO_PIN     13//
#define MAX_DISTANCE 500 //default max distance 400cm
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //constructor NewPing sonar(trigger_pin, echo_pin [, max_cm_distance]);
// Define Variables 
float humidity;    // Stores humidity value in percent
float temp;   // Stores temperature value in Celcius
float duration; // Stores HC-SR04 pulse duration value
float distance; // Stores calculated distance in cm
float soundsp;  // Stores calculated speed of sound in M/S
float soundcm;  // Stores calculated speed of sound in cm/ms
int iterations = 5;
DHT dht(DHTPIN, DHTTYPE); 

//setup() function
void setup() {
  Serial.begin (9600);
 Serial.println("TEMP(*C)  HUMID(RH%)  Speed(m/s)  Distance(cm)");
  dht.begin();
  delay(2000); 
}
// end of setup function 


void loop()
{
// unsigned long start = micros();//use if you want to measure execution time
  humidity = dht.readHumidity();  // Get Humidity value
  temp= dht.readTemperature();  // Get Temperature value
  float   p = 101325;  //pressure is the standard atmospheric pressure (Pa)
  float a0 = 331.5024;
  float a1 = 0.603055;
  float a2 = -0.000528;
  float a3 = 51.471935;
  float a4 = 0.1495874;
  float a5 = -0.000782;
  float a6 = -1.82e-7;       
  float a7 = 3.73e-8;         
  float a8 = -2.93e-10;     
  float a9 = -85.20931;
  float a10 = -0.228525;
  float a11 = 5.91e-5;  
  float a12 = -2.835149;
  float a13 = -2.15e-13; 
  float a14 = 29.179762;
  float a15 = 0.000486;
  float T = temp + 273.15;
  float h = humidity /100.0;
  float f = 1.00062 + 0.0000000314 * p + 0.00000056 * temp * temp;
  float Psv = exp(0.000012811805 * T * T - 0.019509874 * T + 34.04926034 - 6353.6311 / T); // Saturation vapor pressur of water vapor in air:
  float Xw = h * f * Psv / p; //% water vapor mole fraction:
  float c = 331.45 - a0 - p * a6 - a13 * p * p;
  c = sqrt(a9 * a9 + 4 * a14 * c);
  float Xc = ((-1) * a9 - c) / ( 2 * a14);//molar fraction of CO2 
  float soundsp= a0 + a1 * temp + a2 * temp * temp + (a3 + a4 * temp + a5 * temp * temp) * Xw + (a6 + a7 * temp + a8 * temp * temp) * p + (a9 + a10 * temp + a11 * temp * temp) * Xc + a12 * Xw * Xw + a13 * p * p + a14 * Xc * Xc + a15 * Xw * p * Xc;

//-----------------------------------------------------  
soundcm = soundsp / 10000; // Convert to cm/ms
    
duration = sonar.ping_median(iterations);//Added ping_median() method which does a user specified number of pings (default=5) and 
                                             //returns the median ping in microseconds (out of range pings ignored).
  
distance = (duration / 2) * soundcm; // Calculate the distance

    Serial.print(temp);
    Serial.print("  ");
    Serial.print(humidity);
    Serial.print("  ");
    Serial.print(duration);
    Serial.print("  ");
    Serial.print(soundsp);
    Serial.print("  ");

 if (distance >500 || distance <2) {
    Serial.print("0.0");  // print if distance is out of range 
    }
    else {
    Serial.print(distance);
    Serial.print(" cm");

   }
// unsigned long end = micros(); //to measure exectuion time
//unsigned long delta = end - start; //to measure exectuion time
//Serial.println(delta);//dispaly the execution time
 
  delay(2000);  // delay to stabilize the sensors
  Serial.println(" ");
}

