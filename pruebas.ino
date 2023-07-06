#include <Arduino.h>
#include <WiFi.h>
#include <FirebaseESP32.h>
#include <ESP32Time.h>
#include <Adafruit_MCP23X17.h>
#include <Adafruit_MCP23X08.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
ESP32Time rtc;
const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = -6*3600;
const int daylightOffset_sec = 0;
unsigned long currentMillis=0;
unsigned long previousMillis = 0;
unsigned long interval = 30000;
int now;
int day_week;
int  buttonState = 0;
const int buttonPin = 32;

//// variables de tiempo
int ontime_R_01;
int offtime_R_01;
int ontime_R_02;
int offtime_R_02;
int ontime_R_03;
int offtime_R_03;
int ontime_R_04;
int offtime_R_04;
int ontime_R_05;
int offtime_R_05;
int ontime_R_06;
int offtime_R_06;
int ontime_R_07;
int offtime_R_07;
int ontime_R_08;
int offtime_R_08;
int ontime_R_09;
int offtime_R_09;
int ontime_R_10;
int offtime_R_10;
int ontime_R_11;
int offtime_R_11;
int ontime_R_12;
int offtime_R_12;
int ontime_R_13;
int offtime_R_13;
int ontime_R_14;
int offtime_R_14;
int ontime_R_15;
int offtime_R_15;
int ontime_R_16;
int offtime_R_16;
int ontime_R_17;
int offtime_R_17;
int ontime_R_18;
int offtime_R_18;
int ontime_R_19;
int offtime_R_19;
int ontime_R_20;
int offtime_R_20;



////
// Provide the token generation process info.
#include <addons/TokenHelper.h>

// Provide the RTDB payload printing info and other helper functions.
#include <addons/RTDBHelper.h>

/* 1. Define the WiFi credentials */
#define WIFI_SSID "Encuentro_CV"
#define WIFI_PASSWORD "3l3ncu3ntr02023"

//#define WIFI_SSID "IluminacionCV"
//#define WIFI_PASSWORD "IluminacionCV"

//#define WIFI_SSID "HITRON16205-5G"
//#define WIFI_PASSWORD "C88DAHITRON"

// For the following credentials, see examples/Authentications/SignInAsUser/EmailPassword/EmailPassword.ino

/* 2. Define the API Key */
/*#define API_KEY "AIzaSyCvePyLUdKdgRyMbF6B1fjDZ5GD89Z_KXo"
#define DATABASE_URL "https://jetfans-y-extractores-default-rtdb.firebaseio.com/"
#define USER_EMAIL "chavezk78@gmail.com"
#define USER_PASSWORD "Ineleq2023"

#define FIREBASE_AUTH "M9mMg5rZo8z6K6pTkH4Jc3eNRKVDpbYI5hbcpioV"*/

#define API_KEY "AIzaSyBx2yuQpsA-B0EfMGnT_T6J595c3GvAIzA"
#define DATABASE_URL "https://encuentrocv2-default-rtdb.firebaseio.com/"
#define USER_EMAIL "chavezk78@gmail.com"
#define USER_PASSWORD "EncuentroCV2"
#define FIREBASE_AUTH "gUhlfsda8j9t9urSg5qPJEU373bzDZnjM0s2liti"


// Define Firebase Data object
FirebaseData stream;
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;
//bool flag=false;
unsigned long sendDataPrevMillis0 = 0;
bool flag=false;
unsigned long count = 0;
struct  variables_retorno{
  int estadoInicial;
  int estadoFinal;
  int automatico;
  int lunes;
  int martes;
  int miercoles;
  int jueves;
  int viernes;
  int sabado;
  int domingo;
  int I;
  int OFF_h;
  int ON_min;
  int ON_h;
  int OFF_min;
};
variables_retorno panel[20]; 


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OUTPUT1 0
#define OUTPUT2 1
#define OUTPUT3 2
#define OUTPUT4 3
#define OUTPUT5 12
#define OUTPUT6 13
#define OUTPUT7 14
#define OUTPUT8 15

#define OUTPUT9 7
#define OUTPUT10 6
#define OUTPUT11 5
#define OUTPUT12 4
#define OUTPUT13 8
#define OUTPUT14 9
#define OUTPUT15 10
#define OUTPUT16 11

#define OUTPUT17 14
#define OUTPUT18 12
#define OUTPUT19 13
#define OUTPUT20 15

Adafruit_MCP23X17 mcp;

