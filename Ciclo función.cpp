


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
float VaValle = 0;
unsigned long startTime = 0;  // Tiempo de la primera cresta
unsigned long endTime = 0;    // Tiempo de la segunda cresta
float frequency = 0;       // Frecuencia calculada
int x = 0;

//Tipo de Grafica
float Pend1 = 0;
float Pend2 = 0;

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
   { VaCresta = -1023;
	 VaValle = 1023;
   	 Pend1 = 0;
     Pend2 = 0;
     startTime = 0;
    
    while (estado2 == 0)
    {
        estado1 = digitalRead(StartPin);  
        estado2 = digitalRead(StopPin);   
        
        val = analogRead(analogPin);
        //Serial.println(val); 
        
        x++;
        if (x > 10)
        {
          
            if (val > VaCresta)
            {VaCresta = val;}
          
          
            if (val < VaValle)
            {VaValle = val;}
            
         
            if (val > prevVal && !Cresta ) //
            {Cresta = 1;}
          
            if (Pend1 != 0 and Pend2 == 0)
             {
              Pend2 = val-prevVal;
             }
             
            if (val < prevVal && Cresta) //&& Cresta
            {
              Cresta = 0;  // Marcamos que la cresta ha terminado
        	 
              
                    Serial.println(val);
                    Serial.println(prevVal);
                    Serial.println();

                //Si ya hay una primera pendiente asignamos la segunda (Solo una vez)
              
              
              if (startTime == 0) 
               {startTime = millis(); 
               // Si es la primera cresta detectada, guardamos el tiempo y 
               //Ponemos la primera pendiente
               Pend1 = val-prevVal;
               }
               
              else 
               {
                // Si es la segunda cresta, calculamos el periodo
               	endTime = millis();
               	unsigned long period = endTime - startTime;  // Tiempo entre crestas en milisegundos
                startTime = endTime;  // Actualizamos el tiempo inicial
              
                // Convertimos el periodo a segundos y calculamos la frecuencia
               frequency = 1000.0 / period; //F=1/P -> 1Seg= 1000Milis
               
               }
               
                
            }
        }
        
        

      prevVal = val;
    }
  

  } 
  
  if (val != 0)
  {
    VaCresta -= ((VaCresta+VaValle)/2);
    float Amplitud = VaCresta/100;
    	
          
    	
    	
      Serial.println();
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
      lcd_1.print("Amplitud:");
	  lcd_1.print(Amplitud);
      lcd_1.print(" V ");
    
    Serial.println();
      Serial.println();
      Serial.println();

    Serial.println(Pend1);
      Serial.println(Pend2);
        Serial.println();
    Serial.println();
    Serial.println();

    
    
      val =0;
  }
  
}