/************************************************************************************
 *  RTOS
 *  Valentino Parma
 *  2025
 *  Practica N°2
 *  Ejercicio 2
 *
 ************************************************************************************/


 /* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"


/* Demo includes. */
#include "supporting_functions.h"


/* Usado como contador de loop para implementar un delay bloqueante */
#define mainDELAY_LOOP_COUNT    ( 0xffffff )



/* Prototipos de las tareas */
void vTaskA(void* pvParameters);
void vTaskB(void* pvParameters);
void vTaskC(void* pvParameters);

int main(void)
{
    /* Crear las tareas continuas con prioridad 1 */
    xTaskCreate(vTaskA, "TaskA", 400, "Tarea 1 ejecutando\n", 1, NULL);
    xTaskCreate(vTaskB, "TaskB", 400 , "Tarea 2 ejecutando\n", 1, NULL);

    /* Crear la tarea periódica con prioridad 2 */
    xTaskCreate(vTaskC, "TaskC", 400 , "Tarea periodica ejecutando\n", 2, NULL);

    /* Iniciar el planificador */
    vTaskStartScheduler();

    /* Nunca debería llegar aquí */
    for (;;);

    
   
}

/* Tarea A: imprime continuamente */
void vTaskA(void* pvParameters)
{
    const char* msg = (const char*)pvParameters;

    for (;;)
    {
        vPrintString(msg);
    }
}

/* Tarea B: imprime continuamente */
void vTaskB(void* pvParameters)
{
    const char* msg = (const char*)pvParameters;

    for (;;)
    {
        vPrintString(msg);
    }
}

/* Tarea C: periódica con prioridad 2 */
void vTaskC(void* pvParameters)
{
    const char* msg = (const char*)pvParameters;

    TickType_t xLastWakeTime;
    const TickType_t xPeriod = pdMS_TO_TICKS(10); 

    /* Inicializar referencia de tiempo */
    xLastWakeTime = xTaskGetTickCount();

    for (;;)
    {
        vPrintString(msg);

        /* Bloquear hasta el siguiente periodo */
        vTaskDelayUntil(&xLastWakeTime, xPeriod);
    }
}
