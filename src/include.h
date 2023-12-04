#include <SPI.h> // include libraries
#include <LoRa.h>
#include "Lora_Slave_Function.h"

#include "DHT.h"

#define DHTPIN A2     // what digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

static DHT dht(DHTPIN, DHTTYPE);

#define ss 10
#define rst 9
#define dio0 2

#define IN1	5
#define IN2	6
#define ENB	4

static byte MasterNode = 0x1F;
static byte Node1 = 0xBB;
static byte Node2 = 0xCC;



static String outgoing;   // outgoing message
static byte msgCount = 0; // count of outgoing messages
static String SenderNode = "";

// static int AirValue = 590;   // you need to replace this value with Value_1
// static int WaterValue = 300; // you need to replace this value with Value_2
// static int SensorPin = A0;
// static int soilMoistureValue = 0;
// static int soilmoisturepercent = 0;

//static unsigned long time;

extern bool CheckMessage;

static String StringGetData = "";

extern int getLightValuefromMaster;
static String c = "";

const String DauPhay = ",";