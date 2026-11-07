void printDate(date Date)
{
  Serial.println((Date.day<10?"0":"")+String(Date.day) + "/" +(Date.month<10?"0":"")+String(Date.month) + "/" +String(Date.year)+"@"+(Date.hour<10?"0":"")+String(Date.hour)+":"+(Date.min<10?"0":"")+String(Date.min)+":"+(Date.sec<10?"0":"")+String(Date.sec));
}

void getNTP_Time()
{
  
  //Serial.print("UTC time: ");
  char flag = timeClient.update();
  time_t epochTime = timeClient.getEpochTime();
  struct tm *ptm =gmtime((time_t *)&epochTime);
  unsigned short int currentDay = ptm->tm_mday;
  unsigned int currentYear = ptm->tm_year + 1900;
  unsigned short int currentMonth = ptm->tm_mon +1;
  unsigned short int currentSec = timeClient.getSeconds();
  unsigned short int currentMin = timeClient.getMinutes();
  unsigned short int currentHour = timeClient.getHours();
  date result = {currentDay,currentMonth,currentYear,currentHour,currentMin,currentSec};
  
  /*
  printDate(result);
  String currentDateX = "OWO"+ String(currentDay) + "/" +String(currentMonth) + "/" +String(currentYear);
  Serial.print(currentDateX);
  Serial.print("@");
  Serial.print(currentHour);
  Serial.print(":");
  Serial.println(currentMin);
  if(!flag) Serial.println("flag no");
  */
  if (!flag){
    //Serial.println("XD");
    /*
    String currentDateX = String(currentDay) + "/" +String(currentMonth) + "/" +String(currentYear);
    Serial.print(currentDateX);
    Serial.print("@");
    Serial.print(currentHour);
    Serial.print(":");
    Serial.println(currentMin);
    */
    date result = {currentDay,currentMonth,currentYear,currentHour,currentMin,currentSec};
    //printDate(result);
    currentDate=result;
  }
  else{
    //Serial.println("NTP not working");
  }
}

bool isMonth(int number)
{
  return 1<=number && number<=12;
}

bool isDay(int number)
{
  return 1<=number && number<=31;
}

bool isAValidDate(int day,int month)
{
  if(isDay(day) && isMonth(month)){
    if((month == 2 && day<=29)||
      (month == 1 ||month ==  3|| month == 5 || month == 7 ||month == 8 ||month == 10 ||month == 12)&&(day<=31)|| 
      (month == 4 ||month ==  6|| month == 9 || month == 11)&&(day<=30))
      {
        return true;
      }
  }
  return false;
}



bool isFormat(char c1,char c2,char c3,char c4,char c5)
{
  return (isDigit(c1) && isDigit(c2) && c3 == '/' && isDigit(c4) && isDigit(c5));
}

dupleInt isValidSetDate(char c1,char c2,char c3,char c4,char c5)
{
    dupleInt result;
    if(isFormat(c1,c2,c3,c4,c5)){
      result.n1 = 10*(c1-'0')+(c2-'0');
      result.n2 = 10*(c4-'0')+(c5-'0');
      if(isAValidDate(result.n1,result.n2))
      {
        return result;
      }
      else
      {
        result.n1=-1;
        result.n2=-1;
        return result;
      }
    }
    else{
      result.n1=-2;
      result.n2=-2;
      return result;
    }
      
}

bool isAValidTime(int hour,int min)
{
  return (0<=hour && hour<=23) && (0<=min && min<=59);
}

dupleInt isValidSetTime(char c1,char c2,char c3, char c4,char c5)
{
  dupleInt result;
  if(isFormat(c1,c2,c3,c4,c5)){
      result.n1 = 10*(c1-'0')+(c2-'0');
      result.n2 = 10*(c4-'0')+(c5-'0');
      if(isAValidTime(result.n1,result.n2)){
        return result;
      }
      else
        {
          result.n1=-1;
          result.n2=-1;
          return result;
        }
    }
    else{
      result.n1=-2;
      result.n2=-2;
      return result;
    }
}

