#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
// WIFI_SSID and WIFI_PASSWORD are defined in secrets.h (see secrets.example.h)

#define FIRST_CHAR '\n'
#define LAST_CHAR '\r'

#define COMMAND_MAX 30
#define COMMAND_LIST_LEN 7

#define LED LED_BUILTIN
#define SUMMER_TIME 0
#define WINTER_TIME 1
#define SET_ALARM_ON 2
#define SET_ALARM_OFF 3
#define HELP 4
#define LED_ON 5
#define LED_OFF 6

#define INVALID_DATE "\t\tERROR:Invalid date"
#define NON_NUMERICAL_DATE "\t\tERROR:Non-numerical date"
#define INVALID_TIME "\t\tERROR:Invalid time"
#define NON_NUMERICAL_TIME "\t\tERROR:Non-numerical time"
// FIX 2026: help said mm/dd but the parser (isValidSetDate) reads day first, i.e. dd/mm; text now matches the code.
#define HELP_MSG "\t\tset st dd/mm: Se utiliza para configurar la fecha de inicio del horario de verano.\n\t\tset wt dd/mm: Se utiliza para configurar la fecha de inicio del horario de invierno.\n\t\tset alarm_ON hh/mm: Se configura la hora de encendido de la alarma.\n\t\tset alarm_OFF hh/mm: Se configura la hora de apagado de la alarma.\n\t\thelp: Imprime los comandos y los explica.\n\t\tled ON: enciende el led.\n\t\tled OFF: apaga el led.\n"

// FIX 2026: the original had `date currentDate=...` here, before `date` existed, plus unfinished
// `date`/`time`/`Cdate` classes (invalid `typedef short uint suint`, `void` constructors, missing
// semicolons/parentheses, String.at()/toInt(String) that do not exist, isDate() calling nonexistent
// code). The rest of the program only uses `date` as a plain record with public fields
// (aggregate init + .day/.month/.year/.hour/.min/.sec), so it is now a simple struct.
// The unused `time` and `Cdate` classes were removed (nothing referenced them).
typedef struct dupleInts{
  int n1;
  int n2;
}dupleInt;

struct date
{
  unsigned short int day;
  unsigned short int month;
  unsigned int year;
  unsigned short int hour;
  unsigned short int min;
  unsigned short int sec;
};

// FIX 2026: moved after the definition of `date` (was declared before it existed).
date currentDate={1,10,2023,17,30,10};

#endif
