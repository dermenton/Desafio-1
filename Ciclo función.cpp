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

const int StartPin = 2; // Pulsador 1 en pin A1
const int StopPin = 3;  // Pulsador 2 en pin A2
int estado2 = LOW;
int estado3 = LOW;

void setup() {
    Serial.begin(9600);

  // Configurar los pines de los pulsadores como entradas
  pinMode(StartPin, INPUT);
  pinMode(StopPin, INPUT);

  // Iniciar la comunicación serial para ver los resultados
}

void loop() {
  // Leer el estado de los pulsadores
  estado2 = digitalRead(StartPin); // 1 si está presionado, 0 si no
  estado3 = digitalRead(StopPin);   // 1 si está presionado, 0 si no

  // Imprimir el estado de los pulsadores en el monitor serial
  Serial.print("Pulsador 2 (2): ");
  Serial.println(estado2); // Imprime 1 o 0 para el pulsador 1

  Serial.print("Pulsador 3 (3): ");
  Serial.println(estado3);  // Imprime 1 o 0 para el pulsador 2

  delay(100); // Pequeño retraso de 100 ms para evitar lecturas excesivas
}



