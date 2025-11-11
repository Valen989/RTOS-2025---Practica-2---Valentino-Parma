/************************************************************************************
 *  RTOS
 *  Valentino Parma
 *  2025
 *  Practica N°2
 *  Ejercicio 3
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

char frase3[] = "Tarea periódica ejecutando\n";

/* Prototipos */
void vTask1(void* pvParameters);

void vTareaPeriodica(void* pvParameters);





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
        1,        /* Esta tarea se ejecutará en prioridad 1. */
        NULL);   /* No usamos handle de tarea. */

    /* Tarea periódica con vTaskDelayUntil(), prioridad 2 */
    xTaskCreate(vTareaPeriodica, "Tarea 3", 1000, frase3, 2, NULL);


    /* Arranque del scheduler. */
    vTaskStartScheduler();

    vPrintString("Inicio scheduler");

    /* Esta linea no debería ser alcanzada porque vTaskStartScheduler()
    *  solo retornará si no hay suficiente memoria en la heap de FreeRTOS disponible para
    *  crear la tarea Idle. */
    for (; ; )
    {
    }


}
/*-----------------------------------------------------------*/


/* Tareas continuas: imprimen sin demoras */
void vTask1(void* pvParameters)
{
    for (;;)
    {
        vPrintString(pvParameters);
        /* Sin delay */
    }
}

/* Tarea periódica: imprime cada 200 ms */
void vTareaPeriodica(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xPeriod = pdMS_TO_TICKS(200);

    for (;;)
    {
        vPrintString(pvParameters);
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}