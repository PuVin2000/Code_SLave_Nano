#include "include.h"

bool CheckMessage;
// String Mymessage = "";
void setup_Lora_SlaveNano()
{

  Serial.println("LoRa Node1");
  LoRa.setPins(ss, rst, dio0);
  if (!LoRa.begin(433E6))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  //LoRa.setTxPower(20);
  // LoRa.onReceive(onReceive);
  // LoRa.receive();
}
void onReceive(int packetSize)
{
  if (packetSize == 0)
    return; // if there's no packet, return
  // read packet header bytes:
  int recipient = LoRa.read(); // recipient address
  byte sender = LoRa.read();   // sender address
  if (sender == MasterNode)
    SenderNode = "MasterNode:";
  if (sender == Node2)
    SenderNode = "Node2:";

  byte incomingMsgId = LoRa.read();  // incoming msg ID
  byte incomingLength = LoRa.read(); // incoming msg length

  char incoming[256];

  for (int i = 0; i < packetSize; i++)
  {
    incoming[i] = (char)LoRa.read();
  }

  incoming[packetSize] = '\0';
  /*  if (incomingLength != incoming.length()) {  // check length for error
     // Serial.println("error: message length does not match length");
     ;
     return;  // skip rest of function
   } */
  // if the recipient isn't this device or broadcast,
  if (recipient != Node1 && recipient != MasterNode)
  {
    // Serial.println("This message is not for me.");
    ;
    return; // skip rest of function
  }
    if (recipient != Node1 && recipient != Node2)
  {
    // Serial.println("This message is not for me.");
    ;
    return; // skip rest of function
  }
  // Serial.println(incoming);
  if (sender == MasterNode)
  {
    CheckMessage = 1;
    StringGetData = getValue(incoming, ',', 0);
    getLightValuefromMaster = StringGetData.toInt();
    Serial.println(getLightValuefromMaster);
  }
  else if (sender == Node2)
  {
    CheckMessage = 1;
    // v = getValue(incoming, ',', 0);
    // Serial.println(v);
  }
}
void sendMessage(String outgoing, byte MasterNode, byte otherNode)
{
  LoRa.beginPacket();            // start packet
  LoRa.write(otherNode);        // add destination address
  LoRa.write(MasterNode);             // add sender address
  LoRa.write(msgCount);          // add message ID
  LoRa.write(outgoing.length()); // add payload length
  LoRa.print(outgoing);          // add payload
  LoRa.endPacket();              // finish packet and send it
  msgCount++;                    // increment message ID
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

void PWM_Control(int x)
{
  digitalWrite(ENB, 1);
  analogWrite(IN1, x);
  digitalWrite(IN2, LOW);
}