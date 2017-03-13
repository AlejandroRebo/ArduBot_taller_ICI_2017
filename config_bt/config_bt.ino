#include <SoftwareSerial.h>

SoftwareSerial bt_serial (2,3);

void setup () {

    bt_serial.begin(9600);
    Serial.begin(9600);
    Serial.println("Ingresa Comando AT:");

}

void loop() {

    while (bt_serial.available()) {

        Serial.write(bt_serial.read());

    }

    while (Serial.available()) {

        bt_serial.write(Serial.read());

    }

}
