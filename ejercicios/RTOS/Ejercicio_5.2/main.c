/************************************************************************************
 *  RTOS 
 *  
 *  2025
 *
 *  Práctica 2 - Ejercicio 4
 *  Plantilla
 ************************************************************************************/


/* Archivos de bibliotecas FreeRTOS */


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"


/* Archivos de biblioteca para los ejercicios */


#include "supporting_functions.h"


/* Periodos asignados a los timers one-shot y auto-reload respectivamente */
#define AUTO_RELOAD_TIMER_PERIOD    ( pdMS_TO_TICKS( 500UL ) )

#define ONE_SHOT_TIMER_PERIOD   ( pdMS_TO_TICKS( 3333UL ) )


/* Prototipos de las funciones de callback */
static void prvAutoReloadTimerCallback( TimerHandle_t xTimer );

static void prvOneShotTimerCallback(TimerHandle_t xTimer);

/* Variable global para manejar el one-shot timer */
static TimerHandle_t xOneShotTimer = NULL;

int main( void )
{
    /* Variables para manejo de timers */
    TimerHandle_t xAutoReloadTimer;
    BaseType_t xTimer1Started;
    BaseType_t xTimerStarted;


    /* Creación del timer auto reload */
    xAutoReloadTimer = xTimerCreate( "AutoReload", /* Nombre p/ debugging */
                                     AUTO_RELOAD_TIMER_PERIOD, /* Periodo en ticks */
                                     pdTRUE, /* Seteo de uxAutoRealod a pdFALSE (one shot) */
                                     0, /* Timer id (no usado) */
                                     prvAutoReloadTimerCallback ); /* Función de callback */
   
    /* Creación del timer one-shot */
         xOneShotTimer = xTimerCreate("OneShot",              /* Nombre */
        ONE_SHOT_TIMER_PERIOD,  /* Periodo en ticks */
        pdFALSE,                /* One-shot */
        0,                      /* ID no usado */
        prvOneShotTimerCallback); /* Callback */



    /* Chequeo de la creación exitosa de los timers */
         if ((xAutoReloadTimer != NULL) && (xOneShotTimer != NULL))
    {
        /* Inicio de los timers con block time = 0 (sin block time).
         * El scheduler no ha sido iniciado aún por lo que cualquier tiempo de bloqueo
*  que se ponga será ignorado de todos modos */
        xTimer1Started = xTimerStart( xAutoReloadTimer, 0 );

        xTimerStarted = xTimerStart(xOneShotTimer, 0);


        /* Chequeo de inicio exitoso */
        if ((xTimer1Started == pdPASS) && (xTimerStarted == pdPASS))
        {
            /* Inicio del  scheduler. */
            vTaskStartScheduler();
        }
    }


    /* Si el scheduler inicio exitosamente estas lineas nunca serán ejecutadas */
    for( ; ; )
    {
    }


    return 0;
}



static void prvAutoReloadTimerCallback( TimerHandle_t xTimer )
{
    TickType_t xTimeNow = xTaskGetTickCount();


    vPrintStringAndNumber("ejecutando auto-reload timer callback\n ", xTimeNow);

    /* Reinicio del timer one-shot */
    if (xOneShotTimer != NULL)
    {
        if (xTimerReset(xOneShotTimer, 0) == pdPASS)
        {
            vPrintString("One-shot timer fue reseteado desde el auto-reload callback\n");
        }
    }

}

/* Callback del timer one-shot */
static void prvOneShotTimerCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber("One-shot timer callback ejecutado en tick\n", xTimeNow);
}