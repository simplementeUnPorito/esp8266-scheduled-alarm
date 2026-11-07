#include "secrets.h"
#include "definitions.h"
#include "global_variables.h"
#include "functions.h"

void setup() 
{
  char triednumber = 0;
  //configuración puerto E/S
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  //configuración por el puerto serial
  Serial.begin(115200);
  Serial.println();
  
  configTime(0,0,"pool.ntp.org");

  Serial.println();
  Serial.print("Connecting to Wifi ");
  Serial.print(WIFI_SSID);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED && triednumber <20)
  {
      Serial.print(".");
      delay(500);
      triednumber++;
  }
  if(WiFi.status()==WL_CONNECTED)
  {
    Serial.print("\nWifi conected. IP address: ");
    Serial.println(WiFi.localIP());
    timeClient.begin();
    timeClient.setTimeOffset(-10800);
    Serial.println("Ready");
  }
  else
  {
    Serial.println("\nWifi NOT CONNECTED");
  }
}

  

void loop()
{
  
  if(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print("Trying reconnecting to WiFi ");
    Serial.println(WIFI_SSID);
    WiFi.begin(WIFI_SSID,WIFI_PASSWORD);
  }
  else
  {
    updateTime();
    readCommand();
    if(!manualLED)
    {
      if(verifyAlarm())
        digitalWrite(LED,LOW);
      else
        digitalWrite(LED,HIGH);
    }
  }
}

