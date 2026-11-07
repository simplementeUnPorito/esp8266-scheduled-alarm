#ifndef GLOBAL_VARIABLES_H
#define GLOBAL_VARIABLES_H

//WIFI AND TIME CATCHING
unsigned long mynow;
const long utcOffsetInSeconds = -10800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"pool.ntp.org");

//ALARM AND STATES
dupleInt summer_time = {-1,-1};
dupleInt winter_time = {-1,-1};
dupleInt alarmON = {-1,-1};
dupleInt alarmOFF = {-1,-1};
bool manualLED = false;
bool summerTimePlus1 = false;


//COMMANDS
String command;
int cindex = 0;
char inByteNow=0;
char inBytePrevious=0;

String commandList[]={
  "set st ",
  "set wt ",
  "set alarm_ON ",
  "set alarm_OFF ",
  "help",
  "led ON",
  "led OFF",
};



#endif