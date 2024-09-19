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
float Frecuencia = 0;       // Frecuencia calculada
int x = 0;

// Tipo de Grafica
float Pend1 = 0;
float Pend2 = 0;
int eTime2 = 0;
int sTime2 = 0;
int PeriodoPend1 = 0;
int PeriodoPend2 = 0;

// Mem din Almacenar variables
int capacidad = 2; // Capacidad inicial
float* pendientes = new float[capacidad]; // Almacenar Pend1 y Pend2
float* periodos = new float[capacidad]; // PeriodoPend1 y PeriodoPend2
int cantElementos = 0; // Contador de elementos

void redimensionarArreglos(float*& arr, int& capacidad) {
    int nuevaCap = capacidad * 2; //mas capacidad
    float* nuevoArr = new float[nuevaCap]; //nuevo arreglo
    
    // Copiar elementos
    for (int i = 0; i < capacidad; i++) {
        nuevoArr[i] = arr[i];
    }

    delete[] arr; // Liberar memoria del arreglo viejo
    arr = nuevoArr; // Actualizar el puntero
    capacidad = nuevaCap; // Actualizar la capacidad
}



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
    {
        VaCresta = -1023;
        VaValle = 1023;
        Pend1 = 0;
        Pend2 = 0;
        startTime = 0;
    
        while (estado2 == 0) 
        {
            estado1 = digitalRead(StartPin);  
            estado2 = digitalRead(StopPin);   
            
            prevVal = analogRead(analogPin);
            sTime2 = micros();
            Serial.println(prevVal); 
            
            x++;
         if (x > 10) 
           {
          
            if (prevVal > VaCresta)
            {VaCresta = prevVal;}
          
          
            if (prevVal < VaValle)
            {VaValle = prevVal;}
            
         
            if (prevVal > val && !Cresta) //&& !Cresta 
            {Cresta = 1;}
          
            if (Pend1 != 0 and Pend2 == 0)
             {
             val = analogRead(analogPin);
             Pend2 = val-prevVal;
             eTime2 = micros();
             PeriodoPend2 = eTime2- sTime2;
             }
             
          
          
            if (prevVal < val && Cresta) //&& Cresta
            {
              Cresta = 0;  // Marcamos que la cresta ha terminado
        	 
              
              if (startTime == 0) 
               {startTime = millis(); 
               // Si es la primera cresta detectada, guardamos el tiempo y 
               //Ponemos la primera pendiente
               val = analogRead(analogPin);
               Pend1 = val-prevVal;
               eTime2 = micros();
       		   PeriodoPend1 = eTime2- sTime2;
               }
               
              else 
               {
                // Si es la segunda cresta, calculamos el periodo
               	endTime = millis();
               	int period = endTime - startTime;  // Tiempo entre crestas en milisegundos
                startTime = endTime;  // Actualizamos el tiempo inicial
              
                // Convertimos el periodo a segundos y calculamos la frecuencia
                Frecuencia = 1000.0 / period; //F=1/P -> 1Seg= 1000Milis
                    }
                }
            }
        }
    }

    // Almacenamiento variables pendiente
    if (prevVal != 0) 
    {
        if (cantElementos == capacidad) 
        {
            redimensionarArreglos(pendientes, capacidad);
            redimensionarArreglos(periodos, capacidad);
        }
        pendientes[cantElementos] = Pend1; // Guardar Pend1
        periodos[cantElementos] = PeriodoPend1; // Guardar PeriodoPend1
        cantElementos++; // Incrementar el contador

        // Repite para Pend2 y PeriodoPend2
        pendientes[cantElementos] = Pend2; // Guardar Pend2
        periodos[cantElementos] = PeriodoPend2; // Guardar PeriodoPend2
        cantElementos++; // Incrementar el contador

        VaCresta -= ((VaCresta + VaValle) / 2);
        float Amplitud = VaCresta / 100;

        Serial.println();
        Serial.print("Frecuencia: ");
        Serial.print(Frecuencia);
        Serial.println(" Hz");
        Serial.print("Amplitud: ");
        Serial.print(Amplitud);
        Serial.println(" V");
        
        lcd_1.setCursor(0, 0);
        lcd_1.print("Frecuenc:");
        lcd_1.print(Frecuencia);
        lcd_1.print("Hz");
        lcd_1.setCursor(0, 1);
        lcd_1.print("Amplitud:");
        lcd_1.print(Amplitud);
        lcd_1.print(" V ");
        delay(2500);  // Pausa para mostrar resultados
        lcd_1.clear();	
        
        lcd_1.setCursor(0, 0);
        lcd_1.print("El tipo de onda ");
        lcd_1.setCursor(0, 1);

        // Análisis de la forma de onda
        Pend1 = Pend1 * 1000000 / PeriodoPend1;
        Pend2 = Pend2 * 1000000 / PeriodoPend2;

        if (Pend1 == Pend2 and Pend1 == (Pend2 * -1)) 
        {
            Serial.println("La onda es Cuadrada");
            lcd_1.print("es: Cuadrada ");
        } 
        else if ((abs(Pend2) - abs(Pend1)) > 6) 
        {
            Serial.println("La onda es Senoidal");
            lcd_1.print("es: Senoidal ");
        } 
        else if ((abs(Pend2) - abs(Pend1)) < 6) 
        {
            Serial.println("La onda es Triangular");
            lcd_1.print("es: Triangular ");
        } 
        else 
        {
            Serial.println("Ha ocurrido un error, intentelo de nuevo, por favor.");
            lcd_1.print("es: desconocido ");
        }

        prevVal = 0;
    }
}
