#include <stdio.h>
#include "calendar.h"

 
/*
 *
    ╔══════════════════════╗
    ║       July 2026      ║ -> Header del calendario
    ╠══════════════════════╣
    ║ Su Mo Tu We Th Fr Sa ║ -> Días de la semana
    ║          1  2  3  4  ║ 
    ║  5  6  7  8  9 10 11 ║ -> Días enumerados
    ║ 12 13 14 15 16 17 18 ║
    ║ 19 20 21 22 23 24 25 ║
    ║ 26 27 28 29 30 31    ║
    ╚══════════════════════╝*
 *
 *Así es como debería de verse el calendario actual
 * */


re_size_t re_strlen(const char *str){ //Función importada de Re:lib (como le llamo a mi implementación de la libc)
    
    // re_strlen("Python"); -> 6
    // re_strlen(""); -> 0

    re_size_t count = 0; 
    while (*str++) count++;
    return count;

}


void printCenteredHeaderText(const char *text){//Imprimimos el texto del header para que quede centrado

    int len = re_strlen(text);
    int offset1 = (22 - len) / 2;
    int offset2 = (22 - len - offset1);
    printf("%*s", offset1, "");
    printf("%s", text);
    printf("%*s", offset2, "");
    


}

int isLeap(int year){  //Comprobamos si el año actual es o no bisiesto
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


static const char *months_name[12] = {"January", "February", "March", "April", "May", "June", "July",
                        "August", "September", "October", "November", "December"};

static const char *wdays[7] = {"Su", "Mo", "Tu", "We", "Th", "Fr", "Sa"};

/*Los dos arrays de abajo no tiene perdida porque son los meses y los
acronimos de los días de la semana en inglés*/

int daysInMonth(int month, int year){ //Aqui calculamos los dias que tiene el mes
    if (month == 2){
        return isLeap(year) ? 29 : 28;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }

    return 31;
}

/* h = (q + ⌊(13(m+1))/5] + K + ⌊K/4⌋ + ⌊J/4⌋ + 5J) % 7
FORMULA DE ZELLER PARA SACAR EL DÍA DE LA SEMANA CORRESPONDIENTE*/

int getWeekday(int day, int month, int year) { //Obtenemos el primer dia de la primera semana del mes

    if (month < 3){ // Esto se hace porque Enero y Febrero se cuentan como el mes 13 y 14 respectivamente
        month += 12;
        year -= 1;
    }

    //Aplicamos la fórmula de Zeller que hemos visto anteriormente
    int q = day, m = month, K = year % 100, J = year / 100;
    int h = (q + ((13*(m+1))/5) + K + (K/4) + (J/4) + 5*J ) % 7;
    return h == 0 ? 7 : h;
}

void printHeader(int month, int year){ //Imprimimos el header del calendario
   
    puts("╔══════════════════════╗");
    printf("║");
    char text[128];
    snprintf(text, sizeof(text), "%s %04d", months_name[month - 1], year);
    printCenteredHeaderText(text);
    printf("║\n");
    puts("╠══════════════════════╣"); 
}

void printWeekdays(){ //Y aquí lo mismo de antes pero con los acronimos de los días de la semana
    int i;
    printf("║ ");
    for (i = 0; wdays[i] != NULL; i++){
        printf("%s ", wdays[i]);
    }
    printf("║\n");
}

void printNumeratedDays(int day, int month_days, int date_day, int date_month, int date_year, int current_day, int current_month, int current_year){

    //Aquí imprimimos los días enumerados del mes
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