static const uint8_t image_data_Saraarray[1024] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xc0, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xf8, 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x03, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x80, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x1f, 0xfc, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xfc, 0x1f, 0x80, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xf8, 0x0f, 0x80, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf8, 0x07, 0x80, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xc0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x01, 0xe0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0xf0, 0x07, 0x80, 0x07, 0xf8, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xd8, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x07, 0x80, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x01, 0xe3, 0x80, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0x8e, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x7c, 0x00, 0x00, 0x7f, 0xee, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x3c, 0x00, 0x00, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x0f, 0x01, 0xf0, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x3f, 0xe1, 0xe0, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x7f, 0xf1, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0xf8, 0xf9, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xe0, 0x79, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x39, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xc0, 0x39, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void streamCallback(StreamData data){
  Serial.printf("sream path, %s\nevent path, %s\ndata type, %s\nevent type, %s\n\n",
                data.streamPath().c_str(),
                data.dataPath().c_str(),
                data.dataType().c_str(),
                data.eventType().c_str());
  printResult(data); // see addons/RTDBHelper.h
  //Serial.println("tipo de dato: ");
  //Serial.println(data.dataType().c_str());
  String streamPath = String(data.dataPath());
  String caso=streamPath.substring(1);
  //Serial.println("comparando");
  //Serial.println(caso);
  int retorno;
  String subPath;
  
  if(data.dataTypeEnum()==fb_esp_rtdb_data_type_integer){
    procesarPath(caso,retorno,subPath,data); 
  }else if(data.dataTypeEnum() == fb_esp_rtdb_data_type_json){
    //Serial.println("Tipo JSON");
    FirebaseJson json = data.to<FirebaseJson>();
    size_t count = json.iteratorBegin();
    //Serial.println("CUENTA JSON:");
    //Serial.println(count);
    for(size_t i=0;i<count;i++){
      int retorno;
      FirebaseJson::IteratorValue value = json.valueAt(i);
      String child = value.key.c_str();
      String subpath;
      //Serial.println(subpath);
      //Serial.println(child);
      almacenarJson(child,value);
    }
  }
  flag=true;
}

void streamTimeoutCallback(bool timeout)
{
  if (timeout)
    Serial.println("stream timed out, resuming...\n");

  if (!stream.httpConnected())
    Serial.printf("error code: %d, reason: %s\n\n", stream.httpCode(), stream.errorReason().c_str());
}

void setup()
{

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Wire.begin (16, 17);
  if (!mcp.begin_I2C(0x23)) {
    Serial.println("Error.");
    //while (1);
  }
  // configure pin for output
  mcp.pinMode(OUTPUT1, OUTPUT);
  mcp.pinMode(OUTPUT2, OUTPUT);
  mcp.pinMode(OUTPUT3, OUTPUT);
  mcp.pinMode(OUTPUT4, OUTPUT);
  mcp.pinMode(OUTPUT5, OUTPUT);
  mcp.pinMode(OUTPUT6, OUTPUT);
  mcp.pinMode(OUTPUT7, OUTPUT);
  mcp.pinMode(OUTPUT8, OUTPUT);
  mcp.pinMode(OUTPUT9, OUTPUT);
  mcp.pinMode(OUTPUT10, OUTPUT);
  mcp.pinMode(OUTPUT11, OUTPUT);
  mcp.pinMode(OUTPUT12, OUTPUT);
  mcp.pinMode(OUTPUT13, OUTPUT);
  mcp.pinMode(OUTPUT14, OUTPUT);
  mcp.pinMode(OUTPUT15, OUTPUT);
  mcp.pinMode(OUTPUT16, OUTPUT);
  pinMode(OUTPUT17, OUTPUT);
  pinMode(OUTPUT18, OUTPUT);
  pinMode(OUTPUT19, OUTPUT);
  pinMode(OUTPUT20, OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  display.drawBitmap(0, 0, image_data_Saraarray, 128, 64, 1);
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);
  display.println("NORVI IIOT-AE01-R");
  display.setCursor(45, 30);
  display.println("HELLO...");
  display.setCursor(25, 45);
  display.println("Iluminacion P2");
  display.display();
  delay(2000);

  Serial.println("Looping... setup");

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);

  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  struct tm timeinfo;
  if(getLocalTime(&timeinfo)){
  rtc.setTimeStruct(timeinfo);
  }
  // configure p
  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the user sign in credentials */
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  // Or use legacy authenticate method
  // config.database_url = DATABASE_URL;
  // config.signer.tokens.legacy_token = "<database secret>";

  // To connect without auth in Test Mode, see Authentications/TestMode/TestMode.ino

  //////////////////////////////////////////////////////////////////////////////////////////////
  // Please make sure the device free Heap is not lower than 80 k for ESP32 and 10 k for ESP8266,
  // otherwise the SSL connection will fail.
  //////////////////////////////////////////////////////////////////////////////////////////////
  Firebase.begin(DATABASE_URL, FIREBASE_AUTH);
  //Firebase.begin(&config, &auth);

  // Comment or pass false value when WiFi reconnection will control by your code or third party library
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);
  stream.keepAlive(5, 5, 1);
   if (!Firebase.beginStream(stream, "/Iluminacion_CV/Panel_2"))
    Serial.printf("sream begin error, %s\n\n", stream.errorReason().c_str());

  Firebase.setStreamCallback(stream, streamCallback, streamTimeoutCallback);
}

