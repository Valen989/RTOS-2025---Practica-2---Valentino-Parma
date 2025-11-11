/************************************************************************************
 *  RTOS
 *  Valentino Parma
 *  2025
 *  Practica N°2
 *  Ejercicio 1
 *
 ************************************************************************************/


 /* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"


/* Demo includes. */
#include "supporting_functions.h"


/* Usado como contador de loop para implementar un delay bloqueante */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )


/*-----------------------------------------------------------*/


char frase1[] = "Tarea 1 ejecutando \n";

char frase2[] = "Tarea 2 ejecutando \n";

void vTask1(void*);





int main(void)
{
    /* Creación de una tarea. */
    xTaskCreate(vTask1,   /* Puntero a la función que implimenta la tarea. */
        "Task 1", /* Nombre de texto de la tarea, solo se usa en debugging. */
        1000,     /* Profundidad de la pila - la mayoria de los microcontroladores chicos usan mucho menos que esto. */
        frase1,     /* parámetros de tarea. */
        1,        /* Esta tarea se ejecutará en prioridad 1. */
        NULL);   /* No usamos handle de tarea. */

    /* Creación de una tarea. */
    xTaskCreate(vTask1,   /* Puntero a la función que implimenta la tarea. */
        "Task 2", /* Nombre de texto de la tarea, solo se usa en debugging. */
        1000,     /* Profundidad de la pila - la mayoria de los microcontroladores chicos usan mucho menos que esto. */
        frase2,     /* parámetros de tarea. */
        2,        /* Esta tarea se ejecutará en prioridad 2. */
        NULL);   /* No usamos handle de tarea. */



    /* Arranque del scheduler. */
    vTaskStartScheduler();


    /* Esta linea no debería ser alcanzada porque vTaskStartScheduler()
    *  solo retornará si no hay suficiente memoria en la heap de FreeRTOS disponible para
    *  crear la tarea Idle. */
    for (; ; )
    {
    }


    return 0;
}
/*-----------------------------------------------------------*/


void vTask1(void* pvParameters)
{

    volatile uint32_t ul;


    /* Como la mayoria, esta tarea esta implementada con un loop infinito. */
    for (; ; )
    {
        /* Imprime el nombre de la tarea. */
        vPrintString(pvParameters);


        vTaskDelay(pdMS_TO_TICKS(500));
        


        /* Delay bloqueante. */
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
            /* Este delay no hace nada. Más adelante se utilizará
             * una función apropiada para hacer delay/ sleep. */
        }
    }
}

