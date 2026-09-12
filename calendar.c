#include <stdio.h>
#include "calendar.h"


 int is_leap(int year){  //Aqui comprobamos si el año actual es o no bisiesto
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/*
 *
 *
    ╔══════════════════════╗
    ║       July 2026      ║ 
    ╠══════════════════════╣
    ║ Su Mo Tu We Th Fr Sa ║
    ║          1  2  3  4  ║
    ║  5  6  7  8  9 10 11 ║
    ║ 12 13 14 15 16 17 18 ║
    ║ 19 20 21 22 23 24 25 ║
    ║ 26 27 28 29 30 31    ║
    ╚══════════════════════╝*
 *
 *Así es como debería de verse la segunda versión del calendario
 Esta versión del calendario está en desarrollo*
 * */

static const char *months_name[12] = {"January", "February", "March", "April", "May", "June", "July",
                        "August", "September", "October", "November", "December"};

static const char *wdays[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

/*Los dos arrays de abajo no tiene perdida porque son los meses y los
acronimos de los días de la semana*/

int days_in_month(int month, int year){ //Aqui calculamos los dias que tiene el mes
    if (month == 2){
        return is_leap(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }

    return 31;
}

/* h = (q + ⌊(13(m+1))/5] + K + ⌊K/4⌋ + ⌊J/4⌋ + 5J) % 7
FORMULA DE ZELLER PARA SACAR EL DÍA DE LA SEMANA CORRESPONDIENTE*/

int get_weekday(int day, int month, int year) { //Aqui obtenemos el primer dia de la primera semana del mes

    if (month < 3){ // Esta comparativa se hace porque al usar el Epoch time, suele haber una desincronización
        month += 12;
        year -= 1;
    }

    int q = day, m = month, K = year % 100, J = year / 100;
    int h = (q + ((13*(m+1))/5) + K + (K/4) + (J/4) + 5*J ) % 7;
    return h == 0 ? 7 : h;
}

void print_header(int month, int year){ //aqui imprimimos algo como "December 2067" y eso y lo centramos con espacios
   
    puts("╔══════════════════════╗");
    printf("║    ");
    printf("%s %04d", months_name[month - 1], year);
    if (month == 1 || month == 10 ) printf("      ║\n");
    else if (month == 2 || month == 11 || month == 12) printf("     ║\n");
    else if (month == 3 || month == 4) printf("        ║\n");
    else if (month == 5) printf("          ║\n");
    else if (month == 6 || month == 7) printf("         ║\n");
    else if (month == 8) printf("       ║\n");
    else if (month == 9) printf("    ║\n");
    

    puts("╠══════════════════════╣"); 
}

void print_weekdays(){ //Y aquí lo mismo de antes pero con los acronimos de los días de la semana
    int i;
    printf("║ ");
    for (i = 0; wdays[i] != NULL; i++){
        printf("%s ", wdays[i]);
    }
    printf("║\n");
}

void print_calendar(int day, int month_days, int date_day, int date_month, int date_year, int current_day, int current_month, int current_year){ //En esta funcion imprimimos los numeros del calendario
    //printf("\n");
    int i, k = 0; 
    printf("║ ");
    for (int j = 1; j < day; j++){ //En este bucle se imprimen los espacios antes de que inicie el día 1
        printf("   ");
        k++;
    }
    
    for (i = 1; i <= month_days; i++){ //Y en este bucle se imprime día por día
        k++;
        
        if (k == 1 || k == 7) printf("\033[31m%2d \033[0m", i); 
        else if (i == current_day && date_month == current_month && date_year == current_year) printf("\033[7m%2d\033[0m ", i);
        else printf("%2d ", i);
        
        if (k == 7){
            printf("║");
            printf("\n");
            if (i != month_days) printf("║ ");
            k = 0;
        }
    }

    if (k != 0){
        while (k < 7){
            printf("   ");
            k++;        
        }
    printf("║\n");
    }

    puts("╚══════════════════════╝");
}


