//Click
const int StartPin = 2; 
const int StopPin = 4;  
int estado1 = LOW;
int estado2 = LOW;


//LCD
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd_1(0);


//DATOS
///Graficador
int analogPin = 0;
int val = 0;
int prevVal = 0;           // Valor anterior de la señal
int Cresta = 0; 
float VaCresta = 0;
unsigned long startTime = 0;  // Tiempo de la primera cresta
unsigned long endTime = 0;    // Tiempo de la segunda cresta
float frequency = 0;       // Frecuencia calculada
int x = 0;

void setup() 
{
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.print("Hallaremos la");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Frec. y Amplitud");
}

void loop() 
{
  
  estado1 = digitalRead(StartPin); 
  estado2 = digitalRead(StopPin);
  
  if (estado1 == 1)
  { VaCresta = 0;
    while (estado2 == 0)
      {
        
        estado1 = digitalRead(StartPin);  
        estado2 = digitalRead(StopPin);   
       
        val = analogRead(analogPin);
        Serial.println(val); 
      	x++;
      	if (x > 10)
        {
          
        if (val > VaCresta)
        {VaCresta = val;}
        
        if (val > prevVal && !Cresta ) //
        {
   		 Cresta = 1; 
         
  		}
      
      
        if (val < prevVal && Cresta) //&& Cresta
        {
          Cresta = 0;  // Marcamos que la cresta ha terminado
		 
          if (startTime == 0) 
           {
            // Si es la primera cresta detectada, guardamos el tiempo
            startTime = millis();
            } 
          else 
            {
            // Si es la segunda cresta, calculamos el periodo
           	endTime = millis();
           	unsigned long period = endTime - startTime;  // Tiempo entre crestas en milisegundos
           	startTime = endTime;  // Actualizamos el tiempo inicial
          
            // Convertimos el periodo a segundos y calculamos la frecuencia
            frequency = 1000.0 / period;
          }}
        }

  
  prevVal = val;
    }
  

      } 
  if (val != 0)
  {
float Amplitud = (VaCresta/100) ;
  Serial.print("Frecuencia: ");
  Serial.print(frequency);
  Serial.println(" Hz");
  Serial.print("Amplitud: ");
  Serial.print(Amplitud);
  Serial.println(" V");
  
  lcd_1.setCursor(0, 0);
  lcd_1.print("Frecuenc:");
  lcd_1.print(frequency);
  lcd_1.print("Hz");
  lcd_1.setCursor(0, 1);
  lcd_1.print("Amplitud");
    
  val =0;
  }
  
  
  }