void loop()
{ 
  buttonState = analogRead(buttonPin);
  bool salida_1;
  bool salida_2;
  bool salida_3;
  bool salida_4;
  bool salida_5;
  bool salida_6;
  bool salida_7;
  bool salida_8;
  bool salida_9;
  bool salida_10;
  bool salida_11;
  bool salida_12;
  bool salida_13;
  bool salida_14;
  bool salida_15;
  bool salida_16;
  bool salida_17;
  bool salida_18;
  bool salida_19;
  bool salida_20;
  ontime_R_01 = panel[0].ON_h*100+panel[0].ON_min;
  offtime_R_01 = panel[0].OFF_h*100+panel[0].OFF_min;
  ontime_R_02 = panel[1].ON_h*100+panel[1].ON_min;
  offtime_R_02 = panel[1].OFF_h*100+panel[1].OFF_min;
  ontime_R_03 = panel[2].ON_h*100+panel[2].ON_min;
  offtime_R_03 = panel[2].OFF_h*100+panel[2].OFF_min;
  ontime_R_04 = panel[3].ON_h*100+panel[3].ON_min;
  offtime_R_04 = panel[3].OFF_h*100+panel[3].OFF_min;
  ontime_R_05 = panel[4].ON_h*100+panel[4].ON_min;
  offtime_R_05 = panel[4].OFF_h*100+panel[4].OFF_min;
  ontime_R_06 = panel[5].ON_h*100+panel[5].ON_min;
  offtime_R_06 = panel[5].OFF_h*100+panel[5].OFF_min;
  ontime_R_07 = panel[6].ON_h*100+panel[6].ON_min;
  offtime_R_07 = panel[6].OFF_h*100+panel[6].OFF_min;
  ontime_R_08 = panel[7].ON_h*100+panel[7].ON_min;
  offtime_R_08 = panel[7].OFF_h*100+panel[7].OFF_min;
  ontime_R_09 = panel[8].ON_h*100+panel[8].ON_min;
  offtime_R_09 = panel[8].OFF_h*100+panel[8].OFF_min;
  ontime_R_10 = panel[9].ON_h*100+panel[9].ON_min;
  offtime_R_10 = panel[9].OFF_h*100+panel[9].OFF_min;
  ontime_R_11 = panel[10].ON_h*100+panel[10].ON_min;
  offtime_R_11 = panel[10].OFF_h*100+panel[10].OFF_min;
  ontime_R_12 = panel[11].ON_h*100+panel[11].ON_min;
  offtime_R_12 = panel[11].OFF_h*100+panel[11].OFF_min;
  ontime_R_13 = panel[12].ON_h*100+panel[12].ON_min;
  offtime_R_13 = panel[12].OFF_h*100+panel[12].OFF_min;
  ontime_R_14 = panel[13].ON_h*100+panel[13].ON_min;
  offtime_R_14 = panel[13].OFF_h*100+panel[13].OFF_min;
  ontime_R_15 = panel[14].ON_h*100+panel[14].ON_min;
  offtime_R_15 = panel[14].OFF_h*100+panel[14].OFF_min;
  ontime_R_16 = panel[15].ON_h*100+panel[15].ON_min;
  offtime_R_16 = panel[15].OFF_h*100+panel[15].OFF_min;
  ontime_R_17 = panel[16].ON_h*100+panel[16].ON_min;
  offtime_R_17 = panel[16].OFF_h*100+panel[16].OFF_min;
  ontime_R_18 = panel[17].ON_h*100+panel[17].ON_min;
  offtime_R_18 = panel[17].OFF_h*100+panel[17].OFF_min;
  ontime_R_19 = panel[18].ON_h*100+panel[18].ON_min;
  offtime_R_19 = panel[18].OFF_h*100+panel[18].OFF_min;
  ontime_R_20 = panel[19].ON_h*100+panel[19].ON_min;
  offtime_R_20 = panel[19].OFF_h*100+panel[19].OFF_min;
  display.clearDisplay();

  if ((WiFi.status() != WL_CONNECTED) && (currentMillis - previousMillis >=interval)) {
    Serial.print(millis());
    Serial.println("Reconnecting to WiFi...");
    WiFi.disconnect();
    WiFi.reconnect();
    previousMillis = currentMillis;
  }
  if (Firebase.isTokenExpired() || Firebase.ready()==false ){
    //Serial.println("Refresh token");
    Firebase.refreshToken(&config);
  }
  now = rtc.getHour(true) * 100 + rtc.getMinute() ;
  day_week = rtc.getDayofWeek();
  if(day_week == 0){
    day_week = 7;    
  }else{
    day_week = day_week;
  }
  if(Firebase.ready() || (millis() - sendDataPrevMillis0 > 900 || sendDataPrevMillis0 == 0)){
    sendDataPrevMillis0=millis();
    salida_1 = ctrl_iluminacion(now, panel[0].automatico, panel[0].I, ontime_R_01, offtime_R_01, day_week, panel[0].lunes, panel[0].martes, panel[0].miercoles, panel[0].jueves, panel[0].viernes, panel[0].sabado, panel[0].domingo );
    panel[0].estadoFinal = salida_1;
    mcp.digitalWrite(OUTPUT1, salida_1);
    if(panel[0].estadoFinal!=panel[0].estadoInicial){
      ejecutarAccion(0);
    }

    salida_2 = ctrl_iluminacion(now, panel[1].automatico, panel[1].I, ontime_R_02, offtime_R_02, day_week, panel[1].lunes, panel[1].martes, panel[1].miercoles, panel[1].jueves, panel[1].viernes, panel[1].sabado, panel[1].domingo );
    panel[1].estadoFinal = salida_2;
    mcp.digitalWrite(OUTPUT2, salida_2);
    if(panel[1].estadoFinal!=panel[1].estadoInicial){
      ejecutarAccion(1);
    }

    salida_3 = ctrl_iluminacion(now, panel[2].automatico, panel[2].I, ontime_R_03, offtime_R_03, day_week, panel[2].lunes, panel[2].martes, panel[2].miercoles, panel[2].jueves, panel[2].viernes, panel[2].sabado, panel[2].domingo );
    panel[2].estadoFinal = salida_3;
    mcp.digitalWrite(OUTPUT3, salida_3);
    if(panel[2].estadoFinal!=panel[2].estadoInicial){
      ejecutarAccion(2);
    }

    salida_4 = ctrl_iluminacion(now, panel[3].automatico, panel[3].I, ontime_R_04, offtime_R_04, day_week, panel[3].lunes, panel[3].martes, panel[3].miercoles, panel[3].jueves, panel[3].viernes, panel[3].sabado, panel[3].domingo );
    panel[3].estadoFinal = salida_4;
    mcp.digitalWrite(OUTPUT4, salida_4);
    if(panel[3].estadoFinal!=panel[3].estadoInicial){
      ejecutarAccion(3);
    }

    salida_5 = ctrl_iluminacion(now, panel[4].automatico, panel[4].I, ontime_R_05, offtime_R_05, day_week, panel[4].lunes, panel[4].martes, panel[4].miercoles, panel[4].jueves, panel[4].viernes, panel[4].sabado, panel[4].domingo );
    panel[4].estadoFinal = salida_5;
    mcp.digitalWrite(OUTPUT5, salida_5);
    if(panel[4].estadoFinal!=panel[4].estadoInicial){
      ejecutarAccion(4);
    }
    salida_6 = ctrl_iluminacion(now, panel[5].automatico, panel[5].I, ontime_R_06, offtime_R_06, day_week, panel[5].lunes, panel[5].martes, panel[5].miercoles, panel[5].jueves, panel[5].viernes, panel[5].sabado, panel[5].domingo );
    panel[5].estadoFinal = salida_6;
    mcp.digitalWrite(OUTPUT6, salida_6);
    if(panel[5].estadoFinal!=panel[5].estadoInicial){
      ejecutarAccion(5);
    }

    salida_7 = ctrl_iluminacion(now, panel[6].automatico, panel[6].I, ontime_R_07, offtime_R_07, day_week, panel[6].lunes, panel[6].martes, panel[6].miercoles, panel[6].jueves, panel[6].viernes, panel[6].sabado, panel[6].domingo );
    panel[6].estadoFinal = salida_7;
    mcp.digitalWrite(OUTPUT7, salida_7);
    if(panel[6].estadoFinal!=panel[6].estadoInicial){
      ejecutarAccion(6);
    }

    salida_8 = ctrl_iluminacion(now, panel[7].automatico, panel[7].I, ontime_R_08, offtime_R_08, day_week, panel[7].lunes, panel[7].martes, panel[7].miercoles, panel[7].jueves, panel[7].viernes, panel[7].sabado, panel[7].domingo );
    panel[7].estadoFinal = salida_8;
    mcp.digitalWrite(OUTPUT8, salida_8);
    if(panel[7].estadoFinal!=panel[7].estadoInicial){
      ejecutarAccion(7);
    }

    salida_9 = ctrl_iluminacion(now, panel[8].automatico, panel[8].I, ontime_R_09, offtime_R_09, day_week, panel[8].lunes, panel[8].martes, panel[8].miercoles, panel[8].jueves, panel[8].viernes, panel[8].sabado, panel[8].domingo );
    panel[8].estadoFinal = salida_9;
    mcp.digitalWrite(OUTPUT9, salida_9);
    if(panel[8].estadoFinal!=panel[8].estadoInicial){
      ejecutarAccion(8);
    }

    salida_10 = ctrl_iluminacion(now, panel[9].automatico, panel[9].I, ontime_R_10, offtime_R_10, day_week, panel[9].lunes, panel[9].martes, panel[9].miercoles, panel[9].jueves, panel[9].viernes, panel[9].sabado, panel[9].domingo );
    panel[9].estadoFinal = salida_10;
    mcp.digitalWrite(OUTPUT10, salida_10);
    if(panel[9].estadoFinal!=panel[9].estadoInicial){
      ejecutarAccion(9);
    }

    salida_11 = ctrl_iluminacion(now, panel[10].automatico, panel[10].I, ontime_R_11, offtime_R_11, day_week, panel[10].lunes, panel[10].martes, panel[10].miercoles, panel[10].jueves, panel[10].viernes, panel[10].sabado, panel[10].domingo );
    panel[10].estadoFinal = salida_11;
    mcp.digitalWrite(OUTPUT11, salida_11);
    if(panel[10].estadoFinal!=panel[10].estadoInicial){
      ejecutarAccion(10);
    }


    salida_12 = ctrl_iluminacion(now, panel[11].automatico, panel[11].I, ontime_R_12, offtime_R_12, day_week, panel[11].lunes, panel[11].martes, panel[11].miercoles, panel[11].jueves, panel[11].viernes, panel[11].sabado, panel[11].domingo );
    panel[11].estadoFinal = salida_12;
    mcp.digitalWrite(OUTPUT12, salida_12);
    if(panel[11].estadoFinal!=panel[11].estadoInicial){
      ejecutarAccion(11);
    }

    salida_13 = ctrl_iluminacion(now, panel[12].automatico, panel[12].I, ontime_R_13, offtime_R_13, day_week, panel[12].lunes, panel[12].martes, panel[12].miercoles, panel[12].jueves, panel[12].viernes, panel[12].sabado, panel[12].domingo );
    panel[12].estadoFinal = salida_13;
    mcp.digitalWrite(OUTPUT13, salida_13);
    if(panel[12].estadoFinal!=panel[12].estadoInicial){
      ejecutarAccion(12);
    }

    salida_14 = ctrl_iluminacion(now, panel[13].automatico, panel[13].I, ontime_R_14, offtime_R_14, day_week, panel[13].lunes, panel[13].martes, panel[13].miercoles, panel[13].jueves, panel[13].viernes, panel[13].sabado, panel[13].domingo );
    panel[13].estadoFinal = salida_14;
    mcp.digitalWrite(OUTPUT14, salida_14);
    if(panel[13].estadoFinal!=panel[13].estadoInicial){
      ejecutarAccion(13);
    }

    salida_15 = ctrl_iluminacion(now, panel[14].automatico, panel[14].I, ontime_R_15, offtime_R_15, day_week, panel[14].lunes, panel[14].martes, panel[14].miercoles, panel[14].jueves, panel[14].viernes, panel[14].sabado, panel[14].domingo );
    panel[14].estadoFinal = salida_15;
    mcp.digitalWrite(OUTPUT15, salida_15);
    if(panel[14].estadoFinal!=panel[14].estadoInicial){
      ejecutarAccion(14);
    }

    salida_16 = ctrl_iluminacion(now, panel[15].automatico, panel[15].I, ontime_R_16, offtime_R_16, day_week, panel[15].lunes, panel[15].martes, panel[15].miercoles, panel[15].jueves, panel[15].viernes, panel[15].sabado, panel[15].domingo );
    panel[15].estadoFinal = salida_16;
    mcp.digitalWrite(OUTPUT16, salida_16);
    if(panel[15].estadoFinal!=panel[15].estadoInicial){
      ejecutarAccion(15);
    }

    salida_17 = ctrl_iluminacion(now, panel[16].automatico, panel[16].I, ontime_R_17, offtime_R_17, day_week, panel[16].lunes, panel[16].martes, panel[16].miercoles, panel[16].jueves, panel[16].viernes, panel[16].sabado, panel[16].domingo );
    panel[16].estadoFinal = salida_17;
    digitalWrite(OUTPUT17, salida_17);
    if(panel[16].estadoFinal!=panel[16].estadoInicial){
      ejecutarAccion(16);
    }

    salida_18 = ctrl_iluminacion(now, panel[17].automatico, panel[17].I, ontime_R_18, offtime_R_18, day_week, panel[17].lunes, panel[17].martes, panel[17].miercoles, panel[17].jueves, panel[17].viernes, panel[17].sabado, panel[17].domingo );
    panel[17].estadoFinal = salida_18;
    digitalWrite(OUTPUT18, salida_18);
    if(panel[17].estadoFinal!=panel[17].estadoInicial){
      ejecutarAccion(17);
    }

    salida_19 = ctrl_iluminacion(now, panel[18].automatico, panel[18].I, ontime_R_19, offtime_R_19, day_week, panel[18].lunes, panel[18].martes, panel[18].miercoles, panel[18].jueves, panel[18].viernes, panel[18].sabado, panel[18].domingo );
    panel[18].estadoFinal = salida_19;
    digitalWrite(OUTPUT19, salida_19);
    if(panel[18].estadoFinal!=panel[18].estadoInicial){
      ejecutarAccion(18);
    }

    salida_20 = ctrl_iluminacion(now, panel[19].automatico, panel[19].I, ontime_R_20, offtime_R_20, day_week, panel[19].lunes, panel[19].martes, panel[19].miercoles, panel[19].jueves, panel[19].viernes, panel[19].sabado, panel[19].domingo );
    panel[19].estadoFinal = salida_20;
    digitalWrite(OUTPUT20, salida_20);
    if(panel[19].estadoFinal!=panel[19].estadoInicial){
      ejecutarAccion(19);
    }

    //printTodo();
  }
  // After calling stream.keepAlive, now we can track the server connecting status
  if (!stream.httpConnected()){
    Serial.println("Desconexión http");
  }
  if(flag){
    //printTodo();
    flag=false;
  }
  if((buttonState > 3000) && (buttonState < 42000)){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(45, 5);
    display.println("1");
    display.setCursor(55, 5);
    display.println("2");
    display.setCursor(65, 5);
    display.println("3");
    display.setCursor(75, 5);
    display.println("4");
    display.setCursor(85, 5);
    display.println("5");
    display.setCursor(95, 5);
    display.println("6");
    display.setCursor(105, 5);
    display.println("7");
    display.setCursor(115, 5);
    display.println("8");

    display.setCursor(0, 20);
    display.println("Outputs");
    display.setCursor(45, 20);
    display.println(panel[0].estadoFinal);
    display.setCursor(55, 20);
    display.println(panel[1].estadoFinal);
    display.setCursor(65, 20);
    display.println(panel[2].estadoFinal);
    display.setCursor(75, 20);
    display.println(panel[3].estadoFinal);
    display.setCursor(85, 20);
    display.println(panel[4].estadoFinal);
    display.setCursor(95, 20);
    display.println(panel[5].estadoFinal);
    display.setCursor(105, 20);
    display.println(panel[6].estadoFinal);
    display.setCursor(115, 20);
    display.println(panel[7].estadoFinal);
    display.setCursor(0, 30);
    display.println("Outputs");
    display.setCursor(45, 30);
    display.println(panel[8].estadoFinal);
    display.setCursor(55, 30);
    display.println(panel[9].estadoFinal);
    display.setCursor(65, 30);
    display.println(panel[10].estadoFinal);
    display.setCursor(75, 30);
    display.println(panel[11].estadoFinal);
    display.setCursor(85, 30);
    display.println(panel[12].estadoFinal);
    display.setCursor(95, 30);
    display.println(panel[13].estadoFinal);
    display.setCursor(105, 30);
    display.println(panel[14].estadoFinal);
    display.setCursor(115, 30);
    display.println(panel[15].estadoFinal);
    display.display();
    display.clearDisplay();
  }else if((buttonState > 1300) && (buttonState < 2650)){
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Restarting 5s...: ");
    display.display();
    delay(5000);
    ESP.restart();
  }else{
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Now: ");
    display.setCursor(25, 10);
    display.print(now);
    display.setCursor(55, 10);
    display.println("Day: ");
    display.setCursor(85, 10);
    display.print(day_week);
    if ((WiFi.status() != WL_CONNECTED)){
      display.setCursor(0, 25);
      display.println("Desconexion WiFi");
    }else{
      display.setCursor(0, 25);
      display.println("Conexion WiFi");
    }
    display.display();
  }
}


