#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void printDate(date Date);
void getNTP_Time();
bool isMonth(int number);
bool isDay(int number);
bool isAValidDate(int day,int month);
bool isFormat(char c1,char c2,char c3,char c4,char c5);
dupleInt isValidSetDate(char c1,char c2,char c3,char c4,char c5);
bool isAValidTime(int hour,int min);
dupleInt isValidSetTime(char c1,char c2,char c3, char c4,char c5);
bool selectAction(short int action);
void readCommand();
bool dateOrder(dupleInt date1,dupleInt date2);
bool isSummerTime();
void addOneHour();
void updateTime();
bool timeOrder(dupleInt time1,dupleInt time2);
bool verifyAlarm();

#endif