bool selectAction(short int action)
{
  switch(action){
    case SUMMER_TIME:
    {
      printDate(currentDate);
      Serial.println("Command Entered:\n\tSet summer time");
      dupleInt time = isValidSetDate(command[7],command[8],command[9],command[10],command[11]);
      if(time.n1 == -1)
      {
        Serial.println(INVALID_DATE);
        return false;
      }
      else if(time.n1 == -2)
      {
        Serial.println(NON_NUMERICAL_DATE);
        return false;
      }
      else
      {
        Serial.println("\t\tSetting summer time at "+String(time.n1) +"/" + String(time.n2));
        summer_time=time;
        return true;
      }
    }

    
    case WINTER_TIME:
    {
      Serial.println("Command Entered:\n\tSet winter time");
      dupleInt time = isValidSetDate(command[7],command[8],command[9],command[10],command[11]);
      if(time.n1 == -1)
      {
        Serial.println(INVALID_DATE);
        return false;
      }
      else if(time.n1 == -2)
      {
        Serial.println(NON_NUMERICAL_DATE);
        return false;
      }
      else
      {
        Serial.println("\t\tSetting winter time at "+String(time.n1) +"/" + String(time.n2));
        winter_time=time;
        return true;
      }
    }
    case SET_ALARM_ON:
    {
      Serial.println("Command Entered:\n\tSet alarm on");
      dupleInt time = isValidSetTime(command[13],command[14],command[15],command[16],command[17]);
      if(time.n1 == -1)
      {
        Serial.println(INVALID_TIME);
        return false;
      }
      else if(time.n1 == -2)
      {
        Serial.println(NON_NUMERICAL_TIME);
        return false;
      }
      else
      {
        Serial.println("\t\tSetting alarm on at "+String(time.n1) +"/" + String(time.n2));
        alarmON = time;
        return true;
      }
    }
    case SET_ALARM_OFF:
    {
      Serial.println("Command Entered:\n\tSet alarm off");
      dupleInt time = isValidSetTime(command[14],command[15],command[16],command[17],command[18]);
      if(time.n1 == -1)
      {
        Serial.println(INVALID_TIME);
        return false;
      }
      else if(time.n1 == -2)
      {
        Serial.println(NON_NUMERICAL_TIME);
        return false;
      }
      else
      {
        Serial.println("\t\tSetting alarm off at "+String(time.n1) +"/" + String(time.n2));
        alarmOFF = time;
        return true;
      }
    }
      return false;
    case HELP:
      Serial.println("Command Entered:\n\thelp"); 
      Serial.println(HELP_MSG);
      return true;
    case LED_ON:
      Serial.println("Command Entered:\n\tSet led on"); 
      digitalWrite(LED, LOW);
      Serial.println("\t\tDone succesfully");
      manualLED = true;
      return true;
    case LED_OFF:
      Serial.println("Command Entered:\n\tSet led off"); 
      digitalWrite(LED, HIGH);
      Serial.println("\t\tDone succesfully");
      manualLED = true;
      return true;
  }
  return false;
}



void readCommand()
{

  if(Serial.available()){
    inBytePrevious=inByteNow; 
    inByteNow=Serial.read();
    //Serial.println(String((int)inBytePrevious)+","+String((int)inByteNow));
    if((int)inByteNow == LAST_CHAR && (int)inBytePrevious== FIRST_CHAR){
      
      for(int i = 0; i<COMMAND_LIST_LEN; i++){
        //Serial.print("Comparing "); Serial.print(command);  Serial.print(" to "); Serial.print(commandList[i]);
        if(command.substring(0,commandList[i].length()) == commandList[i]){
          //Serial.println(": TRUE");
          if(selectAction(i)==true){
            updateTime();
            printDate(currentDate);
            cindex=0;
            return;
          }
          break;
        }
        //else Serial.println(": FALSE");
      }
      printDate(currentDate);
      Serial.print("Command not recognized:\n\t");
      
      for(int i =0;(i<COMMAND_MAX-1) && (i<=cindex-2);i++){
        Serial.print(command[i]);
      }
      Serial.println("");
      cindex = 0;
    }
    else{
      command[cindex]=inByteNow;
      if(cindex<COMMAND_MAX)
        cindex++;
      else
        cindex=0;
    }
  }
  
}