void printTodo(){
  Serial.println("CAMBIO");
  for(int i=0;i<20;i++){
    Serial.println("RETORNO: "+String(i+1));
    Serial.println("  Automatico: "+String(panel[i].automatico));
    Serial.println("  Lunes: "+String(panel[i].lunes));
    Serial.println("  Martes: "+String(panel[i].martes));
    Serial.println("  Miercoles: "+String(panel[i].miercoles));
    Serial.println("  Viernes: "+String(panel[i].viernes));
    Serial.println("  Sabado: "+String(panel[i].sabado));
    Serial.println("  Domingo: "+String(panel[i].domingo));
    Serial.println("  ON_min: "+String(panel[i].ON_min));
    Serial.println("  ON_h: "+String(panel[i].ON_h));
    Serial.println("  OFF_min: "+String(panel[i].OFF_min));
    Serial.println("  OFF_h: "+String(panel[i].OFF_h));
    Serial.println("  I: "+String(panel[i].I));
    Serial.println("-------------------------------------------------------------------------");

  }
  //flag=false;
}

void procesarPath(String path, int retorno, String subpath,StreamData data){
  subpath=path.substring(4,path.lastIndexOf("_"));
  retorno =path.substring(1,3).toInt()-1;
  //Serial.println(subpath);
  //Serial.println(retorno);
  //Serial.print("DATO: ");
  //Serial.println(data.intData());
  if(subpath=="Lunes"){
      //Serial.println("Fue Lunes");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].lunes=data.intData();
  }else if(subpath=="Martes"){
      //Serial.println("Fue Martes");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].martes=2;
      }else{
        panel[retorno].martes=0;
      }
      
  }else if(subpath=="Miercoles"){
      //Serial.println("Fue Miercoles");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].miercoles=3;
      }else{
        panel[retorno].miercoles=0;
      }
  }else if(subpath=="Jueves"){
      //Serial.println("Fue Jueves");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].jueves=4;
      }else{
        panel[retorno].jueves=0;
      }
  }else if(subpath=="Viernes"){
      //Serial.println("Fue Viernes");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].viernes=5;
      }else{
        panel[retorno].viernes=0;
      }
  }else if(subpath=="Sabado"){
      //Serial.println("Fue Sabado");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].sabado=6;
      }else{
        panel[retorno].sabado=0;
      }
  }else if(subpath=="Domingo"){
      //Serial.print("Fue Domingo");
      //Serial.println("Retorno "+String(retorno));
      if(data.intData()==1){
        panel[retorno].domingo=7;
      }else{
        panel[retorno].domingo=0;
      }

  }else if(subpath=="automatico"){
      //Serial.println("Fue automatico");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].automatico=data.intData();
  }else if(subpath=="OFF_h"){
      //Serial.println("Fue OFF_h");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].OFF_h=data.intData();
  }else if(subpath=="OFF_min"){
      //Serial.println("Fue OFF_min");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].OFF_min=data.intData();
  }else if(subpath=="ON_h"){
      //Serial.println("Fue ON_h");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].ON_h=data.intData();
  }else if(subpath=="ON_min"){
      //Serial.println("Fue ON_min");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].ON_min=data.intData();
  }else if(subpath=="I"){
      //Serial.println("Fue I");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].I=data.intData();
  }else{
      //Serial.println(subpath);
      Serial.println("No se reconoce el path");
      //Serial.println("Retorno "+String(retorno));
  }
}

