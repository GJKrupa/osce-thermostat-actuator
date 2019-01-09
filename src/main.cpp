#include <Arduino.h>
#include <Lora.h>
#include <Servo.h>

#define SS      8
#define RST     4
#define DI0     7
#define BAND    8681E5

Servo servo;

int angle(int temperature) {
  return map(temperature, 6, 34, 0, 180);
}

void setup() {
  Serial.begin(115200);

  servo.attach(10, 400, 2400);

  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialisation error!");
    while (1) {
        servo.write(angle(10));
        delay(500);
        servo.write(angle(30));
        delay(500);
    }
  } else {
    Serial.println("LoRa initialised");
    servo.write(0);
    delay(1000);
    servo.write(180);
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Available");
    String data = LoRa.readString();
    Serial.println(data);
    if (data.startsWith("SETTEMP,")) {
      String tempString = data.substring(8);
      int temperature = tempString.toInt();
      Serial.println(temperature);
      servo.write(angle(temperature));
    }
  }
}