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
#define HELP_MSG "\t\tset st mm/dd: Se utiliza para configurar la fecha de inicio del horario de verano.\n\t\tset wt mm/dd: Se utiliza para configurar la fecha de inicio del horario de invierno.\n\t\tset alarm_ON hh/mm: Se configura la hora de encendido de la alarma.\n\t\tset alarm_OFF hh/mm: Se configura la hora de apagado de la alarma.\n\t\thelp: Imprime los comandos y los explica.\n\t\tled ON: enciende el led.\n\t\tled OFF: apaga el led.\n"


date currentDate={1,10,2023,17,30,10};
typedef struct dupleInts{
  int n1;
  int n2;
}dupleInt;


typedef short uint suint;


class date
{
  private:
    suint day;
    suint month;
    uint year;
    void date()
    {
      day = 0;
      month = 0;
      year = 0;
    }

    bool isFormat(String s)
    {
      return (isDigit(s.at(0)) && isDigit(s.at(1)) && s.at(3) == '/' && isDigit(s.at(4)) && isDigit(s.at(5)));
    }

    bool isLeap(uint Year = year)
    {
      return ((Year % 4 == 0 && Year % 100 != 0) || Year % 400 == 0)
    }
    bool isMonth31(suint Month = month)
    {
      return (Month == 1 ||Month ==  3|| Month == 5 || Month == 7 ||Month == 8 ||Month == 10 ||Month == 12);
    }

    bool isDate(suint Day, suint Month uint Year)
    {
      return (2023<=Year && Month<=12) && (Month == 2 && (isLeap(Year)?Day<=29:Day<=28)) && (isMonth31(Month)?Day<=31:Day<=30);
    }
  public:
    bool update(suint Day, suint Month, uint Year)
    {
      if(isDate(Day, Month, Year))
      {
        day = Day;
        month = Month;
        year = Year;
        return true;
      }
      return false;
    }
    bool updateByCommand(String s)
    {
      if (!isFormat(s))
        return false;
      
      suint Day = s.toInt(s.substring(0,1));
      suint Month = s.toInt(s.substring(4,5);
      return update(Day, Month, 2023);
    }


};


class time
{
  private:
    suint hour;
    suint min;
    suint sec;
    void time()
    {
      hour = 0;
      min = 0;
      sec = 0;
    }

    

  public:
    bool update(suint Hour, suint Min, suint Sec)
    {
      if(isDate(Hour, Min, Sec))
      {
        hour = Hour;
        min = Min;
        sec = Sec;
        return true;
      }
      return false;
    }
    bool updateByCommand(String s)
    {
      if (!isFormat(s))
        return false;
      
      suint Day = s.toInt(s.substring(0,1));
      suint Month = s.toInt(s.substring(4,5);
      return update(Day, Month, 2023);
    }

};

class Cdate
{

};

#endif

