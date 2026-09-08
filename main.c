#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include "calendar.h"



int re_tolower(char string[]){

    //char name[] = "KIRITO"
    //re_tolower(name);
    //printf("%s\n", name); -> kirito
    
    int i = 0;
    int j = (int) string[i];
    
    while (string[i] != '\0'){

    int j = (int) string[i]; 
    if (string[i] >= 65 && string[i] <= 90){ j += 32;}
    string[i] = (char)j;
    i++;
    }

    return 0;
}

int main(int argc, char **argv){
    
    time_t current_date = time(NULL); //Primero obtenemos la fecha en segundos del Epoch time gracias a time(NULL);

    //El Epoch time es el tiempo que ha pasado desde el 1 de enero de 1970 

    struct tm *t = localtime(&current_date); /* Luego guardamos la fecha de forma más legible en un puntero a
    struct tm (porque localtime devuelve un puntero) */ 
    Date date = {
        t->tm_mday,
        t->tm_mon + 1,
        t->tm_year + 1900
    };
    

   Date today = {

        t->tm_mday,
        t->tm_mon + 1,
        t->tm_year + 1900


   }; 


    /*Después copiamos los datos correspondientes del dia mes y año obtenidos con el puntero *t al struct
    (Date) today para saber la fecha de ese día y poner el encabezado del mes y esas cosas*/

    static const char *mn[12] = {"january", "february", "march", "april", "may", "june", "july",  // mn -> months name
                        "august", "september", "october", "november", "december"};

    static const char *mn_short[12] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

    
  
    for (int i = 0; mn[i] != NULL && mn_short[i] != NULL && argc >= 2; i++){
        //printf("%s\n", mn_short[i]); 
        re_tolower(argv[1]);
        if (strcmp(argv[1], mn[i]) == 0) date.month = i + 1;
        else if (strcmp(argv[1], mn_short[i]) == 0){mn_short[i] = mn[i]; date.month = i + 1;}
     
    }

    if (argc >= 3 && argv[2] != NULL){
        int i = atoi(argv[2]);
        if (i != 0 && i >= 1000  && i <= 9999) date.year = i; 
    }


    int DIM = days_in_month(date.month, date.year); // DIM -> Days In Month
    int weekday = get_weekday(1, date.month, date.year);
    puts("");    
    print_header(date.month, date.year); 
    print_weekdays();
    print_calendar(weekday, DIM, date.day, date.month, date.year, today.day, today.month, today.year);
    puts(""); 
}