void almacenarJson(String path,FirebaseJson::IteratorValue value){
  String subpath=path.substring(0,path.lastIndexOf("_"));
  int retorno =path.substring(path.lastIndexOf("_")+2).toInt()-1;
  //Serial.println("RETORNO: "+path.substring(path.lastIndexOf("_")+2));
  //Serial.println("Subpath: "+subpath);
  //Serial.print("Valor:");
  //Serial.println(value.value.toInt());
  if(subpath=="Lunes"){
      //Serial.println("Fue Lunes");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].lunes=value.value.toInt();
      //Serial.println(value.value.toInt());
  }else if(subpath=="Martes"){
      //Serial.println("Fue Martes");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].martes=2;
      }else{
        panel[retorno].martes=0;
      }
      
  }else if(subpath=="Miercoles"){
      //Serial.println("Fue Miercoles");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].miercoles=3;
      }else{
        panel[retorno].miercoles=0;
      }
  }else if(subpath=="Jueves"){
      //Serial.println("Fue Jueves");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].jueves=4;
      }else{
        panel[retorno].jueves=0;
      }
  }else if(subpath=="Viernes"){
      //Serial.println("Fue Viernes");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].viernes=5;
      }else{
        panel[retorno].viernes=0;
      }
  }else if(subpath=="Sabado"){
      //Serial.println("Fue Sabado");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].sabado=6;
      }else{
        panel[retorno].sabado=0;
      }
  }else if(subpath=="Domingo"){
      //Serial.print("Fue Domingo");
      //Serial.println("Retorno "+String(retorno));
      if(value.value.toInt()==1){
        panel[retorno].domingo=7;
      }else{
        panel[retorno].domingo=0;
      }
  }else if(subpath=="automatico"){
      //Serial.println("Fue automatico");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].automatico=value.value.toInt();
  }else if(subpath=="OFF_h"){
      //Serial.println("Fue OFF_h");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].OFF_h=value.value.toInt();
  }else if(subpath=="OFF_min"){
      //Serial.println("Fue OFF_min");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].OFF_min=value.value.toInt();
  }else if(subpath=="ON_h"){
      //Serial.println("Fue ON_h");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].ON_h=value.value.toInt();
  }else if(subpath=="ON_min"){
      //Serial.println("Fue ON_min");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].ON_min=value.value.toInt();
  }else if(subpath=="I"){
      //Serial.println("Fue I");
      //Serial.println("Retorno "+String(retorno));
      panel[retorno].I=value.value.toInt();
  }else{
      //Serial.println(subpath);
      Serial.println("No se reconoce el path");
      //Serial.println("Retorno "+String(retorno));
  }
}

