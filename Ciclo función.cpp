/*//Click
const int StartPin = 2; 
const int StopPin = 4;  
int estado1 = LOW;
int estado2 = LOW;

///Graficador
int analogPin = 0;
int val = 0;

//LCD
#include <Adafruit_LiquidCrystal.h>


int seconds = 0;
Adafruit_LiquidCrystal lcd_1(0);





void setup() 
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Hallaremos la");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Frecuenciaa.");
}

void loop() 
{
  
  estado1 = digitalRead(StartPin); // 1 si está presionado, 0 si no
  estado2 = digitalRead(StopPin);
  
  if (estado1 == 1)
  {
    while (estado2 == 0)
      {
        estado1 = digitalRead(StartPin);  
        estado2 = digitalRead(StopPin);   
        
        val = analogRead(analogPin);
        Serial.println(val); 
  		
      
      } 
  }
 }
 
 



PULSADOR:

const int StartPin = 2; 
const int StopPin = 4;  
int estado1 = LOW;
int estado2 = LOW;

void setup() {
  pinMode(StartPin, INPUT);
  pinMode(StopPin, INPUT);

  Serial.begin(9600);
}

void loop() {
  
  estado1 = digitalRead(StartPin); // 1 si está presionado, 0 si no
  estado2 = digitalRead(StopPin;
  
  if (estado1 == 1)
  {
    while (estado2 == 0)
      {
       estado2 = digitalRead(StopPin);   

  
      } 
  }
 }
      

