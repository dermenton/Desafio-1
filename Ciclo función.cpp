/*int analogPin = 0;
int val = 0;

void setup()
{
  Serial.begin(9600);
}
void loop()
{
  val = analogRead(analogPin);
  Serial.println(val); 
}
*/
//*
#include <Adafruit_LiquidCrystal.h>

int seconds = 0;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  
  lcd_1.print("Ando Aprendiendoskii ");
}

void loop()
{
  lcd_1.setCursor(0, 1);
  lcd_1.print(seconds);
  lcd_1.setBacklight(1);
  delay(100); // Wait for 500 millisecond(s)
  //lcd_1.setBacklight(0);
  //delay(100); // Wait for 500 millisecond(s)
  seconds = seconds+1;
  
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
      

