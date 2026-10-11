#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include "ESP32HTTPClient.h"

//Pin defs
#define TFT_CS 8
#define TFT_RST 9
#define TFT_DC 10

//colours 
#define RED ILI9341_RED
#define ORANGE ILI9341_ORANGE
#define YELLOW ILI9341_YELLOW
#define GREEN ILI9341_GREEN
#define BLUE ILI9341_BLUE
#define PURPLE ILI9341_PURPLE
#define PINK ILI9341_PINK

#define BROWN ILI9341_BROWN
#define BLACK ILI9341_BLACK
#define WHITE ILI9341_WHITE

int delayNum = 100;
int mills = 0;


// Initialize opensky with their base URL
ESP32HTTPClient client("https://opensky-network.org/api");

// create display object
Adafruit_ILI9341 tft =Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);


void setup() {

 //setup tft
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BLACK);
  tft.fillRect(80,80,100,100,RED);
  

  // begin the serial connection
  Serial.begin(115200);

  //setup wifi
  WiFi.begin("Stuff-Fibre_98_2G", "Rapanui2004");
  Serial.println("Connecting");

  //wait until the wifis connected
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(10);
  }

  int time = 0;

  client.get("/states/all").getBody("time", &time);
  Serial.printf("start: %d\n", time);
}
void loop() {
  tft.fillRect(80,80,100,100,GREEN);
  
  //if the wifi is connected it will fetch some data from opensky
  if(WiFi.status() == WL_CONNECTED && mills == delayNum){
    int time = 0;
    client.get("/states/all").getBody("states", &time);

    Serial.printf("time: %d\n", time);
    mills = 0;
  }

  mills++;

  
}