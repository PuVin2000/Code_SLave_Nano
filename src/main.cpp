#include <Arduino.h>
#include "include.h"

int getLightValuefromMaster;
int MapData;
void TempHumid();
void Slave1toMaster(float HumidArea1, float TempArea1);
unsigned long time_1;

String Mymessage = "";

void setup()
{
  Serial.begin(9600); // initialize serial
  while (!Serial)
    ;
  setup_Lora_SlaveNano();

  Serial.println("DHTxx test!");

  dht.begin();
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop()
{
  if ((unsigned long)(millis() - time_1) > 2000)
  {
    time_1 = millis();
    // sendMessage(Mymessage, Node1, Node2);
    // sendMessage("0", Node1, MasterNode);

    TempHumid();
  }

  if (CheckMessage == 1)
  {
    MapData = map(getLightValuefromMaster, 0, 100, 0, 255);
    sendMessage("Node1Received", Node1, MasterNode);
    Serial.println(MapData);
    analogWrite(3, MapData);
  }
  CheckMessage = 0;

  onReceive(LoRa.parsePacket());
}

void TempHumid()
{
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  if (h > 70)
  {
    digitalWrite(4, 0);
  }
  else if (t > 35)
  {
    digitalWrite(4, 0);
  }
  else digitalWrite(4, 1);
  Slave1toMaster(h, t);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f))
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  // float hif = dht.computeHeatIndex(f, h);
  // // Compute heat index in Celsius (isFahreheit = false)
  // float hic = dht.computeHeatIndex(t, h, false);

  // Serial.print("Humidity: ");
  // Serial.print(h);
  // Serial.print(" %t");
  // Serial.print("Temperature: ");
  // Serial.print(t);
  // Serial.print(" *C ");
  // Serial.print(f);
  // Serial.print(" *Ft");
  // Serial.print("Heat index: ");
  // Serial.print(hic);
  // Serial.print(" *C ");
  // Serial.print(hif);
  // Serial.println(" *F");
}

void Slave1toMaster(float HumidArea1, float TempArea1)
{
  String Info = String(HumidArea1) + "," + String(TempArea1);
  sendMessage(Info, Node1, MasterNode);
  Serial.println(Info);
}

// int value = analogRead(A0);
// int percent = map(value, 0, 1023, 0, 100);
// // Serial.println(percent);
// if (percent <= 10)
//   digitalWrite(8, 0);
// else
//   digitalWrite(8, 1);
// String do_am = String(percent);
