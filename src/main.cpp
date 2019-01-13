#include <Arduino.h>
#include <Lora.h>
#include <Servo.h>

#define SS      8
#define RST     4
#define DI0     7
#define BAND    8681E5

#define DEFAULT_TEMP 20

#define MSG_PREAMBLE "APPLYTEMP,"

double angles[] = {
  158.0, // 10
  152.5, // 11
  147, // 12
  141.5, // 13
  133.25, // 14
  125, // 15
  118.2, // 16
  111.4, // 17
  104.9, // 18
  98.1, // 19
  91, // 20
  85.4, // 21
  79.8, // 22
  74.2, // 23
  68.6, // 24
  63, // 25
  57.4, // 26
  51.8, // 27
  46.2, // 18
  40.6, // 19
  35 //20
};

#define ANGLE_10 158
#define ANGLE_15 125
#define ANGLE_20 91
#define ANGLE_25 63
#define ANGLE_30 35

Servo servo;

int angle(int temperature) {
  int effective = temperature;
  if (temperature < 10) {
    effective = 10;
  } else if (temperature > 30) {
    effective = 30;
  }
  return map((int)(angles[effective-10]), 0, 180, 0, 180);
}

void setup() {
  Serial.begin(115200);

  servo.attach(10, 400, 2400);

  LoRa.setPins(SS, RST, DI0);

  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialisation error!");
    while (1);
  } else {
    Serial.println("LoRa initialised");
    servo.write(angle(DEFAULT_TEMP));
  }
}

void loop() {
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.println("Available");
    String data = LoRa.readString();
    Serial.println(data);
    if (data.startsWith(MSG_PREAMBLE)) {
      String tempString = data.substring(strlen(MSG_PREAMBLE));
      int temperature = tempString.toInt();
      Serial.println(temperature);
      servo.write(angle(temperature));
    }
  }
}