bool dateOrder(dupleInt date1,dupleInt date2)
{
  if( (date2.n2>date1.n2) || ((date2.n2==date1.n2)&&(date2.n1>date1.n1)) )
    return true;
  return false;
}

bool isSummerTime()
{
  if(
    (summer_time.n1==-1 || summer_time.n2==-1 || winter_time.n1==-1 || winter_time.n2==-1) ||
    (summer_time.n1==winter_time.n1 && summer_time.n2==winter_time.n2)
    ) //ERROR, summer time and/or winter time invalid/s
    return false;
  
  dupleInt cdate={currentDate.day,currentDate.month};
  /*
  Serial.println(String(cdate.n1) + ":" + String(cdate.n2));
  if(dateOrder(winter_time,summer_time))
    Serial.println("Winter before summer");
  if (dateOrder(summer_time,cdate) || dateOrder(cdate,winter_time))
    Serial.println("summer<cd<winter");
  if(dateOrder(summer_time,winter_time))
    Serial.println("summer before winter");
  if(dateOrder(cdate,summer_time) || dateOrder(winter_time,cdate))
    Serial.println("winter<cd<summer");
  */

  if(
    (dateOrder(winter_time,summer_time) && (dateOrder(cdate,summer_time) || dateOrder(winter_time,cdate) ) )||
    (dateOrder(summer_time,winter_time) && (dateOrder(summer_time,cdate) && dateOrder(cdate,winter_time) ) )
    )
    return true;
  return false;

}

void addOneHour()
{
  currentDate.hour++;
  if(currentDate.hour>23){
    currentDate.hour = 0;
    currentDate.day++;
  }
  if(!isAValidDate(currentDate.day,currentDate.month)){
    currentDate.day=1;
    currentDate.month++;
  }
  if(!isAValidDate(currentDate.day,currentDate.month)){
    currentDate.month=1;
    currentDate.year++;
  }
}

void updateTime()
{
  
  getNTP_Time();
  //printDate(currentDate);
  if(isSummerTime())
     addOneHour();
    
}

bool timeOrder(dupleInt time1,dupleInt time2)
{
  if( (time2.n1>time1.n1) || ((time2.n1==time1.n1)&&(time2.n2>time1.n2)) )
    return true;
  return false;
}

bool verifyAlarm()
{
  if(
    (alarmON.n1==-1 || alarmON.n2==-1 || alarmOFF.n1==-1 || alarmOFF.n2==-1) ||
    (alarmON.n1==alarmOFF.n1 && alarmON.n2==alarmOFF.n2)
    ) //ERROR, summer time and/or winter time invalid/s
    {
      //Serial.println("not valid alarm");
      return false;
    }
    
  
  dupleInt ctime={currentDate.hour,currentDate.min};
  
  if(timeOrder(alarmON,alarmOFF))
    Serial.println("ON<OFF");
  if(timeOrder(alarmOFF,alarmON))
    Serial.println("OFF<ON");
  if((timeOrder(alarmON,ctime) && timeOrder(ctime,alarmOFF)))
    Serial.println("ON<ctime<OFF");
  if((timeOrder(ctime,alarmOFF) || timeOrder(alarmON,ctime)))
    Serial.println("ctime<OFF || ON<cTime");
  
  if(
    (timeOrder(alarmON,alarmOFF) &&(timeOrder(alarmON,ctime) && timeOrder(ctime,alarmOFF)))
    ||
    (timeOrder(alarmOFF,alarmON) &&(timeOrder(ctime,alarmOFF) || timeOrder(alarmON,ctime)))
    )
    {
      //Serial.println("Led encendido");
      return true;
    }
    
  return false;
}