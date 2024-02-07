#include<SoftwareSerial.h>
SoftwareSerial Bluetooth(50, 51); //Tx Rx
//char Data; per vedere i caretteri sul seriale
char Data;

void setup() {
  Bluetooth.begin(9600);
  Serial.begin(9600);
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);

  digitalWrite(3, HIGH);
  digitalWrite(2, LOW);
}

void loop() {
  if(Bluetooth.available()){
    Serial.print("recevuto il messaggio: _");
    while(Bluetooth.available() > 0){
      Data = Bluetooth.read();
      Serial.print(Data);
      Serial.print(" ");
      delay(10);
    }
    Serial.print("_\n");
  }
}
