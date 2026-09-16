#ifndef CALENDAR_H
#define CALENDAR_H

/*En este header vamos a declarar los struct, funiones y constantes que va a usar calendar.c*/

typedef struct{
    int day;
    int month;
    int year;
} Date; /*Aqui tenemos un struct que hace alusión a una fecha cualquiera*/

void printCalendar(int day, int month_days, int date_day, int date_month, int date_year, int current_day, int current_month, int current_year);
void printWeekdays();
void printHeader(int month, int year);
int isLeap(int year);
int daysInMonth(int month, int year);
int getWeekday(int day, int month, int year);

/*Y aqui tenemos funciones que va a usar calendar.c para saber si un año en bisiesto o calcular los dias
que hay en el mes actual y mas*/

#endif
