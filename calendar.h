#ifndef CALENDAR_H
#define CALENDAR_H

typedef unsigned long re_size_t;

typedef struct{
    int day;
    int month;
    int year;
} Date; 

void printCalendar(int day, int month_days, int date_day, int date_month, int date_year, int current_day, int current_month, int current_year);
void printWeekdays();
void printHeader(int month, int year);
int isLeap(int year);
int daysInMonth(int month, int year);
int getWeekday(int day, int month, int year);


#endif
