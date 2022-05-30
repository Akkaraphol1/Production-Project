/************************************************************************************
 *  Created By: Tauseef Ahmad
 *  Created On: October 23, 2021
 *  
 *  Tutorial Video: https://youtu.be/yem5EysVloc
 *  My Channel: https://www.youtube.com/channel/UCOXYfOHgu-C-UfGyDcu5sYw/
 *  
 *  *********************************************************************************
 *  Preferences--> Aditional boards Manager URLs : 
 *  For ESP32:
 *  https://dl.espressif.com/dl/package_esp32_index.json
 *  
 **********************************************************************************/
 
//----------------------------
#include <WiFi.h>
#include <HTTPClient.h>
//----------------------------

// Time and Date

#include "time.h"
//--------------------------------------------

#include <SoftwareSerial.h>
SoftwareSerial mySerial(32, 33); // RX, TX

#define WIFI_STA_NAME "GTT"
#define WIFI_STA_PASS "56/17Thai.EE"

//String inputstring = "";
String Data;

//--------------------------------------------

//---------------------------------------------------------------------

//ENTER_GOOGLE_DEPLOYMENT_ID
String GOOGLE_SCRIPT_ID = "AKfycbyYBvFH1heOUfRYT5lL9VwN3dPmu7yGNT6b0tJgm5IAUwrkOvM";
//---------------------------------------------------------------------

//const int sendInterval = 2000;

/************************************************************************************
 *  setup function starts
 **********************************************************************************/

 void setup() {

Serial.begin(9600);
   // Serial.println("Date & Time, Barcode");
  while (!Serial) ;
  mySerial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_STA_NAME, WIFI_STA_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

void loop() {


// The formattedDate comes with the following format:
  // 2018-05-28T16:00:13Z
  // We need to extract date and time

   while (mySerial.available() > 0)
  {
    int con = 0;
    String shows = "";
    Data = mySerial.readString();
    //Serial.print(Data);
      if (Data.length()- 2 == 6 && (Data.toInt() >= 000000 && Data.toInt() < 1000000 ))
      {

            //Serial.print(",");
             Serial.println(Data);
             con = Data.toInt();
             shows = "out";
             Serial.println(shows);
    
     print_speed(con,shows);
      }
      else
      {
     Serial.print("");
      }
  }

}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void print_speed(int cons, String showss)
{

  String param;

     param  = "id="+String(cons);
     param  += "&status="+String(showss);

    Serial.println(param);
    write_to_google_sheet(param);
  

}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM


/************************************************************************************
 *  loop function starts
 **********************************************************************************/
void write_to_google_sheet(String params) {
   HTTPClient http;
   String url="https://script.google.com/macros/s/"+GOOGLE_SCRIPT_ID+"/exec?"+params;
   //Serial.print(url);
    Serial.println("Send data Scanner to Google Sheet");
    //---------------------------------------------------------------------
    //starts posting data to google sheet
    http.begin(url.c_str());
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);
    int httpCode = http.GET();  
    Serial.print("HTTP Status Code: ");
    Serial.println(httpCode);
    //---------------------------------------------------------------------
    //getting response from google sheet
    String payload;
    if (httpCode > 0) {
        payload = http.getString();
        Serial.println("Payload: "+payload);     
    }
    //---------------------------------------------------------------------
    http.end();
}
//MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
