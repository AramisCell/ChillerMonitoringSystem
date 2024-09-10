// CóDIGO DE ARDUINO PARA MONITOREO DE SENSORES DEL CHILLER.
// POR: ARAMIS CELL, KARLA, DORIS.    07/09/2024

// Librerias de los sensores.
#include <DHT.h>      // Librería del sensor DHT11.
#include "max6675.h"  // Librería del modulo MAX6675 del termopar tipo K.
#include "EmonLib.h"  // Librería del sensor de corriente.

// Definimos los pines de los sensores.
#define thermoSO 4
#define thermoCS 5
#define thermoSCLK 6
#define DHTPIN 7
#define DHTTYPE DHT11

// Creamos la conexion con el sensor.
EnergyMonitor emon1;
DHT dht(DHTPIN, DHTTYPE);
MAX6675 thermocouple(thermoSCLK, thermoCS, thermoSO);

void setup() {
  Serial.begin(9600);     // Inicializamos el puerto serial.
  dht.begin();            // Iniciamos el DHT11.
  emon1.current(A1, 30);  // Iniciamos el sensor de corriente.
  delay(1500);            // Un delay para permitir estabilizar a los sensores.
}

void loop() {
  // Lectura e Impresión de valores de sensado.
  // Serial Out Order:  TempDHT11    TempCouple   TempInstrumentación  HumidityDHT11    Corriente
  Serial.print(dht.readTemperature());
  Serial.print(" ");
  Serial.print(thermocouple.readCelsius() - 5);
  Serial.print(" ");
  Serial.print(analogRead(A0) * 50 / 1023);
  Serial.print(" ");
  Serial.print(dht.readHumidity());
  Serial.print(" ");
  Serial.println(emon1.calcIrms(1480));
}
