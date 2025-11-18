/************************************************************************************
 *  RTOS 
 *  Valentino Parma
 *  2025
 *  IFTS N°14
 *  Práctica 2 - Ejercicio 6
 *  Plantilla
 ************************************************************************************/


#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "supporting_functions.h"

 /* Periodos */
#define HEARTBEAT_PERIOD    ( pdMS_TO_TICKS( 1000UL ) )   // 1 segundo
#define WATCHDOG_PERIOD     ( pdMS_TO_TICKS( 4000UL ) )   // 4 segundos

/* Prototipos */
static void prvHeartbeatCallback(TimerHandle_t xTimer);
static void prvWatchdogCallback(TimerHandle_t xTimer);

/* Timers globales */
static TimerHandle_t xHeartbeatTimer = NULL;
static TimerHandle_t xWatchdogTimer = NULL;

/* Contador de heartbeats */
static int heartbeatCount = 0;

int main(void)
{
    BaseType_t xStarted1, xStarted2;

    /* Crear heartbeat timer (auto-reload) */
    xHeartbeatTimer = xTimerCreate("Heartbeat",
        HEARTBEAT_PERIOD,
        pdTRUE,     /* auto-reload */
        0,
        prvHeartbeatCallback);

    /* Crear watchdog timer (one-shot) */
    xWatchdogTimer = xTimerCreate("Watchdog",
        WATCHDOG_PERIOD,
        pdFALSE,    /* one-shot */
        0,
        prvWatchdogCallback);

    if ((xHeartbeatTimer != NULL) && (xWatchdogTimer != NULL))
    {
        /* Iniciar timers */
        xStarted1 = xTimerStart(xHeartbeatTimer, 0);
        xStarted2 = xTimerStart(xWatchdogTimer, 0);

        if ((xStarted1 == pdPASS) && (xStarted2 == pdPASS))
        {
            vTaskStartScheduler();
        }
    }

    for (;; );
    return 0;
}

/* Callback del heartbeat */
static void prvHeartbeatCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow = xTaskGetTickCount();
    heartbeatCount++;

    vPrintStringAndNumber("Heartbeat enviado en tick\n", xTimeNow);

    /* Resetear watchdog */
    if (    heartbeatCount <= 10    )
    {
        if (xTimerReset(xWatchdogTimer, 0) == pdPASS)
        {
            vPrintString("Watchdog reseteado por heartbeat\n");
        }
    }
    else
    {
        vPrintString("FALLA simulada: no se envia senial de vida");
    }
}

/* Callback del watchdog */
static void prvWatchdogCallback(TimerHandle_t xTimer)
{
    TickType_t xTimeNow = xTaskGetTickCount();
    vPrintStringAndNumber("WATCHDOG ACTIVADO en tick\n", xTimeNow);

    
}