bool ctrl_iluminacion(int h_actual, int hab_auto, int manual, int h_on, int h_off, int d_semana, int d_lunes, int d_martes, int d_miercoles, int d_jueves, int d_viernes, int d_sabado, int d_domingo){
  bool salida;
  int bandera_1;
  if(hab_auto==1){
    if(h_on < h_off){
      if(((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_lunes))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_martes))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_miercoles))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_jueves))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_viernes))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_sabado))||((h_actual >= h_on && h_actual < h_off ) && (d_semana == d_domingo))){
        bandera_1 = 1;
      }else{
        bandera_1 = 0;
      }
    }
    if(h_on > h_off){
      if(((h_actual >= h_on || h_actual < h_off) && (d_semana == d_lunes)) ||((h_actual >= h_on || h_actual < h_off) && (d_semana == d_martes)) || ((h_actual >= h_on || h_actual < h_off) && (d_semana == d_miercoles)) || ((h_actual >= h_on || h_actual < h_off) && (d_semana == d_jueves)) || ((h_actual >= h_on || h_actual < h_off) && (d_semana == d_viernes)) || ((h_actual >= h_on || h_actual < h_off) && (d_semana == d_sabado)) || ((h_actual >= h_on || h_actual < h_off) && (d_semana == d_domingo))){
        bandera_1 = 1;
      }else{
        bandera_1 = 0;
      }
    }
  }else{
    bandera_1 = 0;
  }
  if(manual == 1 || bandera_1 == 1){
    salida = true;
  }else{
    salida = false;
  }
  return salida;
}

void ejecutarAccion(int retorno){
  String path;
  if(retorno> 8){
    path="Iluminacion_CV/PANEL2_INFORMACION/R"+String(retorno+1)+"/estado";
  }else{
    path="Iluminacion_CV/PANEL2_INFORMACION/R0"+String(retorno+1)+"/estado";
  }
  if(panel[retorno].estadoFinal==true){
    if((Firebase.setBool(fbdo,path,true))){
      panel[retorno].estadoInicial=panel[retorno].estadoFinal;
    }else{
      Serial.println("No se escribio");
    }
  }else{
    if((Firebase.setBool(fbdo,path,false))){
      panel[retorno].estadoInicial=panel[retorno].estadoFinal;
    }else{
      Serial.println("No se escribio");
    }
  }
  
}