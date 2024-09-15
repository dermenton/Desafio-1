char receivedString[64]; // Se crea un string que sirve como buffer
int stringIndex = 0;    // Index para recorrer el arreglo
//Inicializando el LCD
LiquidCrystal lcd (2,3,4,5,6,7);

int analogPin = 0;
int val = 0;
void setup()
{
  Serial.begin(9600); 
    // Inicializa comunicación serial a unos baudios definidos
  Serial.begin(9600);

  // Configurar número de filas y columnas del LCD
  lcd.begin(8, 2);


}

void loop() {
  val = analogRead(analogPin);
	Serial.println(val);
  // Revisar si hay datos disponibles por la conexión serial
  if (Serial.available() > 0) {
    // Se lee el caracter o los caracteres
    char incomingChar = Serial.read();
    //String testStr = Serial.readString();

    // Se almacena en el arreglo
    receivedString[stringIndex] = incomingChar;
    stringIndex++;
    Serial.print(incomingChar);

    // Revisar cuál es el caracter de cierre
    if (incomingChar == '.') {
      receivedString[stringIndex] = '\0'; // terminar en nulo
      lcd.setCursor(0, 0);
      lcd.print(receivedString); //Imprimir
      //lcd.print(testStr);
      stringIndex = 0; // Reset index
    }
  }
 
} 